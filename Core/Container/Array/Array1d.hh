// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ARRAY1D_HH
#define RAVL_ARRAY1D_HH
//////////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Container/Array/Array1d.hh"
//! lib=RavlCore
//! userlevel=Basic
//! author="Radek Marik"
//! docentry="Ravl.Core.Arrays.1D"
//! date="2/12/1993"
//! example=exArray1d.cc
//! rcsid="$Id$"

#include "Ravl/Buffer.hh"
#include "Ravl/RBfAcc.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/BfAccIter.hh"
#include "Ravl/BfAccIter2.hh"
#include "Ravl/Types.hh"

namespace RavlN {
  class BinIStreamC;
  class BinOStreamC;
  
  template<class DataT> class Array1dIterC;
  template<class DataT> class Slice1dC;
  template<class DataT> class Slice1dIterC;
  
  //: 1 Dimensional array
  // The class Array1dC is a  reference counted container with a fixed number
  // of items which can accessed in randomly using indexing in a specified
  // range of indeces. The item is expected
  // to have a default constructor, a copy constructor, and an assigment.
  // The class Array1dC is a big object, eg. it has a reference counter. <p>
  //  BIG OBJECT
  
  template <class DataT>
  class Array1dC
    : public RangeBufferAccessC<DataT> 
  { 
  public:  
    //:----------------
    // Type definitions.
    
    enum ExtensionT {
      SoftExt, // The new values are taken from a father array if it exists.
      HardExt  // The new values are always taken from the current subarray.
    };
    
    typedef DataT ElementT;
    //: Allow function templates to find type of array.
    
    typedef IndexC KeyT;
    //: Allow function templates to find type of index.
    
    typedef Array1dIterC<DataT> IteratorT;
    //: Iterator for this container.
    
    //typedef Array1dIterC<DataT> IteratorT;
    //: Type of iterator.
    
    //:---------------------------------------------
    // Constructors, copy, assigment, and destructor
    
    Array1dC();
    //: Creates an empty array.
    
    Array1dC(const Slice1dC<DataT> &slice,bool alwaysCopy = true);
    //: Make an array from a slice.
    // This will create an array with the values from the slice.
    // if the stride of the slice is not 1, and alwaysCopy is true the
    // a copy is done.
    
    Array1dC(SizeT dim);
    //: An array with the range <0, 'dim'-1>.
    
    Array1dC(IndexC min,IndexC max);
    //: An array with the range <min,max>.
    
    Array1dC(IntT min,IntT max);
    //: An array with the range <min,max>.
    
    Array1dC(const IndexRangeC & range);
    //: An array with the range <'range'.Min(), 'range'.Max()>.
    
    Array1dC(istream & s);
    //: Creates an 1-dimensional array from the input stream.
    
    Array1dC(const Array1dC<DataT> & vv);
    //: Another access to the array 'vv'.
    
    Array1dC(DataT *             data,
	     const IndexRangeC & range,
	     bool            removable = true);
    //: An array is created from the memory location 'data' with the range
    //: of access in <'range'.Min(), 'range'.Max()>. <p>
    // 'data' is assumed to point to the location 'range.min()' <p>
    // If flag 'removable' is false,
    // 'data' is not deallocated during destructing of the array, unless
    // 'removable' is set to true.
    
    Array1dC(BufferC<DataT> & bf, const IndexRangeC & range);
    //: Creates the array with limits 'range' using the buffer 'bf'.
    
    Array1dC(BufferC<DataT> & bf, const RangeBufferAccessC<DataT>  & rbf);
    //: Creates the array in 'bf' using access rbf..
    
    Array1dC(const Array1dC<DataT> & vv, const IndexRangeC & range);
    //: The subarray of the 'vv' with the 'range'.
    
    Array1dC(const Array1dC<DataT> & vv, IndexC origin);
    //: Create a new access to array vv with the origin at the given offset.
    
    Array1dC(const SArray1dC<DataT> &oth);
    //: Construct an array from a SArray1dC.
    // Note: This does NOT make a copy, it just creates
    // another access to the buffer.
    
    Array1dC<DataT> Copy() const;
    //: Creates a new physical copy of the array.
    
    Array1dC<DataT> & Copy(const Array1dC<DataT> & orig);
    //: Copies values from the 'orig' array into this array. 
    // Only items
    // from the overlapping part of the ranges are copied. The function
    // returns this array.
    
    Array1dC<DataT> & Copy(const IndexRangeC & r, const IndexC off);
    //: Copies values from the index range 'r' into the new position 
    //: with the offset 'off'. 
    // Only those items
    // which original position and destination are inside of the index range
    // of this array are copied.
    
    Array1dC<DataT> & Copy(const IndexC off, const Array1dC<DataT> & a);
    //: Copies the maximum possible part of array 'a' into this array.
    // The first element of array 'a' is placed into the element 
    // of this array with index  'off'. The functio returns this array.
    
    Array1dC<DataT> &Copy(const Slice1dC<DataT> &data);
    //: Copy data from slice into this array.
    
    const Array1dC<DataT> & operator=(const Array1dC<DataT> & vv);
    //: Assigment, as for a BIG_OBJECT.
    
    // Access to the object elements.
    // ------------------------------
    
    inline const Array1dC<DataT> & Array1d() const
    { return *this; }
    //: Access to the whole array.
    
    inline Array1dC<DataT> & Array1d()
    { return *this; }
    //: Access to the whole array.
    
    inline SArray1dC<DataT> SArray1d(bool doShift = false);
    //: Create an access as an sarray.
    // NB. This does NOT copy the data, it only make a new access to it.
    // If doShift is true element IMin() will become element 0 of the 
    // SArray while the size stays the same. Otherwise if the array 
    // does not contain element '0' an error will occure in check mode, 
    // when optimised is enabled an empty array will be returned. 

    Slice1dC<DataT> Slice1d()
    { return Slice1dC<DataT>(buff,ReferenceElm(),Range(),1); }
    //: Access array as a slice.
    
    //:-----------------------------------
    // Array representation modifications.
    
    Array1dC<DataT> Extend(SizeT n) const;
    //: Returns the array whose range is extended by adding 'n' items with
    //: default value from both limits of the range. 
    // This array value are
    // copied into the same index positions in the returned array.
    
    Array1dC<DataT> & Append(const Array1dC<DataT> & a);
    //: This array is extended by the length of the array 'a' and the contents
    //: of both arrays are copied to it.
    // The function supports empty arrays.
    
    // Logical operations.
    // -------------------
    
    inline bool IsSharing(const Array1dC<DataT> & arr) const
    { return buff == arr.buff; }
    //: Returns true if this array and the array 'arr' are subarrays of the
    //: the same array.
    
    //:-------------------
    // Special operations.
    
    BufferC<DataT> &Buffer()
    { return buff; }
    //: Access buffer in which data is stored.
    
    const BufferC<DataT> &Buffer() const
    { return buff; }
    //: Access buffer in which data is stored.
    
    Array1dC<DataT> operator+(const Array1dC<DataT> & arr) const;
    // Sums 2 numerical arrays. The operator returns the result as a new array.
    
    Array1dC<DataT> operator-(const Array1dC<DataT> & arr) const;
    // Subtracts 2 numerical arrays. The operator returns
    // the result as a new array.
    
    Array1dC<DataT> operator*(const Array1dC<DataT> & arr) const;
    // Mutliplies 2 numerical arrays. The operator returns the result as a new array.
    
    Array1dC<DataT> operator/(const Array1dC<DataT> & arr) const;
    // Devides 2 numerical arrays. The operator returns
    // the result as a new array.
    
    Array1dC<DataT> operator*(const DataT &number) const;
    // Multiplys the array by the 'number'. The operator
    // returns the result as a new array.
    
    Array1dC<DataT> operator/(const DataT &number) const;
    // Divides all array items by the 'number'. The operator 
    // returns the result as a new array.
    
    Array1dC<DataT> operator+(const DataT &number) const;
    // Adds 'number' to the array. The operator
    // returns the result as a new array.
    
    Array1dC<DataT> operator-(const DataT &number) const;
    // Subtracts 'number' from all array items. The operator 
    // returns the result as a new array.
    
    const Array1dC<DataT> & operator+=(const Array1dC<DataT> & arr);
    // Adds the 2nd array to this array.
    
    const Array1dC<DataT> & operator-=(const Array1dC<DataT> & arr);
    // Subtracts the 2nd array from this array.
    
    const Array1dC<DataT> & operator*=(const Array1dC<DataT> & arr);
    // Multiplies the 2nd array to this array.
    
    const Array1dC<DataT> & operator/=(const Array1dC<DataT> & arr);
    // Divides the 2nd array from this array.
    
    const Array1dC<DataT> & operator+=(const DataT &number);
    // Adds 'number' to all array items.
    
    const Array1dC<DataT> & operator-=(const DataT &number);
    // Subtracts 'number' from all array items.
    
    const Array1dC<DataT> & operator*=(const DataT &number);
    // Multiplies the array by the 'number'.
    
    const Array1dC<DataT> & operator/=(const DataT &number);
    // Divides the array elements by the 'number'.
    
    DataT SumSqr() const;
    //: Calculate the sum of the squares of all elements in the array
    
    DataT Sum() const;
    //: Calculate the sum of all elements in the array
    
    Array1dC<DataT> Apply(DataT (*op)(const DataT &func)) const;
    //: Apply a function to each item in the array.
    // The results are put in a new array.
    
    Array1dC<DataT> &ApplyIP(void (*op)(DataT &func));
    //: Apply a function In Place to each item in the array.
    // the changes are made to this array.

    Array1dC<DataT> From(IndexC offset) { 
      if(offset > Range().Max())
	return Array1dC<DataT>(); // Empty array.
      RavlAssert(offset >= Range().Min()); // Ensure its within the array.
      return Array1dC<DataT>(*this,IndexRangeC(offset,Range().Max())); 
    }
    //: Return array from offset to the end of the array.
    // If offset is larger than the array an empty array
    // is returned.  
    
    Array1dC<DataT> From(IndexC offset,UIntT size) { 
      if(offset > Range().Max())
	return Array1dC<DataT>(); // Empty array.
      RavlAssert(Range().Contains(offset) && Range().Contains(offset + size));
      return Array1dC<DataT>(*this,IndexRangeC(offset,(offset+size)-1)); 
    }
    //: Return array from offset for size elements..
    // If offset is larger than the array an empty array
    // is returned.
    
    Array1dC<DataT> After(IndexC offset) 
    { return From(offset+1); }
    //: Return array after offset to the end of the array.
    // If offset is larger than the array an empty array
    // is returned.

    bool SetIMin(IndexC imin) {
      IntT startIndex = buff.ReferenceElm() - ReferenceElm();
      if(imin < startIndex)
	return false;
      range.Min() = imin;
      return true;
    }
    //: Attempt to change the start of the array.
    // This checks the index is within the allocated buffer.
    
    bool SetIMax(IndexC imax) {
      IntT startIndex = buff.ReferenceElm() - ReferenceElm();
      if(imax >= (startIndex + buff.Size()) )
	return false;
      range.Max() = imax;
      return true;      
    }
    //: Attempty to change the end of the array.
    // This checks the index is within the allocated buffer.
    
  private:
    BufferC<DataT> buff;  //: The reference counted storage.
  };
  
