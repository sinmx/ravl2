// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_MTLOCK_HEADER
#define RAVL_MTLOCK_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Base/MTLocks.hh"
//! lib=RavlCore
//! docentry="Ravl.Core.Misc"
//! userlevel=Advanced
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/config.h"
#include "Ravl/Types.hh"

// These functions are designed to provide just enough functionality
// to ensure that the core library is thread safe.  Full threading
// functionality will be provided elsewhere.

//: Ravl namespace.

namespace RavlN {
  
  typedef void (*MTLockFuncT)(int LockId);
  typedef int (*MTThreadIDFuncT)();
  
  extern MTLockFuncT MTReadLock;
  extern MTLockFuncT MTWriteLock;
  extern MTLockFuncT MTUnlockRd;
  extern MTLockFuncT MTUnlockWr;
  extern MTThreadIDFuncT MTGetThreadID;
    
  int MTThreadID();
  //! userlevel=Advanced
  //: Get current thread id.
  
  //:-
  
  //: Lock system for reading.
  // This class provides exceptions safe system DB locking.
  // NB. The locking mechanism is NOT garuanteed to
  // be recursive, so you can't call ReadLock twice then Unlock twice.
  // You also can't go directly between a read lock to a write lock
  // just by calling MTWriteLock(), you have to Unlock the ReadLock
  // first.
  
  class MTReadLockC {
  public:
    MTReadLockC(int nlockId = 0)
      : lockId(nlockId),
        held(false)
      { Lock(); }
    //: Construct lock.
    
    ~MTReadLockC()
      {  
	if(held)
	  MTUnlockRd(lockId);
      }
    //: Construct lock.
    
    void Unlock() {
      if(MTUnlockRd == 0)
	return ;
      if(!held)
	return;
      MTUnlockRd(lockId);
      held = false;
    }
    //: Unlock.
    
    void Lock() {
      if(MTReadLock == 0)
	return ;
      if(held)
	return;
      MTReadLock(lockId); 
      held = true;
    }
    //: Relock for reading.
    
  protected:
    int lockId;
    bool held; // True if lock is held.
  };
  
  //: Lock system for writing.
  // This class provides exceptions safe system DB locking.
  // NB. The locking mechanism is NOT garuanteed to
  // be recursive, so you can't call ReadLock twice then Unlock twice.
  // You also can't go directly between a read lock to a write lock
  // just by calling MTWriteLock(), you have to Unlock the ReadLock
  // first.
  //
  // Id 0 is a genral system lock.
  // Id 1 is used for locking the random number generator.
  // Id 2 is used for non-reentrant 'C' library calls.
  
  class MTWriteLockC {
  public:
    MTWriteLockC(int nlockId = 0)
      : lockId(nlockId),
      held(false)
      {  Lock(); }
    //: Construct lock.
    
    ~MTWriteLockC() {  
      if(held)
	MTUnlockWr(lockId);
    }
    //: Construct lock.
    
    void Unlock() {
      if(MTUnlockWr == 0)
	return ;
      if(!held)
	return;
      MTUnlockWr(lockId);
      held = false;
    }
    //: Unlock.
    
    void Lock() {
      if(MTWriteLock == 0)
	return ;
      if(held)
	return;
      MTWriteLock(lockId);
      held = true;
    }
    //: Relock for writing.
    
  protected:
    int lockId;
    bool held; // True if lock is held.
  };
  
}

#endif
