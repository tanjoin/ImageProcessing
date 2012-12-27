// --------------------------------------------------------------------------
// -                        �摜�T�C�Y��ύX����                            -
// --------------------------------------------------------------------------
#ifndef OPENCV_RESIZE_H_
#define OPENCV_RESIZE_H_

#include <opencv2/opencv.hpp>

class OpenCVResize
{
public:

  OpenCVResize(void) : is_resize_(false), is_original_(false) {}
  OpenCVResize(const cv::Mat& image) : original_image_(image), is_resize_(false), is_original_(true) {}
  virtual ~OpenCVResize(void) {}
  
  // �o�C���j�A��Ԃŉ摜�̃T�C�Y��ύX����
  void bilinear(const double fx = 0.5, const double fy = 0.5){	
    if(!is_original_ || original_image_.empty()) return;
    is_resize_ = true;
	  cv::resize(original_image_, resize_image_, cv::Size(), fx, fy);
  }

  // �o�C�L���[�r�b�N��Ԃŉ摜�̃T�C�Y��ύX����
  void bi_cubic(const double fx = 0.5, const double fy = 0.5){
    if(!is_original_ || original_image_.empty()) return;
    is_resize_ = true;
	  resize_image_ = cv::Mat(static_cast<int>(original_image_.rows * fx), static_cast<int>(original_image_.cols * fy), original_image_.type());
	  cv::resize(original_image_, resize_image_, resize_image_.size(), cv::INTER_CUBIC);
  }

  // Lanczos�@�̕�Ԃŉ摜�̃T�C�Y��ύX����
  void lanczos4(const double fx = 0.5, const double fy = 0.5){
    if(!is_original_ || original_image_.empty()) return;
    is_resize_ = true;
	  resize_image_ = cv::Mat(static_cast<int>(original_image_.rows * fx), static_cast<int>(original_image_.cols * fy), original_image_.type());
	  cv::resize(original_image_, resize_image_, resize_image_.size(), cv::INTER_LANCZOS4);
  }

  // ���ʉ摜
  cv::Mat resize_image(void) { 
    if(is_resize_) { 
      return resize_image_; 
    } else { 
      return cv::Mat(); 
    } 
  }
  
  // ���摜
  cv::Mat original_image(void) {
    if(is_original_) { 
      return original_image_; 
    } else { 
      return cv::Mat(); 
    } 
  }
  void set_original_image(const cv::Mat& original_image) { 
    original_image_ = original_image; 
    is_original_ = true; 
  }

private:

  bool is_original_;
  bool is_resize_;
  cv::Mat original_image_;
  cv::Mat resize_image_;

};

#endif // OPENCV_RESIZE_H_