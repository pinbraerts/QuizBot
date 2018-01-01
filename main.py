#!/usr/bin/python3

from telegram import Bot
from os.path import join, realpath, dirname
import threading
from collections import defaultdict

from UserThread import UserThread
from util.KeyDefaultDict import KeyDefaultDict

bot = Bot(open(join(dirname(realpath(__file__)), "data", "token")).read())

threads = KeyDefaultDict(lambda key: UserThread(bot, key).startReturn())

try:
    lastUpdate = 0
    while True:
        upds = bot.getUpdates(lastUpdate)
        for upd in upds:
            threads[upd.effective_user.id].updates.append(upd)
        if upds:
            lastUpdate = upds[-1].update_id + 1
finally:
    for i in threads.values():
        i.ok = False
