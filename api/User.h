#ifndef USER_H
#define USER_H

#include <string>

#include "../json/Any.h"
#include "../json/Types.h"

struct User {
    unsigned id = 0;
    bool isBot = false;
    std::string firstName;
    std::string lastName;
    std::string username;
    std::string languageCode;

    User(const json::object& obj): id(obj.get<json::Integer>("id")),
        isBot(obj.get<json::Boolean>("is_bot")),
        firstName(obj.get<json::String>("first_name")),
        lastName(obj.getOrDefault<json::String>("last_name")),
        username(obj.getOrDefault<json::String>("username")),
        languageCode(obj.getOrDefault<json::String>("language_code")) {}

    User& operator=(const json::object& obj) {
        new (this) User { obj };
        return *this;
    }
};

#endif // !USER_H
