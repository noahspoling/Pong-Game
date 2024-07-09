/*********************************************************************
 * File: Layout.hpp
 * Description: This file will contain the layout class that will be used to create layouts for the GUI
 * 
 * ================================================================
 * Modification History
 * ================================================================
 * Date:           06/30/2024
 * Author:         Noah
 * Description:    Created Layout class
 * ================================================================
 * Date:           06/30/2024
 * Author:         
 * Description:    
 */
#pragma once

#include <cstring>
#include <string>
#include <vector>
#include <memory>

#include "raylib.h"

#include "Types.hpp"

#include "GUIElement.hpp"
#include "GUIElementInteractive.hpp"
#include "ButtonStyle.hpp"
#include "Button.hpp"

namespace GUI
{
    /**
     * @brief Layout class for creating layouts for the GUI
     *
     * This class will be used to create layouts for the GUI
     * 
     * @param X The x position of the layout
     * @param Y The y position of the layout
     * @param width The width of the layout
     * @param height The height of the layout
     * @param itemSize The size of the items in the layout
     * @param padding The padding of the layout
     * @param gap The gap between the elements
     * @param elements The elements in the layout
     * @param layoutDirection The direction of the layout
     * @param layoutType The type of the layout
     * @param resizeEvent The resize event of the layout
     * 
     * 
    */
    class Layout
    {
    public:
        Layout(/* args */);
        Layout(int x, int y, int width, int height) 
            : X(x), Y(y), width(width), height(height) { }
        ~Layout();

        void add(const std::shared_ptr<GUIElement>& element) {
            elements.push_back(element);
            resizeEvent = true;
        }
        void remove(int index) {
            elements.erase(elements.begin() + index);
            resizeEvent = true;
        }

        void setLayoutDirection(LayoutDirection direction) {
            layoutDirection = direction;
        }

        void setLayoutType(LayoutType type) {
            layoutType = type;
        }

        void setPadding(int padding) {
            this->padding = padding;
        }

        void setItemSize(int size) {
            itemSize = size;
        }

        LayoutDirection getLayoutDirection() {
            return layoutDirection;
        }

        LayoutType getLayoutType() {
            return layoutType;
        }

        

        void Init() // initialize the layout
        {
            #ifdef DEBUG
                TraceLog(LOG_INFO, "Layout initialized");
            #endif
        }
        void Input() // input handling for button driven layouts 
        {
            for(auto &element : elements) {
                element->Input();
            }
        }
        void Update() // update for things like resizing events, adding new elements, etc
        {
            if (resizeEvent) {
                resizeElements();
            }

            for(auto &element : elements) {
                element->Update();
            }
        };

        void Render() // draw the layout
        {
            for(auto &element : elements) {
                element->Render();
            }
        }



    private:
        int X, Y;
        int width, height;
        int innerWidth, innerHeight;
        int itemSize; // for fixed and relative layouts
        int padding; // space between the layout and the elements
        int gap; // gap between elements TODO: move to style
        std::vector<std::shared_ptr<GUIElement>> elements;
        LayoutDirection layoutDirection;
        LayoutType layoutType;
        bool resizeEvent = false;

        void simpleResize() { //elements of the same size
            int numOfElements = elements.size();
            int targetSize;
            switch(layoutDirection) {
                case HORIZONTAL:
                    targetSize = ( innerWidth / numOfElements ) - (gap * elements.size() - 1);
                    break;
                case VERTICAL:
                    targetSize = (height / numOfElements) - (gap * elements.size() - 1);
                    break;
                default:
                    break;
            }

            for(auto &element : elements) {
                switch (layoutDirection)
                {
                case HORIZONTAL:
                    element->setPosition(X, Y);
                    element->setSize(targetSize, height);
                    break;
                
                case VERTICAL:
                    element->setPosition(X, Y);
                    element->setSize(width, targetSize);
                    break;

                default:
                    break;
                }
            }
        }

        void complexResize() { //elements of differnet sizes
            switch (layoutType)
            {
            case FIXED:

                break;
            case RELATIVE:
                /* code */
                break;
            default:
                break;
            }

        }

        void updateButtonPositions() {
            int currentX = X;
            int currentY = Y;

            for(auto &element : elements) {
                element->setPosition(currentX, currentY);
                switch (layoutDirection)
                {
                case HORIZONTAL:
                    currentX += element->getWidth() + gap;
                    break;
                case VERTICAL:
                    currentY += element->getHeight() + gap;
                    break;
                default:
                    break;
                }
            }
        }

        void resizeElements() {
            innerHeight = height - (padding * 2);
            innerWidth = width - (padding * 2);

            switch (layoutType)
            {
            case FILL:
                simpleResize();
                break;
            case FIXED:
            case RELATIVE:

                #ifdef DEBUG
                    TraceLog(LOG_WARNING, "Layout type not supported for resizing");
                #endif

                break;
            default:
                break;

            resizeEvent = false;
            }
        }

        
    };
} // namespace GUI


