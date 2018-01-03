#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include "Types.h"

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

#endif // !JSON_OBJECT_H
