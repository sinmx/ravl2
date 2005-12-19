// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SBFACCITER6_HEADER
#define RAVL_SBFACCITER6_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/BfAccIter6.hh"
//! author="Charles Galambos"
//! lib=RavlCore
//! docentry="Ravl.API.Core.Arrays.Buffer"
//! date="7/1/2003"

#include "Ravl/RBfAcc.hh"
#include "Ravl/SBfAcc.hh"

namespace RavlN {

  //! userlevel=Advanced
  //: Iterator for 3 buffers.
  
  template<class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class Data6T>
  class BufferAccessIter6C {
  public:
    inline BufferAccessIter6C();
    //: Default constructor.
    
    inline BufferAccessIter6C(const BufferAccessC<Data1T> &buff,
			      const BufferAccessC<Data2T> &buff2,
			      const BufferAccessC<Data3T> &buff3,
			      const BufferAccessC<Data4T> &buff4,
			      const BufferAccessC<Data5T> &buff5,
			      const BufferAccessC<Data6T> &buff6,
 			      SizeT size)
    { First(buff,buff2,buff3,buff4,buff5,buff6,size); }
    //: Constructor.

    inline BufferAccessIter6C(const BufferAccessC<Data1T> &buff1,const IndexRangeC &rng1,
			      const BufferAccessC<Data2T> &buff2,const IndexRangeC &rng2,
			      const BufferAccessC<Data3T> &buff3,const IndexRangeC &rng3,
			      const BufferAccessC<Data4T> &buff4,const IndexRangeC &rng4,
			      const BufferAccessC<Data5T> &buff5,const IndexRangeC &rng5,
			      const BufferAccessC<Data6T> &buff6,const IndexRangeC &rng6
			      )
    { First(buff1,rng1,
	    buff2,rng2,
	    buff3,rng3, 
	    buff4,rng4,
	    buff5,rng5,
	    buff6,rng6); 
    }
    //: Constructor.
    
    inline BufferAccessIter6C(const RangeBufferAccessC<Data1T> &buff,
			      const RangeBufferAccessC<Data2T> &buff2,
			      const RangeBufferAccessC<Data3T> &buff3,
			      const RangeBufferAccessC<Data4T> &buff4,
			      const RangeBufferAccessC<Data5T> &buff5,
			      const RangeBufferAccessC<Data6T> &buff6
			      )
    { First(buff,buff2,buff3,buff4,buff5,buff6); }
    //: Constructor.
    
    inline BufferAccessIter6C(const SizeBufferAccessC<Data1T> &buff,
			      const SizeBufferAccessC<Data2T> &buff2,
			      const SizeBufferAccessC<Data3T> &buff3,
			      const SizeBufferAccessC<Data4T> &buff4,
			      const SizeBufferAccessC<Data5T> &buff5,
			      const SizeBufferAccessC<Data6T> &buff6
			      )
    { First(buff,buff2,buff3,buff4,buff5,buff6); }
    //: Constructor.
    
    inline bool First(const BufferAccessC<Data1T> &buff1,const IndexRangeC &rng1,
		      const BufferAccessC<Data2T> &buff2,const IndexRangeC &rng2,
		      const BufferAccessC<Data3T> &buff3,const IndexRangeC &rng3,
		      const BufferAccessC<Data4T> &buff4,const IndexRangeC &rng4,
		      const BufferAccessC<Data5T> &buff5,const IndexRangeC &rng5,
		      const BufferAccessC<Data6T> &buff6,const IndexRangeC &rng6
		      );
    //: Goto first element.
    // returns true if there is a first element.
    
    inline bool First(const BufferAccessC<Data1T> &buff,
		      const BufferAccessC<Data2T> &buff2,
		      const BufferAccessC<Data3T> &buff3,
		      const BufferAccessC<Data4T> &buff4,
		      const BufferAccessC<Data5T> &buff5,
		      const BufferAccessC<Data6T> &buff6,
		      SizeT size);
    //: Goto first element.
    // returns true if there is a first element.
    
    inline bool First(const RangeBufferAccessC<Data1T> &buff,
		      const RangeBufferAccessC<Data2T> &buff2,
		      const RangeBufferAccessC<Data3T> &buff3,
		      const RangeBufferAccessC<Data4T> &buff4,
		      const RangeBufferAccessC<Data5T> &buff5,
		      const RangeBufferAccessC<Data6T> &buff6
		      );
    //: Goto first element.
    // returns true if there is a first element.

    inline bool First(const SizeBufferAccessC<Data1T> &buff,
		      const SizeBufferAccessC<Data2T> &buff2,
		      const SizeBufferAccessC<Data3T> &buff3,
		      const SizeBufferAccessC<Data4T> &buff4,
		      const SizeBufferAccessC<Data5T> &buff5,
		      const SizeBufferAccessC<Data6T> &buff6
		      );
    //: Goto first element.
    // returns true if there is a first element.
    
    inline bool IsElm() const
    { return at1 < endOfRow; }
    //: At valid element ?
    
