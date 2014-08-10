
from libcpp cimport bool, string, vector
from libc.string cimport const_char, const_uchar
import numpy as np

cdef extern from "waptestRtspClient.h":
    ctypedef unsigned char u_int8_t
    ctypedef void (*pyfunc)(unsigned char* frame, int size, void *user_data)
    cdef cppclass waptestRtspClient:
        waptestRtspClient()
        void onCreate(const_char* progName, const_char* rtspURL)
        void onRun() nogil
        void onDestory()
        void registerCallback(pyfunc func, void* user_data) nogil

cdef void callback(unsigned char* frame, int size, void* func) nogil:
    """ decode ad numpy array """
    with gil:
        try:
            # h264 header encode
            datalist = [0x0, 0x0, 0x0, 0x1]
            for i in range(size):
                datalist.append(frame[i])
            arr = np.array(datalist, dtype=np.uint8)
            (<object>func)(arr)
        except Exception as e:
            raise "compose h264 numpy byte array fail"

cdef class cywaptestRtspClient:
    cdef waptestRtspClient *thisptr
    def __cinit__(self):
        self.thisptr = new waptestRtspClient()
    def __dealloc__(self):
        del self.thisptr
    def on_create(self, const_char* prog_nm, const_char* rtsp_url):
        self.thisptr.onCreate(prog_nm, rtsp_url)
    def register_callback(self, func):
        with nogil:
            self.thisptr.registerCallback(callback, <void*>func)
    def on_run(self):
        self.thisptr.onRun()
    def on_destory(self):
        self.thisptr.onDestory()

