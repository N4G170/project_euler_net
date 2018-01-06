#ifndef HASH_HPP
#define HASH_HPP

#include <functional>
#include <string>
#include "structs.hpp"

struct HashFunctions
{
    size_t operator()(const SDLFontParams &param ) const
    {
        return std::hash<std::string>()(param.name) ^ std::hash<int>()(param.size);
    }

    size_t operator()(const FontParams &param ) const
    {
        return std::hash<std::string>{}(param.name) ^ std::hash<int>{}(param.size);//we do not need to use the colours for in the hash
    }
};

#endif //HASH_HPP
