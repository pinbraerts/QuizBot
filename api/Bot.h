#ifndef BOT_H
#define BOT_H

#include <sstream>

#include "Https.h"
#include "User.h"

class Bot {
private:
    constexpr static char prefix[] = "https://api.telegram.org/bot";

public:
    enum ParseMode {
        Markdown, HTML
    };

    Https stdHttps;

    Bot(std::string token);

    inline Https nh() {
        return Https { stdHttps };
    }

    User getMe();

    // TODO: add message class
    void sendMessage(User::Id chatId, std::string text);
    void sendMessage(std::string chatUsername, std::string text);
};

#endif // !BOT_H