  template <class DataT>
  ostream & 
  operator<<(ostream & s, const Array1dC<DataT> & arr);
  // Prints array into the stream 's'.

  template <class DataT>
  istream & 
  operator>>(istream & s, Array1dC<DataT> & arr);
  // Assigns the values into the array 'arr'.
  
  template <class DataT>
  BinOStreamC & operator<<(BinOStreamC & s, const SArray1dC<DataT> & arr);
  // Prints array into the stream 's'.
  
  template <class DataT>
  BinIStreamC & operator>>(BinIStreamC& s, SArray1dC<DataT> & arr);
  // Assigns the values into the array 'arr'.
  
  template <class DataT>
  Array1dC<DataT> &
  BubbleSort(Array1dC<DataT> & arr);
  // Sorts the array 'arr' using operator <.
  
  ///////////////////////////////////////////////
  
  template <class DataT>
  inline
  const Array1dC<DataT> &
  Array1dC<DataT>::operator=(const Array1dC<DataT> & vv) {
    if (this == &vv) return *this;
    RangeBufferAccessC<DataT>::operator=(vv);
    buff=vv.buff;
    return *this;
  }
  
  template <class DataT>
  Array1dC<DataT>::Array1dC()
    : RangeBufferAccessC<DataT>(),
      buff()
  {}
  
