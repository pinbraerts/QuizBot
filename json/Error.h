#ifndef JSON_ERROR
#define JSON_ERROR

#include <iostream>
#include <string>

#include "Defines.h"

class json::TypeError: std::runtime_error {
public:
    TypeError(): runtime_error("JSON: Type Error!") {}
    TypeError(json::Type expected, json::Type got):
        std::runtime_error(((std::ostringstream&)(std::ostringstream{}
            << "JSON: Type Error: '" << typeToStr[expected]
            << "' expected, '" << typeToStr[got]
            << "' got!")).str()) {}
    TypeError(json::Type expected, json::Type got, std::string itemId):
        std::runtime_error(((std::ostringstream&)(std::ostringstream{}
            << "JSON: Type Error while getting item '" << itemId << "': '"
            << typeToStr[expected] << "' expected, '"
            << typeToStr[got] << "' got!")).str()) {}
};

class json::NotFoundError: std::runtime_error {
public:
    NotFoundError(): std::runtime_error("JSON: Item not found Error!") {}
    NotFoundError(std::string itemId):
        std::runtime_error(((std::ostringstream&)(std::ostringstream{}
            << "JSON: Item with id '" << itemId << "' not found!")).str()) {}
};

#endif // !JSON_ERROR
