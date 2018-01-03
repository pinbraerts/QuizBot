#ifndef BOT_H
#define BOT_H

#include <sstream>

#include "Https.h"
#include "../json/JSONParser.h"

class Bot {
private:
    std::string prefix = "https://api.telegram.org/bot";

public:
    Bot(std::string token) {
        prefix += token;
        prefix += '/';
    }

    void getMe(JSONAny& res) {
        res = JSONAny { std::istringstream { Https(prefix + "getMe").make() } };
    }
};

#endif // !BOT_H
