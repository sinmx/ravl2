// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ARRAY3DITER_HEADER
#define RAVL_ARRAY3DITER_HEADER 1
///////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Array/Array3dIter.hh"
//! lib=RavlCore
//! userlevel=Basic
//! author="Charles Galambos"
//! docentry="Ravl.API.Core.Arrays.3D"
//! rcsid="$Id$"
//! example=exArray2.cc
//! date="24/08/1999"

#include "Ravl/BufferAccess3dIter.hh"
#include "Ravl/Array3d.hh"

namespace RavlN {
  
  template <class DataC> class Array3dC;
  
  //! userlevel=Normal
  //: Array1dC iterator.
  
  template<class DataT>
  class Array3dIterC  
    : public BufferAccess3dIterC<DataT>
  {
  public:
    Array3dIterC()
    {}
    //: Default constructor.
    
    Array3dIterC(const Array3dC<DataT> &arr,const IndexRange3dC &rng)
      : dat(arr,rng)
    { First(); }
    //: Constructor.
    
    Array3dIterC(const Array3dC<DataT> &arr)
      : BufferAccess3dIterC<DataT>(arr),
        dat(arr)
    {}
    //: Constructor.
    
    inline bool First() 
    { return BufferAccess3dIterC<DataT>::First(dat.BufferAccess(),dat.ByteStride1(),dat.ByteStride2(),
                                               dat.Range1(),dat.Range2(),dat.Range3()); }
    //: Goto first element in the array.
    // Return TRUE if there actually is one.
    
    const Array3dIterC<DataT> &operator=(const Array3dC<DataT> &arr) {
      dat = arr;
      First();
      return *this;
    }
    //: Assign to another array.
    
    Index3dC Index() const 
    { return dat.IndexOf(this->Data()); }
    //: Get index of current location in array.
    // Has to be calculate, and so is slightly slow.
  protected:
    Array3dC<DataT> dat;
  };
  
}

#endif

