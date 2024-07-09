// Layout.cpp
#include "Layout.hpp"

namespace GUI {

    Layout::Layout() 
        : X(0), Y(0), width(0), height(0), itemSize(0), padding(0), layoutDirection(HORIZONTAL), layoutType(FILL) { 
    }

    Layout::~Layout() { 
    }

} // namespace GUI
