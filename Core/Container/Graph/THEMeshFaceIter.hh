// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_THEMESHFACEITER_HEADER
#define RAVL_THEMESHFACEITER_HEADER 1
//! rcsid="$Id$"
//! lib=RavlCore
//! author="Charles Galambos"
//! docentry="Ravl.Core.Graphs.Half Edge Mesh"
//! date="22/5/2002"

#include "Ravl/THEMeshFace.hh"
#include "Ravl/HEMeshBaseFaceIter.hh"

namespace RavlN {
  
  template<class VertexDataT,class FaceDataT,class EdgeDataT> class THEMeshC;

  //! userlevel=Normal
  //: Mesh face iterator.
  // Note: It is the users responsibility to ensure the current face of the interator is NOT
  // deleted until the iterator is moved to another element.  Methods such as CollapseEdge()
  // are provided to help ensure this.
  
  template<class VertexDataT,class FaceDataT = EmptyC,class EdgeDataT = EmptyC>
  class THEMeshFaceIterC 
    : public HEMeshBaseFaceIterC 
  {
  public:
    THEMeshFaceIterC()
    {}
    //: Default constructor.
    
    THEMeshFaceIterC(const IntrDListC<HEMeshBaseFaceBodyC> &iter)
      : HEMeshBaseFaceIterC(iter)
    {}
    //: Constructor.
    
    THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> Data()
    { return THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT>(HEMeshBaseFaceIterC::Data()); }
    //: Access Face.

    const THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> Data() const
    { return THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT>(HEMeshBaseFaceIterC::Data()); }
    //: Access Face.
    
    THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> operator*()
    { return THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT>(HEMeshBaseFaceIterC::Data()); }
    //: Access Face.
    
    const THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT> operator*() const
    { return THEMeshFaceC<VertexDataT,FaceDataT,EdgeDataT>(HEMeshBaseFaceIterC::Data()); }
    //: Access Face.
    
    bool CollapseEdge(THEMeshEdgeC<VertexDataT,FaceDataT,EdgeDataT> edge)
    { return HEMeshBaseFaceIterC::CollapseEdge(edge); }
    //: Collapse an edge on the current face.
    // If the face is deleted in the process the iterator is moved
    // to the previous valid face. It will return true if the iterator
    // has been changed.
    
  protected:
    
    friend class THEMeshC<VertexDataT,FaceDataT,EdgeDataT>;
  };
  
}


#endif
