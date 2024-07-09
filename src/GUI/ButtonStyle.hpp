#pragma once
#include <iostream>

#include "raylib.h"

namespace GUI
{
    class ButtonStyle
    {
        public:
            ButtonStyle() 
            :   bgColor(RAYWHITE),
                bgHoverColor(GRAY),
                textColor(BLACK),
                hoverTextColor(BLACK),
                borderColor(BLACK),
                borderHoverColor(BLACK) 
            {};

            ButtonStyle(Color color, Color textColor, Color hoverColor, Color hoverTextColor) 
            :   bgColor(color),
                bgHoverColor(hoverColor),
                textColor(textColor),
                hoverTextColor(hoverTextColor),
                borderColor(BLACK),
                borderHoverColor(BLACK) 
            {};

            ~ButtonStyle();
            
            void Load();
            void Unload();

            void SetFontSize(u_int16_t size);
            void SetBorderSize(u_int16_t size);
            void SetDegreeCorner(u_int16_t degree);

            void SetBgColor(Color color);
            void SetBgHoverColor(Color color);
            void SetTextColor(Color color);
            void SetHoverTextColor(Color color);
            void SetBorderColor(Color color);
            void SetBorderHoverColor(Color color);

            u_int16_t GetFontSize();
            u_int16_t GetBorderSize();
            u_int16_t GetDegreeCorner();

            Color GetBgColor();
            Color GetBgHoverColor();
            Color GetTextColor();
            Color GetHoverTextColor();
            Color GetBorderColor();
            Color GetBorderHoverColor();

        private:
            u_int16_t fontSize = 20;
            u_int16_t borderSize = 10;
            u_int16_t degreeCorner = 0;

            Color bgColor, bgHoverColor;
            Color textColor, hoverTextColor;
            Color borderColor, borderHoverColor;

    };

} // namespace GUI