// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! file="Ravl/Image/Processing/Tracking/mosaic.cc"
//! lib=RavlImageProc

#include "Ravl/Option.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/Image/MosaicBuilder.hh"
#include "Ravl/Image/WarpProjective.hh"
#include "Ravl/Image/RemoveDistortion.hh"
#include "Ravl/EntryPnt.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array2dIter3.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/IO.hh"
#include "Ravl/Image/ImgIO.hh"
#include "Ravl/Image/Erode.hh"
#include "Ravl/Image/Dilate.hh"
#include "Ravl/Image/ImageConv.hh"
#include "Ravl/Image/RealRGBValue.hh"

#include "Ravl/Projection2d.hh"
#include "Ravl/Image/ImageTracker.hh"
#include "Ravl/ObservationHomog2dPoint.hh"
#include "Ravl/Ransac.hh"
#include "Ravl/ObservationManager.hh"
#include "Ravl/EvaluateNumInliers.hh"
#include "Ravl/FitHomog2dPoints.hh"
#include "Ravl/StateVectorHomog2d.hh"
#include "Ravl/LevenbergMarquardt.hh"

using namespace RavlN;
using namespace RavlImageN;

static void
 Smooth8Way(ImageC<ByteRGBValueC> &img)
{
  ByteRGBValueC pix[9];
  UIntT weight[9];
  UIntT count;
  ImageC<ByteRGBValueC> imcopy(img.Rows(),img.Cols());
  
  for(UIntT i=0; i<img.Rows(); i++)
    for(UIntT j=0; j<img.Cols(); j++) {
      count = 0;
      pix[count] = img[i][j]; weight[count++] = 4;
      if ( i != 0 ) {
	pix[count] = img[i-1][j];
	weight[count++] = 2;
	if ( j != 0 ) {
	  pix[count] = img[i-1][j-1];
	  weight[count++] = 1;
	}

	if ( j != img.Cols()-1 ) {
	  pix[count] = img[i-1][j+1];
	  weight[count++] = 1;
	}
      }

      if ( i != img.Rows()-1 ) {
	pix[count] = img[i+1][j];
	weight[count++] = 2;
	if ( j != 0 ) {
	  pix[count] = img[i+1][j-1];
	  weight[count++] = 1;
	}

	if ( j != img.Cols()-1 ) {
	  pix[count] = img[i+1][j+1];
	  weight[count++] = 1;
	}
      }

      if ( j != 0 ) {
	pix[count] = img[i][j-1];
	weight[count++] = 2;
      }

      if ( j != img.Cols()-1 ) {
	pix[count] = img[i][j+1];
	weight[count++] = 2;
      }

      UIntT total_weight=0;
      RealRGBValueC total_rgb(0,0,0);
      for(UIntT k=0; k<count; k++) {
	total_weight += weight[k];
	total_rgb.Red()   += (RealT)(weight[k]*pix[k].Red());
	total_rgb.Green() += (RealT)(weight[k]*pix[k].Green());
	total_rgb.Blue()  += (RealT)(weight[k]*pix[k].Blue());
      }

      pix[0].Red()   = (ByteT)(total_rgb.Red()/(RealT)total_weight + 0.5);
      pix[0].Green() = (ByteT)(total_rgb.Green()/(RealT)total_weight + 0.5);
      pix[0].Blue()  = (ByteT)(total_rgb.Blue()/(RealT)total_weight + 0.5);
      imcopy[i][j] = pix[0];
    }

  for(UIntT i=0; i<img.Rows(); i++)
    for(UIntT j=0; j<img.Cols(); j++)
      img[i][j] = imcopy[i][j];
}

