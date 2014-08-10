import live555
import threading
import time
import openh264
import numpy as np

# open test.h264 via VLC or ffplay
# ffplay test.h264
FOUT = open("test.h264", 'wb')
DEBUG = True

def tt():
    pass

H264 = openh264.cywaptestDecH264()
H264.register_callback(tt)


def on_frame_callback(frame):
    """ :param frame : numpy array """
    global DEBUG
    global FOUT
    global H264
    if DEBUG:
        H264.on_run(frame)
        FOUT.write(frame.tostring())

class PywaptestRtspClient(threading.Thread):
    """ PywaptestRtspClient as thread """

    def __init__(self):
        threading.Thread.__init__(self)
        self._client = live555.cywaptestRtspClient()

    def on_create(self, prog_nm, rtsp_url):
        """ create RTSP client channel """
        self._client.on_create(prog_nm, rtsp_url)

    def register_callback(self, func):
        """ register callback func before create and run """
        self._client.register_callback(func)

    def run(self):
        """ as thread run """
        self._client.on_run()

    def on_destory(self):
        """ destory thread """
        self._client.on_destory()

#class testPywaptestRtspClient(unit)

def main():
    #import Queue
    #320x240, 25 fps, 25 tbr
    th_0 = PywaptestRtspClient()
    th_0.register_callback(on_frame_callback)
    th_0.on_create('PywaptestRtspClient', 'rtsp://192.168.1.6:1234')#'rtsp://192.168.1.6:1234?h264=200-20-320-240')
    th_0.daemon = True
    th_0.start()
    time.sleep(5)
    th_0.on_destory()
    th_0.join()

if __name__ == '__main__':
    main()
