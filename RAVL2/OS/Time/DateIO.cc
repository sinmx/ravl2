// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////
//! rcsid="$Id: DateIO.cc 7680 2010-04-06 10:08:11Z craftit $"
//! lib=RavlOS
//! file="Ravl/OS/Time/DateIO.cc"

#include "Ravl/OS/Date.hh"
#include "Ravl/BinStream.hh"

namespace RavlN {
  
  //: Stream operator.
  
  BinOStreamC &operator <<(BinOStreamC &strm,const DateC &date) {
    strm << ((Int64T) date.TotalSeconds()) << ((Int32T) date.USeconds());
    return strm;
  }
  
  //: Stream operator.
  
  BinIStreamC &operator >>(BinIStreamC &strm,DateC &date) {
    Int64T v1;
    Int32T v2;
    strm >> v1 >> v2;
    date = DateC(v1,v2);
    return strm;
  }
}
