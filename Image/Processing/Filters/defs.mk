# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Image/Processing/Filters/defs.mk"

PACKAGE=Ravl/Image

MAINS=doFilter.cc unDistort.cc

HEADERS= Convolve2d.hh ConvolveSeparable2d.hh ConvolveHorz2d.hh \
 ConvolveVert2d.hh HomomorphicFilter.hh HistogramEqualise.hh \
 Correlate2d.hh Matching.hh WarpScale.hh WarpAffine.hh WarpProjective.hh \
 PixelMixer.hh GaussConvolve.hh RemoveDistortion.hh

SOURCES= HomomorphicFilter.cc Correlate2d.cc Matching.cc RemoveDistortion.cc

TESTEXES= testConvolve.cc

LIBDEPS=RavlImageFilter.def

EXAMPLES = exGaussConvolve.cc

PLIB=RavlImageProc

USESLIBS=RavlImageProc RavlMath

PROGLIBS=RavlIO RavlImageIO RavlDPDisplay RavlOSIO

EHT= Ravl.Images.Filtering.html Ravl.Images.Warping.html
