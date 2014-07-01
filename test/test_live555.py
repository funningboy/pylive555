import live555
import threading


class PywaptestRtspClient(threading.Thread):
    """ PywaptestRtspClient as thread """

    def __init__(self):
        super(PywaptestRtspClient, self).__init__()
        self._client = live555.PywaptestRtspClient()

    def on_create(self, prog_nm, rtsp_url):
        self._client.on_create(prog_nm, rtsp_url)

    def run(self):
        """ callback thread run """
        self._client.on_run()

    def on_destory(self):
        self._client.on_destory()

class PywaptestFrameHandler(object):
    """ PywaptestFrameHandler """

    def __init__(self):

    def on_port

    def on_export

def main():
    thread = PywaptestRtspClient('PywaptestRtspClient', 'rtsp://192.168.1.6:1234')
    thread.daemon = True
    thread.start()
    thread.on_destory()
    thread.join()

if __name__ == '__main__':
    main()
