#pragma once
#include <cstring>
#include <string>
#include <iostream>
#include <functional>
#include <array>

#include "Types.hpp"
#include "Style.hpp"

namespace GUI
{
    class GUIElement
    {
    public:
        virtual ~GUIElement() = default;
        virtual void Init() = 0;
        virtual void Input() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;

        void setStyle(Style *style)
        {
            this->style = style;
        }
        Style *getStyle() const { return style; }

        void setPosition(int x, int y)
        {
            X = x;
            Y = y;
        }
        std::array<int, 2> getPosition() const { return {X, Y}; }

        // Size
        void setSize(int width, int height)
        {
            this->width = width;
            this->height = height;
        }
        std::array<int, 2> getSize() const { return {width, height}; }

        // Width
        void setWidth(int width) { this->width = width; }
        int getWidth() const { return width; }

        // Height
        void setHeight(int height) { this->height = height; }
        int getHeight() const { return height; }

        void updateInnerSize() // calculate the inner size of the element
        {
            if (style != nullptr) // if a style is set, calculate the inner size
            {
                Sides padding = style->getPadding();
                Sides margin = style->getMargin();
                innerHeight = height - padding.top - padding.bottom - margin.top - margin.bottom;
                innerWidth = width - padding.left - padding.right - margin.left - margin.right;
            }
            else // if no style is set, the inner size is the same as the outer size
            {
                innerHeight = height;
                innerWidth = width;
            }
        }

    protected:
        // will move the input update render cycle here when there is a GUI Manager implemented
    private:
        int X, Y;
        int width, height;           // total size of the element
        int innerWidth, innerHeight; // calculated after factoring in padding, margin, and border

        Style *style;
    };
}