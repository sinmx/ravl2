// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! rcsid="$Id: exSocket.cc 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlNet
//! file="Ravl/OS/Network/exSocket.cc"
//! author="Charles Galambos"
//! date="15/02/2000"
//! docentry="Ravl.API.OS.Network"
//! userlevel=Normal

#include "Ravl/Option.hh"
#include "Ravl/OS/NetStream.hh"
#include "Ravl/OS/Date.hh"

using namespace RavlN;

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  StringC name = opt.String("n","localhost:4041","Where to connect to.");
  StringC file = opt.String("d","-","Data file");
  bool server = opt.Boolean("s",false,"Server. ");
  bool buffer = opt.Boolean("b",false,"Buffer. ");
  bool listen = opt.Boolean("l",false,"Listen to stream. ");
  opt.Check();
  
  cerr << "Setting up.\n";
  if(listen) {
    cerr << "Listening... \n";
    NetIStreamC ns(name,buffer,server);
    if(!ns) {
      cerr << "Failed to open socket. \n";
      return -1;
    }
    cerr << "Remotehost=" << ns.Socket().ConnectedHost() << "\n";
    OStreamC df(file,true);
    cerr << "Copying data. " << ns.good() << "\n";
    while(ns.good()) {
      cerr << "Copied:" << ns.CopyTo(df) << "\n";
    }
    //df.flush();
    //ns << flush;
    cerr << "Done. \n";
  } else {
    cerr << "Sending... \n";
    NetOStreamC ns(name,buffer,server);
    if(!ns) {
      cerr << "Failed to open socket. \n";
      return -1;
    }
    cerr << "Remotehost=" << ns.Socket().ConnectedHost() << "\n";
    IStreamC df(file);
    cerr << "Copying data. " << ns.good() <<"\n";
    cerr << "Copied:" << df.CopyTo(ns) << "\n";
    cerr << "Done. \n";
  }
  return 0;
}
