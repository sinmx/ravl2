// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/RLog.hh"
#include "Ravl/Option.hh"
#include <rlog/rlog.h>

int main(int nargs,char **argv) {
  RavlN::OptionC opt(nargs,argv);
  opt.Check();
  
  //RavlN::RLogInit(false);  
  //RavlN::RLogSubscribe("TestModule");
  
  RavlN::RLogInit("file", "true", "debug");
  
  rInfo("Exiting... ");
  
  return 0;
}
