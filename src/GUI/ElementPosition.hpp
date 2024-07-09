#pragma once

#include <vector>

namespace GUI
{
    class ElementPosition
    {
    public:
        ElementPosition() = default;
        ElementPosition(int x, int y) : X(x), Y(y) { }
        ~ElementPosition() = default;

        int X;
        int Y;
        
    };
} // namespace GUI