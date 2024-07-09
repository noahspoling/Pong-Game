#pragma once

#include <cstring>
#include <string>

#include "raylib.h"

namespace GUI
{
    // Forward declaration of General Style structs for use in other classes
    typedef enum
    {
        TOP,
        RIGHT,
        BOTTOM,
        LEFT
    } Side;

    typedef struct Sides {
        int top;
        int right;
        int bottom;
        int left;
    } Sides;

    typedef struct Border {
        Sides sides;
        int radius;
        int thickness;
    } Border;

    typedef struct Background {
        Color color;
        Texture2D texture;
    } Background;

    typedef struct Font { // Synomous with forground color
        std::string name;
        int size;
        Color color;
    } Font;


    // Layout Types
    typedef enum
    {
        VERTICAL,
        HORIZONTAL
    } LayoutDirection;

    typedef enum
    {
        FIXED, // absolute pixel value
        RELATIVE, //value relative to sum of elements
        FILL // fill the container
    } LayoutType;
} // namespace GUI