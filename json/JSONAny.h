#ifndef JSON_ANY_H
#define JSON_ANY_H

#include <iostream>
#include <map>
#include <vector>
#include <string>

class JSONAny {
public:
    enum Type {
        Object,
        Array,
        String,
        Bool,
        Number,
        Integer,
        Null
    } type;

    union {
        std::map<std::string, JSONAny> children;
        std::vector<JSONAny> items;
        std::string string;
        bool condition;
        double number;
        int integer;
    };

    friend std::ostream& operator<<(std::ostream& stream, const JSONAny& obj);

    JSONAny& operator=(Type tp);
    JSONAny& operator=(const JSONAny& other);
    JSONAny& operator=(JSONAny&& other);
    JSONAny& operator=(bool ncond);
    JSONAny& operator=(std::string s);
    JSONAny& operator=(nullptr_t np);

    JSONAny();
    JSONAny(const JSONAny& other);
    JSONAny(std::istream& stream);

    void clear();

    ~JSONAny();
};

#endif // !JSON_ANY_H
