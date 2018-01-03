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
        throw std::runtime_error("Type mismatch!")) {}
    __base(Any&& other): Any(other.type == t ? std::move(other) :
        throw std::runtime_error("Type mismatch!")) {}

    inline operator DataType<t>&() {
        return this->*member<t>;
    }
};

struct json::object: json::__base<json::Object> {
    using __base::__base;

    // throw if not found and type mismatch
    template<Type t> inline const DataType<t>& get(std::string id) const {
        auto iter = children.lower_bound(id);
        if(iter == children.end() || iter->first != id)
            throw std::runtime_error(id + " Item not found!");
        if(iter->second.type != t) throw std::runtime_error(id + " Type mismatch!");
        return iter->second.*member<t>;
    }
    // throw if not found and type mismatch
    template<Type t> inline DataType<t>& get(std::string id) {
        auto iter = children.lower_bound(id);
        if(iter == children.end() || iter->first != id)
            throw std::runtime_error(id + " Item not found!");
        if(iter->second.type != t) throw std::runtime_error(id + " Type mismatch!");
        return iter->second.*member<t>;
    }

    // throw if type mismatch
    template<Type t> inline const DataType<t>& getOrDefault(std::string id, const DataType<t>& def = DataType<t>{}) const {
        auto iter = children.lower_bound(id);
        if(iter == children.end() || iter->first != id) return def;
        if(iter->second.type != t) throw std::runtime_error("Type mismatch!");
        return iter->second.*member<t>;
    }

    // throw if type mismatch
    template<Type t> inline DataType<t> getOrDefault(std::string id, DataType<t> def = DataType<t>{}) {
        auto iter = children.lower_bound(id);
        if(iter == children.end() || iter->first != id) return def;
        if(iter->second.type != t) throw std::runtime_error("Type mismatch!");
        return iter->second.*member<t>;
    }

    // nothrow
    template<Type t> inline const DataType<t>& getNearOrDefault(std::string id, const DataType<t>& def = DataType<t>{}) const {
        auto iter = children.lower_bound(id);
        if(iter == children.end() || iter->first != id ||
            iter->second.type != t) return def;
        return iter->second.*member<t>;
    }

    // nothrow
    template<Type t> inline DataType<t> getNearOrDefault(std::string id, DataType<t> def = DataType<t>{}) {
        auto iter = children.lower_bound(id);
        if(iter == children.end() || iter->first != id ||
            iter->second.type != t) return def;
        return iter->second.*member<t>;
    }

    // throw if not found and type mismatch
    template<Type t> inline ItemType<t> getItem(std::string id) {
        auto iter = children.lower_bound(id);
        if(iter == children.end() || iter->first != id)
            throw std::runtime_error(id + " Item not found!");
        if(iter->second.type != t) throw std::runtime_error(id + " Type mismatch!");
        return iter->second;
    }

    // throw if not found and type mismatch
    template<Type t> inline const ItemType<t>& getItem(std::string id) const {
        auto iter = children.lower_bound(id);
        if(iter == children.end() || iter->first != id)
            throw std::runtime_error(id + " Item not found!");
        if(iter->second.type != t) throw std::runtime_error(id + " Type mismatch!");
        return iter->second;
    }

    inline Any& operator[](std::string id) {
        auto iter = children.lower_bound(id);
        if(iter == children.end() || iter->first != id)
            throw std::runtime_error(id + " Item not found!");
        return iter->second;
    }

    inline const Any& operator[](std::string id) const {
        auto iter = children.lower_bound(id);
        if(iter == children.end() || iter->first != id)
            throw std::runtime_error(id + " Item not found!");
        return iter->second;
    }

    inline Any& operator[](const char* id) {
        auto iter = children.lower_bound(id);
        if(iter == children.end() || iter->first != id)
            throw std::runtime_error(std::string { id } + " Item not found!");
        return iter->second;
    }

    inline const Any& operator[](const char* id) const {
        auto iter = children.lower_bound(id);
        if(iter == children.end() || iter->first != id)
            throw std::runtime_error(std::string { id } + " Item not found!");
        return iter->second;
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
