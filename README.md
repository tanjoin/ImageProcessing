ImageProcessing
===============

OpenCVを使った画像処理プログラム集

設定  
===================  
#ａ．環境変数を設定する  
変数名：OpenCV  
変数値：例．C:\OpenCV2.3.1\build  

[Visual C++]  
  プロジェクトのプロパティの[構築プロパティ]にある  
  
  [VC++ ディレクトリ]で 
  インクルード　ディレクトリ : 例．$(OpenCV)\include;  
  参照　ディレクトリ : 例．$(OpenCV)\x64\vc10\bin;  
  ライブラリ　ディレクトリ : 例．$(OpenCV)\x64\vc10\lib;  
  を追加する  
  
  [リンカー] - [入力]で  
  追加の依存ファイル：  
    opencv_calib3d242.lib  
    opencv_contrib242.lib  
    opencv_core242.lib  
    opencv_features2d242.lib  
    opencv_flann242.lib  
    opencv_gpu242.lib  
    opencv_haartraining_engine.lib  
    opencv_highgui242.lib  
    opencv_imgproc242.lib  
    opencv_legacy242.lib  
    opencv_ml242.lib  
    opencv_nonfree242.lib  
    opencv_objdetect242.lib  
    opencv_photo242.lib  
    opencv_stitching242.lib  
    opencv_ts242.lib  
    opencv_video242.lib  
    opencv_videostab242.lib  
  
#ｂ．Pathを設定し、pragma commentを使ってlibを設定する  
  
変数名：Path  
変数値：例．C:\OpenCV2.3.1\build\x86\vc10\bin;  
  
例．  
  
    #include <opencv2\opencv.hpp>  
  
    #ifdef _DEBUG  
        //Debugモードの場合  
        #pragma comment(lib,"opencv_core231d.lib")  
        #pragma comment(lib,"opencv_imgproc231d.lib")  
        #pragma comment(lib,"opencv_highgui231d.lib")  
        #pragma comment(lib,"opencv_objdetect231d.lib")  
        //以下、必要に応じて追加  
        //#pragma comment(lib,"opencv_ml231d.lib")  
        //#pragma comment(lib,"opencv_features2d231d.lib")  
        //#pragma comment(lib,"opencv_video231d.lib")  
        //#pragma comment(lib,"opencv_calib3d231d.lib")  
        //#pragma comment(lib,"opencv_flann231d.lib")  
        //#pragma comment(lib,"opencv_contrib231d.lib")  
        //#pragma comment(lib,"opencv_legacy231d.lib")  
        //#pragma comment(lib,"opencv_gpu231d.lib")  
    #else  
        //Releaseモードの場合  
        #pragma comment(lib,"opencv_core231.lib")  
        #pragma comment(lib,"opencv_imgproc231.lib")  
        #pragma comment(lib,"opencv_highgui231.lib")  
        #pragma comment(lib,"opencv_objdetect231.lib")  
        //以下、必要に応じて追加  
        //#pragma comment(lib,"opencv_ml231.lib")  
        //#pragma comment(lib,"opencv_features2d231.lib")  
        //#pragma comment(lib,"opencv_video231.lib")  
        //#pragma comment(lib,"opencv_calib3d231.lib")  
        //#pragma comment(lib,"opencv_flann231.lib")  
        //#pragma comment(lib,"opencv_contrib231.lib")  
        //#pragma comment(lib,"opencv_legacy231.lib")  
        //#pragma comment(lib,"opencv_gpu231.lib")  
    #endif  


OpenCV-waitKey-with-cursor-key
==============================

cv::waitkeyを使いやすくした 
(主にenumを作成)


    #include <iostream>
    
    #include "opencv_waitkey_with_cursor_key.h"
    
    int main(void){
    
      cv::Mat img = cv::imread("sample.jpg", cv::IMREAD_UNCHANGED);
      
      while(true) {
    
        cv::imshow("img", img);
        std::cout << 
          OpenCVWaitKeyWithCursorKey::inputToString(OpenCVWaitKeyWithCursorKey::waitKey(0))
        << std::endl;
    
      }
    
      return 0;
    }
    

足りない所はpull request



OpenCV-Resize
=============

画像サイズを変更する。  

-バイリニア補間
bilinear
-バイキュービック補間
bi_cubic
-Lanczos法の補間
lanczos4

サンプルコード
    
    #include "opencv_resize.h"
    
    int main(void) {
      
      return 0;
    }
        



OpenCV-PNG-image-with-Silhouette
===========================================
  
OpenCVを使った透明度有りPNG画像作成プログラム  
  
サンプルコード  

    #include "create_png_with_opencv.h"
    
    int main(void) {
    
      OpenCVPNGImageWithSilhouette cpng("capture.jpg", "silhouette.jpg");
      cpng.show();
      cpng.write("dst2.png", true);
      cpng.show();
    
      return 0;
    }
    

HistogramWithOpenCV  
===================  
  
OpenCVを使ってヒストグラムを生成  
  
  
サンプルコード

    
    #include "opencv_histogram.h"
    
    int main(void) {
      cv::Mat src = cv::imread("src.png", cv::IMREAD_UNCHANGED);
      OpenCVHistogram hist(src);
      hist.CreateHistogram();
      hist.write("dst.png");
      cv::Mat dst = hist.histogram_image();
      cv::imshow("背景ヒストグラム", dst);
      cv::waitKey(0);
      return 0;
    }

