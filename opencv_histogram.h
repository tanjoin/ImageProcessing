#ifndef OPENCV_HISTOGRAM_H_
#define OPENCV_HISTOGRAM_H_

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

class OpenCVHistogram
{

public:

  OpenCVHistogram() 
    : src_image_(cv::Mat()), is_src_image_(false), is_histogram_(false), is_histogram_image_(false),
      is_src_image_histogram_channel_(false), histogram_image_base_height_(200), histogram_(3) {}
  OpenCVHistogram(const cv::Mat& image) 
    : src_image_(image), is_src_image_(true), is_histogram_(false), is_histogram_image_(false),
      is_src_image_histogram_channel_(false), histogram_image_base_height_(200), histogram_(3) {}
  OpenCVHistogram(const std::string filename) 
    : src_image_(cv::imread(filename, cv::IMREAD_UNCHANGED)), 
      is_src_image_(true), is_histogram_(false), is_histogram_image_(false),
      is_src_image_histogram_channel_(false), histogram_image_base_height_(200), histogram_(3) {}
  virtual ~OpenCVHistogram() {}

  cv::Mat histogram_image(void) {
    if (this->is_histogram_image_) {
      return this->histogram_image_;
    } else {
      return cv::Mat();
    }
  }
  void set_histogram_image_base_height(int height) {
    this->histogram_image_base_height_ = height;
  }
  void CreateHistogram(void) {
    if (is_src_image_) {
      this->__create_histogram();
    }
  }
  void CreateHistogram(const cv::Mat& image) {
    this->__create_histogram();
  }
  void write(const std::string& filename) {
    
    if (this->is_histogram_) {
      this->__create_histogram_image();
    }
    if (this->is_histogram_image_) {
      std::vector<int> params(2);
      params[0] = cv::IMWRITE_PNG_COMPRESSION;
      params[1] = this->params_;
      std::string copyname = filename;
      std::cout << copyname << std::endl;
      if(!(this->isExtensionPNG(copyname))) {
        copyname.append(".png");
      }
      cv::imwrite(copyname, this->histogram_image_, params);
    }

  }

private:

  static const int histogram_image_base_width_ = 260;
  static const int histogram_size_ = 256;
  static const int hdims[];
  static const float hranges[];
  static const float* ranges[];
  static const cv::Scalar RED;
  static const cv::Scalar GREEN;
  static const cv::Scalar BLUE;
  static const cv::Scalar BLACK;
  static const cv::Scalar WHITE;
  static const cv::Scalar GRAY;
  static const cv::Scalar color_ch1[];
  static const cv::Scalar color_ch2[];
  static const cv::Scalar color_ch3[];
  static const cv::Scalar color_ch4[];
  static const cv::Scalar* color[];
  double histogram_max_;
  int histogram_image_base_height_;
  int src_image_histogram_channel_;
  bool is_src_image_histogram_channel_;
  bool is_src_image_;
  bool is_histogram_;
  bool is_histogram_image_;
  int params_;
	cv::Mat src_image_;
  cv::Mat histogram_image_;
  std::vector<cv::MatND> histogram_;

  void __create_histogram(void) {

    if (!(this->is_src_image_)) return;
    if(!(this->src_image_.data)) return;

    this->src_image_histogram_channel_ = this->src_image_.channels();
    this->is_src_image_histogram_channel_ = true;

    if(!(this->is_src_image_histogram_channel_)) return;
    
    if(this->src_image_histogram_channel_ == 1) {
      cv::calcHist(&(this->src_image_), 1, 0, cv::Mat(), (this->histogram_)[0], 1, OpenCVHistogram::hdims, OpenCVHistogram::ranges, true, false);
      cv::minMaxLoc((this->histogram_)[0], 0, &(this->histogram_max_));
    } else if (this->src_image_histogram_channel_ == 4) {
      std::vector<cv::Mat> split_image;
      cv::split(this->src_image_, split_image);
      cv::imshow("alpha", split_image[3]);
      cv::Mat rgb_image;
      cv::cvtColor(this->src_image_, rgb_image, CV_BGRA2BGR);
      for (int i = 0; i < rgb_image.channels(); ++i) {
        cv::calcHist(&rgb_image, 1, &i, split_image[3], (this->histogram_)[i], 1, OpenCVHistogram::hdims, OpenCVHistogram::ranges, true, false);
        double tmp_val;
        cv::minMaxLoc((this->histogram_)[i], 0, &tmp_val);
        this->histogram_max_ = (this->histogram_max_ < tmp_val) ? tmp_val : this->histogram_max_;
      }
    } else {
      for (int i = 0; i < this->src_image_histogram_channel_; ++i) {
        cv::calcHist(&(this->src_image_), 1, &i, cv::Mat(), (this->histogram_)[i], 1, OpenCVHistogram::hdims, OpenCVHistogram::ranges, true, false);
        double tmp_val;
        cv::minMaxLoc((this->histogram_)[i], 0, &tmp_val);
        this->histogram_max_ = (this->histogram_max_ < tmp_val) ? tmp_val : this->histogram_max_;
      }
    }

    this->is_histogram_ = true;
  }

