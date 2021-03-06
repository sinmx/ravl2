// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Container/SArray/testSArray2d.cc"
//! docentry="Ravl.API.Core.Arrays.2D"
//! userlevel=Develop

#include "Ravl/SArray2d.hh"
#include "Ravl/Slice1d.hh"
#include "Ravl/SArray2dIter.hh"
#include "Ravl/SArray2dIter2.hh"
#include "Ravl/SArray2dIter3.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/BinStream.hh"

using namespace RavlN;

int testBasic();
int testSArrayIter();
int testSubArray();
int testIO();

int main() {
  int ln ;
  if((ln = testBasic()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testSubArray()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testSArrayIter()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testIO()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";
  return 0; 
}

int testBasic() {
  cerr << "Starting test of SArray2d.\n";
  
  SArray2dC<int> testArr(10,10);
  
  // Sizes look right ?
  if(testArr.Size1() != 10)
    return __LINE__;
  if(testArr.Size2() != 10)
    return __LINE__;
  if(testArr.Range1().Size() != 10)
    return __LINE__;
  if(testArr.Range2().Size() != 10)
    return __LINE__;

  // Can we index elements ok?
  testArr[Index2dC(1,1)] = 1;
  testArr[Index2dC(1,2)] = 2;
  testArr[Index2dC(2,1)] = 3;
  testArr[Index2dC(2,2)] = 4;
  if(testArr[1][1] != 1) return __LINE__;
  if(testArr[1][2] != 2) return __LINE__;
  if(testArr[2][1] != 3) return __LINE__;
  if(testArr[2][2] != 4) return __LINE__;
  
  testArr.Fill(0);
  if(testArr[0][0] != 0) return __LINE__;
  if(testArr[1][1] != 0) return __LINE__;
  if(testArr[1][2] != 0) return __LINE__;
  if(testArr[2][1] != 0) return __LINE__;
  if(testArr[2][2] != 0) return __LINE__;
  if(testArr[9][9] != 0) return __LINE__;

 
  // Fill with a simple pattern.
  int place = 0;
  for(IndexC i = 0;i < 10;i++)
    for(IndexC j = 0;j < 10;j++)
      testArr[i][j] = place++;

  // Check simple iteration.
  place = 0;
  for(SArray2dIterC<int> it(testArr);it;it++,place++) {
    if(*it != place) {
      std::cerr << "Failed at Index=" << it.Index() << " Value=" << *it << " Expected=" << place << "\n";
      return __LINE__;
    }
  }
  
  // Sub array.
  SArray2dC<int> subArr(testArr,5,5);
  for(SArray2dIter2C<int,int> it(subArr,testArr);it;it++)
    if(it.Data1() != it.Data2()) return __LINE__;
  
  IndexRange2dC subRng2(IndexRangeC(1,2),IndexRangeC(2,4));
  SArray2dC<int> subArr2(testArr,subRng2);
  if(subArr2[0][0] != testArr[subRng2.Origin()]) return __LINE__;
  if(subArr2.Size1() != subRng2.Rows()) return __LINE__;
  if(subArr2.Size2() != subRng2.Cols()) return __LINE__;
  
  Slice1dC<int> slice = testArr.Diagonal();
  int v = 0;
  for(int i = 0;i < (IntT) slice.Size();i++,v+=11) {
    if(slice[i] != v) {
      cerr << "Diagonal slice test failed. Index=" << i << " Slice=" << slice[i] << " Expected=" << v << "\n";
      return __LINE__;
    }
  }
  v = 0;
  for(Slice1dIterC<int> its(slice);its;its++,v+=11) {
    if(*its != v) {
      cerr << "Diagonal slice iter test failed. " << *its << " " << v << "\n";
      return __LINE__;
    }
  }
  v = 0;
  for(SArray2dIterC<int> it(testArr);it;it++,v++) {
    if(*it != v) {
      cerr << "Iterator test failed. " << *it << " " << v << "\n";
      return __LINE__;
    }
    *it = 0;
  }
  testArr /= 2;
  testArr += 1;
  testArr = testArr + testArr;
  
  for(SArray2dIter2C<int,int> it(testArr,testArr);it;it++)
    it.Data1() = 0;
  for(SArray2dIter3C<int,int,int> it(testArr,testArr,testArr);it;it++)
    it.Data1() = 0;
  
  
  Index2dC at(0,0);
  if(testArr[at] != testArr[0][0]) return __LINE__;
  SArray2dC<int> testMin(1,1);
  testMin.Fill(1);
  if(testMin[0][0] != 1) return __LINE__;
    
  return 0;
}

int testIO() {
  SArray2dC<RealT> m(2,3);
  
  for(int i = 0;i < 2;i++)
    for(int j = 0;j < 3;j++)
      m[i][j] = i + j;

  // Test binary IO.
  {
    StrOStreamC os;
    {
      BinOStreamC bin(os);
      bin << m;
    }
    SArray2dC<RealT> m2;
    {
      StrIStreamC ifs(os.String());
      BinIStreamC bin(ifs);
      bin >> m2; 
    }
    if((m - m2).SumOfSqr() > 0.000001)
      return __LINE__;
  }
  
  // Test text IO.
  {
    StrOStreamC os;
    {
      os << m;
    }
    SArray2dC<RealT> m2;
    {
      StrIStreamC ifs(os.String());
      ifs >> m2; 
    }
    if((m - m2).SumOfSqr() > 0.000001)
      return __LINE__;
  }
  
  return 0;
}

int testSubArray() {
  SArray2dC<IntT> arr(5,7);
  IntT i = 0;
  for(SArray2dIterC<IntT> it(arr);it;it++,i++)
    *it = i;
  //cerr << arr << "\n";
  for(UIntT j = 1;j < arr.Size1();j++) {
    for(UIntT k = 1;k < arr.Size2();k++) {
      SArray2dC<IntT> sarr(arr,j,k);
      //cerr << sarr << "\n";
      UIntT area = 0;
      for(SArray2dIter2C<IntT,IntT> it2(sarr,arr);it2;it2++) {
	if(it2.Data1() != it2.Data2()) return __LINE__;
	area++;
      }
      if(area != j * k) return __LINE__;
    }
  }
  return 0;
}

int testSArrayIter() {
  SArray2dC<IntT> arr1(5,7);
  IntT i = 0;
  for(SArray2dIterC<IntT> it(arr1);it;it++,i++)
    *it = i;
  SArray2dC<short> arr2(5,7);
  i = 0;
  for(SArray2dIterC<short> it(arr2);it;it++,i++)
    *it = i;

  // Test 2 array iterator.
  i = 0;
  for(SArray2dIter2C<IntT,short> it(arr1,arr2);it;it++,i++) {
    //std::cerr << " " << it.Data1() << " " << it.Data2() << " i=" << i<< "\n";
    if(it.Data1() != it.Data2())
      return __LINE__;
  }
  SArray2dC<double> arr3(5,7);
  i = 0;
  for(SArray2dIterC<double> it(arr3);it;it++,i++)
    *it = i;

  // Test 3 array iterator.
  i = 0;
  for(SArray2dIter3C<IntT,short,double> it(arr1,arr2,arr3);it;it++,i++) {
    //std::cerr << " " << it.Data1() << " " << it.Data2() << " " << it.Data3() << " i=" << i <<"\n";
    if(it.Data1() != it.Data2())
      return __LINE__;
    if(it.Data1() != Round(it.Data3()))
      return __LINE__;
    if(it.Data1() != i)
      return __LINE__;
  }

  return 0;
}


template class SArray2dC<UIntT>;
template class SArray2dIterC<UIntT>;
template class SArray2dIter2C<UIntT,RealT>;
template class SArray2dIter3C<UIntT,RealT,ByteT>;
