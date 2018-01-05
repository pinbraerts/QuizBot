#ifndef JSON_ANY_H
#define JSON_ANY_H

#include <sstream>

#include "Defines.h"
#include "Error.h"
#include "Parser.h"
#include "DataTypes.h"

class json::Any {
public:
    Type type;

    union {
        DataType<Object>  children;
        DataType<Array>   items;
        DataType<String>  str;
        DataType<Boolean> cond;
        DataType<Number>  num;
        DataType<Integer> integ;
    };

    friend std::ostream& operator<<(std::ostream& stream, const Any& obj);
    friend inline std::istream& operator>>(std::istream& stream, Any& obj);

    Any();
    Any(Type tp);
    Any(const Any& other);
    Any(Any&& other);
    Any(std::istream&& stream);
    Any(std::string&& str);

    inline Any& operator=(Type tp) {
        clear();
        new (this) json::Any { tp };
        return *this;
    }
    inline Any& operator=(const Any& other) {
        clear();
        new (this) Any { other };
        return *this;
    }
    inline Any& operator=(Any&& other) {
        clear();
        new (this) Any { std::move(other) };
        return *this;
    }
    Any& operator=(DataType<Boolean> ncond);
    Any& operator=(DataType<String> s);
    Any& operator=(DataType<Null> np);

    /*template<Type t> inline operator DataType<t>&() {
        if(type != t) throw std::runtime_error("Type mismatch!");
        return this->*member<t>;
    }
    inline operator DataType<Object>&() {
        if(type != Object) throw std::runtime_error("Type mismatch!");
        return children;
    }
    inline operator DataType<Array>&() {
        if(type != Array) throw std::runtime_error("Type mismatch!");
        return items;
    }*/
    inline operator DataType<String>&() {
        if(type != String) throw TypeError(String, type);
        return str;
    }
    inline operator DataType<Boolean>&() {
        if(type != Boolean) throw TypeError(Boolean, type);
        return cond;
    }
    inline operator DataType<Number>&() {
        if(type != Number) throw TypeError(Number, type);
        return num;
    }
    inline operator DataType<Integer>&() {
        if(type != Integer) throw TypeError(Integer, type);
        return integ;
    }

    inline operator const DataType<String>&() const {
        if(type != String) throw TypeError(String, type);
        return str;
    }
    inline operator const DataType<Boolean>&() const {
        if(type != Boolean) throw TypeError(Boolean, type);
        return cond;
    }
    inline operator const DataType<Number>&() const {
        if(type != Number) throw TypeError(Number, type);
        return num;
    }
    inline operator const DataType<Integer>&() const {
        if(type != Integer) throw TypeError(Integer, type);
        return integ;
    }

    void clear();

    ~Any();
};

#endif // !JSON_ANY_H
