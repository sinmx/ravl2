// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_RBFACC2ITER6_HEADER
#define RAVL_RBFACC2ITER6_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/BufferAccess2dIter6.hh"
//! lib=RavlCore
//! docentry="Ravl.API.Core.Arrays.Buffer"
//! userlevel=Default
//! author="Charles Galambos"
//! date="7/1/2003"

#include "Ravl/BufferAccessIter6.hh"
#include "Ravl/Index2d.hh"
#include "Ravl/IndexRange2d.hh"


namespace RavlN {
  
  //! userlevel=Advanced
  //: Iterate through a 2d buffer.
  
  template <class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class Data6T>
  class BufferAccess2dIter6C {
  public:
    BufferAccess2dIter6C()
    {}
    //: Default constructor.
    
    BufferAccess2dIter6C(const BufferAccessC<Data1T> &pbuf1,IntT stride1,
			 const BufferAccessC<Data2T> &pbuf2,IntT stride2,
			 const BufferAccessC<Data3T> &pbuf3,IntT stride3,
			 const BufferAccessC<Data4T> &pbuf4,IntT stride4,
			 const BufferAccessC<Data5T> &pbuf5,IntT stride5,
			 const BufferAccessC<Data6T> &pbuf6,IntT stride6,
                         IntT size1,IntT size2)
    { First(pbuf1,stride1,
            pbuf2,stride2,
            pbuf3,stride3,
            pbuf4,stride4,
            pbuf5,stride5,
            pbuf6,stride6,
            size1,size2);
    }
    //: Constructor.

    BufferAccess2dIter6C(const BufferAccessC<Data1T> &pbuf1,IntT byteStride1,
                         const BufferAccessC<Data2T> &pbuf2,IntT byteStride2,
                         const BufferAccessC<Data3T> &pbuf3,IntT byteStride3,
                         const BufferAccessC<Data4T> &pbuf4,IntT byteStride4,
                         const BufferAccessC<Data5T> &pbuf5,IntT byteStride5,
                         const BufferAccessC<Data6T> &pbuf6,IntT byteStride6,
                         SizeT size1,SizeT size2) {
      First(pbuf1,byteStride1,
            pbuf2,byteStride2,
            pbuf3,byteStride3,
            pbuf4,byteStride4,
            pbuf5,byteStride5,
            pbuf6,byteStride6,
            size1,size2);
    }
    //: Constructor

    BufferAccess2dIter6C(const BufferAccessC<Data1T> &pbuf1,IntT byteStride1,const IndexRange2dC &range1,
			 const BufferAccessC<Data2T> &pbuf2,IntT byteStride2,const IndexRange2dC &range2,
                         const BufferAccessC<Data3T> &pbuf3,IntT byteStride3,const IndexRange2dC &range3,
                         const BufferAccessC<Data4T> &pbuf4,IntT byteStride4,const IndexRange2dC &range4,
                         const BufferAccessC<Data5T> &pbuf5,IntT byteStride5,const IndexRange2dC &range5,
                         const BufferAccessC<Data6T> &pbuf6,IntT byteStride6,const IndexRange2dC &range6
                         )
    { First(pbuf1,byteStride1,range1.Range1(),range1.Range2(),
            pbuf2,byteStride2,range2.Range1(),range2.Range2(),
            pbuf3,byteStride3,range3.Range1(),range3.Range2(),
            pbuf4,byteStride4,range4.Range1(),range4.Range2(),
            pbuf5,byteStride5,range5.Range1(),range5.Range2(),
            pbuf6,byteStride6,range6.Range1(),range6.Range2()
           );
    }
    //: Constructor.

    BufferAccess2dIter6C(const BufferAccessC<Data1T> &pbufA,IntT byteStrideA,const IndexRangeC &nrng1a,const IndexRangeC &nrng2a,
			 const BufferAccessC<Data2T> &pbufB,IntT byteStrideB,const IndexRangeC &nrng1b,const IndexRangeC &nrng2b,
                         const BufferAccessC<Data3T> &pbufC,IntT byteStrideC,const IndexRangeC &nrng1c,const IndexRangeC &nrng2c,
                         const BufferAccessC<Data4T> &pbufD,IntT byteStrideD,const IndexRangeC &nrng1d,const IndexRangeC &nrng2d,
                         const BufferAccessC<Data5T> &pbufE,IntT byteStrideE,const IndexRangeC &nrng1e,const IndexRangeC &nrng2e,
                         const BufferAccessC<Data6T> &pbufF,IntT byteStrideF,const IndexRangeC &nrng1f,const IndexRangeC &nrng2f
                        )
    { First(pbufA,byteStrideA,nrng1a,nrng2a,
	    pbufB,byteStrideB,nrng1b,nrng2b,
            pbufC,byteStrideC,nrng1c,nrng2c,
            pbufD,byteStrideD,nrng1d,nrng2d,
            pbufE,byteStrideE,nrng1e,nrng2e,
            pbufF,byteStrideF,nrng1f,nrng2f
           );
    }
    //: Constructor.

