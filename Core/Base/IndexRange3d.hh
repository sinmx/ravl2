// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLINDEXRANGE3D_HH
#define RAVLINDEXRANGE3D_HH
///////////////////////////////////////////////////////////
//! file="Ravl/Core/Base/IndexRange3d.hh"
//! lib=RavlCore
//! author="Radek Marik"
//! docentry="Ravl.Core.Indexing"
//! rcsid="$Id$"
//! date="06/08/95"
//! userlevel=Default

#include "Ravl/Index.hh"
#include "Ravl/IndexRange1d.hh"
#include "Ravl/Index3d.hh"

namespace RavlN {

  class BinIStreamC;
  class BinOStreamC;
  
  //! userlevel=Normal
  //: An index range of a 3D array
  
  class IndexRange3dC {
  public:
    IndexRange3dC()
    {}
    //: Default constructor.
    
    IndexRange3dC(IndexC iNumber, IndexC jNumber, IndexC kNumber)
      : is(0, iNumber-1), 
	js(0, jNumber-1),
	ks(0, kNumber-1)
    {}
    //: Constructor.
    
    IndexRange3dC(const IndexRangeC & iRange,
		  const IndexRangeC & jRange,
		  const IndexRangeC & kRange);
    //: Constructor.
    
    IndexRange3dC(const Index3dC &org,const Index3dC &end)
      : is(org.I(), end.I()), 
	js(org.J(), end.J()), 
	ks(org.K(), end.K())
    {}
    //: Create an 3d range from corner points.
    
    IndexRange3dC(IndexC minI, IndexC maxI,
		  IndexC minJ, IndexC maxJ,
		  IndexC minK, IndexC maxK)
      : is(minI, maxI), 
	js(minJ,maxJ),
	ks(minK,maxK)
    {}
    //: Create rectangle from individual values.
    
    inline Index3dC Origin() const
    { return Index3dC(is.Min(),js.Min()); }
    //: Returns the origin index of the rectangle.
    
    inline Index3dC  End() const
    { return Index3dC(is.Max(),js.Max()); }
    //: Returns the end index of the rectangle.
    
    inline Index3dC Center() const
    { return Index3dC(is.Center(),js.Center(),ks.Center()); }
    //: Returns the index which is in the middle of the rectangle
    
    inline IndexC MinI() const
    { return is.Min(); }
    //: Returns the min value of I.
    
    inline IndexC MinJ() const
    { return js.Min(); }
    //: Returns the min value of J.

    inline IndexC MinK() const
    { return ks.Min(); }
    //: Returns the min value of K.
    
    inline IndexC MaxI() const
    { return is.Max(); }
    //: Returns the max value of I.
    
    inline IndexC MaxJ() const
    { return js.Max(); }
    //: Returns the max value of J.

    inline IndexC MaxK() const
    { return ks.Max(); }
    //: Returns the max value of K.
    
    inline IndexC &MinI()
    { return is.Min(); }
    //: Returns the min value of I.
    
    inline IndexC &MinJ()
    { return js.Min(); }
    //: Returns the min value of J.
    
    inline IndexC &MinK()
    { return ks.Min(); }
    //: Returns the min value of K.
    
    inline IndexC &MaxI()
    { return is.Max(); }
    //: Returns the max value of I.
    
    inline IndexC &MaxJ()
    { return js.Max(); }
    //: Returns the max value of J.

    inline IndexC &MaxK()
    { return ks.Max(); }
    //: Returns the max value of K.
    
    inline SizeT Is() const
    { return is.Size(); }
    //: The number of i's in the rectangle.

    inline SizeT Js() const
    { return js.Size(); }
    //: The number of j's in the rectangle.

    inline SizeT Ks() const
    { return ks.Size(); }
    //: The number of k's in the rectangle.
    
    inline SizeT Volume() const
    { return (SizeT) Is() * Js() * Ks(); }
    //: Returns the volume of the prism expressed in number of indexs.
    
    inline IndexRange3dC Dilate() const 
    { return IndexRange3dC(is.Expand(1),js.Expand(1),ks.Expand(1)); }
    //: Returns a new rectangle one index larger on each side.
    
    inline IndexRange3dC Erode() const
    { return IndexRange3dC(is.Shrink(1),js.Shrink(1),ks.Shrink(1)); }
    //: Removes one index layer on each side.
    
    inline IndexRange3dC Expand(IndexC n) const
    { return IndexRange3dC(is.Expand(n),js.Expand(n),ks.Expand(n)); }
    // Expands the rectangle by adding 'n' indexs on each side.
    
    inline IndexRange3dC Shrink(IndexC n) const
    { return IndexRange3dC(is.Shrink(n),js.Shrink(n),ks.Shrink(n)); }
    // Returns a new rectangle which has layer of the width of 'n' indexs
    // removed.
    
    inline IndexRange3dC & ClipBy(const IndexRange3dC & r) {
      Range1().ClipBy(r.Range1());
      Range2().ClipBy(r.Range2());
      Range3().ClipBy(r.Range3());
      return *this;
    }
    //: This index range is clipped to contain at most the index range 'r'.

