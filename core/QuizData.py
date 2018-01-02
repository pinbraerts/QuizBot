from os.path import join, realpath, dirname, isfile
import struct

from util.KeyDefaultDict import KeyDefaultDict

class QuizData:
    instances = KeyDefaultDict()

    class QuizType:
        @staticmethod
        def write(file, num):
            file.write()

    def __init__(self, name):
        self.name = name
        self._file_name = join(
            dirname(realpath(__file__)), '..', 'data', 'quiz', self.name
        ) # `dirname $0`/../data/quiz/$name
        self.file = None

    @property
    def exists(self):
        if self._exists is None:
            self._exists = isfile(self._file_name)
        self._

    def save(self):
        with open(self._file_name, 'wb') as self.file:
            self.file.write(struct.pack('L', some_unsigned_long))
