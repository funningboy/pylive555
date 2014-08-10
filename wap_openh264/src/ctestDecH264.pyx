
from libc.string cimport const_char, const_uchar
cimport numpy as np

cdef extern from "waptestDecH264.h":
    ctypedef unsigned char u_int8_t
    cdef struct Plane:
        unsigned char* data
        int width
        int height
        int stride
    cdef struct Frame:
        Plane y
        Plane u
        Plane v
    ctypedef void (*pyfunc)(Frame* frame, void *user_data)
    cdef cppclass waptestDecH264:
        waptestDecH264()
        void DecodeFrame(unsigned char* src, int sliceSize)
        void registerCallback(pyfunc func, void* user_data) nogil

cdef void callback(Frame* frame, void*func) nogil:
    with gil:
        try:
            yuv = (frame.y.data, frame.u.data, frame.v.data)
            print yuv
            #(<object>func)(yuv)
        except Exception as e:
            raise "compose yuv byte array fail"

cdef class cywaptestDecH264:
    cdef waptestDecH264 *thisptr
    def __cinit__(self):
        self.thisptr = new waptestDecH264()
    def __dealloc__(self):
        del self.thisptr
    def register_callback(self, func):
        with nogil:
            self.thisptr.registerCallback(callback, <void*>func)
    def on_run(self, frame):
        """ as numpy array frame """
    #    cdef np.ndarray[unsigned char, mode="c"] c_frame = np.ascontiguousarray(frame, dtype=np.uint8)
        cdef c_size = <int>(frame.shapes[0])
    #    self.thisptr.DecodeFrame(&c_frame[0], c_size)
    #def on_destory(self):
    #    self.thisptr.onDestory()
