// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: Index3d.cc 1175 2002-05-21 14:51:59Z craftit $"
//! lib=RavlCore
//! file="Ravl/Core/Base/Index3d.cc"

#include "Ravl/Stream.hh"
#include "Ravl/Index3d.hh"

namespace RavlN {
  
  //====================================================================
  //======= Index3dC ===================================================
  //====================================================================
  
  ostream &
  operator<<(ostream & outS, const Index3dC & index) { 
    outS << index.I() << ' ' << index.J() << ' ' << index.K();
    return outS;
  }
  
  istream & 
  operator>>(istream & inS, Index3dC & index) { 
    inS >> index.I() >> index.J() >> index.K();
    return inS;
  }
  
}
