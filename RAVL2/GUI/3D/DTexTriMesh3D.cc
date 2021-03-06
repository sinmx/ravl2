// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////
//! rcsid="$Id: DTexTriMesh3D.cc 6640 2008-03-04 09:38:04Z craftit $"
//! lib=RavlGUI3D
//! file="Ravl/GUI/3D/DTexTriMesh3D.cc"

#include "Ravl/GUI/DTexTriMesh3D.hh"
#include "Ravl/GUI/Canvas3D.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/Image/WarpScale.hh"
#include "GL/gl.h"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

#define USEMESHCOLOUR 0

namespace RavlGUIN {

  DTexTriMesh3DBodyC::DTexTriMesh3DBodyC(const TexTriMeshC &oTexTriMesh)
    :  DTriMesh3DBodyC(oTexTriMesh),
       tmodel(oTexTriMesh),
       texNames(NULL)
  {}
  //: Constructor.

  DTexTriMesh3DBodyC::~DTexTriMesh3DBodyC() {
    // Make sure textures are free'd in an appropriate context.
    if(m_glContext.IsValid() && texNames.Size() > 0)
      m_glContext.FreeTextures(texNames);
  }
  
  //: Render object.
  static int PowerOfTwo(int Val)
  {
    Val--;
    for(int i = 31; i > 0; i--)
      if(Val >> i)
        return 1 << (i+1);
    return 0;
  }

  bool DTexTriMesh3DBodyC::GUIRender(Canvas3DC &canvas) const
  {
    ONDEBUG(cerr << "DTexTriMesh3DBodyC::GUIRender\n");
    if (!tmodel.IsValid())
      return true; // Don't do anything.

    // Setup GL texturing if it's not already done
    if (texNames.Size() == 0 && tmodel.NumTextures() != 0) {
      ONDEBUG(cerr << "creating tex names\n");

      //roate texture coordinates
      glMatrixMode(GL_TEXTURE);
      glLoadIdentity();
      glRotated(-90, 0., 0., 1.);

      // Not sure what this line does...
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      // Allocate textures
      texNames = SArray1dC<unsigned int>(tmodel.NumTextures());
      
      // Remeber the context we about to allocate the textures in
      m_glContext = canvas.GUIGLContext();
      
      // Create texture name
      glGenTextures(tmodel.NumTextures(), &(texNames[0]));
      for(int i = 0; i < tmodel.NumTextures(); i++)
      {
        //cerr << "texture:" << i << endl;
        glBindTexture(GL_TEXTURE_2D, texNames[i]);
        // Setup texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Setup texture image
        const ImageC<ByteRGBValueC> &curTexture = tmodel.Textures()[i];
        //cerr << "size:" << curTexture.Cols() << "  " << curTexture.Rows() << endl;

        IntT newRows = PowerOfTwo(curTexture.Rows());
        IntT newCols = PowerOfTwo(curTexture.Cols());
        
        if(canvas.HaveExtNonPowerOfTwoTexture() || ((IntT) curTexture.Rows() == newRows &&
                                                    (IntT) curTexture.Cols() == newCols)) {
          // We don't care what size the texture is, we can use it.
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                       curTexture.Cols(), curTexture.Rows(),
                       0, GL_RGB, GL_UNSIGNED_BYTE,
                       (void *)(curTexture.Row(curTexture.TRow())));
          
        } else {
          
          // Create texture with power of two size
          //cerr << "size:" << newCols << "  " << newRows << endl;
          ImageC<ByteRGBValueC> texture =
            WarpScaleC<ByteRGBValueC, ByteRGBValueC>(ImageRectangleC(newRows, newCols)).
            Apply(curTexture);
          //cerr << "size:" << texture.Cols() << "  " << texture.Rows() << endl;
          
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                       texture.Cols(), texture.Rows(),
                       0, GL_RGB, GL_UNSIGNED_BYTE,
                       (void *)(texture.Row(texture.TRow())));
        }
      }
      //cerr << "tex names ok\n";
    }

    // Setup materials and colours as appropriate
    if (canvas.GetLightingMode()) {
      GLfloat ambient[]  = {0.2,0.2,0.2,1.0};
      GLfloat diffuse[]  = {0.9,0.9,0.9,1.0};
      glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
      glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
    } else {
      glColor3f(1.0,1.0,1.0);
    }
    // Render
    Canvas3DRenderMode eMode = canvas.GetRenderMode();
    const SArray1dC<VertexC> &verts = tmodel.Vertices();

