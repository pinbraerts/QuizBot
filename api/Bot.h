#ifndef BOT_H
#define BOT_H

#include <sstream>

#include "Https.h"
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
        json::object res { Https(prefix + "getMe").make() };
        if(!res["ok"]) throw std::runtime_error("Telegram error! " +
                res.get<json::String>("description"));
        return res.getItem<json::Object>("result");
    }

    // TODO: add message class
    void sendMessage(User::Id chatId, std::string text) {
        json::object res {
            Https(prefix + "sendMessage?chat_id=" +
                std::to_string(chatId) + "&text=" + text).make()
        };
        if(!res["ok"]) throw std::runtime_error("Telegram error! " +
                res.get<json::String>("description"));
    }

    // TODO: add message class
    void sendMessage(std::string chatUsername, std::string text) {
        json::object res {
            Https(prefix + "sendMessage?chat_id=" +
                chatUsername + "&text=" + text).make()
        };
        if(!res["ok"]) throw std::runtime_error("Telegram error! " +
                res.get<json::String>("description"));
    }
};

#endif // !BOT_H
