# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 7510 2010-02-11 18:31:29Z craftit $"
#! file="Ravl/Core/Math/defs.mk"

DESCRIPTION=Common mathematical operations.  sin, sqrt, etc....

# PACKAGE = a subpath determining the name of the package
PACKAGE = Ravl

#  MAINS = all modules containing the main function separated by space.
MAINS	 = 

# HEADERS = all include files of this project to be exported
HEADERS = StdMath.hh Random.hh RandomGauss.hh Angle.hh ScalMath.hh \
 TFMatrix.hh RandomMersenneTwister.hh LogValue.hh RankedScoreArray.hh


# SOURCES = all C modules, not containing main separated by space. The compiled
#   code of these modules is stored in the project library.
SOURCES = StdMath.cc Random.cc RandomGauss.cc Angle.cc ScalMath.cc \
 RandomMersenneTwister.cc Erf.cc LogValue.cc

# EMGRavl.cc UsefulFn.cc Erf.cc

# LOCALHEADERS = all include files of this project used only for compilation
LOCALHEADERS = 

# PLIB = the project library ... where the objects will be archived
PLIB = RavlCore

# Libraries this uses.
USESLIBS = RavlCore

# File of library dependencies
LIBDEPS = RavlCoreMath.def

# Examples - programs demonstrating using of software in this directory.
# exUsefFn.cc 

# Tests - program testing runtime consistency of the software
TESTEXES = testMath.cc

EHT = RandomGeneration.html
