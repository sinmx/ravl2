// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath
//! file="Ravl/Math/Statistics/MeanCovariance/MeanVariance.cc"

#include "Ravl/MeanVariance.hh"
#include "Ravl/Statistics.hh"
#include "Ravl/SArr1Iter.hh"
#include "Ravl/StdConst.hh"
#include "Ravl/StdMath.hh"

namespace RavlN {
  
  //: Calculate the mean and variance from an array of numbers.
  
  MeanVarianceC::MeanVarianceC(const SArray1dC<RealT> &data) {
    n = data.Size();
    mean = 0;
    var = 0;
    for(SArray1dIterC<RealT> it(data);it;it++) {
      mean += *it;
      var += Sqr(*it);
    }
    mean /= (RealT) n;
    var = (var - Sqr(mean)/(RealT)n)/((RealT)n-1);
  }

  //: Add another MeanVariance to this one.
  
  MeanVarianceC &MeanVarianceC::operator+=(const MeanVarianceC &mv) {
    if(mv.Number() == 0)
      return *this;
    const RealT number1 = (RealT) Number();
    const RealT number2 = (RealT) mv.Number();
    const RealT nDen    = number1 + number2;
    const RealT p1 = number1 / nDen;
    const RealT p2 = number2 / nDen;
    
    var *= p1;
    var += mv.Variance() * p2;
    var += ((mv.Mean() - Mean()) * p1*p2);
    
    // Update the mean.
    mean = mean * p1 + mv.Mean() * p2;
    n += mv.Number();
    return *this;
  }

  //: Remove another MeanVariance from this one.
  
  MeanVarianceC &MeanVarianceC::operator-=(const MeanVarianceC &mv) { 
    if(mv.Number() == 0)
      return *this;
    const RealT number1 = (RealT) Number();
    const RealT number2 = (RealT) mv.Number();
    const RealT nDen    = number1 - number2;
    const RealT p1 = nDen / number1;
    const RealT p2 = number2 / number1;
    
    // Update the mean.
    mean = (mean - mv.Mean() * p2) / p1 ;
    
    // Update the variance.
    var -= ((mv.Mean() - Mean()) * p1*p2);
    var -= mv.Variance() * p2;
    var /= p1;
    
    n -= mv.Number();
    return *this;
  }
  
  //: Value of the gauss distribution at x.
  
  RealT MeanVarianceC::Gauss(RealT x) {
    RealT sig = Sqrt(var);
    return Exp(-0.5 * Sqr((x-mean)/sig)) /(sig * RavlConstN::sqrt2Pi);
  }

  //: Find the probability of getting a sample with value 'at' +/- delta.
  
  RealT MeanVarianceC::Probability(RealT low,RealT high) {
    RealT sig = Sqrt(var);
    return (StatNormalQ(low/sig) - StatNormalQ(high/sig))/sig;
  }
  

  ostream& operator<<(ostream &s,const MeanVarianceC &mv) {
    s << mv.Number() << ' ' << mv.Mean() << ' ' << mv.Variance();
    return s;
  }

  istream& operator>>(istream &s, MeanVarianceC &mv) {
    SizeT n;
    RealT v1,v2;
    s >> n >> v1 >> v2;
    mv = MeanVarianceC(n,v1,v2);
    return s;
  }
  
}
