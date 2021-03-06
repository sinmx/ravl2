// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2010, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////
//! file = "Ravl/OS/XMLFactory/ConfigParameter.hh"
//! lib = Ravl
//! docentry = "Ravl.API.Core.IO.XMLFactory"

#ifndef RAVL_CONFIGPARAMETER_HEADER
#define RAVL_CONFIGPARAMETER_HEADER 1

#include "Ravl/Threads/Signal1.hh"
#include "Ravl/SmartPtr.hh"
#include "Ravl/XMLFactory.hh"
#include <string>

namespace RavlN
{

  //! userlevel=Normal
  //: Generic configuration parameter.

  template<typename DataT>
  class ConfigParameterC
  : public RCBodyVC
  {
  public:
    ConfigParameterC(const XMLFactoryContextC &factory)
    : m_sigUpdate(DataT())
    {
      if (factory.HasChild("Value"))
      {
        factory.UseComponent("Value", m_value);
      }
      else
      {
        factory.Attribute("value", m_value);
      }
    }
    //: Default.

    ConfigParameterC(const DataT &initialValue = DataT())
    : m_value(initialValue),
      m_sigUpdate(initialValue)
    {}
    //: Ctor.

    void SetValue(const DataT &newValue)
    {
      RWLockHoldC hold(m_access,RWLOCK_WRITE);
      if (m_value == newValue)
        return;
      m_value = newValue;
      DataT tmp = m_value;
      hold.Unlock();
      m_sigUpdate(tmp);
    }
    //: Set parameter value.

    DataT Value() const
    {
      RWLockHoldC hold(m_access,RWLOCK_READONLY);
      return m_value;
    }
    //: Access current value.

    Signal1C<DataT> &SigUpdate()
    { return m_sigUpdate; }
    //: Access update signal.

    typedef SmartPtrC<ConfigParameterC<DataT> > RefT;
    //! Handle to this class.

  protected:
    RWLockC m_access;
    DataT m_value;
    Signal1C<DataT> m_sigUpdate;
  };

  //: std::string configuration parameter.

  class ConfigParameterStringC
  : public ConfigParameterC<std::string>
  {
  public:
    ConfigParameterStringC(const XMLFactoryContextC &factory);
    //: Factory ctor.

    ConfigParameterStringC(const std::string &initialValue = "")
    : ConfigParameterC<std::string>(initialValue)
    {}
    //: Construct from default value.

    typedef SmartPtrC<ConfigParameterStringC> RefT;
    //: Handle to this class.
  };

}

#endif