    inline bool IsLast() const
    { return (at1+1) == endOfRow; }
    //: Test if we're at the last valid element in the range.
    // Note: This is slightly slower than IsElm().

    inline operator bool() const
    { return at1 < endOfRow; }
    //: At valid element ?
    
    inline void Next();
    //: Goto next element.
    // Call ONLY if IsElm() is valid.

    inline void Next(int skip) {
      at1 += skip;
      at2 += skip;
      at3 += skip;
      at4 += skip;
      at5 += skip;
      at6 += skip;
    }
    //: Advance 'skip' elements.
    // Call ONLY if you know this will not go past the end of the array.
    
    BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T> &operator++()
    { Next(); return *this; }
    //: Goto next element.
    // Call ONLY if IsElm() is valid.
    
    inline BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T> & operator+=(int skip)
    { Next(skip); return *this; }
    //: Advance 'skip' elements.
    // WARNING: When using negative values, positions before the begining of the array will
    // not be detected correctly by IsElm().
    
    inline BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T> & operator-=(int skip)
    { Next(-skip); return *this; }
    //: Go back 'skip' elements.
    // WARNING: When using positive values, positions before the begining of the array will
    // not be detected correctly by IsElm().
    
    inline void operator++(int)
    { Next(); }
    //: Goto next elment.
    
    inline Data1T &Data1()
    { return *at1; }
    //: Access data.
    
    inline const Data1T &Data1() const
    { return *at1; }
    //: Access data.
    
    inline Data2T &Data2()
    { return *at2; }
    //: Access data.
    
    inline const Data2T &Data2() const
    { return *at2; }
    //: Access data.
    
    inline Data3T &Data3()
    { return *at3; }
    //: Access data.
    
    inline const Data3T &Data3() const
    { return *at3; }
    //: Access data.

    inline Data4T &Data4()
    { return *at4; }
    //: Access data.
    
    inline const Data4T &Data4() const
    { return *at4; }
    //: Access data.
    
    inline Data5T &Data5()
    { return *at5; }
    //: Access data.
    
    inline const Data5T &Data5() const
    { return *at5; }
    //: Access data.

    inline Data6T &Data6()
    { return *at6; }
    //: Access data.
    
    inline const Data6T &Data6() const
    { return *at6; }
    //: Access data.
    
    inline void Invalidate();
    //: Make IsElm() return false.
    
    inline bool operator>(const BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T> &oth) const
    { return at1 > oth.at1; }
    //: Is this at a position passed 'oth' ?
    // Using position in first buffer as a reference.
    
    inline bool operator<(const BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T> &oth) const
    { return at1 < oth.at1; }
    //: Is this at a position before 'oth' ?
    // Using position in first buffer as a reference.

    inline bool operator>=(const BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T> &oth) const
    { return at1 >= oth.at1; }
    //: Is this at a position passed or equal to 'oth' ?
    // Using position in first buffer as a reference.
    
    inline bool operator<=(const BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T> &oth) const
    { return at1 <= oth.at1; }
    //: Is this at a position before or equal to 'oth' ?
    // Using position in first buffer as a reference.

    inline bool operator==(const BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T> &oth) const
    { return at1 == oth.at1; }
    //: Is this at the same position as 'oth' ?
    // Using position in first buffer as a reference.
    
    IntT operator-(const BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T> &oth)
    { return at1 - oth.at1; }
    //: Return the difference in position of the iterators.
    // Using position in first buffer as a reference.
    
  protected:    
    Data1T *at1;
    Data2T *at2;
    Data3T *at3;
    Data4T *at4;
    Data5T *at5;
    Data6T *at6;
    const Data1T *endOfRow;
  };
  
  //////////////////////////////////////////////////////
  
  template<class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class Data6T>
  inline 
  BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T>::BufferAccessIter6C()
    : at1(0), 
      endOfRow(0)
  {}

  template<class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class Data6T>
  inline 
  bool BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T>::First(const BufferAccessC<Data1T> &buff,
									    const BufferAccessC<Data2T> &buff2,
									    const BufferAccessC<Data3T> &buff3,
									    const BufferAccessC<Data4T> &buff4,
									    const BufferAccessC<Data5T> &buff5,
									    const BufferAccessC<Data6T> &buff6,
									    SizeT size)
  {
    if(size <= 0) {
      at1 = 0;
      endOfRow = 0;
      return false;
    }
    at1 = const_cast<Data1T *>(buff.ReferenceElm());
    at2 = const_cast<Data2T *>(buff2.ReferenceElm());
    at3 = const_cast<Data3T *>(buff3.ReferenceElm());
    at4 = const_cast<Data4T *>(buff4.ReferenceElm());
    at5 = const_cast<Data5T *>(buff5.ReferenceElm());
    at6 = const_cast<Data6T *>(buff6.ReferenceElm());
    endOfRow = &(at1[size]);
    return true;
  }

