import time

from base.BaseThread import BaseThread

class UserProcessor(BaseThread):
    UNKNOWN_CMD_ERROR = "Error: Unknown command: '{}'!"
    WRONG_ARGUMENTS_ERROR = "Error: Wrong arguments {} for command {}!"

    class EventType:
        Nothing = 0
        Message = 1
        Command = 2

    def _wait_generator_factory(self):
        while not self._stop_event:
            if self.msg is not None:
                msg = self.msg
                self.msg = None
                yield self.EventType.Message, msg
            if self.cmd is not None:
                cmd = self.cmd
                self.cmd = None
                yield self.EventType.Command, cmd
            time.sleep(2)

    def __init__(self, bot, uid):
        super().__init__()
        self.bot = bot
        self.uid = uid
        self.msg = None
        self.cmd = None
        self._wait_generator = self._wait_generator_factory()
        self.wait = lambda: next(self._wait_generator)

    def step(self):
        if self.cmd is not None:
            _, cmd, args = self.cmd
            self.cmd = None
            try:
                proc = self.cmds[cmd]
                try:
                    proc(self, *args)
                except TypeError as e:
                    print(e)
                    self.sendMessage(
                        self.WRONG_ARGUMENTS_ERROR.format(args, cmd)
                    )
            except KeyError:
                self.sendMessage(self.UNKNOWN_CMD_ERROR.format(cmd))

    def update(self, upd):
        if upd.message is not None:
            msg = upd.message.text
            if msg.startswith('/'):
                cmd, *args = msg.split(' ')
                cmd = cmd[1:]
                self.cmd = upd.message, cmd, args
            else:
                self.msg = upd.message

    def ask(self, question): # TODO:, *answers):
        self.sendMessage(question)
        ev, data = self.wait()
        if ev == self.EventType.Message:
            return data.text

    def cmdStart(self): # TODO:, testId=None):
        self.sendMessage("ok")

    def cmdCreate(self, testId=None):
        while testId is None: # TODO: or not existsTest(testId):
            testId = self.ask("Please, enter test id!")
        self.sendMessage("Modifying test: " + testId)

    def sendMessage(self, *args):
        return self.bot.sendMessage(self.uid, *args)

    cmds = {
        "start": cmdStart,
        "create": cmdCreate
    }
