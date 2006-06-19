# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2003, OmniPerception Ltd.
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 3690 2003-11-18 15:21:00Z ees1wc $"
#! file="Ravl/Contrib/Audio/DevAudio/defs.mk"

ORGANISATION=OmniPerception Ltd.

SUPPORT_ONLY = linux  

PACKAGE= Ravl/Audio

HEADERS= DevAudioIO.hh DevAudioFormat.hh

SOURCES= DevAudioIO.cc DevAudioFormat.cc

MUSTLINK = RavlDevAudio.cc

PLIB = RavlDevAudio

USESLIBS=RavlIO RavlAudioUtil RavlOSIO RavlAudioIO

EHT = Audio_IO.html

EXAMPLES= exAudioIO.cc

PROGLIBS=RavlCore
