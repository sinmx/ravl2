// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_IMAGECONV_HEADER
#define RAVLIMAEG_IMAGECONV_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/ImageIO/ImageConv.hh"
//! lib=RavlImageIO
//! userlevel=Normal
//! author="Charles Galambos"
//! date="16/03/1999"
//! docentry="Ravl.Images.Converters"

#include "Ravl/Image/Image.hh"

namespace RavlImageN {

  class ByteYUVValueC;
  class ByteYUVAValueC;
  class ByteYUV422ValueC;
  class ByteVYUValueC;
  class RealYUVValueC;
  class ByteRGBValueC;
  class RealRGBValueC;
  class ByteRGBAValueC;
  class ByteRGBMedianC;
  class RealRGBAverageC;
  class UInt16RGBValueC;
  class RealHSVValueC ; 

  ImageC<ByteRGBValueC> ByteRGBAImageCT2ByteRGBImageCT(const ImageC<ByteRGBAValueC> &dat);
  //: Byte RGBA to Byte RGB image
  
  ImageC<ByteRGBAValueC> ByteRGBImageCT2ByteRGBAImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte RGB to Byte RGBA image
  
  ImageC<RealT> ByteImageCT2DoubleImageCT(const ImageC<ByteT> &dat);
  //: Byte to double image.
    
  ImageC<IntT> ByteImageCT2IntImageCT(const ImageC<ByteT> &dat);
  //: Byte to int image.
  
  ImageC<RealT> IntImageCT2DoubleImageCT(const ImageC<IntT> &dat);
  //: Int to double image.
  
  ImageC<ByteRGBValueC> ByteImageCT2ByteRGBImageCT(const ImageC<ByteT> &dat);
  //: Byte grey level to colour image.
    
  ImageC<ByteYUVValueC> ByteImageCT2ByteYUVImageCT(const ImageC<ByteT> &dat);
  // Byte grey level to byte YUV colour image.
  
  ImageC<ByteT> DoubleImageCT2ByteImageCT(const ImageC<RealT> &dat) ; 
  //: Double -> Byte (clipped to fit)
  // This will clip, then round the double value (NOT floor!) to fit in a byte value 0 to 255.
  
  ImageC<RealRGBValueC> RealYUVImageCT2RealRGBImageCT(const ImageC<RealYUVValueC> &dat);
  //: Real YUV -> RGB
  
  ImageC<RealYUVValueC> RealRGBImageCT2RealYUVImageCT(const ImageC<RealRGBValueC> &dat);
  //: Real RGB -> YUV

  ImageC<ByteT> ByteYUVImageCT2ByteImageCT(const ImageC<ByteYUVValueC> &dat);
  //: Byte grey level to byte YUV colour image.
  
  ImageC<ByteT> RGBImageCT2ByteImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte colour to byte grey image.
  
  ImageC<RealT> RGBImageCT2DoubleImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte Colour to double image.
  
  ImageC<ByteRGBValueC> YUVImageCT2RGBImageCT(const ImageC<ByteYUVValueC> &dat);
  //: Byte YUV to byte RGB image.
  
  ImageC<ByteYUVValueC> RGBImageCT2YUVImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte RGB to byte YUV image.

  ImageC<ByteRGBValueC>  RealRGBAverageImageC2ByteRGBImageCT(const ImageC<RealRGBAverageC> &dat);
  //: Real RGB rolling average -> RGB

  ImageC<ByteRGBValueC>  ByteRGBMedianImageC2ByteRGBImageCT(const ImageC<ByteRGBMedianC> &dat);
  //: Byte RGB median -> RGB

  ImageC<RealRGBValueC>  ByteRGBImageCT2RealRGBImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte RGB -> Real RGB

  ImageC<ByteRGBValueC>  RealRGBImageCT2ByteRGBImageCT(const ImageC<RealRGBValueC> &dat);
  //: Real RGB -> Byte RGB

  ImageC<UInt16RGBValueC> ByteRGBImageCT2UInt16RGBImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte RGB -> UInt16 RGB

  ImageC<ByteRGBValueC>  UInt16RGBImageCT2ByteRGBImageCT(const ImageC<UInt16RGBValueC> &dat);
  //: UInt16 RGB -> Byte RGB

  ImageC<ByteYUVValueC> ByteYUVAImageCT2ByteYUVImageCT(const ImageC<ByteYUVAValueC> &dat);
  //: YUVA -> YUV
  
  ImageC<ByteYUVAValueC> ByteYUVImageCT2ByteYUVAImageCT(const ImageC<ByteYUVValueC> &dat);
  //: YUV -> YUVA
  
  ImageC<RealYUVValueC> ByteYUVImageCT2RealYUVImageCT(const ImageC<ByteYUVValueC> &dat);
  //: Byte YUV -> Read YUV
  
  ImageC<ByteYUVValueC> RealYUVImageCT2ByteYUVImageCT(const ImageC<ByteYUVValueC> &dat);
  //: Real YUV -> Byte YUV
  
  ImageC<ByteT> BoolImageC2ByteImageCT(const ImageC<bool> &dat);
  //: Boolean Image -> Byte Image
  
  ImageC<ByteYUVValueC> ByteVYUImageCT2ByteYUVImageCT(const ImageC<ByteVYUValueC> &dat);
  //: Byte VYU -> Byte YUV
  
  ImageC<ByteVYUValueC> ByteYUVImageCT2ByteVYUImageCT(const ImageC<ByteYUVValueC> &dat);
  //: Byte YUV -> Byte VYU
  
  ImageC<ByteYUVValueC> ByteYUV422ImageCT2ByteYUVImageCT(const ImageC<ByteYUV422ValueC> &dat);
  //: Byte YUV422 -> Byte YUV
  
  ImageC<ByteRGBValueC> ByteYUV422ImageCT2ByteRGBImageCT(const ImageC<ByteYUV422ValueC> &dat);
  //: Byte YUV -> Byte YUV422
  
  ImageC<ByteT> ByteYUV422ImageCT2ByteImageCT(const ImageC<ByteYUV422ValueC> &dat);
  //: Byte YUV422 -> Byte
  
  ImageC<ByteYUV422ValueC> ByteImageCT2ByteYUV422ImageCT(const ImageC<ByteT> &dat);
  //: Byte -> Byte YUV422

  ImageC<ByteYUV422ValueC> ByteRGBImageCT2ByteYUV422ImageCT(const ImageC<ByteRGBValueC> &dat);
  //: Byte RGB -> Byte YUV422

  ImageC<RealT> UIntTImageCT2DoubleImageCT(const ImageC<UIntT> &dat);
  //: UIntT -> RealT

  ImageC<UIntT> UInt16TImageCT2UIntTImageCT(const ImageC<UInt16T> &dat);
  //: UInt16T -> UIntT

  ImageC<UInt16T> UIntTImageCT2UInt16TImageCT(const ImageC<UIntT> &dat);
  //: UIntT -> UInt16T

  ImageC<RealHSVValueC> RealRGBImageCT2RealHSVImageCT(const ImageC<RealRGBValueC> & dat) ;
  //: Real RGB -> Real HLS 
  
  ImageC<RealRGBValueC> RealHSVImageCT2RealRGBImageCT(const ImageC<RealHSVValueC> & dat) ;
  //: Real HLS -> Real RGB

};

#endif
