// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_DRAWPOLYGON_HEADER
#define RAVLIMAGE_DRAWPOLYGON_HEADER 1
///////////////////////////////////////////////////////////////////
//! rcsid="$Id: DrawPolygon.hh 5240 2005-12-06 17:16:50Z plugger $"
//! author="James Smith"
//! date="27/10/2002"
//! docentry="Ravl.API.Images.Drawing"
//! lib=RavlImage
//! userlevel=Normal
//! file="Ravl/Image/Base/DrawPolygon.hh"
//! example=exDraw.cc

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/DrawLine.hh"
#include "Ravl/DList.hh"
#include "Ravl/DLIter.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array1dIter.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/Polygon2d.hh"
#include "Ravl/Array2dPolygon2dIter.hh"

namespace RavlImageN {
  
  template<class DataT>
  void DrawPolygon(Array2dC<DataT> &dat,const DataT &value,const Polygon2dC &poly, bool fill=false) {
    // Draw one-colour polygon
    if (fill) {
      for (Array2dPolygon2dIterC<DataT> it(dat, poly); it; it++)
        *it = value;
    } else {
      // Draw individual lines
      for (DLIterC<Point2dC> it(poly); it; it++) {
	DrawLine(dat,value,it.Data(),it.NextCrcData());
      }
    }
  }
  //: Draw a single-colour polygon into the image


  template<class DataT>
  void DrawPolyline(Array2dC<DataT> &dat,const DataT &value,const DListC<Point2dC> &poly) {
    // Draw individual lines
    DLIterC<Point2dC> it(poly);
    if(!it) return ; // Nothing to draw!
    Point2dC last = *it;
    for (it++; it; it++) {
      DrawLine(dat,value,last,*it);
      last = *it;
    }
  }
  //: Draw a poly line into the image.
  
  template<class DataT>
  void DrawPolygon(Array2dC<DataT> &dat,const DListC<DataT>& values,const Polygon2dC &poly, bool fill=false) {
    // Draw shaded polygon
    if (fill) {
      for (Array2dPolygon2dIterC<DataT> it(dat, poly); it; it++) {
        Point2dC pnt(it.Index());
        // Calculate barycentric coords
        SArray1dC<RealT> coord = poly.BarycentricCoordinate(pnt);
        // Calculate interpolated value
        DataT value;
        SetZero(value);
        SArray1dIterC<RealT> cit(coord);
        DLIterC<DataT> vit(values);
        while (cit && vit) {
          value += DataT(vit.Data() * cit.Data());
          cit++;
          vit++;
        }
        // Set value
        *it = value;
      }
    }
    // Draw individual lines
    DLIterC<DataT> val(values);
    for (DLIterC<Point2dC> pnt(poly); pnt && val; pnt++, val++) {
      DrawLine(dat,val.Data(),val.NextCrcData(),pnt.Data(),pnt.NextCrcData());
    }
  }
  //: Draw a shaded polygon into the image
  // This function requires that DataT has a working operator*(double) function
  
}

#endif