  void __create_histogram_image(void) {
    std::cout << "[Start] write" << std::endl;
    if(!(this->is_histogram_)) return;
    std::cout << "[Start] write" << std::endl;
    if(this->histogram_.size() == 0) return;
    
    const int channels = this->src_image_histogram_channel_ < 4 ? this->src_image_histogram_channel_ : 3; 

    this->histogram_image_ = cv::Mat(cv::Size(OpenCVHistogram::histogram_image_base_width_ * channels, histogram_image_base_height_),
                                     CV_8UC3,
                                     cv::Scalar::all(255));

    for (int i = 0; i < channels; ++i) {      
      (this->histogram_)[i].convertTo((this->histogram_)[i], (this->histogram_)[i].type(), this->histogram_max_ ? 200.0 / this->histogram_max_ : 0.0, 0);

      for (int j = 0; j < this->histogram_size_; ++j) {
        int bin_w = cv::saturate_cast<int>((double)(OpenCVHistogram::histogram_image_base_width_) / this->histogram_size_);
        cv::rectangle(this->histogram_image_, 
          cv::Point(    j * bin_w + ( i * OpenCVHistogram::histogram_image_base_width_ ), this->histogram_image_.rows),
          cv::Point((j+1) * bin_w + ( i * OpenCVHistogram::histogram_image_base_width_ ), this->histogram_image_.rows - cv::saturate_cast<int>((this->histogram_)[i].at<float>(j))),
          color[channels - 1][i],
          -1);
      }
    }
    this->is_histogram_image_ = true;
  }

  bool isExtensionPNG(const std::string &src) {
    size_t index = src.rfind(".", src.size());
    if (index == std::string::npos) {
      return false;
    }
    std::string extension;
    extension = src.substr(index + 1);
    extension = this->SetLower(extension);
    if (!extension.compare("png")) {
      return true;
    } else {
      return false;
    }
  }

  std::string SetLower(const std::string &src) {
    char fname[1024];
    strcpy_s(fname, src.c_str());
    for (int i = 0; fname[i] != '\0'; ++i) {
      fname[i] = tolower(fname[i]);
    }
    std::string str = fname;
    return str;
  }
};

const int OpenCVHistogram::hdims[]      = { OpenCVHistogram::histogram_size_ };
const float OpenCVHistogram::hranges[]  = {0, 256};
const float* OpenCVHistogram::ranges[]  = {hranges};
const cv::Scalar OpenCVHistogram::RED   = cv::Scalar(0, 0, 255);
const cv::Scalar OpenCVHistogram::GREEN = cv::Scalar(0, 255, 0);
const cv::Scalar OpenCVHistogram::BLUE  = cv::Scalar(255, 0, 0);
const cv::Scalar OpenCVHistogram::BLACK = cv::Scalar(0, 0, 0);
const cv::Scalar OpenCVHistogram::WHITE = cv::Scalar(255, 255, 255);
const cv::Scalar OpenCVHistogram::GRAY  = cv::Scalar(128, 128, 128);
const cv::Scalar OpenCVHistogram::color_ch1[] = { OpenCVHistogram::BLACK };
const cv::Scalar OpenCVHistogram::color_ch2[] = { OpenCVHistogram::BLUE, 
                                                  OpenCVHistogram::RED };
const cv::Scalar OpenCVHistogram::color_ch3[] = { OpenCVHistogram::BLUE,
                                                  OpenCVHistogram::GREEN, 
                                                  OpenCVHistogram::RED };
const cv::Scalar OpenCVHistogram::color_ch4[] = { OpenCVHistogram::BLUE, 
                                                  OpenCVHistogram::GREEN, 
                                                  OpenCVHistogram::RED, 
                                                  OpenCVHistogram::GRAY };
const cv::Scalar* OpenCVHistogram::color[]    = { OpenCVHistogram::color_ch1, 
                                                  OpenCVHistogram::color_ch2,
                                                  OpenCVHistogram::color_ch3,
                                                  OpenCVHistogram::color_ch4 };

#endif // OPENCV_HISTOGRAM_H_