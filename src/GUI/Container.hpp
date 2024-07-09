/**
 * @file Container.hpp
 * @brief This file will contain the container class that will be used to create containers for the GUI for non GUI elements (e.i. canvas like html)
 */

#pragma once

#include <cstring>
#include <string>

#include "raylib.h"

#include "GUIElement.hpp"
#include "GUIElementInteractive.hpp"


namespace GUI {
    class Container : public GUIElement, public InteractiveElement
    {
        
    };
}