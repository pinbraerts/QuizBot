#ifndef BOT_H
#define BOT_H

#include <sstream>

#include "Https.h"
#include "../json/Parser.h"
#include "User.h"

class Bot {
private:
    std::string prefix = "https://api.telegram.org/bot";

public:
    Bot(std::string token) {
        prefix += token;
        prefix += '/';
    }

    User getMe() {
        json::object res { std::istringstream { Https(prefix + "getMe").make() } };
        if(!res.get<json::Boolean>("ok")) throw std::runtime_error("Telegram error!");
        return res.getItem<json::Object>("result");
    }
};

#endif // !BOT_H
