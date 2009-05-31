// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_BUFFERACCESS3ITER2_HEADER
#define RAVL_BUFFERACCESS3ITER2_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/BufferAccess3dIter2.hh"
//! docentry="Ravl.API.Core.Arrays.Buffer"
//! lib=RavlCore
//! userlevel=Advanced
//! author="Charles Galambos"

#include "Ravl/BufferAccessIter2.hh"
#include "Ravl/BufferAccess2dIter2.hh"
#include "Ravl/IndexRange3d.hh"
#include "Ravl/IndexRange1d.hh"

namespace RavlN {
  template <class DataT> class RangeBufferAccess3dC;
  template <class DataT> class SizeBufferAccess3dC;

  //! userlevel=Advanced
  //: 3D buffer iterator.
  
  template <class Data1T,class Data2T>
  class BufferAccess3dIter2C {
  public:
    BufferAccess3dIter2C()
    {}
    //: Default constructor.
    
    BufferAccess3dIter2C(const BufferAccessC<Data1T> &pbufA,IntT byteStride1a,IntT byteStride2a,
                         const BufferAccessC<Data2T> &pbufB,IntT byteStride1b,IntT byteStride2b,
                         SizeT size1,SizeT size2,SizeT size3
                        )
    { First(pbufA,byteStride1a,byteStride2a,
            pbufB,byteStride1b,byteStride2b,
            size1,size2,size3); }
    //: Constructor.

    BufferAccess3dIter2C(const RangeBufferAccess3dC<Data1T> &bufA,
                         const RangeBufferAccess3dC<Data2T> &bufB,
                         const IndexRangeC &range1,const IndexRangeC &range2,const IndexRangeC &range3);
    //: Construct from a 3d buffer.

    BufferAccess3dIter2C(const RangeBufferAccess3dC<Data1T> &bufA,
                         const RangeBufferAccess3dC<Data2T> &bufB,
                         const IndexRange3dC &rng);
    //: Construct from a 3d buffer.

    BufferAccess3dIter2C(const SizeBufferAccess3dC<Data1T> &pbufA,
                         const SizeBufferAccess3dC<Data2T> &pbufB,
                         SizeT size1,SizeT size2,SizeT size3
                        );
    //: Constructor.
    
    BufferAccess3dIter2C(const BufferAccessC<Data1T> &pbufA,IntT byteStride1a,IntT byteStride2a,
                         const BufferAccessC<Data2T> &pbufB,IntT byteStride1b,IntT byteStride2b,
                         const IndexRangeC &range1,const IndexRangeC &range2,const IndexRangeC &range3
                        )
    { First(pbufA,byteStride1a,byteStride2a,
            pbufB,byteStride1b,byteStride2b,
            range1,range2,range3); }
    //: Constructor.

    bool First(const BufferAccessC<Data1T> &pbufA,IntT byteStride1a,IntT byteStride2a,
               const BufferAccessC<Data2T> &pbufB,IntT byteStride1b,IntT byteStride2b,
               const IndexRangeC &range1,const IndexRangeC &range2,const IndexRangeC &range3
               )
    {
      m_slice1 = reinterpret_cast<char *>(pbufA.ReferenceElm() + range3.Min().V()) + range1.Min().V() * byteStride1a + range2.Min().V() * byteStride2a;
      m_slice2 = reinterpret_cast<char *>(pbufB.ReferenceElm() + range3.Min().V()) + range1.Min().V() * byteStride1b + range2.Min().V() * byteStride2b;
      m_sliceEnd = m_slice1 + byteStride1a * range1.Max().V();
      m_size2 = range2.Size();
      if(m_slice1 == m_sliceEnd || m_size2 == 0) {
        m_sit.Invalidate();
        return false;
      }
      m_sit.First(reinterpret_cast<Data1T*>(m_slice1),byteStride2a,
                  reinterpret_cast<Data2T*>(m_slice2),byteStride2b,
                  m_size2,range3.Size());
      m_stride1 = byteStride1a;
      m_stride2 = byteStride1b;
      return true;
    }
    //: Goto first element in the array

    bool First(const BufferAccessC<Data1T> &pbufA,IntT byteStride1a,IntT byteStride2a,
               const BufferAccessC<Data2T> &pbufB,IntT byteStride1b,IntT byteStride2b,
               SizeT size1,SizeT size2,SizeT size3
               )
    {
      m_slice1 = reinterpret_cast<char *>(pbufA.ReferenceElm());
      m_slice2 = reinterpret_cast<char *>(pbufB.ReferenceElm());
      m_sliceEnd = m_slice1 + byteStride1a * size1;
      if(m_slice1 == m_sliceEnd || size2 == 0 || size3 == 0) {
        m_sit.Invalidate();
        return false;
      }
      m_size2 = size2;
      m_sit.First(reinterpret_cast<Data1T*>(m_slice1),byteStride2a,
                  reinterpret_cast<Data2T*>(m_slice2),byteStride2b,
                  size2,size3);
      m_stride1 = byteStride1a;
      m_stride2 = byteStride1b;
      return true;
    }
    //: Goto first element in the array
    
    bool SliceStart()
    { return m_sit.First(reinterpret_cast<Data1T*>(m_slice1),
                         reinterpret_cast<Data2T*>(m_slice2),
                         m_size2
		        );
    }
    //: Go back to the begining of this row.
    
    bool NextSlice() {
      m_slice1 += m_stride1;
      m_slice2 += m_stride2;
      if(m_slice1 == m_sliceEnd) return false;
      SliceStart();
      return true;      
    }
    //: Go to the begining of the next row.
    // returns true if iterator is left at the begining of a valid row or
    // false if the end of the array has been reached.
    
    bool Next() { 
      m_sit++;
      if(!m_sit.IsElm()) {
	NextSlice();
	return false;
      }
      return true;
    }
    //: Goto next element.
    // Goto next element in the array. Returns true if the element
    // is on the same row of the array. It returns false if the element is on
    // the next row or at the end of the array.
    
    bool IsElm() const
    { return m_sit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    operator bool() const
    { return m_sit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    void operator++() {  
      m_sit++;
      if(!m_sit.IsElm())
	NextSlice();
    }
    //: Goto next element.
    
    void operator++(int) {  
      m_sit++;
      if(!m_sit.IsElm())
	NextSlice();
    }
    //: Goto next element.
    
    Data1T &Data() 
    { return m_sit.Data1(); }
    //: Access data of current element

    const Data1T &Data() const
    { return m_sit.Data1(); }
    //: Access data of current element
    
    Data1T &Data1() 
    { return m_sit.Data1(); }
    //: Access data of current element
    
    const Data1T &Data1() const
    { return m_sit.Data1(); }
    //: Access data of current element
    
    Data2T &Data2() 
    { return m_sit.Data2(); }
    //: Access data of current element
    
    const Data2T &Data2() const
    { return m_sit.Data2(); }
    //: Access data of current element
    
  protected:

    const char *m_sliceEnd;
    char *m_slice1;
    char *m_slice2;
    BufferAccess2dIter2C<Data1T,Data2T> m_sit;
    SizeT m_size1;
    SizeT m_size2;
    IntT m_stride1;
    IntT m_stride2;
  };
    
}


#endif
