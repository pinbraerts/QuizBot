#include "Any.h"

using namespace json;

json::Any::Any(): type(Null), num(0.0) {}

json::Any::Any(std::string&& str): Any(std::istringstream { str }) {}

json::Any::Any(const json::Any& other): type(other.type) {
    switch(type) {
    case Object:
        new (&children) DataType<Object> { other.children };
        break;
    case Array:
        new (&items) DataType<Array> { other.items };
        break;
    case String:
        new (&str) DataType<String> { other.str };
        break;
    case Boolean:
        cond = other.cond;
        break;
    case Number:
        num = other.num;
        break;
    case Integer:
        integ = other.integ;
        break;
    case Null:
        num = 0.0;
        break;
    }
}

void json::Any::clear() {
    switch(type) {
    case Object: children.clear(); break;
    case Array: items.clear(); break;
    case String: str.clear(); break;
    case Boolean: cond = false; break;
    case Number: num = 0.0; break;
    case Integer: integ = 0; break;
    case Null: num = 0.0; break;
    }
}

Any::~Any() {
    clear();
}

json::Any& json::Any::operator=(json::Type tp) {
    clear();
    type = tp;
    switch(type) {
    case Object:
        new (&children) DataType<Object> {};
        break;
    case Array:
        new (&items) DataType<Array> {};
        break;
    case String:
        new (&str) DataType<String> {};
        break;
    case Boolean:
        cond = false;
        break;
    case Number:
        num = 0.0;
        break;
    case Integer:
        integ = 0;
        break;
    case Null:
        num = 0.0;
        break;
    }
    return *this;
}

json::Any& json::Any::operator=(json::DataType<String> s) {
    clear();
    type = String;
    new (&str) std::string { s };
}

json::Any& json::Any::operator=(const json::Any& other) {
    clear();
    switch(type = other.type) {
    case Object:
        new (&children) DataType<Object> { other.children };
        break;
    case Array:
        new (&items) DataType<Array> { other.items };
        break;
    case String:
        new (&str) DataType<String> { other.str };
        break;
    case Boolean:
        cond = other.cond;
        break;
    case Number:
        num = other.num;
        break;
    case Integer:
        integ = other.integ;
        break;
    case Null:
        num = 0.0;
        break;
    }
    return *this;
}

json::Any& json::Any::operator=(json::Any&& other) {
    clear();
    switch(type = other.type) {
    case Object:
        new (&children) DataType<Object> { std::move(other.children) };
        break;
    case Array:
        new (&items) DataType<Array> { std::move(other.items) };
        break;
    case String:
        new (&str) DataType<String> { std::move(other.str) };
        break;
    case Boolean:
        cond = other.cond;
        break;
    case Number:
        num = other.num;
        break;
    case Integer:
        integ = other.integ;
        break;
    case Null:
        num = 0.0;
        break;
    }
    return *this;
}

json::Any& json::Any::operator=(json::DataType<Boolean> ncond) {
    clear();
    type = Boolean;
    cond = ncond;
}

json::Any& json::Any::operator=(json::DataType<Null> np) {
    clear();
    type = Null;
    num = 0.0;
}

json::Any::Any(std::istream&& stream) {
    Parser { stream }.parse(*this);
}

std::ostream& json::operator<<(std::ostream& stream, const json::Any& obj) {
    switch(obj.type) {
    case Object:
        stream << '{';
        {
            auto end = --obj.children.end();
            for(auto i = obj.children.begin(); i != end; ++i)
                stream << '"' << i->first << "\":" << i->second << ',';
            if(obj.children.size()) stream << '"' << end->first << "\":" << end->second;
        }
        stream << '}';
        break;
    case Array:
        stream << '[';
        {
            auto end = --obj.items.end();
            for(auto i = obj.items.begin(); i < end; ++i)
                stream << (*i) << ',';
            if(obj.items.size()) stream << (*end);
        }
        stream << ']';
        break;
    case String:
        stream << '"' << obj.str << '"';
        break;
    case Boolean:
        if(obj.cond) stream << "true";
        else stream << "false";
        break;
    case Number:
        stream << obj.num;
        break;
    case Integer:
        stream << obj.integ;
        break;
    case Null:
        stream << "null";
        break;
    }
    return stream;
}

inline std::istream& json::operator>>(std::istream& stream, json::Any& obj) {
    Parser { stream }.parse(obj);
}
