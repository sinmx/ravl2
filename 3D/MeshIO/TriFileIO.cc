
#include "Ravl/3D/TriFileIO.hh"
#include "Ravl/SArr1Iter.hh"

namespace Ravl3DN {
  //: Open file.
  
  DPITriFileBodyC::DPITriFileBodyC(const StringC &fn)
    : inf(fn),
      done(false)
  {}
  
  //: Open file.
  
  DPITriFileBodyC::DPITriFileBodyC(IStreamC &is)
    : inf(is),
      done(false)
  {}
  
  //: Is valid data ?
  
  bool DPITriFileBodyC::IsGetEOS() const {
    return !done && inf;
  }
  
  //: Get next piece of data.
  
  TriSetC DPITriFileBodyC::Get() {
    if(done)
      return TriSetC();
    UIntT nvertex,nelement;
    inf >> nvertex >>  nelement;
    SArray1dC<VertexC> verts(nvertex);
    for(SArray1dIterC<VertexC> vit(verts);vit;vit++) {
      inf >> vit->Position();
      vit->Normal() = Vector3dC(0,0,0);
    }
    SArray1dC<TriC> faces(nelement);
    UIntT n,i1,i2,i3;
    SArray1dIterC<TriC> it(faces);
    UIntT i = 0;
    for(;i < nelement;i++) {
      inf >> n;
      if(n != 3) { // Dump non-triangular faces.
	for(UIntT i = 0;i < n;i++)
	  inf >> n;
	continue;
      }
      inf >> i1 >> i2 >> i3;
      it->VertexPtr(0) = &(verts[i1]);
      it->VertexPtr(1) = &(verts[i2]);
      it->VertexPtr(2) = &(verts[i3]);
      it->UpdateFaceNormal();
      it++;
    }
    done = true;
    // The faces array is resized in case we had to drop any non trianglular faces.
    TriSetC ret(verts,SArray1dC<TriC>(faces,it.Index().V()));
    ret.UpdateVertexNormals();
    return ret;
  }

  ////////////////////////////////////////////////////////////////////////////////////////

  //: Open file.
  
  DPOTriFileBodyC::DPOTriFileBodyC(const StringC &fn)
    : outf(fn),
      done(false)
  {}
  
  //: Open file.
  
  DPOTriFileBodyC::DPOTriFileBodyC(OStreamC &is)
    : outf(is),
      done(false)
  {}
  
  //: Put data.
  
  bool DPOTriFileBodyC::Put(const TriSetC &dat) {
    if(done || !outf)
      return false;
    outf << dat.Vertices().Size() << ' ' << dat.Faces().Size() << '\n';
    for(SArray1dIterC<VertexC> vit(dat.Vertices());vit;vit++)
      outf << vit->Position() << '\n';
    const VertexC *x = &(dat.Vertices()[0]);
    for(SArray1dIterC<TriC> it(dat.Faces());it;it++)
      outf << "3 " << (it->VertexPtr(0) - x) << ' ' << (it->VertexPtr(1) - x) << ' ' << (it->VertexPtr(2) - x) << '\n';
    
    return true;
  }
  
  //: Is port ready for data ?
  
  bool DPOTriFileBodyC::IsPutReady() const 
  { return !done && outf; }

}
