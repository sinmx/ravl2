// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: RealYUVValue.cc 130 2001-05-24 22:50:53Z ees1se $"
//! lib=RavlImage
//! file="Ravl/Image/Base/RealDVSYUVValue.cc"

#include "Ravl/BinStream.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/RealYUVValue.hh"
#include "Ravl/Image/RealDVSYUVValue.hh"
#include "Ravl/TypeName.hh"

namespace RavlImageN {
  static TypeNameC type2(typeid(RealDVSYUVValueC),"RealDVSYUVValueC");
  static TypeNameC type3(typeid(ImageC<RealDVSYUVValueC>),"ImageC<RealDVSYUVValueC>");
}
