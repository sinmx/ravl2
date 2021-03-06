# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 5974 2006-11-20 18:04:15Z craftit $"
#! file="Ravl/Contrib/HTTP/defs.mk"

REQUIRES= libCurl

DONOT_SUPPORT=VCPP

PACKAGE=Ravl/IO

EXAMPLES = exURL.cc

HEADERS= URLStream.hh

SOURCES= URLStream.cc

MUSTLINK= URLIO.cc

PLIB= RavlURLIO

USESLIBS=RavlCore RavlIO RavlOS RavlThreads libcurl

AUXFILES= libcurl.def

AUXDIR=lib/RAVL/libdep

EHT=Ravl.API.Core.IO.URL_Handling.html