    inline bool Contains(const Index3dC & oth) const
    { return Range1().Contains(oth[0]) && Range2().Contains(oth[1]) && Range3().Contains(oth[2]); }
    //: Returns true if this range contains the subrange 'oth'.
    
    inline bool Contains(const IndexRange3dC & oth) const
    { return Range1().Contains(oth.Range1()) && Range2().Contains(oth.Range2()) && Range3().Contains(oth.Range3()); }
    //: Returns true if this range contains the subrange 'oth'.
    
    inline const IndexRange3dC & operator+=(const Index3dC & offset);
    //: Shifts the rectangle to the new position.
    
    inline const IndexRange3dC & operator-=(const Index3dC & offset);
    //: Shifts the rectangle to the new position.

    inline IndexRange3dC operator+(const Index3dC & offset) const
    { return IndexRange3dC(is + offset[0],js + offset[1],ks + offset[2]); }
    //: Shifts the rectangle to the new position.
    
    inline IndexRange3dC operator-(const Index3dC & offset) const
    { return IndexRange3dC(is - offset[0],js - offset[1],ks - offset[2]); }
    //: Shifts the rectangle to the new position.
    
    inline const IndexRangeC & IRange() const
    { return is; }
    //: Access i range.
    
    inline const IndexRangeC & JRange() const
    { return js; }
    //: Access j range.

    inline const IndexRangeC & KRange() const
    { return ks; }
    //: Access k range.
    
    inline IndexRangeC & IRange()
    { return is; }
    //: Access i range.
    
    inline IndexRangeC & JRange()
    { return js; }
    //: Access j range.
    
    inline IndexRangeC & KRange()
    { return ks; }
    //: Access k range.
    
    inline const IndexRangeC & Range1() const
    { return is; }
    //: Access i range.
    
    inline const IndexRangeC & Range2() const
    { return js; }
    //: Access j range.

    inline const IndexRangeC & Range3() const
    { return ks; }
    //: Access k range.
    
    inline IndexRangeC & Range1()
    { return is; }
    //: Access i range.
    
    inline IndexRangeC & Range2()
    { return js; }
    //: Access j range.
    
    inline IndexRangeC & Range3()
    { return ks; }
    //: Access k range.
    
    inline const IndexRange3dC &Involve(const Index3dC & index);
    //: Checks and changes, if necessary, the 2 dimensional range
    //: to contain the 'index'.
    
    inline const IndexRange3dC &Involve(const IndexRange3dC & subRange);
    //: Checks and changes, if necessary, the 2 dimensional range
    //: to contain the 'subRange'.
    
    inline 
    bool IsValid() const 
    { return is.IsValid() && js.IsValid() && ks.IsValid(); }
    // Returns TRUE if this rectangle contains at least one index.

    bool operator==(const IndexRange3dC &oth) const
    { return oth.Range1() == Range1() && oth.Range2() == Range2() && oth.Range3() == Range3(); }
    //: Are two ranges equal ?

    bool operator!=(const IndexRange3dC &oth) const
    { return oth.Range1() != Range1() || oth.Range2() != Range2() || oth.Range3() != Range3(); }
    //: Are two ranges unequal ?
    
  protected:
    inline const IndexRange3dC & Range() const
    { return(*this); }
    
  private:
    IndexRangeC is;
    IndexRangeC js;
    IndexRangeC ks;
  };

  inline
  ostream &operator<<(ostream &s,const IndexRange3dC &ir) {
    s << ir.Range1() << ' ' << ir.Range2() << ' ' << ir.Range3();
    return s;
  }
  
  inline
  istream &operator>>(istream &s,IndexRange3dC &ir) {
    s >> ir.Range1() >> ir.Range2() >> ir.Range3();
    return s;
  }

  BinOStreamC &operator<<(BinOStreamC &s,const IndexRange3dC &ir);  
  BinIStreamC &operator>>(BinIStreamC &s,IndexRange3dC &ir);
  
  ///////////////////////////////////////////////////////
  
  inline const IndexRange3dC &IndexRange3dC::operator+=(const Index3dC & offset) {
    is += offset.I();
    js += offset.J();
    ks += offset.K();
    return *this;
  }
  
  inline const IndexRange3dC & IndexRange3dC::operator-=(const Index3dC & offset) {
    is -= offset.I();
    js -= offset.J();
    ks -= offset.K();
    return *this;
  }
  
  inline const IndexRange3dC &IndexRange3dC::Involve(const Index3dC & index) {
    Range1().Involve(index[0]);
    Range2().Involve(index[1]);
    Range3().Involve(index[2]);
    return *this;
  }

  
  inline const IndexRange3dC &IndexRange3dC::Involve(const IndexRange3dC & subRange) {
    Range1().Involve(subRange.Range1());
    Range2().Involve(subRange.Range2());
    Range3().Involve(subRange.Range3());
    return *this;
  }
  
}
#endif
