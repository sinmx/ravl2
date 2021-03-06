// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLFFT1D_HEADER
#define RAVLFFT1D_HEADER 1
////////////////////////////////////////////////////////////////////
//! rcsid="$Id: FFT1d.hh 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlMath
//! file="Ravl/Math/Signals/1D/FFT1d.hh"
//! example=exFFT1d.cc
//! author="Charles Galambos"
//! docentry="Ravl.API.Math.Signals.1D"

#include "Ravl/RefCounter.hh"
#include "Ravl/Complex.hh"
#include "Ravl/Array1d.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Interface class for 1d FFTW
  
  class FFT1dBodyC
    : public RCBodyC
  {
  public:
    FFT1dBodyC(int n,bool iinv,bool zeroPad = false);
    //: Constructor.
    
    ~FFT1dBodyC();
    //: Destructor
    
    bool Init(int n,bool iinv);
    //: Create a plan with the given setup.
    
    Array1dC<ComplexC> Apply(const Array1dC<ComplexC> &dat);
    //: Apply transform to array.
    // Note, only the first 'n' byte of dat are proccessed.
    // if the array is shorter than the given length, an
    // exception 'ErrorOutOfRangeC' will be thrown.
    
    Array1dC<ComplexC> Apply(const Array1dC<RealT> &dat);
    //: Apply transform to real array 
    // Note, only the first 'n' byte of dat are proccessed.
    // if the array is shorter than the given length, an
    // exception 'ErrorOutOfRangeC' will be thrown.
    
    IntT N() const
      { return n; }
    //: The size of the transform.
    
    bool IsZeroPad() const
    { return zeroPad; }
    //: Test if we're doing zero padding.
    
  protected:
    IntT n;  // Size of the transform.
    bool inv; // Is the transform backward ??
    bool pwr2; // Is length a power of two ?
    bool zeroPad; // Zero pad input to 'n' bytes ?
    int primeFactors[32];
    int nf; // Number of factors. Sufficent for all 32-bit lengths.
  };
  
  //! userlevel=Normal
  //: Handle to 1d FFT.
  
  class FFT1dC
    : public RCHandleC<FFT1dBodyC>
  {
  public:
    FFT1dC()
      {}
    //: Default constructor.
    
    FFT1dC(int n,bool iinv = false,bool zeroPad = false)
      : RCHandleC<FFT1dBodyC>(*new FFT1dBodyC(n,iinv,zeroPad))
      {}
    //: Create a fft class.
    // If iinv is true do an inverse transform
    
    bool Init(int n,bool iinv = false)
    { return Body().Init(n,iinv); }
    //: Create a plan with the given setup.
    
    Array1dC<ComplexC> Apply(const Array1dC<ComplexC> &dat)
      { return Body().Apply(dat); }
    //: Apply transform to array.
    // Note, only the first 'n' byte of dat are proccessed.
    // if the array is shorter than the given length, an
    // exception 'ErrorOutOfRangeC' will be thrown.
    
    Array1dC<ComplexC> Apply(const Array1dC<RealT> &dat)
      { return Body().Apply(dat); }
    //: Apply transform to real array 
    // Note, only the first 'n' byte of dat are proccessed.
    // if the array is shorter than the given length, an
    // exception 'ErrorOutOfRangeC' will be thrown.
    
    IntT N() const
      { return Body().N(); }
    //: The size of the transform.
    
    bool IsZeroPad() const
    { return Body().IsZeroPad(); }
    //: Test if we're doing zero padding.
    
  };

}

#endif