#if USEMESHCOLOUR
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
#endif

    // Enable and set up texturing
    if(canvas.GetTextureMode())
    {
      //cerr << "enabling texture\n";
      glEnable(GL_TEXTURE_2D);
      //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    }

    switch(eMode) {
    case C3D_SMOOTH:
    case C3D_POINT:
    case C3D_WIRE:
      //cerr << "set normals\n";
      //FIXME
      //glEnableClientState(GL_NORMAL_ARRAY);
      //glNormalPointer(GL_DOUBLE, sizeof(VertexC), (void *)&(verts[0].Normal()));
      //break;
    case C3D_FLAT:
      //cerr << "set vertices\n";
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3,GL_DOUBLE,sizeof(VertexC),(void *)&(verts[0].Position()));
      break;
    }

    switch(eMode)
    {
    case C3D_POINT:
      // Draw individual points
      glDrawArrays(GL_POINTS,0,verts.Size());
      break;
    case C3D_WIRE:
      for(SArray1dIterC<TriC> it(tmodel.Faces());it;it++) {
        glBindTexture(GL_TEXTURE_2D,texNames[it->TextureID()]);
        glBegin(GL_LINE_LOOP);
        GLTexCoord(it->TextureCoord(0));
        glArrayElement(tmodel.Index(*it,0));
        GLTexCoord(it->TextureCoord(1));
        glArrayElement(tmodel.Index(*it,1));
        GLTexCoord(it->TextureCoord(2));
        glArrayElement(tmodel.Index(*it,2));
        glEnd();
      }
      break;
    case C3D_FLAT: {
      ONDEBUG(cerr << "flat render. \n");
      IntT eGLShadeModel;
      glGetIntegerv(GL_SHADE_MODEL,&eGLShadeModel);
      glShadeModel(GL_FLAT); // Flat shading
      // Draw filled polygon
      for(SArray1dIterC<TriC> it(tmodel.Faces());it;it++) {
#if USEMESHCOLOUR
        glColor3ubv(&(it->Colour()[0]));
#endif
        GLNormal(it->FaceNormal());
        //cerr << "textureid:" << int(it->TextureID()) << endl;
        glBindTexture(GL_TEXTURE_2D, texNames[it->TextureID()]);
        glBegin(GL_POLYGON);
        //cerr << "tc: " << it->TextureCoord(0) << "  " << it->TextureCoord(1) << "  " << it->TextureCoord(2) << endl;
        GLTexCoord(it->TextureCoord(0));
        glArrayElement(tmodel.Index(*it, 0));
        GLTexCoord(it->TextureCoord(1));
        glArrayElement(tmodel.Index(*it, 1));
        GLTexCoord(it->TextureCoord(2));
        glArrayElement(tmodel.Index(*it, 2));
        glEnd();
      }
      glShadeModel((GLenum)eGLShadeModel); // Restore old shade model
    } break;
    case C3D_SMOOTH: {
      ONDEBUG(cerr << "Smooth render. \n");
      IntT eGLShadeModel;
      glGetIntegerv(GL_SHADE_MODEL, &eGLShadeModel);
      glShadeModel(GL_SMOOTH); // smooth shading
      // Draw filled polygon
      for(SArray1dIterC<TriC> it(model.Faces()); it; it++)
      {
#if USEMESHCOLOUR
        glColor3ubv(&(it->Colour()[0]));
#endif
        //cerr << "textureid:" << int(it->TextureID()) << endl;
        glBindTexture(GL_TEXTURE_2D, texNames[it->TextureID()]);
        //glBegin(GL_POLYGON);
        glBegin(GL_TRIANGLES);
        //cerr << "tc: " << it->TextureCoord(0) << "  " << it->TextureCoord(1) << "  " << it->TextureCoord(2) << endl;
        GLTexCoord(it->TextureCoord(0));
        glArrayElement(tmodel.Index(*it, 0));
        GLTexCoord(it->TextureCoord(1));
        glArrayElement(tmodel.Index(*it, 1));
        GLTexCoord(it->TextureCoord(2));
        glArrayElement(tmodel.Index(*it, 2));
        glEnd();
      }
      glShadeModel((GLenum)eGLShadeModel); // Restore old shade model
    } break;
    };

    // Disable texturing
    if (canvas.GetTextureMode()) {
      glDisable(GL_TEXTURE_2D);
    }

    // Disable arrays
    switch(eMode) {
    case C3D_SMOOTH:
    case C3D_POINT:
    case C3D_WIRE:
      glDisableClientState(GL_NORMAL_ARRAY);
    case C3D_FLAT:
      glDisableClientState(GL_VERTEX_ARRAY);
      break;
    }
#if USEMESHCOLOUR
    glDisable(GL_COLOR_MATERIAL);
#endif
    return true;
  }

  ostream &operator<<(ostream &strm,const DTexTriMesh3DC &) {
    RavlAssert(0);
    return strm;
  }

  istream &operator>>(istream &strm,DTexTriMesh3DC &) {
    RavlAssert(0);
    return strm;
  }
}

