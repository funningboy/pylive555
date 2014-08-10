#ifndef __BASEDECODERTEST_H__
#define __BASEDECODERTEST_H__

#include "test_stdint.h"
#include <limits.h>
#include <fstream>
#include "codec_api.h"
#include <iostream>

#include "utils/BufferedData.h"

using namespace std;

class waptestDecH264;
struct Plane;
struct Frame;

typedef void (*pyfunc)(Frame *frame, void *user_data);

struct Plane {
  const uint8_t* data;
  int width;
  int height;
  int stride;
};

struct Frame {
  Plane y;
  Plane u;
  Plane v;
};


class waptestDecH264 {
 public:

  waptestDecH264();
  ~waptestDecH264();
//  bool DecodeNextFrame (Callback* cbk);

 public:
  void DecodeFrame (const uint8_t* src, int sliceSize);
  void onFrameCallback(Frame *frame);
  void registerCallback(pyfunc func, void* user_data);

 private:
  ISVCDecoder* decoder_;
  BufferedData buf_;
  pyfunc func;
  void* user_data;
};

#endif //__BASEDECODERTEST_H__
