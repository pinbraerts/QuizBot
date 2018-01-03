#ifndef JSON_DEFINES_H
#define JSON_DEFINES_H

#include <iostream>

namespace json {
    enum Type {
        Object,
        Array,
        String,
        Boolean,
        Number,
        Integer,
        Null
    };

    template<Type t> struct __dthelper;
    template<Type t> using DataType = typename __dthelper<t>::type;

    class Any;

    template<Type t> inline DataType<t> Any::* const member;

    template<Type t> struct __ithelper;
    template<Type t> using ItemType = typename __ithelper<t>::type;

    template<Type t> class __base;
    class object;
    class array;
    class string;
    class boolean;
    class number;
    class integer;


    std::ostream& operator<<(std::ostream& stream, const Any& obj);
    inline std::istream& operator>>(std::istream& stream, Any& obj);

    class Parser;
}

#endif // !JSON_DEFINES_H
