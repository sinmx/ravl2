// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FUNCLINEARCOEFF_HEADER
#define RAVL_FUNCLINEARCOEFF_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! date="21/4/1998"
//! author="Robert Crida and Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Numerical Modeling"

#include "Ravl/PatternRec/Function.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Function with linear coeffiecents.
  
  class FuncLinearCoeffBodyC
    : public FunctionBodyC
  {
  public:
    FuncLinearCoeffBodyC();
    //: Default constructor.
    
    FuncLinearCoeffBodyC(UIntT inSize,UIntT outSize)
      : FunctionBodyC(inSize,outSize)
    {}
    //: Create a function with the given number of inputs and outputs.
    
    virtual VectorC Apply(const VectorC &data) const;
    //: Apply function to 'data'
    
    virtual MatrixC Jacobian (const VectorC &X) const;
    //: Calculate Jacobian matrix at X
    
    virtual VectorC MakeInput (const VectorC &X) const;
    //: Expand vector to linear coefficients.
    
    virtual VectorC MakeJacobianInput (const VectorC &X, IntT i) const;
    //: Expand vector to linear coefficients.
    
    virtual UIntT NumberCoeffs(UIntT inputSize) const;
    //: Calculate the number of coefficents for a given input size.

    bool SetTransform(const MatrixC &a);
    //: Attempt to set transform matrix.
  protected:
    MatrixC a;
  };

  //! userlevel=Develop
  //: Function with linear coeffiecents.
  
  class FuncLinearCoeffC
    : public FunctionC
  {
  public:
    FuncLinearCoeffC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
  protected:
    FuncLinearCoeffC(FuncLinearCoeffBodyC &bod)
      : FunctionC(bod)
    {}
    //: Body constructor.
    
    FuncLinearCoeffBodyC &Body()
    { return static_cast<FuncLinearCoeffBodyC &>(FunctionC::Body()); }
    //: Access body.
    
    const FuncLinearCoeffBodyC &Body() const
    { return static_cast<const FuncLinearCoeffBodyC &>(FunctionC::Body()); }
    //: Access body.
    
  public:
    bool SetTransform(const MatrixC &a)
    { return Body().SetTransform(a); }
    //: Attempt to set transform matrix.
    
    VectorC MakeInput(const VectorC &X) const
    { return Body().MakeInput(X); }
    //: Expand vector to linear coefficients.
    
    VectorC MakeJacobianInput (const VectorC &X, IntT i) const
    { return Body().MakeJacobianInput(X,i); }
    //: Expand vector to linear coefficients.
    
    UIntT NumberCoeffs(UIntT inputSize) const
    { return Body().NumberCoeffs(inputSize); }
    //: Calculate the number of coefficents for a given input size.
    
  };
  
}
#endif
