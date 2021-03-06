// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DISTANCECITYBLOCK_HEADER 
#define RAVL_DISTANCECITYBLOCK_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id: DistanceCityBlock.hh 7581 2010-02-22 11:38:11Z kier $"
//! lib=RavlPatternRec
//! docentry="Ravl.API.Pattern Recognition.Distance"
//! file="Ravl/PatternRec/Distance/DistanceCityBlock.hh"

#include "Ravl/PatternRec/Distance.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Distance city block body.
  // Calculates the sum of the difference of the corresponding vector elements.
  
  class DistanceCityBlockBodyC
    : public DistanceBodyC
  {
  public:
    DistanceCityBlockBodyC()
    {}
    //: Default constructor.

    DistanceCityBlockBodyC(const XMLFactoryContextC &factory);
    //: Construct from XML factory
    
    DistanceCityBlockBodyC(istream &strm);
    //: Load from stream.
    
    DistanceCityBlockBodyC(BinIStreamC &strm);
    //: Load from binary stream.

    virtual bool Save (ostream &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to stream, can be loaded using constructor
    
    virtual RealT Measure(const VectorC &d1,const VectorC &d2) const;
    //: Measure the distance from d1 to d2.
    
    virtual RealT Magnitude(const VectorC &d1) const;
    //: Measure the magnitude of d1.
    
    virtual MatrixC Jacobian (const VectorC &X) const;
    //: Calculates Jacobian matrix at X
    
  };

  //! userlevel=Normal
  //: Distance, City block Metric
  // Calculates the sum of the difference of the corresponding vector elements.
  
  class DistanceCityBlockC
    : public DistanceC
  {
  public:
    DistanceCityBlockC()
      : DistanceC(*new DistanceCityBlockBodyC())
    {}
    //: Default constructor.

    DistanceCityBlockC(const XMLFactoryContextC &factory)
      :  DistanceC(*new DistanceCityBlockBodyC(factory))
    {}
    //: Construct from XML factory
    
    DistanceCityBlockC(istream &strm);
    //: Load from stream.
    
    DistanceCityBlockC(BinIStreamC &strm);
    //: Load from binary stream.
    
  };
  
  inline istream &operator>>(istream &strm,DistanceCityBlockC &obj) {
    obj = DistanceCityBlockC(strm);
    return strm;
  }
  //: Load from a stream.
  // Uses virtual constructor.
  
  inline ostream &operator<<(ostream &out,const DistanceCityBlockC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
  inline BinIStreamC &operator>>(BinIStreamC &strm,DistanceCityBlockC &obj) {
    obj = DistanceCityBlockC(strm);
    return strm;
  }
  //: Load from a binary stream.
  // Uses virtual constructor.
  
  inline BinOStreamC &operator<<(BinOStreamC &out,const DistanceCityBlockC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.

}



#endif