#define IMAGE_ZHOMOG 100.0
#define MOSAIC_ZHOMOG 1.0

  
int Mosaic(int nargs,char **argv) {
  OptionC opt(nargs,argv);
  int newFreq    = opt.Int("nf",5,"Frequency of introducing new features. ");
  int cthreshold = opt.Int("ct",30,"Corner threshold. ");
  int cwidth     = opt.Int("cw",7,"Corner filter width. ");
  int mthreshold = opt.Int("mt",20,"Match threshold. ");
  int mwidth     = opt.Int("mw",17,"Tracker feature width. ");
  int lifeTime   = opt.Int("ml",8,"Lifetime of a point without a match in the incoming images. ");
  int searchSize = opt.Int("ss",25,"Search size. How far to look from the predicted position of the feature.");
  RealT cx_ratio = opt.Real("cx",0.5,"Image centre x coordinate as ratio of image width. ");
  RealT cy_ratio = opt.Real("cy",0.5,"Image centre y coordinate as ratio of image height. ");
  RealT fx = opt.Real("fx",1.0,"Focal distance in vertical pixels. ");
  RealT fy = opt.Real("fy",1.0,"Focal distance in horizontal pixels. ");
  RealT K1 = opt.Real("K1",0.0,"Cubic radial distortion coefficient. ");
  RealT K2 = opt.Real("K2",0.0,"Quintic radial distortion coefficient. ");
  int borderC    = opt.Int("bc", 200, "Width of horizontal border around image");
  int borderR    = opt.Int("br", 200, "Width of vertical border around image");
  int cropT = opt.Int("crt", 0, "Width of cropping region at top of image");
  int cropB = opt.Int("crb", 0, "Width of cropping region at bottom of image");
  int cropL = opt.Int("crl", 0, "Width of cropping region at left of image");
  int cropR = opt.Int("crr", 0, "Width of cropping region at right of image");
  Point2dC pointTL = opt.Point2d("ptl", 0.0, 0.0, "Top-left coordinates of first image");
  Point2dC pointTR = opt.Point2d("ptr", 0.0, 1.0, "Top-right coordinates of first image");
  Point2dC pointBL = opt.Point2d("pbl", 1.0, 0.0, "Bottom-left coordinates of first image");
  Point2dC pointBR = opt.Point2d("pbr", 1.0, 1.0, "Bottom-right coordinates of first image");
  int maxFrames = opt.Int("mf",-1,"Maximum number of frames to process ");
  StringC ifn = opt.String("","@V4LH:/dev/video0","Input sequence. ");
  StringC ofn = opt.String("","@X","Output sequence. ");
  opt.Check();

  // Open an input stream.
  DPIPortC<ImageC<ByteRGBValueC> > inp;
  if(!OpenISequence(inp,ifn)) {
    cerr << "Failed to open input '" << ifn << "'\n";
    return 1;
  }
#if 0
  inp.SetAttr("FrameBufferSize","2");
#endif
  ImageC<ByteRGBValueC> img;
#if 0
  for(UIntT frameNo = 0;frameNo < 200;frameNo++)
    // Read an image from the input.
    if(!inp.Get(img)) {
      cerr << "Failed to read image from input '" << ifn << "'\n";
      return 1;
    }
#endif
  
  // Create a mosaic class instance
  MosaicBuilderC mosaicBuilder(cthreshold, cwidth, mthreshold, mwidth,
			       lifeTime, searchSize, newFreq,
			       borderC, borderR, IMAGE_ZHOMOG,
			       cropT, cropB, cropL, cropR,
			       pointTL, pointTR, pointBL, pointBR,
			       maxFrames);

  // declare distortion correction object
  RemoveDistortionC<ByteRGBValueC,ByteRGBValueC> distortionRemover;
  ImageC<ByteRGBValueC> linearImg;

  for(IntT frameNo = 0;frameNo < maxFrames;frameNo++) {
    if(!inp.Get(img))
      return 1;

    if(K1 == 0.0 && K2 == 0.0) {
      // no distortion, so build mosaic from original images
      if(!mosaicBuilder.Apply(img))
	return 1;
    }
    else {
      if(frameNo==0) {
	// create distortion correction object at the first frame
	distortionRemover = RemoveDistortionC<ByteRGBValueC,ByteRGBValueC>(
						cx_ratio*(RealT)img.Rows(),
						cy_ratio*(RealT)img.Cols(),
						fx, fy, K1, K2);
	
	// create linear camera image at first frame
	linearImg = img.Copy();
      }

      // apply distortion correction
      distortionRemover.Apply(img,linearImg);
      if(!mosaicBuilder.Apply(linearImg))
	return 1;
    }

    Save("@X:Mosaic",mosaicBuilder.GetMosaic());
  }

  ImageC<ByteRGBValueC> mosaicRGB = DPConvByteRGBMedianImageC2ByteRGBValueImageCT(mosaicBuilder.GetMosaic());

  // save constructed mosaic
  Save("/tmp/mosaic.ppm",mosaicRGB);

  // reopen input sequence
  if(!OpenISequence(inp,ifn)) {
    cerr << "Failed to open input '" << ifn << "'\n";
    return 1;
  }

#if 0
  for(UIntT frameNo = 0;frameNo < 200;frameNo++)
    // Read an image from the input.
    if(!inp.Get(img)) {
      cerr << "Failed to read image from input '" << ifn << "'\n";
      return 1;
    }
#endif
  // Open the output stream for the foreground segmentation images.
  DPOPortC<ImageC<ByteRGBValueC> > outp;
  if(!OpenOSequence(outp,ofn,"")) {
    cerr << "Failed to open output '" << ofn << "'\n";
    return 1;
  }

  // 5x5 kernel for morphological operations, with this shape:
  //  ***
  // *****
  // *****
  // *****
  //  ***
  IndexRangeC centred(-2,2);
  ImageC<bool> kernel(centred,centred);
  kernel.Fill(true);
  kernel[-2][-2] = kernel[-2][2] = kernel[2][-2] = kernel[2][2] = false;

  // image tracker
  ImageTrackerC tracker(17,25,20);

  // first motion estimate for registration with the mosaic
  Projection2dC proj(mosaicBuilder.GetMotion(0),IMAGE_ZHOMOG,MOSAIC_ZHOMOG);

  // convert mosaic to grey level
  ImageC<ByteT> mosaicGrey = RGBImageCT2ByteImageCT(mosaicRGB);

  // compute foreground segmented image
  for(IntT frameNo = 0;frameNo < maxFrames;frameNo++) {
    // Read an image from the input.
    if(!inp.Get(img))
      break;

    // crop image and convert to grey level
    img = ImageC<ByteRGBValueC>(img,mosaicBuilder.GetCropRect());
    ImageC<ByteT> imgGrey = RGBImageCT2ByteImageCT(img);

    // compute corner matches to mosaic
    DListC<PairC<Point2dC> > matchList = tracker.TrackImage(mosaicGrey,imgGrey,proj);

    // set corner error covariance matrix to 2x2 identity
    MatrixRSC epos(2);
    epos[0][0] = 1;
    epos[1][1] = 1;
    epos[1][0] = 0;
    epos[0][1] = 0;

    // RANSAC objects
    FitHomog2dPointsC fitHomog2d(IMAGE_ZHOMOG,MOSAIC_ZHOMOG);
    EvaluateNumInliersC evalInliers(1.0,2.0);

    // Generate an observation set for tracked points.
    DListC<ObservationC> obsList;
    for(DLIterC<PairC<Point2dC> > it(matchList);it;it++) {
      const Point2dC& loc1=it->A();
      const Point2dC& loc2=it->B();
      cout << "A=" << loc1 << " B=" << loc2 << endl;
      obsList.InsLast(ObservationHomog2dPointC(Vector2dC(loc1[0],loc1[1]),epos,
                                               Vector2dC(loc2[0],loc2[1]),epos));
    }

    ObservationListManagerC obsListManager(obsList);
    RansacC ransac(obsListManager,fitHomog2d,evalInliers);

    for(int i = 0;i <100;i++)
      ransac.ProcessSample(8);

    // carry on optimising solution if Ransac succeeding
    if(!ransac.GetSolution().IsValid())
      // failed to find a solution
      continue;

    // select observations compatible with solution
    DListC<ObservationC> compatible_obs_list = evalInliers.CompatibleObservations(ransac.GetSolution(),obsList);

    // initialise Levenberg-Marquardt algorithm
    StateVectorHomog2dC sv = ransac.GetSolution();
    LevenbergMarquardtC lm = LevenbergMarquardtC(sv, compatible_obs_list);

    cout << "2D homography fitting: Initial residual=" << lm.GetResidual() << endl;
    cout << "Selected " << compatible_obs_list.Size() << " observations using RANSAC" << endl;
    VectorC x = lm.SolutionVector();
    x /= x[8];
    try {
      // apply iterations
      RealT lambda = 100.0;
      for ( int i = 0; i < 4; i++ ) {
        bool accepted = lm.Iteration(compatible_obs_list, lambda);
        if ( accepted )
          // iteration succeeded in reducing the residual
          lambda /= 10.0;
        else
          // iteration failed to reduce the residual
          lambda *= 10.0;

        cout << " Accepted=" << accepted << " Residual=" << lm.GetResidual();
        cout << " DOF=" << 2*compatible_obs_list.Size()-8 << endl;
      }
    } catch(...) {
      // Failed to find a solution.
      cerr << "Caught exception from LevenbergMarquardtC. \n";
      return false;
    }

    // get solution homography
    sv = lm.GetSolution();
    Matrix3dC P = sv.GetHomog();
    P /= P[2][2];

    cout << "Solution: (" << P[0][0] << " " << P[0][1] << " " << P[0][2] << ")" << endl;
    cout << "          (" << P[1][0] << " " << P[1][1] << " " << P[1][2] << ")" << endl;
    cout << "          (" << P[2][0] << " " << P[2][1] << " " << P[2][2] << ")" << endl;

    // update 2D projection from image onto mosaic
    proj = Projection2dC(P.Inverse(),IMAGE_ZHOMOG,MOSAIC_ZHOMOG);

    P = mosaicBuilder.GetMotion(frameNo).Inverse();
    P /= P[2][2];

    cout << "Mosaic: (" << P[0][0] << " " << P[0][1] << " " << P[0][2] << ")" << endl;
    cout << "        (" << P[1][0] << " " << P[1][1] << " " << P[1][2] << ")" << endl;
    cout << "        (" << P[2][0] << " " << P[2][1] << " " << P[2][2] << ")" << endl;

    ImageC<ByteRGBValueC> warped_img(mosaicBuilder.GetCropRect());
    WarpProjectiveC<ByteRGBValueC,ByteRGBValueC> pwarp(mosaicBuilder.GetCropRect(),proj.Matrix(),MOSAIC_ZHOMOG,IMAGE_ZHOMOG,true);
    pwarp.Apply(mosaicRGB,warped_img);

    // smooth both images to suppress artefacts
    for(IntT i=0; i < 3; i++) {
      Smooth8Way(img);
      Smooth8Way(warped_img);
    }

    // subtract and threshold
    ImageC<bool> mask(mosaicBuilder.GetCropRect());
    mask.Fill(false);
    for(Array2dIter3C<ByteRGBValueC,ByteRGBValueC,bool> it(img,warped_img,mask);
	it.IsElm(); it.Next()) {
      IntT diff2 = Sqr((IntT)it.Data1().Red()   - (IntT)it.Data2().Red()) +
                   Sqr((IntT)it.Data1().Green() - (IntT)it.Data2().Green()) +
	           Sqr((IntT)it.Data1().Blue()  - (IntT)it.Data2().Blue());
      if ( diff2 > 600 )
	it.Data3() = true;
    }

    // erode and dilate binary mask
    ImageC<bool> result(mosaicBuilder.GetCropRect());
    BinaryErode(mask, kernel, result);
    cout << "result.TL=(" << result.Frame().TRow() << "," << result.Frame().LCol() << ") result.BR=(" << result.Frame().BRow() << "," << result.Frame().RCol() << ")" << endl;
    BinaryDilate(result, kernel, mask);
    cout << "mask.TL=(" << mask.Frame().TRow() << "," << mask.Frame().LCol() << ") mask.BR=(" << mask.Frame().BRow() << "," << mask.Frame().RCol() << ")" << endl;
    cout << "mask.Rows()=" << mask.Rows() << " mask.Cols()=" << mask.Cols() << endl;

    ByteRGBValueC val(0,0,0);
    for(Array2dIter2C<ByteRGBValueC,bool> it(img,mask);
	it.IsElm(); it.Next()) {
      if ( !it.Data2() )
	it.Data1() = val;
    }

    // Write an image out.
    outp.Put(img);
  }

  cout << "Output finished" << endl;
  return 0;
}

RAVL_ENTRY_POINT(Mosaic)
