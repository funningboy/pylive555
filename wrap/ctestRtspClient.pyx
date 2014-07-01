
from libcpp cimport bool, string, vector
from libc.string cimport const_char, const_uchar

cdef extern from "waptestRtspClient.h":
    cdef cppclass waptestRtspClient:
        waptestRtspClient()
        void onCreate(const_char* progName, const_char* rtspURL)
        void onRun()
        void onDestory()
    #cdef cppclass frame:

    #cdef cppclass frameHandler:
    #    framHandler()
    #    void onReceive()
    #    void onSend()
#@ no gc
cdef class PywaptestRtspClient:
    cdef waptestRtspClient *thisptr
    def __cinit__(self):
        self.thisptr = new waptestRtspClient()
    def __dealloc__(self):
        del self.thisptr
    def on_create(self, prog_nm, rtsp_url):
        self.thisptr.onCreate(prog_nm, rtsp_url)
    def on_run(self):
        self.thisptr.onRun()
    def on_destory(self):
        self.thisptr.onDestory()
