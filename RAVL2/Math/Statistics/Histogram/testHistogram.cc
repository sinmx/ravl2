// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: testHistogram.cc 6188 2007-06-08 10:42:33Z ees1wc $"
//! lib=RavlMath
//! file="Ravl/Math/Statistics/Histogram/testHistogram.cc"
//! author="Charles Galambos"
//! docentry="Ravl.API.Math.Statistics.Histogram"
//! userlevel=Develop

#include "Ravl/Histogram.hh"
#include "Ravl/RealHistogram1d.hh"
#include "Ravl/RealHistogram2d.hh"
#include "Ravl/RealHistogram3d.hh"
#include "Ravl/Parzen.hh"

using namespace RavlN;

int testBasic();
int testCompare();
int testRealHistogram1d();
int testRealHistogram2d();
int testRealHistogram3d();
int testParzen();

int main() {
  int ln;
  
  if((ln = testBasic()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testCompare()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testRealHistogram1d()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testRealHistogram2d()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testRealHistogram3d()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testParzen()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  cerr << "Test passed. \n";
  return 0;
}

int testBasic() {
  HistogramC<int> h1;
  if(h1.Size() != 0) return __LINE__;
  if(h1.Vote(1) != 1) return __LINE__;
  if(h1.Vote(2) != 1) return __LINE__;
  if(h1.Vote(2) != 2) return __LINE__;
  if(h1.Vote(3) != 1) return __LINE__;
  if(h1.Size() != 3) return __LINE__;
  if(h1.Total() != 4) return __LINE__;
  if(Abs(h1.Information() - 1.5) > 0.00000001) return __LINE__;
  if(Abs(h1.Energy() - 0.375) > 0.00000001) return __LINE__;  
  return 0;
}

int testCompare() {
  HistogramC<int> h1,h2;
  h1.Vote(1,2);
  h1.Vote(2,3);
  h1.Vote(3,1);
  if(h1.Total() != 6) return __LINE__;
  h2.Vote(2,1);
  h2.Vote(3,4);
  h2.Vote(4,2);
  if(h2.Total() != 7) return __LINE__;
  if(h1.SumIntersection(h2) != 2) return __LINE__;
  if(h2.SumIntersection(h1) != 2) return __LINE__;
  
  int key = -2;
  int ldiff = -2;
  UIntT c = h1.LargestDifference(h2,key,ldiff);
  if(c != 1) return __LINE__;
  if(key != 3) return __LINE__;
  if(ldiff != 3) return __LINE__;
  c = h2.LargestDifference(h1,key,ldiff);
  if(c != 1) return __LINE__;
  if(key != 3) return __LINE__;
  if(ldiff != 3) return __LINE__;
  return 0;
}

int testRealHistogram1d() {
  RealHistogram1dC rhist(0,1,100);
  rhist.Vote(1);
  rhist.Vote(0);
  rhist.CheckVote(23);
  if(rhist.TotalVotes() != 2) return __LINE__;
  Array1dC<RealT> a(16);
  a.Fill(0.6);
  a[12] = 1.6;
  if (rhist.ArrayVote(a)) return __LINE__;
  if(rhist.TotalVotes() != 17) return __LINE__;
  if (rhist[rhist.Bin(0.6)] != 15) return __LINE__;
  return 0;
}

int testRealHistogram2d() {
  RealHistogram2dC rhist(Point2dC(0,0),Point2dC(10,10),Index2dC(100,100));
  rhist.Vote(Point2dC(10,10));
  rhist.Vote(Point2dC(0,0));
  rhist.Vote(Point2dC(5,5));
  if(rhist.TotalVotes() != 3) return __LINE__;
  return 0;
}
int testRealHistogram3d() {
  RealHistogram3dC rhist(Point3dC(0,0,0),Point3dC(10,10,10),Index3dC(100,100,100));
  rhist.Vote(Point3dC(10,10,10));
  rhist.Vote(Point3dC(0,0,0));
  rhist.Vote(Point3dC(5,5,5));
  if(rhist.TotalVotes() != 3) return __LINE__;
  return 0;
}

int testParzen() {
  Array1dC<RealT> a(16);
  a.Fill(0.6);
  a[12] = 1.6;
  ParzenWindowC p(a, 3.2);
  if(Abs(p.PdfEstimate(1.0)-0.25446761)>10e-8) return __LINE__;
  return 0;
}
