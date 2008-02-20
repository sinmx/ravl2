// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html


%include "Ravl/Swig/Types.i"
%include "Ravl/Swig/Index2d.i"

%{
#undef Copy
#include "Ravl/IndexRange2d.hh"
#define Copy(s,d,n,t)   (MEM_WRAP_CHECK_(n,t) (void)memcpy((char*)(d),(const char*)(s), (n) * sizeof(t)))
%}

namespace RavlN {

  class IndexRange2dC {
  public:
    IndexRange2dC();
    IntT Rows() const;
    IntT Cols() const;
    SizeT Area() const;
    bool Contains(Index2dC index) const;
    IndexRange2dC Expand(IntT n) const;
    void ClipBy(IndexRange2dC range);
  };
}
