// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SOCKET_HEADER
#define RAVL_SOCKET_HEADER 1
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/OS/Network/Socket.hh"
//! lib=RavlNet
//! author="Charles Galambos"
//! example=exSocket.cc
//! date="15/02/2000"
//! docentry="Ravl.OS.Network"

#include "Ravl/String.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/OS/SktError.hh"

// Some forward declarations to avoid including extra header
// files.

struct sockaddr_in;
struct sockaddr;

namespace RavlN {

  class SocketC;

  //! userlevel=Develop
  //: Socket connection body class.
  // For dealing with low level stream sockets.
  
  class SocketBodyC 
    : public RCBodyC
  {
  public:
    SocketBodyC(StringC name,bool server = false);
    //: Open socket.
    // The 'name' has the format  'host:port' where port may be a
    // host name or its ip (dotted numbers) address and port is the 
    // number of the port to use.
    
    SocketBodyC(StringC name,UIntT portno,bool server = false);
    //: Open socket.
    
    SocketBodyC(struct sockaddr *addr,int nfd,bool server = false);
    //: Open socket.
    
    ~SocketBodyC();
    //: Open socket.
    
    int Fd() const
    { return fd; }
    //: Access file descriptor.
    
    bool IsOpen() const
    { return fd >= 0; }
    //: Test if socket is open.
    
    SocketC Listen(bool block = true,int backLog = 1);
    //: Listen for a connection from a client.
    // Can only be used on server sockets.
    // If block is true, the call will not return until there
    // is a valid client.
    
    void Close();
    //: Close the socket.
    
    void SetDontClose(bool ndontClose)
    { dontClose = ndontClose; }
    //: Setup don't close flag.
    
    StringC ConnectedHost();
    //: Get the name of the host at the other end of the connection.
    
    IntT ConnectedPort();
    //: Get the port number at the other end of the connection.
    
    void SetNoDelay();
    //: Send data as soon as possible. 
    // Don't gather data into larger packets. 
    // This should make transactions faster at the expense of sending more 
    // packets over the network.
    
  protected:
    bool GetHostByName(const char *name,struct sockaddr_in &sin);
    //: Attempt to get info about named host.
    // returns true on success.
    
    bool GetHostByAddr(struct sockaddr &sin,int sinLen,StringC &name);
    //: Attempt to find hostname by the address.
    // returns true on success and assignes the hostname to name.
    
    int OpenSocket(struct sockaddr_in &sin,IntT sockNo);
    //: Open a socket to the given address / port no.
    
    int OpenClient(const char *name,IntT sockNo);
    //: Open a client socket.
    
    int OpenServer(const char *name,IntT sockNo);
    //: Open a server socket.
    // Its then ready for listening.
    
    int fd;
    bool server;
    struct sockaddr *addr; // Allocated as a char array.
    bool dontClose;
  };
  
  
  //! userlevel=Normal
  //: Socket connection handle.
  // For dealing with low level stream sockets.
  
  class SocketC 
    : public RCHandleC<SocketBodyC>
  {
  public:
    SocketC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
    SocketC(StringC address,bool server = false)
      : RCHandleC<SocketBodyC>(*new SocketBodyC(address,server))
    {}
    //: Open socket.
    // The 'address' has the format  'host:port' where port may be a
    // host name or its ip (dotted numbers) address and port is the 
    // number of the port to use.
    
    SocketC(StringC host,UIntT portno,bool server = false)
      : RCHandleC<SocketBodyC>(*new SocketBodyC(host,portno,server))
    {}
    //: Open socket.
    // 'host' is the host name to connect to or its ip address (dotted numbers)
    // 'port' is the port number to use.
    
  protected:
    SocketC(struct sockaddr *addr,int nfd,bool server = false)
      : RCHandleC<SocketBodyC>(*new SocketBodyC(addr,nfd,server))
    {}
    //: Open socket.
    
    SocketBodyC &Body()
    { return RCHandleC<SocketBodyC>::Body(); }
    //: Access body.
    
    const SocketBodyC &Body() const
    { return RCHandleC<SocketBodyC>::Body(); }
    //: Access body.
    
  public:
    int Fd() const
    { return Body().Fd(); }
    //: Access file descriptor.
    
    bool IsOpen() const
    { return Body().IsOpen(); }
    //: Test if socket is open.
    
    inline SocketC Listen(bool block = true,int backLog = 1)
    { return Body().Listen(block,backLog); }
    //: Listen for a connection from a client.
    // Can only be used on server sockets. <br>
    // If block is true, the call will not return until there
    // is a valid client. <br>
    // 'backLog' is the maximum number of connects that will be kept pending, between calls
    // to Listen().
    
    void Close()
    { Body().Close(); }
    //: Close the socket.
    
    void SetDontClose(bool ndontClose)
    { Body().SetDontClose(ndontClose); }
    //: Setup don't close flag.
    
    StringC ConnectedHost()
    { return Body().ConnectedHost(); }
    //: Get host name 
    
    IntT ConnectedPort()
    { return Body().ConnectedPort(); }
    //: Get other port number.
    
    void SetNoDelay()
    { Body().SetNoDelay(); }
    //: Send data as soon as possible. 
    // Don't gather data into larger packets. 
    // This should make transactions faster at the expense of sending more 
    // packets over the network.
    
    friend class SocketBodyC;
  };
  
}
#endif
