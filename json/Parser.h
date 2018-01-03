#ifndef JSON_READER_H
#define JSON_READER_H

#include <iostream>

#include "Defines.h"
#include "Any.h"

class json::Parser {
public:
    Parser(std::istream& in);

    std::istream& input;

    void parse(Any& root);
    void parseObject(Any& root);
    DataType<String> parseString();
    void parseArray(Any& root);
    void skipSpaces();
};

#endif // !JSON_READER_H
