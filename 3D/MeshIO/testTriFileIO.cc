
#include "Ravl/Option.hh"
#include "Ravl/DP/FileFormatIO.hh"
 
using namespace Ravl3DN;

int main() {
  
  TriSetC ts;
  if(!Load("/vol/vssp/motion3d/DispMap/cubehead/detail.tri",ts,"",true)) {
    cerr << "Failed to load file. \n";
    return 1;
  }
  if(!Save("detail.tri",ts,"",true)) {
    cerr<< "Failed to save. \n";
    return 1;
  }
  
  return 0;
}
