#include "JSONParser.h"

#include <sstream>

void JSONParser::parse(JSONAny& root) {
    skipSpaces();
    if(!input) { root.type = JSONAny::Null; return; }
    switch(input.peek()) {
    case '{': parseObject(root); break;
    case '[': parseArray(root); break;
    case '"': case '\'':
        root = parseString();
        break;
    case 't':
        input.get();
        if(!input || input.get() != 'r' ||
            !input || input.get() != 'u' ||
            !input || input.get() != 'e')
            throw std::runtime_error("Expected boolean literal!");
        root = true;
        break;
    case 'f':
        input.get();
        if(!input || input.get() != 'a' ||
            !input || input.get() != 'l' ||
            !input || input.get() != 's' ||
            !input || input.get() != 'e')
            throw std::runtime_error("Expected boolean literal!");
        root = false;
        break;
    case 'n':
        input.get();
        if(!input || input.get() != 'u' ||
            !input || input.get() != 'l' ||
            !input || input.get() != 'l')
            throw std::runtime_error("Expected null literal!");
        root = nullptr;
        break;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        input >> root.number;
        if(!input) throw std::runtime_error("Expected number literal!");
        {
            int i = root.number;
            if(i == root.number) {
                root.type = JSONAny::Integer;
                root.integer = i;
            } else root.type = JSONAny::Number;
        }
        break;
    }
}

void JSONParser::parseObject(JSONAny& root) {
    if(!input || input.get() != '{')
        throw std::runtime_error("Expected object!");
    root = JSONAny::Object;
    while(input) {
        skipSpaces();
        JSONAny child;
        std::string s = parseString();
        std::cerr << "Item: " << s << std::endl;
        skipSpaces();
        if(input.get() != ':')
            throw std::runtime_error("Expected colon!");
        parse(child);
        root.children[s] = std::move(child);
        skipSpaces();
        if(input.peek() != ',') break;
        input.get();
    }
    if(!input || input.get() != '}')
        throw std::runtime_error("Expected end of object!");
}

std::string JSONParser::parseString() {
    if(!input) throw std::runtime_error("Expected string!");
    char d = input.get();
    if(d != '"' && d != '\'') throw std::runtime_error("Expected string!");
    std::ostringstream res;
    while(input) {
        if(input.peek() == '\\') res << char(input.get());
        else if(input.peek() == d) {
            input.get();
            return res.str();
        }
        res << char(input.get());
    }
    throw std::runtime_error("Expected end of string literal!");
}

void JSONParser::parseArray(JSONAny& root) {
    if(!input || input.get() != '[')
        throw std::runtime_error("Expected array!");
    root = JSONAny::Array;
    while(input) {
        skipSpaces();
        JSONAny child;
        parse(child);
        root.items.push_back(std::move(child));
        skipSpaces();
        if(input.peek() != ',') break;
        input.get();
    }
    if(!input || input.get() != ']')
        throw std::runtime_error("Expected end of array!");
}

void JSONParser::skipSpaces() {
    while(input && isspace(input.peek())) input.get();
}
