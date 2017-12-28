#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>

//#include "texture.h"
//#include "message_writer.h"
//class MessageWriter;

enum TextAlignment
{
    TOP_LEFT = 0,
    CENTER = 1,
    TOP_RIGHT = 2
};

//{ Region Custom unique_ptr deleters
/**
* \brief Struct defining custom destruction rules that are needed by some unique_ptrs
*/
struct Deleters
{

};


//{ "Global" pointers struct
/**
* \brief Struct holding "global" pointers that are used by many parts of the application
*/
struct MainPointers
{

};
//}

#endif // STRUCTS_H
