// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlVDF
//! author="Charles Galambos"

#include "Ravl/DF/DFPump.hh"
#include "Ravl/DF/GUIView.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlDFN {
  
  DFPumpBodyC::DFPumpBodyC(const StringC &nname,const DPIOConnectBaseC &ndata)
    : DFStreamOpBodyC(nname,ndata),
      connect(ndata)
  {}
  
  //: Render object to view.
  
  bool DFPumpBodyC::Render(GUIViewBodyC &view,const Index2dC &at,DFRenderModeT mode) {
    return DFStreamOpBodyC::Render(view,at,mode);
  }

}
