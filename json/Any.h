#ifndef JSON_ANY_H
#define JSON_ANY_H

#include "Defines.h"
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

    Any& operator=(Type tp);
    Any& operator=(const Any& other);
    Any& operator=(Any&& other);
    Any& operator=(DataType<Boolean> ncond);
    Any& operator=(DataType<String> s);
    Any& operator=(DataType<Null> np);

    Any();
    Any(const Any& other);
    Any(std::istream&& stream);
    Any(std::string&& str);

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
        if(type != String) throw std::runtime_error("Type mismatch!");
        return str;
    }
    inline operator DataType<Boolean>&() {
        if(type != Boolean) throw std::runtime_error("Type mismatch!");
        return cond;
    }
    inline operator DataType<Number>&() {
        if(type != Number) throw std::runtime_error("Type mismatch!");
        return num;
    }
    inline operator DataType<Integer>&() {
        if(type != Integer) throw std::runtime_error("Type mismatch!");
        return integ;
    }

    inline operator const DataType<String>&() const {
        if(type != String) throw std::runtime_error("Type mismatch!");
        return str;
    }
    inline operator const DataType<Boolean>&() const {
        if(type != Boolean) throw std::runtime_error("Type mismatch!");
        return cond;
    }
    inline operator const DataType<Number>&() const {
        if(type != Number) throw std::runtime_error("Type mismatch!");
        return num;
    }
    inline operator const DataType<Integer>&() const {
        if(type != Integer) throw std::runtime_error("Type mismatch!");
        return integ;
    }

    void clear();

    ~Any();
};

#endif // !JSON_ANY_H