  template <class DataT>
  Array1dC<DataT>::Array1dC(const SizeT dim)
    : RangeBufferAccessC<DataT>(),
      buff(dim)
  { Attach(buff,dim); }

  
  template <class DataT>
  Array1dC<DataT>::Array1dC(IntT min,IntT max)
    : RangeBufferAccessC<DataT>(),
      buff(IndexRangeC(min,max).Size())
  {
    RavlAssert(min <= max);
    Attach(buff,IndexRangeC(min,max)); 
  }
  
  template <class DataT>
  Array1dC<DataT>::Array1dC(IndexC min,IndexC max)
    : RangeBufferAccessC<DataT>(),
      buff(IndexRangeC(min,max).Size())
  {
    RavlAssert(min <= max);
    Attach(buff,IndexRangeC(min,max)); 
  }
  
  template <class DataT>
  Array1dC<DataT>::Array1dC(const IndexRangeC & range)
    : RangeBufferAccessC<DataT>(),
      buff(range.Size())
  { Attach(buff,range); }
  

  template <class DataT>
  Array1dC<DataT>::Array1dC(const Array1dC<DataT> & vv)
    : RangeBufferAccessC<DataT>(vv),
      buff(vv.buff)
  {}
  
  template <class DataT>
  Array1dC<DataT>::Array1dC(const Array1dC<DataT> & vv, IndexC origin)
    : RangeBufferAccessC<DataT>(const_cast<DataT *>(&vv[vv.IMin()]),IndexRangeC(origin,origin + (vv.IMax() - vv.IMin()))),
      buff(vv.buff)
  {}
  
