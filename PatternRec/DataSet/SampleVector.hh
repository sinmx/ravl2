// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SAMPLEVECTOR_HEADER
#define RAVL_SAMPLEVECTOR_HEADER 1
//! rcsid="$Id$"
//! author="Kieron Messer"
//! docentry="Ravl.Pattern Recognition.Data Set"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/SampleVector.hh"

#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/Vector.hh"

namespace RavlN {
  
  class MeanCovarianceC;  
  
  //! userlevel=Normal
  //: Sample of vectors.
  
  class SampleVectorC
    : public SampleC<VectorC>
  {
    
  public:
    SampleVectorC(SizeT maxSize=10)
      : SampleC<VectorC>(maxSize)
    {}
    //: Create a sample of data with a maximum size
    
    SampleVectorC(const SArray1dC<VectorC> & dat)
      : SampleC<VectorC>(dat)
    {}
    //: Create a sample of data from an array
    
    SampleVectorC(const SampleC<VectorC> &svec)
      : SampleC<VectorC>(svec)
    {}
    //: Construct from base class.
    
    VectorC Mean() const;
    //: Find the mean vector of the sample.
    
    MeanCovarianceC MeanCovariance() const;
    //: Find the mean and covariance of the sample
  }; 
  
}

#endif