    bool RowStart() {
      return m_cit.First(reinterpret_cast<Data1T*>(m_rit1),
                         reinterpret_cast<Data2T*>(m_rit2),
                         reinterpret_cast<Data3T*>(m_rit3),
                         reinterpret_cast<Data4T*>(m_rit4),
                         reinterpret_cast<Data5T*>(m_rit5),
                         reinterpret_cast<Data6T*>(m_rit6),
                         m_size2);
    }
    //: Goto start of current row.

  protected:
    bool CNextRow();
    //: Non inlined version of NextRow() to help compiler get inlining right

  public:
    bool First(const BufferAccessC<Data1T> &pbuf1,IntT byteStride1,
               const BufferAccessC<Data2T> &pbuf2,IntT byteStride2,
               const BufferAccessC<Data3T> &pbuf3,IntT byteStride3,
               const BufferAccessC<Data4T> &pbuf4,IntT byteStride4,
               const BufferAccessC<Data5T> &pbuf5,IntT byteStride5,
               const BufferAccessC<Data6T> &pbuf6,IntT byteStride6,
               SizeT size1,SizeT size2) {
      if(size1 == 0 || size2 == 0) {
        m_cit.Invalidate();
        return false;
      }
      RavlAssert(byteStride1 != 0);
      m_size2 = size2;
      m_stride1 = byteStride1;
      m_stride2 = byteStride2;
      m_stride3 = byteStride3;
      m_stride4 = byteStride4;
      m_stride5 = byteStride5;
      m_stride6 = byteStride6;
      m_rit1 = reinterpret_cast<char *>(pbuf1.ReferenceElm());
      m_rit2 = reinterpret_cast<char *>(pbuf2.ReferenceElm());
      m_rit3 = reinterpret_cast<char *>(pbuf3.ReferenceElm());
      m_rit4 = reinterpret_cast<char *>(pbuf4.ReferenceElm());
      m_rit5 = reinterpret_cast<char *>(pbuf5.ReferenceElm());
      m_rit6 = reinterpret_cast<char *>(pbuf6.ReferenceElm());
      m_endRow = m_rit1+m_stride1 * size1;
      RowStart();
      return true;
    }
    //: Goto first element.
    // returns true if there is one.

    bool First(const Data1T *pbuf1,
               const Data2T *pbuf2,
               const Data3T *pbuf3,
               const Data4T *pbuf4,
               const Data5T *pbuf5,
               const Data6T *pbuf6,
               SizeT size1) {
      RavlAssert(m_stride1 != 0 && m_stride2 != 0);
      m_rit1   = reinterpret_cast<char *>(const_cast<Data1T*>(pbuf1));
      m_rit2   = reinterpret_cast<char *>(const_cast<Data2T*>(pbuf2));
      m_rit3   = reinterpret_cast<char *>(const_cast<Data3T*>(pbuf3));
      m_rit4   = reinterpret_cast<char *>(const_cast<Data4T*>(pbuf4));
      m_rit5   = reinterpret_cast<char *>(const_cast<Data5T*>(pbuf5));
      m_rit6   = reinterpret_cast<char *>(const_cast<Data6T*>(pbuf6));
      m_endRow = m_rit1 + m_stride1 * (IntT) size1;
      RowStart();
      return true;
    }
    //: Goto first assuming stride and m_size2 are already setup correctly and size1 is not zero.

    bool First(const BufferAccessC<Data1T> &pbuf1,IntT byteStride1,
               const BufferAccessC<Data2T> &pbuf2,IntT byteStride2,
               const BufferAccessC<Data3T> &pbuf3,IntT byteStride3,
               const BufferAccessC<Data4T> &pbuf4,IntT byteStride4,
               const BufferAccessC<Data5T> &pbuf5,IntT byteStride5,
               const BufferAccessC<Data6T> &pbuf6,IntT byteStride6,
               const IndexRangeC &range1,const IndexRangeC &range2) {
      m_size2 = range2.Size();
      if(range1.IsEmpty() || m_size2 == 0) {
        m_cit.Invalidate();
        return false;
      }
      m_stride1 = byteStride1;
      m_stride2 = byteStride2;
      m_stride3 = byteStride3;
      m_stride4 = byteStride4;
      m_stride5 = byteStride5;
      m_stride6 = byteStride6;
      m_rit1 = reinterpret_cast<char *>(pbuf1.ReferenceElm() + range2.Min().V()) + byteStride1 * range1.Min().V();
      m_rit2 = reinterpret_cast<char *>(pbuf2.ReferenceElm() + range2.Min().V()) + byteStride2 * range1.Min().V();
      m_rit3 = reinterpret_cast<char *>(pbuf3.ReferenceElm() + range2.Min().V()) + byteStride3 * range1.Min().V();
      m_rit4 = reinterpret_cast<char *>(pbuf4.ReferenceElm() + range2.Min().V()) + byteStride4 * range1.Min().V();
      m_rit5 = reinterpret_cast<char *>(pbuf5.ReferenceElm() + range2.Min().V()) + byteStride5 * range1.Min().V();
      m_rit6 = reinterpret_cast<char *>(pbuf6.ReferenceElm() + range2.Min().V()) + byteStride6 * range1.Min().V();
      m_endRow = m_rit1 + byteStride1 * range1.Size();
      RowStart();
      return true;
    }
    //: Goto first element in the array

