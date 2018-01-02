import threading
import time

class BaseThread(threading.Thread):
    def __init__(self):
        super().__init__()
        self._stop_event = False

    def step(self):
        raise NotImplementedError("BaseThread.step")

    def run(self):
        while not self._stop_event:
            self.step()
            time.sleep(2)

    def stop(self):
        self._stop_event = True

    def startReturn(self):
        self.start()
        return self