  template <class DataT>
  Array1dC<DataT>::Array1dC(const Slice1dC<DataT> &slice,bool alwaysCopy) { 
    if(!alwaysCopy && slice.Stride() == 1) {
      buff = slice.Buffer();
      RangeBufferAccessC<DataT>::operator=(RangeBufferAccessC<DataT>(slice.Range(),
								     const_cast<DataT *>(&(slice.ReferenceElm()))));
      return ;
    }
    buff = BufferC<DataT>(slice.Size());
    Attach(buff.BufferAccess(),slice.Range());
    // Copy data.
    DataT *at = buff.ReferenceElm();
    for(Slice1dIterC<DataT> it(slice);it;it++,at++)
      *at = *it;
  }
  
  template <class DataT>
  Array1dC<DataT>::Array1dC(DataT * data, 
			    const IndexRangeC & range,
			    bool    removable)
    : RangeBufferAccessC<DataT>(data, range),
      buff(range.Size(),data,false, removable)
  {}
  
  template <class DataT>
  Array1dC<DataT>::Array1dC(BufferC<DataT> & bf, const IndexRangeC & range)
    : RangeBufferAccessC<DataT>(bf.BufferAccess(), range),
      buff(bf)
  {}
  
  template <class DataT>
  Array1dC<DataT>::Array1dC(BufferC<DataT> & bf, const RangeBufferAccessC<DataT>  & rbf) 
    : RangeBufferAccessC<DataT>(rbf),
      buff(bf)
  {}
  
