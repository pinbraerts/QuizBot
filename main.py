from telegram import Bot
from os.path import join

bot = Bot(open(join("data", "token")).read())