    bool First(const BufferAccessC<Data1T> &pbufa,IntT byteStrideA,const IndexRangeC &range1a,const IndexRangeC &range2a,
	       const BufferAccessC<Data2T> &pbufb,IntT byteStrideB,const IndexRangeC &range1b,const IndexRangeC &range2b,
	       const BufferAccessC<Data3T> &pbufc,IntT byteStrideC,const IndexRangeC &range1c,const IndexRangeC &range2c,
	       const BufferAccessC<Data4T> &pbufd,IntT byteStrideD,const IndexRangeC &range1d,const IndexRangeC &range2d,
 	       const BufferAccessC<Data5T> &pbufe,IntT byteStrideE,const IndexRangeC &range1e,const IndexRangeC &range2e,
 	       const BufferAccessC<Data6T> &pbuff,IntT byteStrideF,const IndexRangeC &range1f,const IndexRangeC &range2f
              ) {
      m_size2 = range2a.Size();
      RavlAssert((IntT) m_size2 <= range2b.Size());
      if(range1a.IsEmpty() || m_size2 == 0) {
        m_cit.Invalidate();
        return false;
      }
      RavlAssert(range1a.Size() >= range1b.Size());
      RavlAssert(range1a.Size() >= range1c.Size());
      RavlAssert(range1a.Size() >= range1d.Size());
      RavlAssert(range1a.Size() >= range1e.Size());
      RavlAssert(range1a.Size() >= range1f.Size());
      m_stride1 = byteStrideA;
      m_stride2 = byteStrideB;
      m_stride3 = byteStrideC;
      m_stride4 = byteStrideD;
      m_stride5 = byteStrideE;
      m_stride6 = byteStrideF;
      m_rit1 = reinterpret_cast<char *>(pbufa.ReferenceElm() + range2a.Min().V()) + byteStrideA * range1a.Min().V();
      m_rit2 = reinterpret_cast<char *>(pbufb.ReferenceElm() + range2b.Min().V()) + byteStrideB * range1b.Min().V();
      m_rit3 = reinterpret_cast<char *>(pbufc.ReferenceElm() + range2c.Min().V()) + byteStrideC * range1c.Min().V();
      m_rit4 = reinterpret_cast<char *>(pbufd.ReferenceElm() + range2d.Min().V()) + byteStrideD * range1d.Min().V();
      m_rit5 = reinterpret_cast<char *>(pbufe.ReferenceElm() + range2e.Min().V()) + byteStrideE * range1e.Min().V();
      m_rit6 = reinterpret_cast<char *>(pbuff.ReferenceElm() + range2f.Min().V()) + byteStrideF * range1f.Min().V();
      m_endRow = m_rit1 + byteStrideA * range1a.Size();
      RowStart();
      return true;
    }
    //: Goto first element.
    // returns true if there is one.

    bool First(const BufferAccessC<Data1T> &pbufa,IntT byteStrideA,const IndexRange2dC &rangea,
	       const BufferAccessC<Data2T> &pbufb,IntT byteStrideB,const IndexRange2dC &rangeb,
	       const BufferAccessC<Data3T> &pbufc,IntT byteStrideC,const IndexRange2dC &rangec,
	       const BufferAccessC<Data4T> &pbufd,IntT byteStrideD,const IndexRange2dC &ranged,
	       const BufferAccessC<Data5T> &pbufe,IntT byteStrideE,const IndexRange2dC &rangee,
	       const BufferAccessC<Data6T> &pbuff,IntT byteStrideF,const IndexRange2dC &rangef
               ) {
      return First(pbufa,byteStrideA,rangea.Range1(),rangea.Range2(),
                   pbufb,byteStrideB,rangeb.Range1(),rangeb.Range2(),
                   pbufc,byteStrideC,rangec.Range1(),rangec.Range2(),
                   pbufd,byteStrideD,ranged.Range1(),ranged.Range2(),
                   pbufe,byteStrideE,rangee.Range1(),rangee.Range2(),
                   pbuff,byteStrideF,rangef.Range1(),rangef.Range2()
                  );
    }
    //: Goto first element.
    // returns true if there is one.


