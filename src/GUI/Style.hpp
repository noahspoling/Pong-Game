/**
 * @file Style.hpp
 * @brief Style class header file of parameters shared by all elements, inputs, containers etc/
 * 
 * This file contains the Style class header file of parameters shared by all elements, inputs, containers etc.
 * Via pointers to the Style class, the parameters can be shared without using more memory
 * 
 */
#pragma once

#include <cstring>
#include <string>
#include <vector>

#include "raylib.h"

#include "Types.hpp"

namespace GUI
{
    // typedef enum
    // {
    //     TOP,
    //     RIGHT,
    //     BOTTOM,
    //     LEFT
    // } Side;

    // typedef struct Padding {
    //     int top;
    //     int right;
    //     int bottom;
    //     int left;
    // } Padding;

    // typedef struct Margin {
    //     int top;
    //     int right;
    //     int bottom;
    //     int left;
    // } Margin;

    // typedef struct Border {
    //     int top;
    //     int right;
    //     int bottom;
    //     int left;
    //     int radius;
    //     int thickness;
    // } Border;

    // typedef struct Background {
    //     Color color;
    //     Texture2D texture;
    // } Background;

    // typedef struct Font { // Synomous with forground color
    //     std::string name;
    //     int size;
    //     Color color;
    // } Font;

    /**
     * @brief Style class of parameters shared by all elements, inputs, containers etc.
     * 
     * This class contains the Style class of parameters shared by all elements, inputs, containers etc.
     * Via pointers to the Style class, the parameters can be shared without using more memory
     * @param padding space inside the element
     * @param margin space around the element
     * @param gap gap between elements in grids/containers/layouts etc.
     * @param border border of the element
     * @param background background of the element
     * @param font font of the element
     * 
     */
    class Style
    {
    public:
        Style(/* args */);
        ~Style();

        void SetPadding(int top, int right, int bottom, int left) {
            padding.top = top;
            padding.right = right;
            padding.bottom = bottom;
            padding.left = left;
        };

        void SetPaddingX(int value) {
            padding.top = value;
            padding.bottom = value;
        };

        void SetPaddingY(int value) {
            padding.right = value;
            padding.left = value;
        }

        void SetPaddingAll(int value) {
            padding.top = value;
            padding.right = value;
            padding.bottom = value;
            padding.left = value;
        }

        void SetPaddingSide(int value, Side side) {
            switch (side)
            {
            case TOP:
                padding.top = value;
                break;
            case RIGHT:
                padding.right = value;
                break;
            case BOTTOM:
                padding.bottom = value;
                break;
            case LEFT:
                padding.left = value;
                break;
            default:
                break;
            }
        }

        int getPaddingSide(Side side) {
            switch (side)
            {
            case TOP:
                return padding.top;
                break;
            case RIGHT:
                return padding.right;
                break;
            case BOTTOM:
                return padding.bottom;
                break;
            case LEFT:
                return padding.left;
                break;
            default:
                return 0;
                break;
            }
        }
        Sides getPadding() { return padding; }

        void SetMargin(int top, int right, int bottom, int left) {
            margin.top = top;
            margin.right = right;
            margin.bottom = bottom;
            margin.left = left;
        }

        void SetMarginX(int value) {
            margin.top = value;
            margin.bottom = value;
        }

        void SetMarginY(int value) {
            margin.right = value;
            margin.left = value;
        }

        void SetMarginAll(int value, Side side) {
            margin.top = value;
            margin.right = value;
            margin.bottom = value;
            margin.left = value;
        }

        void SetMarginSide(int value, Side side) {
            switch (side)
            {
            case TOP:
                margin.top = value;
                break;
            case RIGHT:
                margin.right = value;
                break;
            case BOTTOM:
                margin.bottom = value;
                break;
            case LEFT:
                margin.left = value;
                break;
            default:
                break;
            }
        }

        Sides getMargin() { return margin; }

    private:
        Sides padding; //space inside the element
        Sides margin; // space around the element
        int gap; // gap between elements in grids/containers/layouts etc.
        Border border;
        Background background;
        Font font;
    };
    
}