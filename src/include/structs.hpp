#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include "SDL.h"
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>


class Texture;

/**
* \brief Small struct used to define a Transform. More elements will be added as needed (like scale and rotation)
*/
struct Transform
{
    SDL_Rect rect;
};


//SDL helper structs
struct Window
{
    // std::unique_ptr<SDL_Window, Deleters> window;
    SDL_Rect window_size;
};

struct MainFlags
{
    bool quit;
};

struct FontColours
{
    SDL_Colour foreground;
    SDL_Colour background;
};

struct SDLFontParams
{
    std::string name;
    int size;

    bool operator==(const SDLFontParams& right) { return (name == right.name && size == right.size); }
};

struct FontParams
{
    std::string name;
    int size;
    FontColours colours;

    bool operator==(const FontParams& right) { return (name == right.name && size == right.size); }
};
#endif // STRUCTS_HPP
