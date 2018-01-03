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
        DataType<String>  string;
        DataType<Boolean> condition;
        DataType<Number>  number;
        DataType<Integer> integer;
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

    void clear();

    ~Any();
};

#endif // !JSON_ANY_H
