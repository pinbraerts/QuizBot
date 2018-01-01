import threading
from collections import deque

class UserThread(threading.Thread):
    def __init__(self, bot, uid, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.bot = bot
        self.ok = True
        self.updates = deque()
        self.uid = uid
        self.log = open("log.log", "w")

    def run(self):
        while self.run:
            print("ok", file=self.log)
            while self.updates:
                if not self.ok: return
                upd = self.updates.popleft()
                self.bot.sendMessage(self.uid, "ok")

    def startReturn(self):
        self.start()
        return self

    def __delete__(self):
        self.log.close()
