// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
// $Id$
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Container/Buffer/testBuffer3d.cc"
//! docentry="Ravl.API.Core.Arrays.Buffer"
//! author="Charles Galambos"
//! userlevel=Develop

#include "Ravl/Stream.hh"
#include "Ravl/Buffer3d.hh"
#include "Ravl/SizeBufferAccess3d.hh"
#include "Ravl/RangeBufferAccess3d.hh"
#include "Ravl/BufferAccess3dIter.hh"
#include "Ravl/BufferAccess3dIter2.hh"
#include "Ravl/BufferAccess3dIter3.hh"

using namespace RavlN;

int TestRangeBuffer();
int TestSizeBuffer();
int TestRangeBufferIter();
int TestSizeBufferIter();

int main()
{
  int ln;
  if((ln = TestRangeBuffer()) != 0) {
    cerr << "Buffer test failed on line :" << ln << "\n";
    return 1;
  }
  if((ln = TestSizeBuffer()) != 0) {
    cerr << "Buffer test failed on line :" << ln << "\n";
    return 1;
  }
  if((ln = TestRangeBufferIter()) != 0) {
    cerr << "Buffer test failed on line :" << ln << "\n";
    return 1;
  }
  if((ln = TestSizeBufferIter()) != 0) {
    cerr << "Buffer test failed on line :" << ln << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

int TestRangeBuffer() {

  IndexRangeC r1(1,3);
  IndexRangeC r2(2,5);
  IndexRangeC r3(3,7);

  Buffer3dC<int> bf (r1.Size(),r2.Size(),r3.Size());
  if(bf.Size1() != (UIntT) r1.Size()) return __LINE__;
  if(bf.Size2() != (UIntT) r2.Size()) return __LINE__;
  if(bf.Size3() != (UIntT) r3.Size()) return __LINE__;
  
  //cerr << "Buffer at :" << ((void *) bf.Data().ReferenceElm()) << "\n";
  
  RangeBufferAccess3dC<int> rba;
  rba.Attach(bf,r1,r2,r3);
  
  if(r1 != rba.Range1()) {
    cerr<< "Range 1 incorrect. " << rba.Range1() <<" should be " << r1 << "\n";
    return __LINE__;
  }
  if(r2 != rba.Range2()) {
    cerr<< "Range 2 incorrect. " << rba.Range2() <<" should be " << r2 << "\n";
    return __LINE__;
  }

  if(r3 != rba.Range3()) {
    cerr<< "Range 3 incorrect. " << rba.Range2() <<" should be " << r2 << "\n";
    return __LINE__;
  }
    
  if(&(rba[rba.Range1().Min()][rba.Range2().Min()][rba.Range3().Min()]) != bf.ReferenceElm()) {
    cerr << "Buffer setup incorrect. Min @" << ((void *)&(rba[rba.Range1().Min()][rba.Range2().Min()][rba.Range3().Min()])) << "\n";
    cerr << "Ref @" << ((void *) bf.ReferenceElm()) << "\n";
    return __LINE__;
  }
  
  BufferAccess3dIterC<int> it(rba);
  if(!it.IsElm()) {
    cerr << "Failed to create valid iterator. \n";
    return __LINE__;
  }
  if(&(*it) != &(rba[rba.Range1().Min()][rba.Range2().Min()][rba.Range3().Min()])) {
    cerr << "Inital iterator position incorrect. " << ((void *) &(*it) ) << " should be " << ((void *) &(rba[rba.Range1().Min()][rba.Range2().Min()][rba.Range3().Min()])) <<  "\n";
    return __LINE__;
  }
  SizeT count = 0;
  for(;it;it++) {
    *it = 0;
    count++;
  }
  SizeT totalSize = (r1.Size() * r2.Size() * r3.Size());
  if(count != totalSize) {
    std::cerr << "Count mismatch in iterator test. Counter=" << count << " Size=" << totalSize << "\n";
    return __LINE__;
  }

return 0;
}


int TestSizeBuffer() {
  SizeT s1 = 2;
  SizeT s2 = 3;
  SizeT s3 = 4;

  Buffer3dC<int> bf (s1,s2,s3);
  if(bf.Size1() != s1) return __LINE__;
  if(bf.Size2() != s2) return __LINE__;
  if(bf.Size3() != s3) return __LINE__;

  SizeBufferAccess3dC<int> rba(bf,s1,s2,s3);
  if(s1 != rba.Size1()) {
    cerr<< "Size 1 incorrect. " << rba.Size1() <<" should be " << s1 << "\n";
    return __LINE__;
  }
  if(s2 != rba.Size2()) {
    cerr<< "Size 2 incorrect. " << rba.Size2() <<" should be " << s2 << "\n";
    return __LINE__;
  }

  if(s3 != rba.Size3()) {
    cerr<< "Size 3 incorrect. " << rba.Size2() <<" should be " << s2 << "\n";
    return __LINE__;
  }

  if(&(rba[0][0][0]) != bf.ReferenceElm()) {
    cerr << "Buffer setup incorrect. Min @" << ((void *)&(rba[0][0][0])) << "\n";
    cerr << "Ref @" << ((void *) bf.ReferenceElm()) << "\n";
    return __LINE__;
  }
  
  BufferAccess3dIterC<int> it(rba);
  if(!it.IsElm()) {
    cerr << "Failed to create valid iterator. \n";
    return __LINE__;
  }
  if(&(*it) != &(rba[0][0][0])) {
    cerr << "Inital iterator position incorrect. " << ((void *) &(*it) ) << " should be " << ((void *) &(rba[0][0][0])) <<  "\n";
    return __LINE__;
  }
  SizeT count = 0;
  for(;it;it++) {
    *it = 0;
    count++;
  }
  if(count != (s1 * s2 * s3)) {
    return __LINE__;
  }

  return 0;
}

int TestRangeBufferIter() {
  IndexRangeC r1(-1,3);
  IndexRangeC r2(-2,5);
  IndexRangeC r3(-3,7);

  Buffer3dC<Index3dC> bf1 (r1.Size(),r2.Size(),r3.Size());
  RangeBufferAccess3dC<Index3dC> rba1;
  rba1.Attach(bf1,r1,r2,r3);

  // Check indexing works.
  for(IndexC i = r1.Min();i <= r1.Max();i++){
    for(IndexC j = r2.Min();j <= r2.Max();j++) {
      for(IndexC k = r3.Min();k <= r3.Max();k++) {
        Index3dC ind(i,j,k);
        rba1[i][j][k] = ind;
        if(rba1[ind] != ind) return __LINE__;
        if(rba1.Index1Of(rba1[ind]) != i) return __LINE__;
        if(rba1.Index2Of(rba1[ind]) != j) return __LINE__;
        if(rba1.Index3Of(rba1[ind]) != k) return __LINE__;
        if(rba1.IndexOf(rba1[ind]) != ind) return __LINE__;
      }
    }
  }


  Buffer3dC<double> bf2 (r1.Size(),r2.Size(),r3.Size());
  RangeBufferAccess3dC<double> rba2;
  rba2.Attach(bf2,r1,r2,r3);

  Buffer3dC<int> bf3 (r1.Size(),r2.Size(),r3.Size());
  RangeBufferAccess3dC<int> rba3;
  rba3.Attach(bf3,r1,r2,r3);

  int count = 0;
  for(BufferAccess3dIterC<int> it(rba3,r1,r2,r3);it;it++) {
    *it = count++;
  }

  count = 0;
  for(BufferAccess3dIter2C<Index3dC,double> it(rba1,rba2,r1,r2,r3);it;it++) {
    if(rba1.IndexOf(it.Data1()) != it.Data1()) return __LINE__;
    it.Data2() = count++;
  }

  count = 0;
  for(BufferAccess3dIter3C<Index3dC,double,int> it(rba1,rba2,rba3,r1,r2,r3);it;it++) {
    if(rba1.IndexOf(it.Data1()) != it.Data1()) return __LINE__;
    if(it.Data2() != count) return __LINE__;
    if(it.Data3() != count++) return __LINE__;
  }

  return 0;
}

int TestSizeBufferIter() {
  SizeT r1 = 4;
  SizeT r2 = 5;
  SizeT r3 = 7;

  Buffer3dC<Index3dC> bf1 (r1,r2,r3);
  SizeBufferAccess3dC<Index3dC> sba1;
  sba1.Attach(bf1,r1,r2,r3);

  // Check indexing works.
  for(IndexC i = 0;i < r1;i++){
    for(IndexC j = 0;j < r2;j++) {
      for(IndexC k = 0;k < r3;k++) {
        Index3dC ind(i,j,k);
        sba1[i][j][k] = ind;
        if(sba1[ind] != ind) return __LINE__;
        if(sba1.Index1Of(sba1[ind]) != i) return __LINE__;
        if(sba1.Index2Of(sba1[ind]) != j) return __LINE__;
        if(sba1.Index3Of(sba1[ind]) != k) return __LINE__;
        if(sba1.IndexOf(sba1[ind]) != ind) return __LINE__;
      }
    }
  }

  Buffer3dC<double> bf2 (r1,r2,r3);
  SizeBufferAccess3dC<double> sba2;
  sba2.Attach(bf2,r1,r2,r3);

  Buffer3dC<int> bf3 (r1,r2,r3);
  SizeBufferAccess3dC<int> sba3;
  sba3.Attach(bf3,r1,r2,r3);

  int count = 0;
  for(BufferAccess3dIterC<int> it(sba3,r1,r2,r3);it;it++) {
    *it = count++;
  }

  count = 0;
  for(BufferAccess3dIter2C<Index3dC,double> it(sba1,sba2,r1,r2,r3);it;it++) {
    if(sba1.IndexOf(it.Data1()) != it.Data1()) return __LINE__;
    it.Data2() = count++;
  }

#if 1
  count = 0;
  for(BufferAccess3dIter3C<Index3dC,double,int> it(sba1,sba2,sba3,r1,r2,r3);it;it++) {
    if(sba1.IndexOf(it.Data1()) != it.Data1()) return __LINE__;
    if(it.Data2() != count) return __LINE__;
    if(it.Data3() != count++) return __LINE__;
  }
#endif
  return 0;
}

template class Buffer3dBodyC<IntT>;
template class Buffer3dC<IntT>;

template class BufferAccess3dIterC<IntT>;
template class BufferAccess3dIter2C<IntT,RealT>;
template class BufferAccess3dIter3C<IntT,RealT,ByteT>;
