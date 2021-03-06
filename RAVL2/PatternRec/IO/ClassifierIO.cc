// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: ClassifierIO.cc 4561 2004-09-12 18:57:43Z craftit $"
//! lib=RavlPatternRecIO
//! file="Ravl/PatternRec/IO/ClassifierIO.cc"

#include "Ravl/Vector.hh"
#include "Ravl/PatternRec/Classifier.hh"
#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/PatternRec/ClassifierKNearestNeighbour.hh"
#include "Ravl/PatternRec/ClassifierNearestNeighbour.hh"
#include "Ravl/PatternRec/ClassifierAverageNearestNeighbour.hh"
#include "Ravl/PatternRec/ClassifierDiscriminantFunction.hh"
#include "Ravl/Types.hh"

namespace RavlN {

  void InitRavlClassifierIO()
  {
  }
  
  //:- ClassifierC ------------------------------------------------------------------
  
  FunctionC Classifier2Function(const ClassifierC &func)
  { return func; }
  
  DP_REGISTER_CONVERSION_NAMED(Classifier2Function ,1,
			       "RavlN::FunctionC RavlN::Convert(const RavlN::ClassifierC &)");
  
  static TypeNameC type1(typeid(ClassifierC),"RavlN::ClassifierC");
  
  FileFormatStreamC<ClassifierC> FileFormatStream_Classifier;
  FileFormatBinStreamC<ClassifierC> FileFormatBinStream_Classifier;

  //:- ClassifierNearestNeighbourC ------------------------------------------------------------------
  
  ClassifierC ClassifierNearestNeighbour2Classifier(const ClassifierNearestNeighbourC &func)
  { return func; }
  
  DP_REGISTER_CONVERSION_NAMED(ClassifierNearestNeighbour2Classifier ,1,
			       "RavlN::ClassifierC RavlN::Convert(const RavlN::ClassifierNearestNeighbourC &)");
  
  static TypeNameC type2(typeid(ClassifierNearestNeighbourC),"RavlN::ClassifierNearestNeighbourC");
  
  FileFormatStreamC<ClassifierNearestNeighbourC> FileFormatStream_ClassifierNearestNeighbour;
  FileFormatBinStreamC<ClassifierNearestNeighbourC> FileFormatBinStream_ClassifierNearestNeighbour;
  
  //:- ClassifierKNearestNeighbourC ------------------------------------------------------------------
  
  ClassifierC ClassifierKNearestNeighbour2Classifier(const ClassifierKNearestNeighbourC &func)
  { return func; }
  
  DP_REGISTER_CONVERSION_NAMED(ClassifierKNearestNeighbour2Classifier ,1,
			       "RavlN::ClassifierC RavlN::Convert(const RavlN::ClassifierKNearestNeighbourC &)");
  
  static TypeNameC type3(typeid(ClassifierKNearestNeighbourC),"RavlN::ClassifierKNearestNeighbourC");
  
  FileFormatStreamC<ClassifierKNearestNeighbourC> FileFormatStream_ClassifierKNearestNeighbour;
  FileFormatBinStreamC<ClassifierKNearestNeighbourC> FileFormatBinStream_ClassifierKNearestNeighbour;
  
  //:- ClassifierAverageNearestNeighbourC ------------------------------------------------------------------

  ClassifierC ClassifierAverageNearestNeighbour2Classifier(const ClassifierAverageNearestNeighbourC &func)
  { return func; }
  
  DP_REGISTER_CONVERSION_NAMED(ClassifierAverageNearestNeighbour2Classifier ,1,
			       "RavlN::ClassifierC RavlN::Convert(const RavlN::ClassifierAverageNearestNeighbourC &)");
  
  static TypeNameC type5(typeid(ClassifierAverageNearestNeighbourC),"RavlN::ClassifierAverageNearestNeighbourC");
  
  FileFormatStreamC<ClassifierAverageNearestNeighbourC> FileFormatStream_ClassifierAverageNearestNeighbour;
  FileFormatBinStreamC<ClassifierAverageNearestNeighbourC> FileFormatBinStream_ClassifierAverageNearestNeighbour;
  
  //:- ClassifierDiscriminantFunctionC ------------------------------------------------------------------
  
  ClassifierC ClassifierDiscriminantFunction2Classifier(const ClassifierDiscriminantFunctionC &func)
  { return func; }
  
  DP_REGISTER_CONVERSION_NAMED(ClassifierDiscriminantFunction2Classifier ,1,
			       "RavlN::ClassifierC RavlN::Convert(const RavlN::ClassifierDiscriminantFunctionC &)");
  
  static TypeNameC type6(typeid(ClassifierDiscriminantFunctionC),"RavlN::ClassifierDiscriminantFunctionC");
  
  FileFormatStreamC<ClassifierDiscriminantFunctionC> FileFormatStream_ClassifierDiscriminantFunction;
  FileFormatBinStreamC<ClassifierDiscriminantFunctionC> FileFormatBinStream_ClassifierDiscriminantFunction;

  
  
}
