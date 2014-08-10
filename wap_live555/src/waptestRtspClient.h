
#ifndef _WAPTEST_RTSPCLIENT_
#define _WAPTEST_RTSPCLIENT_

#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"
#include <iostream>
#include <list>
#include <ostream>
#include <fstream>
#include <string>

using namespace std;

// by default, print verbose output from each "RTSPClient"
#define RTSP_CLIENT_VERBOSITY_LEVEL 1

typedef void (*pyfunc)(u_int8_t *frame, int size, void *user_data);

class StreamClientState;
class ourRTSPClient;
class waptestRtspClient;
class DummySink;


// RTSP 'response handlers':
void continueAfterDESCRIBE(RTSPClient* rtspClient, int resultCode, char* resultString);
void continueAfterSETUP(RTSPClient* rtspClient, int resultCode, char* resultString);
void continueAfterPLAY(RTSPClient* rtspClient, int resultCode, char* resultString);

// Other event handler functions:
// called when a stream's subsession (e.g., audio or video substream) ends
void subsessionAfterPlaying(void* clientData);
// called when a RTCP "BYE" is received for a subsession
void subsessionByeHandler(void* clientData);
// called at the end of a stream's expected duration (if the stream has not already signaled its end using a RTCP "BYE")
void streamTimerHandler(void* clientData);

// The main streaming routine (for each "rtsp://" URL):
void openURL(UsageEnvironment& env, char const* progName, char const* rtspURL);

// Used to iterate through each stream's 'subsessions', setting up each one:
void setupNextSubsession(RTSPClient* rtspClient);

// Used to shut down and close a stream (including its "RTSPClient" object):
void shutdownStream(RTSPClient* rtspClient, int exitCode = 1);

// Define a class to hold per-stream state that we maintain throughout each stream's lifetime:
class StreamClientState {
public:
  StreamClientState();
  virtual ~StreamClientState();

public:
  MediaSubsessionIterator* iter;
  MediaSession* session;
  MediaSubsession* subsession;
  TaskToken streamTimerTask;
  double duration;
};

// Define a data sink (a subclass of "MediaSink") to receive the data for each subsession (i.e., each audio or video 'substream').
// In practice, this might be a class (or a chain of classes) that decodes and then renders the incoming audio or video.
// Or it might be a "FileSink", for outputting the received data into a file (as is done by the "openRTSP" application).
// In this example code, however, we define a simple 'dummy' sink that receives incoming data, but does nothing with it.

class DummySink: public MediaSink {
public:
  static DummySink* createNew(UsageEnvironment& env,
			      MediaSubsession& subsession, // identifies the kind of data that's being received
			      char const* streamId = NULL,
            RTSPClient* rtspClient = NULL); // identifies the stream itself (optional)

private:
  DummySink(UsageEnvironment& env, MediaSubsession& subsession, char const* streamId, RTSPClient* rtspClient);
    // called only by "createNew()"
  virtual ~DummySink();

  static void afterGettingFrame(void* clientData, unsigned frameSize,
                                unsigned numTruncatedBytes,
				struct timeval presentationTime,
                                unsigned durationInMicroseconds);
  void afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
			 struct timeval presentationTime, unsigned durationInMicroseconds);

private:
  // redefined virtual functions:
  virtual Boolean continuePlaying();

private:
  u_int8_t* fReceiveBuffer;
  MediaSubsession& fSubsession;
  char* fStreamId;
  RTSPClient* fRtspClient;
  int first;
};


class ourRTSPClient: public RTSPClient {
public:
  static ourRTSPClient* createNew(UsageEnvironment& env, char const* rtspURL,
				  int verbosityLevel = 0,
				  char const* applicationName = NULL,
				  portNumBits tunnelOverHTTPPortNum = 0);
 public:
  void registerCallback(pyfunc func, void *user_data);
  void onFrameCallback(u_int8_t* frame, long size);
  void onDebug(u_int8_t* frame, long size);
protected:
  ourRTSPClient(UsageEnvironment& env, char const* rtspURL,
		int verbosityLevel, char const* applicationName, portNumBits tunnelOverHTTPPortNum);
    // called only by createNew();
  virtual ~ourRTSPClient();

public:
  StreamClientState scs;
  pyfunc func;
  void* user_data;
  H264VideoFileSink* fileSink;
};


// wap RTSP Client
class waptestRtspClient {
  public:
    waptestRtspClient() {}
   ~waptestRtspClient() {}
  public:
   void onCreate(char const* progName, char const* rtspURL);
   void onRun();
   void onDestory();
   void registerCallback(pyfunc func, void *user_data);
  private:
   pyfunc func;
   void* user_data;
};



#endif
