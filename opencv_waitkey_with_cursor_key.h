#ifndef OPENCV_WAITKEY_WITH_CURSOR_KEY_H_
#define OPENCV_WAITKEY_WITH_CURSOR_KEY_H_

#include <string>
#include <sstream>
#include <opencv2/opencv.hpp>

class OpenCVWaitKeyWithCursorKey
{

public:

  enum CursorKey {
    CV_WAITKEY_CURSORKEY_TOP    = 2490368,
    CV_WAITKEY_CURSORKEY_BOTTOM = 2621440,
    CV_WAITKEY_CURSORKEY_RIGHT  = 2555904,
    CV_WAITKEY_CURSORKEY_LEFT   = 2424832,
    CV_WAITKEY_ENTER            = 13,
    CV_WAITKEY_ESC              = 27,
    CV_WAITKEY_SPACE            = 32,
    CV_WAITKEY_TAB              = 9,
    CV_WAITKEY_BACKSPACE        = 8,
    CV_WAITKEY_F1               = 7340032,
    CV_WAITKEY_F2               = 7405568,
    CV_WAITKEY_F3               = 7471104,
    CV_WAITKEY_F4               = 7536640,
    CV_WAITKEY_F5               = 7602176,
    CV_WAITKEY_F6               = 7667712,
    CV_WAITKEY_F7               = 7733248,
    CV_WAITKEY_F8               = 7798784,
    CV_WAITKEY_F9               = 7864320,
    CV_WAITKEY_F10              = 7929856,
    CV_WAITKEY_F11              = 7995392,
    CV_WAITKEY_DELETE           = 3014656,
    CV_WAITKEY_INSERT           = 2949120,
    CV_WAITKEY_HOME             = 2359296,
    CV_WAITKEY_END              = 2293760,
    CV_WAITKEY_PAGEDOWN         = 2228224,
    CV_WAITKEY_PAGEUP           = 2162688,
    CV_WAITKEY_CTRL_Z           = 26,
    CV_WAITKEY_CTRL_Y           = 25
  };

  static int waitKey(const int delay = 0) {
    return cv::waitKey(delay);
  }

  static std::string inputToString(int integer_of_returned_waitKey) {

    switch(integer_of_returned_waitKey) {

    case CV_WAITKEY_CURSORKEY_TOP:
      return "ª";
    case CV_WAITKEY_CURSORKEY_BOTTOM:
      return "«";
    case CV_WAITKEY_CURSORKEY_RIGHT:
      return "¨";
    case CV_WAITKEY_CURSORKEY_LEFT:
      return "©";
    case CV_WAITKEY_ENTER:
      return "[Enter]";
    case CV_WAITKEY_ESC:
      return "[ESC]";
    case CV_WAITKEY_SPACE:
      return "[SPACE]";
    case CV_WAITKEY_TAB:
      return "[TAB]";    
    case CV_WAITKEY_BACKSPACE:
      return "[BACKSPACE]";
    case CV_WAITKEY_F1:
      return "[F1]";
    case CV_WAITKEY_F2:
      return "[F2]";
    case CV_WAITKEY_F3:
      return "[F3]";
    case CV_WAITKEY_F4:
      return "[F4]";
    case CV_WAITKEY_F5:
      return "[F5]";
    case CV_WAITKEY_F6:
      return "[F6]";
    case CV_WAITKEY_F7:
      return "[F7]";
    case CV_WAITKEY_F8:
      return "[F8]";
    case CV_WAITKEY_F9:
      return "[F9]";
    case CV_WAITKEY_F10:
      return "[F10]";
    case CV_WAITKEY_F11:
      return "[F11]";
    case CV_WAITKEY_DELETE:
      return "[Delete]";
    case CV_WAITKEY_INSERT:
      return "[Insert]";
    case CV_WAITKEY_HOME:
      return "[Home]";
    case CV_WAITKEY_END:
      return "[End]";
    case CV_WAITKEY_PAGEDOWN:
      return "[Page Down]";
    case CV_WAITKEY_PAGEUP:
      return "[Page Up]";
    case CV_WAITKEY_CTRL_Z:
      return "[Ctrl+Z]";
    default:
      if(integer_of_returned_waitKey > 32 && 127 > integer_of_returned_waitKey) {
        char tmp[2];
        tmp[0] = integer_of_returned_waitKey;
        tmp[1] = 0;
        return std::string(tmp);
      } else {
        std::stringstream ss;
        ss << "[–¢‘Î‰ž‚È“ü—Í‚Å‚·] :"
           << integer_of_returned_waitKey;
        return  ss.str();
      }

    }

  }

};
typedef OpenCVWaitKeyWithCursorKey cvWait;

#endif // OPENCV_WAITKEY_WITH_CURSOR_KEY_H_