  template <class DataT>
  Array1dC<DataT>::Array1dC(const Array1dC<DataT> & vv, 
			    const IndexRangeC & range)
    : RangeBufferAccessC<DataT>(vv.RAccess(), range),
      buff(vv.buff)
  {}
  
  template <class DataT>
  Array1dC<DataT>::Array1dC(const SArray1dC<DataT> &oth)
    : RangeBufferAccessC<DataT>(const_cast<DataT *>(&(oth[0])),IndexRangeC(0,oth.Size()-1)),
      buff(oth.Buffer())
  {}
  
  template <class DataT>
  Array1dC<DataT>
  Array1dC<DataT>::Copy() const {
    return Array1dC<DataT>(RangeBufferAccessC<DataT>::Copy().DataStart(), 
			   Range());
  }
  
  template <class DataT>
  Array1dC<DataT> & 
  Array1dC<DataT>::Copy(const Array1dC<DataT> & orig) {
    IndexRangeC r(orig.Range());
    r.ClipBy(Range());
    for(BufferAccessIter2C<DataT,DataT> it(*this,orig,r);it;it++)
      it.Data1() = it.Data2();
    return *this;
  }
  
  template <class DataT>
  Array1dC<DataT> & 
  Array1dC<DataT>::Copy(const IndexRangeC & r, const IndexC off) {
    // Construct the destination range.
    IndexRangeC destination(r);
    destination.ClipBy(Range());   // the clipped source domain
    destination += off;
    destination.ClipBy(Range());   // destination.Size() <= source.Size()
    // Both 'destination' and 'source' ranges are inside the array.
    
    const IndexC min = destination.Min();
    const IndexC max = destination.Max();
    if (off <= 0)
      for (IndexC c = min; c <= max; c++)
	(*this)[c] = (*this)[c+off];
    else 
      for (IndexC c = max; c >= min; c--)
	(*this)[c] = (*this)[c-off];
    return *this;
  }
  
  template <class DataT>
  Array1dC<DataT> & 
  Array1dC<DataT>::Copy(const IndexC off, const Array1dC<DataT> & a) {
    const SizeT mySize = (IMax() - off +1).V();
    DataT * myElm = &((*this)[off]);
    DataT const * aElm  = &(a[a.IMin()]);
    const DataT * myEnd  = mySize < a.Size() ? (myElm+mySize-1)
      : (myElm+a.Size()-1);
    while (myElm <= myEnd)
      *(myElm++) = *(aElm++);
    return *this;
  }
  
  //: Copy data from slice into this array.
  
  template <class DataT>
  Array1dC<DataT> &Array1dC<DataT>::Copy(const Slice1dC<DataT> &data) {
    RavlAssert(Range().Contains(data.Range()));
    DataT *at = &(*this)[data.Range().Min()];
    for(Slice1dIterC<DataT> it(data);it;it++,at++)
      *at = *it;
    return *this;
  }

  template <class DataT>
  Array1dC<DataT> 
  Array1dC<DataT>::Extend(const SizeT n) const {
    IndexRangeC rng(IMin(),IMax() + n);
    Array1dC<DataT> x(rng);
    x.Copy(*this);
    return x;
  }

  template <class DataT>
  Array1dC<DataT> & 
  Array1dC<DataT>::Append(const Array1dC<DataT> & a) {
    if (!a.IsValid()) return *this;
    if (!IsValid()) {
      *this = a.Copy();
      return *this;
    }
    const IndexRangeC newRange(IMin(), IMax() + a.Size());
    Array1dC<DataT>   newArr(newRange);
    newArr.Copy(*this);
    newArr.Copy(IMax()+1,a);
    *this = newArr;
    return *this;
  }
  
  template <class DataT>
  inline 
  SArray1dC<DataT> Array1dC<DataT>::SArray1d(bool doShift) {
    if(doShift)
      return SArray1dC<DataT>(buff,&((*this)[IMin()]),Size());
    if(!Contains(0)) {
      RavlAssert(Contains(0)); // Cause assertion failure in debug/check mode
      return SArray1dC<DataT>();
    }
    return SArray1dC<DataT>(buff,&((*this)[0]) ,IMax().V());
  }

