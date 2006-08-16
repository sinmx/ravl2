// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include "Ravl/GUI/MarkupPolygon2d.hh"
#include "Ravl/GUI/GUIMarkupCanvas.hh"
#include "Ravl/Projection2d.hh"
#include "Ravl/OS/SysLog.hh"
#include "Ravl/RCWrap.hh"
#include "Ravl/GUI/MarkupLayerInfo.hh"
//! rcsid="$Id: fixSource.cfg 5642 2006-06-23 10:51:11Z craftit $"
//! lib=RavlGUI2D

#include <gdk/gdk.h>

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
  //: Constructor.
  
  MarkupPolygon2dBodyC::MarkupPolygon2dBodyC(Int64T id,IntT zOrder,const Polygon2dC &_poly)
    : MarkupInfoBodyC(id,zOrder),
      poly(_poly),
      orgPoly(_poly.Copy()),
      useCustomColour(false),
      colour(255,255,0) 
  {}

  //: Constructor.
  
  MarkupPolygon2dBodyC::MarkupPolygon2dBodyC(Int64T id,IntT zOrder,const Polygon2dC &_poly,const ByteRGBValueC &_colour)
    : MarkupInfoBodyC(id,zOrder),
      poly(_poly),
      orgPoly(_poly.Copy()),
      useCustomColour(true),
      colour(_colour) 
  {}
  
  //: Extent of object.
  
  RealRange2dC MarkupPolygon2dBodyC::Extent(GUIMarkupCanvasBodyC &mv) const {
    RealRange2dC rextent;
    bool polyOk = true;
    bool isFirst = true;
    
    // Work out extent of this polygon allowing for dodgy points.
    
    for(DLIterC<Point2dC> it(poly);it;it++) {
      Point2dC &dir = *it;
      if(IsNan(dir[0]) || IsNan(dir[1]) || IsInf(dir[0]) || IsInf(dir[1])) {
        //SysLog(SYSLOG_ERR) << "MarkupPolygon2dBodyC::Extent, Illegal polygon : " << poly;
        polyOk = false;
        continue;
      }
      if(isFirst) {
        rextent = RealRange2dC(*it,0.0);
        isFirst = false;
        continue;
      } 
      rextent.Involve(dir);
    }
    if(!isFirst)
      rextent = rextent.Expand(2);
    
    // Involve extent of children
    for(DLIterC<MarkupPolygon2dC> it(children);it;it++) {
      if(isFirst) {
        rextent = it->Extent(mv);
        isFirst = false;
      } else
        rextent.Involve(it->Extent(mv));
    }
    
    // If 'isFirst' is true then we haven't found a single usefull point.
    
    if((rextent.Range1().Min() > rextent.Range1().Max()) || (rextent.Range2().Min() > rextent.Range2().Max()) || isFirst) {
      SysLog(SYSLOG_WARNING) << "MarkupPolygon2dBodyC::Extent, Negative or invalid extent=" << rextent << " ";
      return RealRange2dC(0,0);
    }
    return rextent;
  }

  //: Set colour for polygon.
  
  void MarkupPolygon2dBodyC::SetColour(const ByteRGBValueC &_colour) {
    colour = _colour;
    useCustomColour = true;
  }



  void MarkupPolygon2dBodyC::UnsetColour()
  {
    useCustomColour = false;
  }
  
  //: Add child markup.
  
  bool MarkupPolygon2dBodyC::Insert(const MarkupPolygon2dC &markupPoly) {
    children.InsLast(markupPoly);
    return true;
  }

  //: Call when some part of the polygon has been updated.
  // This will update the position of any child polygons appropriatly.
  
  bool MarkupPolygon2dBodyC::MovePoly() {
    Projection2dC proj;
    try {
      proj = FitProjection(orgPoly,poly);
    } catch(ExceptionC &) { // Catch numerical problems.
      return false; // Couldn't fit projection so ignore.
    }
    for(DLIterC<MarkupPolygon2dC> it(children);it;it++)
      it->ApplyTransform(proj);
    return true;
  }
  
  //: Apply transform to this polygon
  // This replaces poly with orgPoly transformed by the given projection.
  
  bool MarkupPolygon2dBodyC::ApplyTransform(const Projection2dC &proj) {
    poly = proj * orgPoly;
    for(DLIterC<MarkupPolygon2dC> it(children);it;it++)
      it->ApplyTransform(proj);
    return true;
  }
  
  //: Update database with changes to this polygon
  
  bool MarkupPolygon2dBodyC::UpdateDb() {
    orgPoly = poly.Copy();
    if(trigUpdate.IsValid()) {
      if(!trigUpdate.Call(poly,id))
        SysLog(SYSLOG_WARNING) << "MarkupPolygon2dBodyC::UpdateDb, Update failed.... ";
    }
    for(DLIterC<MarkupPolygon2dC> it(children);it;it++)
      it->UpdateDb();
    return true;
  }
  
  //: Method for rendering frame.
  
  bool MarkupPolygon2dBodyC::Render(GUIMarkupCanvasBodyC &mv,const RealRange2dC &area,bool selected) { 
    if(poly.IsEmpty())
      return true;
    
    // Set up the gc
    if (!SetDrawStyle(mv))
      return true;
    GdkGC *dc = mv.GcDrawContext();

    // Use an overrding colour
    if (useCustomColour)
    {
      GdkColor gcolour;
      gcolour.red = (IntT) colour.Red() * 256;
      gcolour.green = (IntT) colour.Green() * 256;
      gcolour.blue = (IntT) colour.Blue() * 256;
      gdk_gc_set_rgb_fg_color(dc, &gcolour);
    }
    
    // Draw the polygon
    int n = 0;
    Point2dC last = poly.Last();
    for(DLIterC<Point2dC> it(poly);it;it++,n++) {
      if(n == 1) {
        Vector2dC dir = (*it) - last;
        if(IsNan(dir[0]) || IsNan(dir[1]) || IsInf(dir[0]) || IsInf(dir[1])) {
          SysLog(SYSLOG_ERR) << "MarkupPolygon2dBodyC::Render, Illegal polygon : " << poly;
          break;
        }
        
        // Draw the arrow
        RealT len = dir.Magnitude();
        if(len == 0) len = 1; // Look out for zero's
        dir *= 3/len;
        Vector2dC perp = dir.Perpendicular()/2;
        Point2dC p1 = last + dir;
        Point2dC p2 = last + perp + (dir/3);
        Point2dC p3 = last - perp + (dir/3);
        mv.GUIDrawLine(dc,p2,p1);
        mv.GUIDrawLine(dc,p3,p1);
        mv.GUIDrawLine(dc,last,p2);
        mv.GUIDrawLine(dc,last,p3);
        
        // Draw the line
        mv.GUIDrawLine(dc,p1,*it);
      } else
        // Draw the line
        mv.GUIDrawLine(dc,last,*it);
        
      if (selected)
      {
        const IntT boxSize = 2;
        mv.GUIDrawLine(dc, Point2dC(*it - Point2dC(-boxSize, -boxSize)), Point2dC(*it - Point2dC(-boxSize,  boxSize)));
        mv.GUIDrawLine(dc, Point2dC(*it - Point2dC( boxSize, -boxSize)), Point2dC(*it - Point2dC( boxSize,  boxSize)));
        mv.GUIDrawLine(dc, Point2dC(*it - Point2dC( boxSize, -boxSize)), Point2dC(*it - Point2dC(-boxSize, -boxSize)));
        mv.GUIDrawLine(dc, Point2dC(*it - Point2dC( boxSize,  boxSize)), Point2dC(*it - Point2dC(-boxSize,  boxSize)));
      }
      
      last = *it;
    }
    return true;
  }
  
  //: Find a point on the polygon
  // Returns the number of the point.
  
  bool MarkupPolygon2dBodyC::FindClosestPoint(const Point2dC &pnt,RealT &score,IntT &pntNo) {
    IntT c = 0;
    IntT best = -1;
    RealT bestDist = Sqr(6);
    for(DLIterC<Point2dC> it(poly);it;it++,c++) {
      RealT dist = pnt.SqrEuclidDistance(*it);
      if(IsNan(dist) || IsInf(dist) || dist >= bestDist)  // Be paranoid about corrupted data.
	continue;
      bestDist = dist;
      best = c;
    }
    if(best < 0)
      return false;
    score = Sqrt(bestDist);
    pntNo = best;
    return true;
  }
  
  //: Check if we've selected something in this object.
  
  RealT MarkupPolygon2dBodyC::SelectTest(GUIMarkupCanvasBodyC &mv,const Point2dC &at,const MouseEventC &me) {
    RealT score = -1;
    IntT pn;
    if(FindClosestPoint(at,score,pn)) {
      if(mv.GUIIsSelected(Id()) && score < 6) // Only show bias within a circle.
        score /= 20; // Give it a strong bias towards selected polygons
      return score;
    }
    //SysLog(SYSLOG_DEBUG) << "MarkupPolygon2dBodyC::SelectTest, Contains=" << poly.Contains(at) << " Area=" << poly.Area() << "\n";
    if(poly.Contains(at)) {
      score = Abs(poly.Area());
      return score;
    }
    return -1;
  }
 
  //: Handle mouse event.
  // Returns true if even has been handled.
  // States:
  // -2 = Select event, no op.
  // -1 = Whole rectangle drag.
  //  0   n = Drag single corner
  //  100 n+100 = Mark each corner.
  
  bool MarkupPolygon2dBodyC::MouseEventPress(GUIMarkupCanvasBodyC &mv,const Point2dC &at,const MouseEventC &me,IntT &state,bool &refresh) {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "MarkupPolygon2dBodyC::MouseEventPress() At=" << at << " State=" << state << " " << " ");
    ONDEBUG(SysLog(SYSLOG_DEBUG) << " Press " << me.HasChanged(0) << " " << me.HasChanged(1) << " " << me.HasChanged(2) << " " << me.HasChanged(3) << " " << " " << me.HasChanged(4) << " ");
    if(state >= 100) {
      IntT size = (IntT) poly.Size();
      IntT pat = state - 100;
      if(pat >= size) return false;
      poly.Nth(pat) = at;
      MovePoly();
      refresh = true;
      return true;
    }
    if(me.HasChanged(0)) { // Button 0 press ?
      IntT newState = -1;
      RealT score = -1;
      if(FindClosestPoint(at,score,newState)) {
        state = newState;
        if(newState == 0 && me.HasChanged(1))
          state = 100; // Put it into markup mode.
        return true;
      }
    }
    //SysLog(SYSLOG_DEBUG) << "MarkupPolygon2dBodyC::MouseEventPress, Contains=" << poly.Contains(at) << " Area=" << poly.Area() << "\n";
    if(poly.Contains(at)) { // Click inside the rect ? 
      if(me.HasChanged(1) && (me.IsShift() || me.IsCntrl())) { // Is it inside the polygon ?
        mv.SetMouseInfo(RCWrapC<Polygon2dC>(poly.Copy()).Abstract());
        state = -1;
        return true;
      }
      if(me.HasChanged(0)) { // Attempting a select operation ?
        ONDEBUG(SysLog(SYSLOG_DEBUG) << " Select... Id=" << Id() );
        if(Id() >= 0) {
          state = -2;
          if(me.IsCntrl()) { //        *** Cntrl select. ***
            if(!mv.GUIIsSelected(Id()))
              mv.GUIAddSelect(Id());
            else
              mv.GUIDelSelect(Id());
            refresh = true;
	      return true;
          } else if(me.IsShift()) {//  *** Shift select ***
            if(!mv.GUIIsSelected(Id())) {
              mv.GUIAddSelect(Id());
              refresh = true;
              return true;
            }
            return false;
          } else {  //                 *** Plain ***
            mv.GUIClearSelect(false);
            mv.GUIAddSelect(Id());
            refresh = true;
            return true;
          }
        }
      }
    }
    return false;
  }
  
  //: Handle mouse event.
  // Returns true if even has been handled.
  
  bool MarkupPolygon2dBodyC::MouseEventMove(GUIMarkupCanvasBodyC &mv,const Point2dC &at,const MouseEventC &me,IntT &state,bool &refresh) {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "MarkupPolygon2dBodyC::MouseEventMove() At=" << at << " State=" << state << " " << " ");
    ONDEBUG(SysLog(SYSLOG_DEBUG) << " Press " << me.HasChanged(0) << " " << me.HasChanged(1) << " " << me.HasChanged(2) << " " << me.HasChanged(3) << " " << " " << me.HasChanged(4) << " ");
    if(state == -2)
      return false;
    if(state == -1) { // Move whole polygon ?
      RCWrapC<Polygon2dC> oldPoly(mv.MouseInfo());
      RavlAssert(oldPoly.IsValid());
      poly = oldPoly.Data().Copy();
      Point2dC offset = (at - mv.MousePressAt());
      for(DLIterC<Point2dC> oit(poly);oit;oit++)
        *oit += offset;
      if(!me.IsCntrl())
        MovePoly();
      refresh = true;
      return true;
    }
    // Normal move.
    if(state < 100) {
      if(state < (IntT) poly.Size())
        poly.Nth(state) = at;
      else
        SysLog(SYSLOG_WARNING) << "MarkupPolygon2dBodyC::MouseEvent, Odd state=" << state << " Size=" << poly.Size() << " ";
      if(!me.IsCntrl())
        MovePoly();
      refresh = true;
      return true;
    }
    // Markup mode.
    if(state >= 100) {
      IntT pat = state - 100;
      if(pat >= (IntT) poly.Size())
        return false;
      poly.Nth(pat) = at;
      if(!me.IsCntrl())
        MovePoly();
      refresh = true;	
      return true;
    }
    return false;
  }
  
  //: Handle mouse event.
  // Returns true if even has been handled.
  
  bool MarkupPolygon2dBodyC::MouseEventRelease(GUIMarkupCanvasBodyC &mv,const Point2dC &at,const MouseEventC &me,IntT &state,bool &refresh) {
    ONDEBUG(SysLog(SYSLOG_DEBUG) << "MarkupPolygon2dBodyC::MouseEventRelease() At=" << at << " State=" << state << " " << " ");
    ONDEBUG(SysLog(SYSLOG_DEBUG) << " Press " << me.HasChanged(0) << " " << me.HasChanged(1) << " " << me.HasChanged(2) << " " << me.HasChanged(3) << " " << " " << me.HasChanged(4) << " ");
    if(state == -2)
      return false;
    if(state < 100 && state >= -1) {
      UpdateDb();
    } else { // State >= 0, initial create mode.
      IntT size = poly.Size();
      state++;
      if((state - 100) == size) {
        UpdateDb();
        return false;
      }
      return true;
    }
    return false;
  }

    
  //: Does polygon have child with given id ?
  
  bool MarkupPolygon2dBodyC::HasChild(Int64T anId) const {
    for(DLIterC<MarkupPolygon2dC> it(children);it;it++) {
      if(it->Id() == anId) return true;
      if(it->HasChild(anId)) return true;
    }
    return false;
  }
  
}
