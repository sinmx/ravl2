// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! rcsid = "$Id: exFFmpeg.cc 5123 2005-09-27 08:39:26Z ees1wc $"
//! lib = RavlPython
//! author = "Warren Moore"
//! file = "Ravl/Contrib/Python/exPython.cc"

#include "Ravl/Python.hh"
#include "Ravl/PythonObject.hh"
#include "Ravl/String.hh"

using namespace RavlN;

int main(int argc, char **argv)
{
  // Initialise the python module
  PythonC python(true);
  
  if (!python.Initialised())
  {
    cerr << "Failed to initialise interpreter" << endl;
    return -1;
  }
    
  // Import a module
  python.AppendSystemPath(".");
  bool ret = python.Import("ravlexample");
  cerr << "Importing 'ravlexample': " << (ret ? "OK" : "FAIL") << endl;
  
  //  Build the arguments list
  PythonObjectC name = python.NewObject();
  name.BuildString("your-name-here");
  DListC<PythonObjectC> argList;
  argList.InsLast(name);
  PythonObjectC args = python.NewObject();
  args.BuildTuple(argList);
  
  // Call the example function and display the results
  cerr << "Calling 'ravlexample.myprint(" << name.String() << ")'" << endl;
  PythonObjectC res = python.Call("ravlexample", "myprint", args);
  cerr << "Result valid: " << (res.IsValid() ? "YES" : "NO") << endl;
  if (res.IsValid())
  {
    if (res.IsString())
      cerr << "Result(string): " << res.String() << endl;
  }
  else
  {
    cerr << "Failed to import and call script" << endl;
    return -1;
  }
  
  // Run a script from a string
  const char* script = "print 'hello again'\nx = 5";
  cerr << "Calling script from string" << endl;
  if (python.Run(script))
  {
    // Read the globals from the script
    PythonObjectC x = python.GetGlobal("x");
    cerr << "Found 'x': " << (x.IsValid() ? "YES" : "NO") << endl;
    if (x.IsValid() && x.IsInt())
      cerr << "'x'= " << x.Int() << endl;
    else
      cerr << "'x' not an int" << endl;
  }
  else
  {
    cerr << "Failed to run script" << endl;
    return -1;
  }

  return 0;
}
