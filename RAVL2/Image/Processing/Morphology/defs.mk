# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 7123 2009-03-08 22:00:15Z craftit $"
#! file="Ravl/Image/Processing/Morphology/defs.mk"

PACKAGE=Ravl/Image

HEADERS=Erode.hh Dilate.hh DilateSubSample2X.hh MorphOpen.hh MorphClose.hh

PLIB=RavlImageProc

LIBDEPS=RavlImageMorphology.def

USESLIBS=RavlImageProc 

EHT=Ravl.API.Images.Morphology.html

TESTEXES=testMorphology.cc

EXAMPLES= exMorphology.cc