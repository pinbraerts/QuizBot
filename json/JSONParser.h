#ifndef JSON_READER_H
#define JSON_READER_H

#include <iostream>

#include "JSONAny.h"

struct JSONParser {
    std::istream& input;

    void parse(JSONAny& root);

    void parseObject(JSONAny& root);

    std::string parseString();

    void parseArray(JSONAny& root);

    void skipSpaces();
};

#endif // !JSON_READER_H
