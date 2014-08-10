import openh264
import threading
import time

DEBUG = False

#def on_frame_callback():
#    global DEBUG
#    pass
#
#class PywaptestDec264(threading.Thread):
#    """ PywaptestDec264 as thread """
#
#    def __init__(self):
#        threading.Thread.__init__(self)
#        self._dec264 = openh264.cywaptestDecH264()
#
#    def run(self):
#        """ as thread run """
#        self._dec264.on_run("")
#
#    def on_destory(self):
#        """ destory thread """
#        self._dec264.on_destory()
#

def tt():
    pass

def main():
#    th_0 = PywaptestDec264()
#    th_0.register_callback(on_frame_callback)
#    th_0.daemon = True
#    th_0.start()
#    time.sleep(2)
#    th_0.on_destory()
#    th_0.join()

    H264 = openh264.cywaptestDecH264()
    H264.register_callback(tt)
    H264.on_run("",)

if __name__ == '__main__':
    main()
