
#include <fstream>
#include <gtest/gtest.h>
#include "codec_def.h"
#include "codec_app_def.h"
#include "utils/BufferedData.h"
#include "waptestDecH264.h"

waptestDecH264::waptestDecH264() {
  long rv = WelsCreateDecoder (&decoder_);
  ASSERT_EQ (0, rv);
  ASSERT_TRUE (decoder_ != NULL);

  SDecodingParam decParam;
  memset (&decParam, 0, sizeof (SDecodingParam));
  decParam.eOutputColorFormat  = videoFormatI420;
  decParam.uiTargetDqLayer = UCHAR_MAX;
  decParam.eEcActiveIdc = ERROR_CON_SLICE_COPY;
  decParam.sVideoProperty.eVideoBsType = VIDEO_BITSTREAM_DEFAULT;

  rv = decoder_->Initialize (&decParam);
  ASSERT_EQ (0, rv);
}

waptestDecH264::~waptestDecH264() {}

void
waptestDecH264::DecodeFrame (const uint8_t* src, int sliceSize) {
  uint8_t* data[3];
  SBufferInfo bufInfo;
  memset (data, 0, sizeof (data));
  memset (&bufInfo, 0, sizeof (SBufferInfo));

//  DECODING_STATE rv = decoder_->DecodeFrame2 (src, sliceSize, data, &bufInfo);
//  //ASSERT_TRUE (rv == dsErrorFree);
//
//  if (bufInfo.iBufferStatus == 1) {
//    Frame frame = {
//      {
//        // y plane
//        data[0],
//        bufInfo.UsrData.sSystemBuffer.iWidth,
//        bufInfo.UsrData.sSystemBuffer.iHeight,
//        bufInfo.UsrData.sSystemBuffer.iStride[0]
//      },
//      {
//        // u plane
//        data[1],
//        bufInfo.UsrData.sSystemBuffer.iWidth / 2,
//        bufInfo.UsrData.sSystemBuffer.iHeight / 2,
//        bufInfo.UsrData.sSystemBuffer.iStride[1]
//      },
//      {
//        // v plane
//        data[2],
//        bufInfo.UsrData.sSystemBuffer.iWidth / 2,
//        bufInfo.UsrData.sSystemBuffer.iHeight / 2,
//        bufInfo.UsrData.sSystemBuffer.iStride[1]
//      },
//    };
//    this->onFrameCallback(&frame);
//  }
}

void
waptestDecH264::registerCallback(pyfunc func, void *user_data)
{
  this->func = func;
  this->user_data = user_data;
}

void
waptestDecH264::onFrameCallback(Frame *frame)
{
  this->func(frame, this->user_data);
}
