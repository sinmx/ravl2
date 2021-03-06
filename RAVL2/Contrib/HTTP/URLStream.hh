// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, James Smith
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_URLISTREAM_HEADER
#define RAVL_URLISTREAM_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id: URLStream.hh 6226 2007-06-27 10:29:57Z craftit $"
//! lib=RavlURLIO
//! author="James Smith"
//! docentry="Ravl.API.Core.IO.URL Handling"
//! file="Ravl/Contrib/HTTP/URLStream.hh"
//! date="30/10/2002"

#include "Ravl/Stream.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/OS/Filename.hh"

namespace RavlN {
  
  IntT URLRetrieve(const StringC &url,SArray1dC<char> &buf);
  //: Retrieve file into a byte array.
  //!param:url - URL to retrieve
  //!param:buf - buffer to store data into.
  //!return: Error code, 0 if all's well.

  IntT URLRetrieve(const StringC &url,const StringC &user,const StringC &passwd,SArray1dC<char> &buf);
  //: Retrieve file into a byte array.
  //!param:url - URL to retrieve
  //!param:user - Username
  //!param:passwd - Password
  //!param:buf - buffer to store data into.
  //!return: Error code, 0 if all's well.
  
  //:-
  
  ////////////////////////////
  //! userlevel=Normal
  //: Get a URL
  
  class URLIStreamC 
    : public IStreamC
  {
  public:

    URLIStreamC()
    {}
    //: Default constructor
    
    URLIStreamC(const StringC &url,bool buffered=true);
    //: Open net connection for input
    
    URLIStreamC(const StringC &url,const StringC &user,const StringC &password);
    //: Open net connection for input.
    //: Uses Basic http authentication with the given username and password. 
    
    ~URLIStreamC();
    //: Destructor

    IntT Error() const {return m_iError;}
    //: Get CURL error code

    StringC ErrorString() const;
    //: Get a string describing the error

    static StringC URLEncode(const StringC& string);
    //: URL-encode a string
    // All non-alphnumeric characters will be converted to %XX format,
    // i.e. "hello world" becomes "hello%20world".
    // Do not use this on complete URLs, as special URL characters will be coded as well.
    // This is really useful for encoding passwords and things to be sent as part of a URL.

    static StringC AddUserPass(const StringC& url, const StringC& user, const StringC& pass);
    //: Inserts username and password into the appropriate place in the URL. 
    // Also encodes them as required.

  protected:

    FilenameC m_strTemp;
    
    IntT m_iError;

  };
  
}


#endif
