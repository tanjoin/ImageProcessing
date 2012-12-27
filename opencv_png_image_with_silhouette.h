#ifndef OPENCV_PNG_IMAGE_WITH_SILHOUETTE_H_
#define OPENCV_PNG_IMAGE_WITH_SILHOUETTE_H_

#include <iostream>
#include <cstring>
#include <vector>
#include <opencv2/opencv.hpp>

class OpenCVPNGImageWithSilhouette
{
public:
  OpenCVPNGImageWithSilhouette(void) : src_(), silhouette_(), is_src_(false), is_silhouette_(false), is_dst_(false), params_(3) {}
  OpenCVPNGImageWithSilhouette(const cv::Mat& src, const cv::Mat& silhouette) : src_(src), silhouette_(silhouette), is_src_(true), is_silhouette_(true), is_dst_(false), params_(3) {}
  OpenCVPNGImageWithSilhouette(const std::string& src, const std::string& silhouette) : is_src_(true), is_silhouette_(true), is_dst_(false), params_(3) {
    this->src_ = cv::imread(src, cv::IMREAD_UNCHANGED);
    this->silhouette_ = cv::imread(silhouette, cv::IMREAD_GRAYSCALE);
  }
  virtual ~OpenCVPNGImageWithSilhouette(void) {}

  void set_src(const cv::Mat& src) {
    this->src_ = src;
    this->is_src_ = true;
  }
  void set_silhouette(const cv::Mat& silhouette) {
    this->silhouette_ = silhouette;
    this->is_silhouette_ = true;
  }
  void set_params(const int& params) {
    this->params_ = params;
  }
  cv::Mat dst() {
    if (this->is_dst_) {
      return this->dst_;
    } else {
      std::cout << 
        "[Error OpenCVPNGImageWithSilhouette@dst] PNG Image isn't created ." 
      << std::endl;
      return cv::Mat();
    }
  }
  void write(const std::string& filename, bool isInverse = false) {
    if(isInverse) {
      cv::bitwise_not(this->silhouette_, this->silhouette_);
    }
    this->__CreatePNGImage();
    if (this->is_dst_) {
      std::vector<int> params(2);
      params[0] = cv::IMWRITE_PNG_COMPRESSION;
      params[1] = this->params_;
      std::string copyname = filename;
      std::cout << copyname << std::endl;
      if(!this->isExtensionPNG(copyname)) {
        copyname.append(".png");
      }
      cv::imwrite(copyname, this->dst_, params);
    }
  }
  void show() {
    if(this->is_src_) {
      cv::imshow("src", this->src_);
    }
    if(this->is_silhouette_) {
      cv::imshow("silhouette", this->silhouette_);
    }
    if(this->is_dst_) {
      cv::imshow("dst", this->dst_);
    }
    cv::waitKey(0);
  }


private:
  bool is_src_;
  bool is_silhouette_;
  bool is_dst_;
  cv::Mat src_;
  cv::Mat silhouette_;
  cv::Mat dst_;
  int params_;

  void __CreatePNGImage(void) {
    // pngÇ∆Ç©
    if (this->is_src_ && this->is_silhouette_ && this->src_.channels() == 4) {
      this->dst_ = cv::Mat(this->src_.size(), CV_8UC4);
      for (int y = 0; y < this->src_.rows; ++y) {
        const cv::Vec4b* src_ptr = this->src_.ptr<cv::Vec4b>(y);
        const uchar* bit_ptr = this->silhouette_.ptr<uchar>(y);
        cv::Vec4b* dst_ptr = this->dst_.ptr<cv::Vec4b>(y);
        for (int x = 0; x < this->src_.cols; ++x) {
          // èàóù
          dst_ptr[x][0] = src_ptr[x][0];
          dst_ptr[x][1] = src_ptr[x][1];
          dst_ptr[x][2] = src_ptr[x][2];
          if(bit_ptr[x] < 128) {
            dst_ptr[x][3] = 0;
          } else {
            dst_ptr[x][3] = 255;
          }
        }
      }
      this->is_dst_ = true;
    }
    // jpgÇ∆Ç©
    if (this->is_src_ && this->is_silhouette_ && this->src_.channels() == 3) {
      this->dst_ = cv::Mat(this->src_.size(), CV_8UC4);
      for (int y = 0; y < this->src_.rows; ++y) {
        const cv::Vec3b* src_ptr = this->src_.ptr<cv::Vec3b>(y);
        const uchar* bit_ptr = this->silhouette_.ptr<uchar>(y);
        cv::Vec4b* dst_ptr = this->dst_.ptr<cv::Vec4b>(y);
        for (int x = 0; x < this->src_.cols; ++x) {
          // èàóù
          dst_ptr[x][0] = src_ptr[x][0];
          dst_ptr[x][1] = src_ptr[x][1];
          dst_ptr[x][2] = src_ptr[x][2];
          if(bit_ptr[x] < 128) {
            dst_ptr[x][3] = 0;
          } else {
            dst_ptr[x][3] = 255;
          }
        }
      }
      this->is_dst_ = true;
    }
    // grayscaleÇ∆Ç©
    if (this->is_src_ && this->is_silhouette_ && this->src_.channels() == 1) {
      this->dst_ = cv::Mat(this->src_.size(), CV_8UC4);
      for (int y = 0; y < this->src_.rows; ++y) {
        const uchar* src_ptr = this->src_.ptr<uchar>(y);
        const uchar* bit_ptr = this->silhouette_.ptr<uchar>(y);
        cv::Vec4b* dst_ptr = this->dst_.ptr<cv::Vec4b>(y);
        for (int x = 0; x < this->src_.cols; ++x) {
          // èàóù
          dst_ptr[x][0] = src_ptr[x];
          dst_ptr[x][1] = src_ptr[x];
          dst_ptr[x][2] = src_ptr[x];
          if(bit_ptr[x] < 128) {
            dst_ptr[x][3] = 0;
          } else {
            dst_ptr[3] = 255;
          }
        }
      }
      this->is_dst_ = true;
    }
  }

  bool isExtensionPNG(const std::string &src) {
    int index = src.rfind(".", src.size());
    if (index == std::string::npos) {
      return false;
    }
    std::string extension;
    extension = src.substr(index + 1);
    extension = this->SetLower(extension);
    if (extension.compare("png")) {
      return true;
    } else {
      return false;
    }
  }

  std::string SetLower(const std::string &src) {
    char fname[1024];
    strcpy(fname, src.c_str());
    for (int i = 0; fname[i] != '\0'; ++i) {
      fname[i] = tolower(fname[i]);
    }
    std::string str = fname;
    return str;
  }

};

#endif // OPENCV_PNG_IMAGE_WITH_SILHOUETTE_H_