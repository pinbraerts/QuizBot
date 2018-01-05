#ifndef JSON_TYPES_H
#define JSON_TYPES_H

#include <string>
#include <map>
#include <vector>

#include "Defines.h"
#include "Any.h"

template<> inline auto json::Any::* json::member<json::Object> = &json::Any::children;
template<> inline auto json::Any::* json::member<json::Array> = &json::Any::items;
template<> inline auto json::Any::* json::member<json::String> = &json::Any::str;
template<> inline auto json::Any::* json::member<json::Boolean> = &json::Any::cond;
template<> inline auto json::Any::* json::member<json::Number> = &json::Any::num;
template<> inline auto json::Any::* json::member<json::Integer> = &json::Any::integ;

template<> struct json::__ithelper<json::Object> {
    using type = json::object;
};
template<> struct json::__ithelper<json::Array> {
    using type = json::array;
};
template<> struct json::__ithelper<json::String> {
    using type = json::string;
};
template<> struct json::__ithelper<json::Boolean> {
    using type = json::boolean;
};
template<> struct json::__ithelper<json::Number> {
    using type = json::number;
};
template<> struct json::__ithelper<json::Integer> {
    using type = json::integer;
};

template<json::Type t> class json::__base: public json::Any {
public:
    __base(const Any& other): Any(other.type == t ? other :
        throw TypeError(t, other.type)) {}
    __base(Any&& other): Any(other.type == t ? std::move(other) :
        throw TypeError(t, other.type)) {}
    __base(std::istream&& stream): Any(std::move(stream)) {
        if(t != type) throw TypeError(t, type);
    }
    __base(std::string&& str): Any(std::move(str)) {
        if(t != type) throw TypeError(t, type);
    }
};

struct json::array: json::__base<json::Array> {
    using __base::__base;

};

struct json::string: json::__base<json::String> {
    using __base::__base;

};

struct json::boolean: json::__base<json::Boolean> {
    using __base::__base;

};

struct json::number: json::__base<json::Number> {
    using __base::__base;

};

struct json::integer: json::__base<json::Integer> {
    using __base::__base;

};

#endif // !JSON_TYPES_H
