#ifndef JSON_DATA_H
#define JSON_DATA_H

#include <map>
#include <vector>
#include <string>

#include "Defines.h"

template<> struct json::__dthelper<json::Object> {
    using type = std::map<std::string, json::Any>;
};
template<> struct json::__dthelper<json::Array> {
    using type = std::vector<json::Any>;
};
template<> struct json::__dthelper<json::String> {
    using type = std::string;
};
template<> struct json::__dthelper<json::Boolean> {
    using type = bool;
};
template<> struct json::__dthelper<json::Number> {
    using type = double;
};
template<> struct json::__dthelper<json::Integer> {
    using type = long;
};
template<> struct json::__dthelper<json::Null> {
    using type = nullptr_t;
};

#endif // !JSON_DATA_H
