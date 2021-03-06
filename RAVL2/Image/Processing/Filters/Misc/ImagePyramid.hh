// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_IMAGEPYRAMID_HEADER
#define RAVLIMAGE_IMAGEPYRAMID_HEADER 1
//! author="Charles Galambos"
//! docentry="Ravl.API.Images.Filtering"
//! lib=RavlImageProc
//! rcsid="$Id: ImagePyramid.hh 6440 2007-11-13 18:11:20Z ees1wc $"
//! userlevel=Normal 
//! file="Ravl/Image/Processing/Filters/Misc/ImageExtend.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ImageExtend.hh"
#include "Ravl/Image/GaussConvolve2d.hh"
#include "Ravl/Collection.hh"
#include "Ravl/CollectionIter.hh"
#include "Ravl/Tuple3.hh"
#include "Ravl/Image/WarpScale.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Image pyramid.
  // This class creates a set of images each filtered such that
  // that its effective resolution is reduced by a power of 2.
  
  template<typename PixelT,typename SumTypeT = PixelT>
  class ImagePyramidC {
  public:
    ImagePyramidC()
    {}
    //: Default constructor.
    
    ImagePyramidC(const ImageC<PixelT> &img,IntT nScales = 2,bool subSample = false,bool recursive = false)
    { ComputeImages(img,nScales,subSample,recursive); }
    //: Constructor.
    //!param: img - Image to filter.
    //!param: nScales - Number of scales to generate. -1 = Generate a complete pyramid.
    //!param: subSample - If true sub-sample the pixels as well as filtering.

    ImagePyramidC(const ImageC<PixelT> &img,RealT scaleFactor,IntT nScales = 2,bool subSample = false)
    { ComputeImages(img,scaleFactor,nScales,subSample); }
    //: Constructor for non-diadic pyramid
    //!param: img - Image to filer
    //!param: scaleFactor - the scale factor to apply between levels (2.0 == double size)
    //!param: nScales - Number of scales to generate. -1 = Generate a complete pyramid.
    //!param: subSample - If true sub-sample the picels as well as filtering.
    
    void ComputeImages(const ImageC<PixelT> &img,IntT nScales,bool subSample,bool recursive = false);
    //: Compute images over given scales.
    //!param: img - Image to filter.
    //!param: nScales - Number of scales to generate. -1 = Generate a complete pyramid.
    //!param: subSample - If true sub-sample the pixels as well as filtering.
    //!param: recursive - If true when subsampling, then use the results of previous filtering operations as input for the next.

    void ComputeImages(const ImageC<PixelT> &img,RealT scaleFactor,IntT nScales,bool subSample);
    //: Compute images over given scales for non-diadic pyramids.
    //!param: img - Image to filer
    //!param: scaleFactor - the scale factor to apply between levels (2.0 == double size)
    //!param: nScales - Number of scales to generate. -1 = Generate a complete pyramid.
    //!param: subSample - If true sub-sample the picels as well as filtering.
    
    ImageC<PixelT> ScaleImage(const ImageC<PixelT> &img,IntT scale,bool subSample,IntT imgScale = 1);
    //: Compute a scaled image and add it to the pyramid.
    //!param: img - Image to filter.
    //!param: scale - Scaling to apply.
    //!param: subSample - Sub sample the pixels in the image ?
    //!param: imgScale - Scale of image passed to routine, use 1 if the image at the original scale.
    //!return: resulting image.
    
    ImageC<PixelT> ScaleImage(const ImageC<PixelT> &img,RealT scale,bool subSample);
    //: Compute a scaled image and add it to the pyramid.
    //!param: img - Image to filter.
    //!param: scale - Scaling to apply.
    //!param: subSample - Sub sample the pixels in the image ?
    //!return: resulting image.
    
    bool Find(RealT reqScale,ImageC<PixelT> &img,RealT &filterScale,RealT &pixelScale,bool notSmaller = false) const;
    //: Find image with closest scale.
    //!param: reqScale - Requested scale.
    //!param: img - Image found
    //!param: actualScale - Scale of image
    //!param: notSmaller - If true use the image with scale equal or larger size to that requested if one is available.
    //!return: Set to true if image found, only fails if class is not initalised.
    
    CollectionC<Tuple3C<RealT,RealT,ImageC<PixelT> > > &Images()
    { return images; }
    //: Access available images.
    
    const CollectionC<Tuple3C<RealT,RealT,ImageC<PixelT> > > &Images() const
    { return images; }
    //: Access available images.
    
  protected:
    CollectionC<Tuple3C<RealT,RealT,ImageC<PixelT> > > images;
  };
  
  template<typename PixelT,typename SumTypeT>
  void ImagePyramidC<PixelT,SumTypeT>::ComputeImages(const ImageC<PixelT> &img,IntT nscales,bool subSample,bool recursive) {
    images = CollectionC<Tuple3C<RealT,RealT,ImageC<PixelT> > >(nscales+1);
    images.Insert(Tuple3C<RealT,RealT,ImageC<PixelT> >(1,1,img));
    //cerr << " No Scales=" << nscales << "\n";
    IntT minSize = Min(img.Rows(),img.Cols());
    if(subSample && recursive) {
      ImageC<PixelT> srcImg = img;
      IntT scale = 1;
      for(int i = 1;(i < nscales) || nscales < 0;i ++) {
	if((scale * 4-1) >= minSize)
	  break;
	srcImg = ScaleImage(srcImg,2,true,scale);
	scale *= 2;
      }
    } else {
      for(int i = 1;(i < nscales) || nscales < 0;i ++) {
	IntT scale = 1 << i;
	IntT kernelSize = scale*2 - 1;
	if(kernelSize >= minSize) // No point in scaling beyond the image size.
	  break;
	ScaleImage(img,scale,subSample,1);
      }
    }
  }

  template<typename PixelT,typename SumTypeT>
  void ImagePyramidC<PixelT,SumTypeT>::ComputeImages(const ImageC<PixelT> &img,RealT scaleFactor,IntT nScales,bool subSample) {
    images = CollectionC<Tuple3C<RealT,RealT,ImageC<PixelT> > >(nScales+1);
    images.Insert(Tuple3C<RealT,RealT,ImageC<PixelT> >(1,1,img));
    IntT minSize = Min(img.Rows(),img.Cols());
    RealT scale = 1.0;
    for(int i = 1;(i < nScales) || nScales < 0; i++) {
      scale *= scaleFactor;
      IntT kernelSize = (IntT)(scale * 2.0) - 1;
      if (!(kernelSize & 1))
        kernelSize++;
      if(kernelSize >= minSize) // No point in scaling beyond the image size.
        break;
      ScaleImage(img,scale,subSample);
    }
  }
  
  //: Generate a single filtered image.
  //!param: img - Image to filter.
  //!param: scale - Scaling to apply.
  //!param: subSample - Sub sample the pixels in the image ?
  //!param: imgScale - Scale of image passed to routine, use 1 if the image at the original scale.
  
  template<typename PixelT,typename SumTypeT>
  ImageC<PixelT> ImagePyramidC<PixelT,SumTypeT>::ScaleImage(const ImageC<PixelT> &img,IntT scale,bool subSample,IntT imgScale) {
    IntT kernelSize = scale*2 - 1;
    IndexRange2dC outRange = img.Frame();
    ImageC<PixelT> prepImage;
    ExtendImageCopy(img,scale-1,prepImage);
    GaussConvolve2dC<PixelT,PixelT,RealT,SumTypeT> filter(kernelSize);
    ImageC<PixelT> filteredImage = filter.Apply(prepImage);
    if(!subSample) {
      images.Insert(Tuple3C<RealT,RealT,ImageC<PixelT> >(scale * imgScale,imgScale,filteredImage));
      return filteredImage;
    }
    // FIXME:- This isn't the most efficient way of getting a subsampled image, we could
    // compute filered values for the points we want in the final image. 
    //cerr << " Scale=" << scale << "\n";
    IndexRange2dC alignedFrame = filteredImage.Frame().AlignWithin(scale);
    IndexRange2dC subFrame = alignedFrame / scale;
    ImageC<PixelT> subImage(subFrame);
      //cerr << " Frame=" << alignedFrame << " SF=" << subFrame << "\n";
    Array2dIterC<PixelT> dit(subImage);
    for(Array2dIterC<PixelT> sit(ImageC<PixelT>(filteredImage,alignedFrame));sit;sit += scale,dit++)
      *dit = *sit;
    images.Insert(Tuple3C<RealT,RealT,ImageC<PixelT> >(scale * imgScale,scale * imgScale,subImage));
    return subImage;
  }
  
  //: Generate a single filtered image.
  //!param: img - Image to filter.
  //!param: scale - Scaling to apply.
  //!param: subSample - Sub sample the pixels in the image ?
  
  template<typename PixelT,typename SumTypeT>
  ImageC<PixelT> ImagePyramidC<PixelT,SumTypeT>::ScaleImage(const ImageC<PixelT> &img,RealT scale,bool subSample) {
    IntT kernelSize = (IntT)(scale * 2.0) - 1;
    if (!(kernelSize & 1))
      kernelSize++;
    IndexRange2dC outRange = img.Frame();
    ImageC<PixelT> prepImage;
    if (((kernelSize - 1) >> 1) > 0)
      ExtendImageCopy(img,(kernelSize-1) >> 1,prepImage);
    else
      prepImage = img;
    if(!subSample) {
      GaussConvolve2dC<PixelT,PixelT,RealT,SumTypeT> filter(kernelSize);
      ImageC<PixelT> filteredImage = filter.Apply(prepImage);
      images.Insert(Tuple3C<RealT,RealT,ImageC<PixelT> >(scale,1.0,filteredImage));
      return filteredImage;
    }
    ImageC<SumTypeT> filteredImage;
    if (kernelSize > 1) {
      GaussConvolve2dC<PixelT,SumTypeT,RealT,SumTypeT> filter(kernelSize);
      filteredImage = filter.Apply(prepImage);
    } else {
      filteredImage = ImageC<SumTypeT>(prepImage.Frame());
      for(Array2dIter2C<SumTypeT,PixelT> it(filteredImage,prepImage);it;it++)
        it.Data1() = static_cast<SumTypeT>(it.Data2());
    }
    // FIXME:- This isn't the most efficient way of getting a subsampled image, we could
    // compute filered values for the points we want in the final image. 
    //cerr << " Scale=" << scale << "\n";
    IndexRange2dC alignedFrame;
    if (((kernelSize-1) >> 1) > 0)
      alignedFrame = filteredImage.Frame().AlignWithin((kernelSize-1) >> 1);
    else
      alignedFrame = filteredImage.Frame();
    IndexRange2dC subFrame(alignedFrame.Range1().Min() / scale, alignedFrame.Range1().Max() / scale,
                           alignedFrame.Range2().Min() / scale, alignedFrame.Range2().Max() / scale);
    WarpScaleC<SumTypeT,PixelT> warpScale(subFrame);
    ImageC<PixelT> subImage = warpScale.Apply(ImageC<SumTypeT>(filteredImage, alignedFrame));
    images.Insert(Tuple3C<RealT,RealT,ImageC<PixelT> >(scale,scale,subImage));
    return subImage;
  }
  
  //: Find image with closest scale.
  //!param: reqScale - Requested scale.
  //!param: img - Image found
  //!param: actualScale - Scale of image
  
  template<typename PixelT,typename SumTypeT>
  bool ImagePyramidC<PixelT,SumTypeT>::Find(RealT reqScale,ImageC<PixelT> &img,RealT &filterScale,RealT &pixelScale,bool notSmaller) const {
    CollectionIterC<Tuple3C<RealT,RealT,ImageC<PixelT> > > it(const_cast<CollectionC<Tuple3C<RealT,RealT,ImageC<PixelT> > > &>(images));
    if(!it) return false;
    // The first image should be the unscaled. Which is the default if reqScale is less than 1 and notSmaller is set.
    RealT diff = Abs(it->Data1() - reqScale);
    img = it->Data3();
    RealT bestScale =  diff;
    filterScale = it->Data1();
    pixelScale = it->Data2();
    
    for(it++;it;it++) {
      diff = Abs(it->Data1() - reqScale);
      if(diff < bestScale && (!notSmaller || it->Data1() < reqScale)) {
        img = it->Data3();
	bestScale = diff;
        filterScale = it->Data1();
        pixelScale = it->Data2();
      }
    }
    return true;
  }
  
}

#endif
