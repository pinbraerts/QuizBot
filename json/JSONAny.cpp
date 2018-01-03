#include "JSONAny.h"
#include "JSONParser.h"

JSONAny::JSONAny(): type(Null), number(0.0) {}

JSONAny::JSONAny(const JSONAny& other): type(other.type) {
    switch(type = other.type) {
    case Object: children = std::move(other.children); break;
    case Array: items = std::move(other.items); break;
    case String: string = std::move(other.string); break;
    case Bool: condition = other.condition; break;

    case Number: number = other.number; break;
    case Integer: integer = other.integer; break;
    case Null: number = 0.0; break;
    }
}

void JSONAny::clear() {
    switch(type) {
    case Object: children.clear(); break;
    case Array: items.clear(); break;
    case String: string.clear(); break;
    case Bool: condition = false; break;

    case Number: number = 0.0; break;
    case Integer: integer = 0; break;
    case Null: number = 0.0; break;
    }
}

JSONAny::~JSONAny() {
    clear();
}

JSONAny& JSONAny::operator=(JSONAny::Type tp) {
    clear();
    type = tp;
    switch(type) {
    case Object:
        new (&children) std::map<std::string, JSONAny> {};
        break;
    case Array:
        new (&items) std::vector<JSONAny> {};
        break;
    case String:
        new (&string) std::string {};
        break;
    case Bool:
        condition = false;
        break;
    case Number:
        number = 0.0;
        break;
    case Integer:
        integer = 0;
        break;
    case Null:
        number = 0.0;
        break;
    }
    return *this;
}

JSONAny& JSONAny::operator=(std::string s) {
    clear();
    type = String;
    new (&string) std::string { s };
}

JSONAny& JSONAny::operator=(const JSONAny& other) {
    clear();
    switch(type = other.type) {
    case Object: children = other.children; break;
    case Array: items = other.items; break;
    case String: string = other.string; break;
    case Bool: condition = other.condition; break;

    case Number: number = other.number; break;
    case Integer: integer = other.integer; break;
    case Null: number = 0.0; break;
    }
    return *this;
}

JSONAny& JSONAny::operator=(JSONAny&& other) {
    clear();
    switch(type = other.type) {
    case Object: children = std::move(other.children); break;
    case Array: items = std::move(other.items); break;
    case String: string = std::move(other.string); break;
    case Bool: condition = other.condition; break;

    case Number: number = other.number; break;
    case Integer: integer = other.integer; break;
    case Null: number = 0.0; break;
    }
    return *this;
}

JSONAny& JSONAny::operator=(bool ncond) {
    clear();
    type = Bool;
    condition = ncond;

}

JSONAny& JSONAny::operator=(nullptr_t np) {
    clear();
    type = Null;
    number = 0.0;
}

JSONAny::JSONAny(std::istream& stream) {
    JSONParser { stream }.parse(*this);
}

std::ostream& operator<<(std::ostream& stream, const JSONAny& obj) {
    switch(obj.type) {
    case JSONAny::Object:
        stream << '{';
        {
            auto end = --obj.children.end();
            for(auto i = obj.children.begin(); i != end; ++i)
                stream << '"' << i->first << "\":" << i->second << ',';
            if(obj.children.size()) stream << '"' << end->first << "\":" << end->second;
        }
        stream << '}';
        break;
    case JSONAny::Array:
        stream << '[';
        {
            auto end = --obj.items.end();
            for(auto i = obj.items.begin(); i < end; ++i)
                stream << (*i) << ',';
            if(obj.items.size()) stream << (*end);
        }
        stream << ']';
        break;
    case JSONAny::String:
        stream << '"' << obj.string << '"';
        break;
    case JSONAny::Bool:
        if(obj.condition) stream << "true";

        else stream << "false";
        break;
    case JSONAny::Number:
        stream << obj.number;
        break;
    case JSONAny::Integer:
        stream << obj.integer;
        break;
    case JSONAny::Null:
        stream << "null";
        break;
    }
    return stream;
}