  template<class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class Data6T>
  inline 
  bool BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T>::First(const BufferAccessC<Data1T> &buff1,const IndexRangeC &rng1,
									    const BufferAccessC<Data2T> &buff2,const IndexRangeC &rng2,
									    const BufferAccessC<Data3T> &buff3,const IndexRangeC &rng3,
									    const BufferAccessC<Data4T> &buff4,const IndexRangeC &rng4,
									    const BufferAccessC<Data5T> &buff5,const IndexRangeC &rng5,
									    const BufferAccessC<Data6T> &buff6,const IndexRangeC &rng6
									    )
  {
    if(rng1.Size() <= 0) {
      at1 = 0;
      endOfRow = 0;
      return false;
    }
    RavlAssert(rng1.Size() <= rng2.Size()); 
    RavlAssert(rng1.Size() <= rng3.Size()); 
    RavlAssert(rng1.Size() <= rng4.Size()); 
    RavlAssert(rng1.Size() <= rng5.Size()); 
    RavlAssert(rng1.Size() <= rng6.Size()); 
    at1 = const_cast<Data1T *>(&buff1[rng1.Min()]);
    at2 = const_cast<Data2T *>(&buff2[rng2.Min()]);
    at3 = const_cast<Data3T *>(&buff3[rng3.Min()]);
    at4 = const_cast<Data4T *>(&buff4[rng4.Min()]);
    at5 = const_cast<Data5T *>(&buff5[rng5.Min()]);
    at6 = const_cast<Data6T *>(&buff6[rng6.Min()]);
    endOfRow = &(at1[rng1.Size()]);
    return true;
  }
  
  template<class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class Data6T>
  inline 
  bool BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T>::First(const RangeBufferAccessC<Data1T> &buff,
									    const RangeBufferAccessC<Data2T> &buff2,
									    const RangeBufferAccessC<Data3T> &buff3,
									    const RangeBufferAccessC<Data4T> &buff4,
									    const RangeBufferAccessC<Data5T> &buff5,
									    const RangeBufferAccessC<Data6T> &buff6
									    )
  {
    RavlAssert(buff.Size() <= buff2.Size()); 
    RavlAssert(buff.Size() <= buff3.Size()); 
    RavlAssert(buff.Size() <= buff4.Size()); 
    RavlAssert(buff.Size() <= buff5.Size()); 
    RavlAssert(buff.Size() <= buff6.Size()); 
    if(buff.Size() <= 0) {
      at1 = 0;
      endOfRow = 0;
      return false ;
    }
    at1 = const_cast<Data1T *>(&buff[buff.IMin()]);
    at2 = const_cast<Data2T *>(&buff2[buff2.IMin()]);
    at3 = const_cast<Data3T *>(&buff3[buff3.IMin()]);
    at4 = const_cast<Data4T *>(&buff4[buff4.IMin()]);
    at5 = const_cast<Data5T *>(&buff5[buff5.IMin()]);
    at6 = const_cast<Data6T *>(&buff6[buff6.IMin()]);
    endOfRow = &(at1[buff.Size()]);
    return true;
  }

  template<class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class Data6T>
  inline 
  bool BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T>::First(const SizeBufferAccessC<Data1T> &buff,
									    const SizeBufferAccessC<Data2T> &buff2,
									    const SizeBufferAccessC<Data3T> &buff3,
									    const SizeBufferAccessC<Data4T> &buff4,
									    const SizeBufferAccessC<Data5T> &buff5,
									    const SizeBufferAccessC<Data6T> &buff6
									    )
  {
    RavlAssert(buff.Size() <= buff2.Size()); 
    RavlAssert(buff.Size() <= buff3.Size()); 
    RavlAssert(buff.Size() <= buff4.Size()); 
    RavlAssert(buff.Size() <= buff5.Size()); 
    RavlAssert(buff.Size() <= buff6.Size()); 
    if(buff.Size() <= 0) {
      at1 = 0;
      endOfRow = 0;
      return false;
    }
    at1 = const_cast<Data1T *>(buff.ReferenceElm());
    at2 = const_cast<Data2T *>(buff2.ReferenceElm());
    at3 = const_cast<Data3T *>(buff3.ReferenceElm());
    at4 = const_cast<Data4T *>(buff4.ReferenceElm());
    at5 = const_cast<Data5T *>(buff5.ReferenceElm());
    at6 = const_cast<Data6T *>(buff6.ReferenceElm());
    endOfRow = &(at1[buff.Size()]);
    return true;
  }
  
  template<class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class Data6T>
  inline 
  void BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T>::Next() {
    RavlAssert(at1 < endOfRow);
    at1++;
    at2++;
    at3++;
    at4++;
    at5++;
    at6++;
  }
  
  template<class Data1T,class Data2T,class Data3T,class Data4T,class Data5T,class Data6T>
  inline 
  void BufferAccessIter6C<Data1T,Data2T,Data3T,Data4T,Data5T,Data6T>::Invalidate() { 
    at1 = 0;
    endOfRow = 0; 
  }
  
}
#endif