  template <class DataT>
  ostream &
  operator<<(ostream & s, const Array1dC<DataT> & arr) {
    const IndexRangeC range(arr.Range());
    s << range << '\n'; 
    for(BufferAccessIterC<DataT> it(arr);it;it++)
      s  << ((const DataT &) *it) << '\n';
    return s;
  }
  
  
  template <class DataT>
  istream &
  operator>>(istream & s, Array1dC<DataT> & arr) {
    IndexRangeC range(s);
    s.get(); // Get '\n' after size to avoid trouble with reading StringC's.
    if (range != arr.Range()) {
      Array1dC<DataT> brr(range);
      arr = brr;
    }
    for(BufferAccessIterC<DataT> it(arr);it;it++)
      s >> *it;
    return s;
  }
  
  template<class DataT>
  BinOStreamC &
  operator<<(BinOStreamC & s, const Array1dC<DataT> & arr) {
    s << arr.Range().Min() << arr.Range().Max();
    for(BufferAccessIterC<DataT> it(arr);it;it++)
      s << *it;
    return s;
  }

  template<class DataT>
  BinIStreamC &
  operator>>(BinIStreamC & s, Array1dC<DataT> & arr) {
    IndexRangeC rng;
    s >> rng.Min() >> rng.Max();
    arr = Array1dC<DataT>(rng);
    for(BufferAccessIterC<DataT> it(arr);it;it++)
      s >> *it;
    return s;
  }
  
