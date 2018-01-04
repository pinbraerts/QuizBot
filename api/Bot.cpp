#include "Bot.h"

Bot::Bot(std::string token): stdHttps { prefix } {
    stdHttps << token << '/';
}

void Bot::sendMessage(std::string chatUsername, std::string text) {
    json::object res {
        nh() << "sendMessage?chat_id=" << chatUsername
            << "&text=" << text << Https::make
    };
    if(!res["ok"]) throw std::runtime_error("Telegram error! " +
            res.get<json::String>("description"));
}

User Bot::getMe() {
    json::object res { nh() << "getMe" << Https::make };
    if(!res["ok"]) throw std::runtime_error("Telegram error! " +
            res.get<json::String>("description"));
    return res.getItem<json::Object>("result");
}

void Bot::sendMessage(User::Id chatId, std::string text) {
    json::object res {
        nh() << "sendMessage?chat_id=" << chatId
            << "&text=" << text << Https::make
    };
    if(!res["ok"]) throw std::runtime_error("Telegram error! " +
            res.get<json::String>("description"));
}
