// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_USERINFO_HEADER
#define RAVL_USERINFO_HEADER 1
/////////////////////////////////////////////////////////////////////////
//! file="Ravl/OS/FileSystem/UserInfo.hh"
//! lib=RavlOS
//! userlevel=Normal
//! author="Charles Galambos"
//! date="29.8.1997"
//! docentry="Ravl.OS"
//! rcsid="$Id$"

#include "Ravl/String.hh"
#include "Ravl/Types.hh"

struct passwd;

namespace RavlN 
{
  
  class TextFileC;
  
  //: User information.
  // This is a small object.
  
  class UserInfoC {
  public:
    UserInfoC();
    //: Default constructor.
    // Creates a null structure.
    
    UserInfoC(StringC login);
    //: Constructor from login.
    
    UserInfoC(UIntT uid);
    //: Constructor from user id.
    
    bool Exists() const { return exists; }
    //: Does user exist ?
  
    bool IsValid() const { return !login.IsEmpty(); }
    //: Could be a valid login ?
    // Mainly to check if UserInfoC was constructed
    // with the default constructor.
    
    void NullUser();
    //: Make this entry invalid.
    
    const StringC Login() const { return login; }
    //: Get login.
    
    const StringC FullName() const { return fullname; }
    //: Get login.
    
    const StringC HomeDir() const { return homedir; }
    //: Get home directory.
    
    const StringC Shell() const { return shell; }
    //: Get default shell.
    
    UIntT Hash() const { return uid; }
    //: Get a hash value.
    
    bool Mail(StringC Content);
    //: Attempt to mail the user
    // This takes a raw message and formats in appropriately.
    // It expects the message to be in the following format.<p>
    // To:xxx<p>
    // Subject:xxx<p>
    // (empty line)<p>
    // Message contents.
    
    bool Mail(StringC Subject,StringC Content);
    //: Attempt to mail the user
    
    bool Mail(StringC Subject,TextFileC &Content);
    //: Attempt to mail the user
    
    bool MailFile(StringC Subject,StringC Filename);
    //: Attempt to mail the user
    
    bool operator==(const UserInfoC &oth) const 
      { return (uid == oth.uid); }
    //: Are two users equal ?
    
    bool operator!=(const UserInfoC &oth) const 
      { return (uid != oth.uid); }
    //: Are two users unequal ?
    
    bool IsRoot() const
      { return uid == 0; }
    //: Test is user is root.
    
    static UserInfoC WhoAmI();
    //: Get current user.
    
  protected:
    bool Init(UIntT aUserid);
    //: Initalise from userid.
    
    bool Init(StringC aLogin);
    //: Initalise from a login.
    
    void Init(struct passwd *pw);
    //: Initalise from a password structure.
    
  private:
    bool exists; // TRUE = is a real user.
    UIntT uid;       // id.
    UIntT gid;       // group id.
    StringC login;   // login.
    StringC fullname;// Full name.
    StringC homedir; // Home directory.
    StringC shell;   // Shell
  };
  
  //: Stream operator.
  
  inline
  ostream &operator <<(ostream &out,const UserInfoC &ui) {
    out << ui.Login();
    return out;
  }
  
}


#endif