  template<class DataT>
  Array1dC<DataT> Array1dC<DataT>::operator+(const Array1dC<DataT> & arr) const {
    Array1dC<DataT> ret(Size());
    for(BufferAccessIter3C<DataT,DataT,DataT> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() + it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array1dC<DataT> Array1dC<DataT>::operator-(const Array1dC<DataT> & arr) const {
    Array1dC<DataT> ret(Size());
    for(BufferAccessIter3C<DataT,DataT,DataT> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() - it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array1dC<DataT> Array1dC<DataT>::operator*(const Array1dC<DataT> & arr) const {
    Array1dC<DataT> ret(Size());
    for(BufferAccessIter3C<DataT,DataT,DataT> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() * it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array1dC<DataT> Array1dC<DataT>::operator/(const Array1dC<DataT> & arr) const {
    Array1dC<DataT> ret(Size());
    for(BufferAccessIter3C<DataT,DataT,DataT> it(ret,*this,arr);it;it++)
      it.Data1() = it.Data2() / it.Data3();
    return ret;
  }
  
  template<class DataT>
  Array1dC<DataT> Array1dC<DataT>::operator+(const DataT &number) const {
    Array1dC<DataT> ret(Size());
    for(BufferAccessIter2C<DataT,DataT> it(ret,*this);it;it++)
      it.Data1() = it.Data2() + number;
    return ret;
  }
  
  template<class DataT>
  Array1dC<DataT> Array1dC<DataT>::operator-(const DataT &number) const {
    Array1dC<DataT> ret(Size());
    for(BufferAccessIter2C<DataT,DataT> it(ret,*this);it;it++)
      it.Data1() = it.Data2() - number;
    return ret;
  }
  
  template<class DataT>
  Array1dC<DataT> Array1dC<DataT>::operator*(const DataT &number) const {
    Array1dC<DataT> ret(Size());
    for(BufferAccessIter2C<DataT,DataT> it(ret,*this);it;it++)
      it.Data1() = it.Data2() * number;
    return ret;
  }
  
  template<class DataT>
  Array1dC<DataT> Array1dC<DataT>::operator/(const DataT &number) const {
    Array1dC<DataT> ret(Size());
    for(BufferAccessIter2C<DataT,DataT> it(ret,*this);it;it++)
      it.Data1() = it.Data2() / number;
    return ret;
  }
  
  template<class DataT>
  const Array1dC<DataT> & Array1dC<DataT>::operator+=(const Array1dC<DataT> & arr) {
    for(BufferAccessIter2C<DataT,DataT> it(*this,arr);it;it++)
      it.Data1() += it.Data2();
    return *this;
  }
  
  template<class DataT>
  const Array1dC<DataT> & Array1dC<DataT>::operator-=(const Array1dC<DataT> & arr) {
    for(BufferAccessIter2C<DataT,DataT> it(*this,arr);it;it++)
      it.Data1() -= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const Array1dC<DataT> & Array1dC<DataT>::operator*=(const Array1dC<DataT> & arr) {
    for(BufferAccessIter2C<DataT,DataT> it(*this,arr);it;it++)
      it.Data1() *= it.Data2();
    return *this;
  }
    
  template<class DataT>
  const Array1dC<DataT> & Array1dC<DataT>::operator/=(const Array1dC<DataT> & arr) {
    for(BufferAccessIter2C<DataT,DataT> it(*this,arr);it;it++)
      it.Data1() /= it.Data2();
    return *this;
  }
  
  template<class DataT>
  const Array1dC<DataT> & Array1dC<DataT>::operator+=(const DataT &number) {
    for(BufferAccessIterC<DataT> it(*this);it;it++)
      it.Data1() += number;
    return *this;
  }
  
  
  template<class DataT>
  const Array1dC<DataT> & Array1dC<DataT>::operator-=(const DataT &number) {
    for(BufferAccessIterC<DataT> it(*this);it;it++)
      it.Data1() -= number;
    return *this;
  }
  
  template<class DataT>
  const Array1dC<DataT> & Array1dC<DataT>::operator*=(const DataT &number) {
    for(BufferAccessIterC<DataT> it(*this);it;it++)
      it.Data1() *= number;
    return *this;
  }
  
  template<class DataT>
  const Array1dC<DataT> & Array1dC<DataT>::operator/=(const DataT &number) {
    for(BufferAccessIterC<DataT> it(*this);it;it++)
      it.Data1() /= number;
    return *this;
  }
  
  template<class DataT>
  DataT Array1dC<DataT>::SumSqr() const {
    BufferAccessIterC<DataT> it(*this);
    DataT ret;
    if(!it) { // Zero length array ?
      SetZero(ret);
      return ret;
    }
    ret = Sqr(*it);
    for(it++;it;it++)
      ret += Sqr(it.Data1());
    return ret;
  }
  
  template<class DataT>
  DataT Array1dC<DataT>::Sum() const {
    BufferAccessIterC<DataT> it(*this);
    DataT ret;
    if(!it) { // Zero length array.
      SetZero(ret);
      return ret;
    }
    ret = StdCopy(*it); // Need to copy in case its a reference counted object. 
    for(it++;it;it++)
      ret += *it;
    return ret;
  }
  
  template<class DataT>
  Array1dC<DataT> Array1dC<DataT>::Apply(DataT (*op)(const DataT &func)) const {
    Array1dC<DataT> ret(Range());
    for(BufferAccessIter2C<DataT,DataT> it(ret,*this);it;it++)
      it.Data1() = op(it.Data2());
    return ret;
  }
  
  template<class DataT>
  Array1dC<DataT> &Array1dC<DataT>::ApplyIP(void (*op)(DataT &func)) {
    for(BufferAccessIterC<DataT> it(*this);it;it++)
      op(*it);
    return *this;
  }
  
  template <class DataT>
  Array1dC<DataT> &
  BubbleSort(Array1dC<DataT> & arr) {
    IndexC    low = arr.Range().Min();
    IndexC    upp = arr.Range().Max();
    bool  change;
    DataT  *  ev = new DataT(); // A big piggish ...... according G. Matas.
    do {
      change = false;
      for (IndexC i = low; i < upp; ++i) {
	if (arr[i] < arr[i+1]) {
	  *ev = arr[i];
	  arr[i] = arr[i+1];
	  arr[i+1] = *ev;
	  change = true;
	}
      }
      --upp; // at the moment the last item is the smallest one
    } while(change);
    return(arr);
  }
  
}
#endif
