from core.UserProcessor import UserProcessor

class Processor(UserProcessor):
    def cmdStart(self): # TODO:, testName=None):
        self.sendMessage("ok")

    def cmdCreate(self, testName=None):
        while testName is None: # TODO: or not existsTest(testName):
            if testName is not None: # test is not exists
                self.sendMessage()
            testName = self.ask("Please, enter test name!")
        self.sendMessage("Create test: " + testName)

    def cmdModify(self, testName=None):
        while testName is None:
            testName = self.ask("Please, enter test name!")
        # TODO: if not existsTest(testName):
        # TODO:     answer = self.ask("Test {testName} isn't exists, create new test?")
        # TODO:     if positiveAnswer(answer):
        # TODO:         createNewTest(test)
        # TODO:     else:
        # TODO:         self.sendMessage("Test modifying canceled")
        # TODO:         return
        self.sendMessage("Modifying test " + testName)

for k, v in Processor.__dict__.items():
    if k.startswith('cmd'):
        Processor.cmds[k[3:].lower()] = v
