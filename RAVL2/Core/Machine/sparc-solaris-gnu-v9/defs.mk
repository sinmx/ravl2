# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 2151 2002-12-10 13:12:11Z plugger $"
#! file="Ravl/Core/Machine/sparc-solaris-gnu/defs.mk"

DESCRIPTION= Atomic operations for solaris-sparc-v9

NESTED=

PACKAGE=sol2/Ravl

SUPPORT_ONLY=sol2

HEADERS=Atomic.hh

PLIB=RavlCore

USESLIBS=Math
#CCPPFLAGS=-Wa,-xarch=v8plus -mcpu=v9 