    bool Next() {
      m_cit.Next();
      if(!m_cit.IsElm()) {
	CNextRow();
	return false;
      }
      return true;
    }
    //: Goto next element.
    // returns true if on the same row.

    bool NextRow() {
      return CNextRow();
    }
    //: Go to the begining of the next row.
    // Returns true if the iterator is begining of a valid row, and false
    // if it is at the end of the array.
    
    bool NextRow(IntT offset) {
      if(!CNextRow() || offset >= (IntT) m_size2) return false;
      m_cit.First(reinterpret_cast<Data1T*>(m_rit1) + offset,
                  reinterpret_cast<Data2T*>(m_rit2) + offset,
                  reinterpret_cast<Data3T*>(m_rit3) + offset,
                  reinterpret_cast<Data4T*>(m_rit4) + offset,
                  reinterpret_cast<Data5T*>(m_rit5) + offset,
                  reinterpret_cast<Data6T*>(m_rit6) + offset,
                  m_size2 - offset);
      return true;
    }
    //: Go to the 'offset' from the first element in the next row.
    // Returns true if the iterator is in a valid row, and false
    // if it is at the end of the array.

    bool SkipRow(IntT offset) {
      m_rit1 += m_stride1 * offset;
      m_rit2 += m_stride2 * offset;
      m_rit3 += m_stride3 * offset;
      m_rit4 += m_stride4 * offset;
      m_rit5 += m_stride5 * offset;
      m_rit6 += m_stride6 * offset;
      if(m_stride1 > 0) {
        if(m_rit1 >= m_endRow) return false;
      } else {
        if(m_rit1 <= m_endRow) return false;
      }
      RowStart();
      return true;
    }
    //: Skip 'offset' rows.
    // Leaves the iterator 'offset' rows further down the image, in the first column. <br>
    // Returns true if the iterator is left on a valid element.

    void NextCol(int skip)
    { m_cit.Next(skip); }
    //: Go forward 'skip' columns, without checking for row change.
    // Use with care.

    bool IsElm() const
    { return m_cit.IsElm(); }
    //: At a valid element ?
    
    operator bool() const
    { return m_cit.IsElm(); }
    //: At a valid element ?
    
    void operator++() 
    { Next(); }
    //: Goto next element.

    void operator++(int) 
    { Next(); }
    //: Goto next element.
    
    Data1T &Data1() 
    { return m_cit.Data1(); }
    //: Access data from array 1.

    const Data1T &Data1() const
    { return m_cit.Data1(); }
    //: Access data from array 1.

    Data2T &Data2() 
    { return m_cit.Data2(); }
    //: Access data from array 2.

    const Data2T &Data2() const
    { return m_cit.Data2(); }
    //: Access data from array 2.
    
    Data3T &Data3()
    { return m_cit.Data3(); }
    //: Access data from array 3.

    const Data3T &Data3() const
    { return m_cit.Data3(); }
    //: Access data from array 3.

    Data4T &Data4()
    { return m_cit.Data4(); }
    //: Access data from array 4.

    const Data4T &Data4() const
    { return m_cit.Data4(); }
    //: Access data from array 4.
    
    Data5T &Data5()
    { return m_cit.Data5(); }
    //: Access data from array 5.
    
    const Data5T &Data5() const
    { return m_cit.Data5(); }
    //: Access data from array 5.
    
    Data6T &Data6()
    { return m_cit.Data6(); }
    //: Access data from array 6.
    
    const Data6T &Data6() const
    { return m_cit.Data6(); }
    //: Access data from array 6.
        
  protected:
    BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T> m_cit;
    SizeT m_size2;
    char  *m_rit1; // Start of current row for array 1
    char  *m_rit2;
    char  *m_rit3;
    char  *m_rit4;
    char  *m_rit5;
    char  *m_rit6;
    const char *m_endRow;
    IntT m_stride1;
    IntT m_stride2;
    IntT m_stride3;
    IntT m_stride4;
    IntT m_stride5;
    IntT m_stride6;
  };

  template <class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class Data6T>
  bool BufferAccess2dIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T>::CNextRow() {
    m_rit1 += m_stride1;
    m_rit2 += m_stride2;
    m_rit3 += m_stride3;
    m_rit4 += m_stride4;
    m_rit5 += m_stride5;
    m_rit6 += m_stride6;
    if(m_rit1 == m_endRow)
      return false;
    m_cit.First(reinterpret_cast<Data1T*>(m_rit1),
                reinterpret_cast<Data2T*>(m_rit2),
                reinterpret_cast<Data3T*>(m_rit3),
                reinterpret_cast<Data4T*>(m_rit4),
                reinterpret_cast<Data5T*>(m_rit5),
                reinterpret_cast<Data6T*>(m_rit6),
                m_size2);
    return true;
  }


}

#endif

