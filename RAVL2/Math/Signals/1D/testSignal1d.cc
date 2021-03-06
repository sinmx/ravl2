// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: testSignal1d.cc 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlMath
//! file="Ravl/Math/Signals/1D/testSignal1d.cc"
//! author="Charles Galambos"
//! docentry="Ravl.API.Math.Signals.1D"
//! userlevel=Develop

#include "Ravl/Convolution1d.hh"
#include "Ravl/Correlation1d.hh"
#include "Ravl/FFT1d.hh"
#include "Ravl/Array1dIter2.hh"

using namespace RavlN;

int testConvolve();
int testCorrelate();
int testfft();

int main()
{
  int ln;
  if((ln = testfft()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testConvolve()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  if((ln = testCorrelate()) != 0) {
    cerr << "Test failed at " << ln << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

int testfft() {
  cerr << "Testing fft. \n";
  Array1dC<RealT> x(16);
  x.Fill(0);
  x[4] = 2;
  x[5] = 1;
  FFT1dC fft(x.Size());
  Array1dC<ComplexC> res = fft.Apply(x);
  FFT1dC ifft(x.Size(),true);
  Array1dC<ComplexC> res2= ifft.Apply(res);
  if(res2.Size() != x.Size()) return __LINE__;
  for(Array1dIter2C<ComplexC,RealT> it(res2,x);it;it++) {
    if(Abs(it.Data1().Re()) > 0.000001)
      cerr << it.Data1().Re() << ":";
    else
      cerr << "0:";
    
    if(Abs(it.Data1().Im()) > 0.000001)
      cerr << it.Data1().Im() << " ";
    else
      cerr << "0 ";
    
    if(Abs(it.Data1().Re() - it.Data2()) > 0.000000001) return __LINE__;
    if(Abs(it.Data1().Im()) > 0.000000001) return __LINE__;
  }
  return 0;
}

int testConvolve() {
  cerr << "Testing Convolution. \n";
  Array1dC<RealT> x(3),y(2);
  UIntT i;
  for(i = 1;i <= y.Size();i++)
    y[i-1]= i;

  for(i = 1;i <= x.Size();i++)
    x[i-1]= i;
  
  Array1dC<RealT> res = Convolve1d(x,y);
  if(res.Size() != 2) return __LINE__;
  if(Abs(res[0] - 4) > 0.0000001) return __LINE__;
  if(Abs(res[1] - 7) > 0.0000001) return __LINE__;
  return 0;
}

int testCorrelate() {
  cerr << "Testing Correlation. \n";
  Array1dC<RealT> arr1(8);
  Array1dC<RealT> arr2(8);
  arr1.Fill(0);
  arr2.Fill(0);
  arr1[6] = 1;
  arr2[5] = 1;
  //arr2[2] = 1;
  Correlation1dC corr(8);
  Array1dC<RealT> res = corr.Apply(arr1,arr2);
  cerr << "Correlation:\n";
  cerr << res;
  return 0;
}
