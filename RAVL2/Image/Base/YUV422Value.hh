// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_YUV422VALUE_HEADER
#define RAVLIMAGE_YUV422VALUE_HEADER 1
////////////////////////////////////////////////////////////////////
//! rcsid="$Id: YUV422Value.hh 6965 2008-09-18 16:48:28Z ees1wc $"
//! lib=RavlImage
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.API.Images.Pixel Types.YCbCr"
//! file="Ravl/Image/Base/YUV422Value.hh"

#include "Ravl/TFVector.hh"
#include "Ravl/Traits.hh"

namespace RavlImageN {
  using namespace RavlN;
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using RavlN::TFVectorC;
  using RavlN::BinIStreamC;
  using RavlN::BinOStreamC;
#endif
  
  //! userlevel=Normal
  //: YUV422 Pixel base class.
  // Pixels even image columns contain U and odd columns V
  
  template<class CompT>
  class YUV422ValueC 
    : public TFVectorC<CompT,2>
  {
  public:
    YUV422ValueC()
    {}
    //: Default constructor.
    // Contents of pixels are left undefined.
    
    YUV422ValueC(const CompT &uv,const CompT &y)
    { this->data[0] =uv; this->data[1] = y; }
    //: Construct from components.
    
    inline const CompT &UV() const
    { return (*this)[0]; }
    //: Access u or v component.
    
    inline CompT &UV()
    { return (*this)[0]; }
    //: Access u or v component.
    
    inline const CompT &Y() const
    { return (*this)[1]; }
    //: Access Y component.
    
    inline CompT &Y()
    { return (*this)[1]; }
    //: Access Y component.
    
  };

  
  template<class CompT>
  inline
  istream &operator>>(istream &strm,YUV422ValueC<CompT> &val) 
  { return strm >> ((TFVectorC<CompT,2> &)(val)); }
  //: Stream input.
  
  template<class CompT>
  inline
  ostream &operator<<(ostream &strm,const YUV422ValueC<CompT> &val) 
  { return strm << ((const TFVectorC<CompT,2> &)(val)); }
  //: Stream output.
  
  template<class CompT>
  inline
  BinIStreamC &operator>>(BinIStreamC &strm,YUV422ValueC<CompT> &val) 
  { return strm >> ((TFVectorC<CompT,2> &)(val)); }
  //: Binary stream input.
  
  template<class CompT>
  inline
  BinOStreamC &operator<<(BinOStreamC &strm,const YUV422ValueC<CompT> &val) 
  { return strm << ((const TFVectorC<CompT,2> &)(val)); }
  //: Binary stream output

}

namespace RavlN {
  
  //! userlevel=Advanced
  //: Traits for type
  
  template<typename PixelT>
  struct NumericalTraitsC<RavlImageN::YUV422ValueC<PixelT> > {
    typedef RavlImageN::YUV422ValueC<typename NumericalTraitsC<PixelT>::AccumT> AccumT;    //: Type to use for accumulator, guarantee's at least 2x no bits for interger types.
    typedef RavlImageN::YUV422ValueC<typename NumericalTraitsC<PixelT>::RealAccumT> RealAccumT; //: Type to use for a floating point accumulator.
    typedef RavlImageN::YUV422ValueC<typename NumericalTraitsC<PixelT>::LongAccumT> LongAccumT; //: Type to use for accumulators that can take large sums.(10000's of elements at least.)
  };
}

#endif
