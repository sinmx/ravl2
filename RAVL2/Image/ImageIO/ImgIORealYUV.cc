// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id: ImgIORealYUV.cc 393 2001-09-17 12:54:55Z craftit $"
//! lib=RavlImageIO
//! file="Ravl/Image/ImageIO/ImgIORealYUV.cc"

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/RealYUVValue.hh"
#include "Ravl/TypeName.hh"
//#include "Ravl/DP/Converter.hh"
//#include "Ravl/Array2dIter2.hh"

namespace RavlImageN {

  void InitImgIORealYUV()
  {}
  
  static TypeNameC type1(typeid(ImageC<RealYUVValueC>),"ImageC<RealYUVValueC>");  
  
  FileFormatStreamC<ImageC<RealYUVValueC> > FileFormatStream_ImageC_RealYUVValueC;
  FileFormatBinStreamC<ImageC<RealYUVValueC> > FileFormatBinStream_ImageC_RealYUVValueC;
}
