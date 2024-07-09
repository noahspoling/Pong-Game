#pragma once

#include <cstring>
#include <string>
#include <iostream>
#include <functional>



#include "raylib.h"

#include "GUIElement.hpp"
#include "GUIElementInteractive.hpp"
#include "ButtonStyle.hpp"
#include "Style.hpp"

namespace GUI 
{
    class Button : public GUIElement, public InteractiveElement
    {
        public:
            Button(std::string name, int posX, int posY)
                : name(name), X(posX), Y(posY), width(250), height(80), margin(3)//, style(new ButtonStyle())
            {
                const int length = name.length();
                char* char_array = new char[length + 1];

                std::strcpy(char_array, name.c_str());
                Wave selectFX = LoadWave("rescources/sounds/select.wav");
                Wave clickFX = LoadWave("rescources/sounds/click.wav");

                SelectFX_AsSound = LoadSoundFromWave(selectFX);
                ClickFX_asSound = LoadSoundFromWave(clickFX);

                UnloadWave(clickFX);
                UnloadWave(selectFX);
                
                this->name = char_array;
            };

            Button(std::string name, int posX, int posY, int width, int height)
                : name(name), X(posX), Y(posY), width(width), height(height), margin(3)
            {
                
                const int length = name.length();
                char* char_array = new char[length + 1];

                std::strcpy(char_array, name.c_str());
                Wave selectFX = LoadWave("rescources/sounds/select.wav");
                Wave clickFX = LoadWave("rescources/sounds/click.wav");

                SelectFX_AsSound = LoadSoundFromWave(selectFX);
                ClickFX_asSound = LoadSoundFromWave(clickFX);

                UnloadWave(clickFX);
                UnloadWave(selectFX);
                
                this->name = char_array;
            };

            void Init() override
            {
                // style->Init();
            }

            void Input() override
            {

                // style->Input();
            }

            void click() {
                if (onClickCallback) {
                    TraceLog(LOG_INFO, "Button callback was called!");
                    onClickCallback();
                }
                TraceLog(LOG_INFO, "Button callback was not called!");
            }


            void addStyle(GUI::ButtonStyle* style)
            {
                // this->style = style;
            }


            /// @brief Render button on screen, if it's hovered, it will be in another color
            /// @param _setup function that will be executed when the button is clicked
            void Render() override {

                DrawRectangle(X, Y, width, height, (isHovered(GetMouseX(), GetMouseY()) ? RED : BLACK));
                DrawRectangle(X + margin, Y + margin, width - (margin * 2), height - (margin * 2), (isHovered(GetMouseX(), GetMouseY()) ? GRAY : WHITE));
                DrawText(name.c_str(), X + ((width/2) - MeasureText(name.c_str(), 30) / 2), Y + 25, 30, (isHovered(GetMouseX(), GetMouseY()) ? RED : BLACK));

                if(isHovered(GetMouseX(), GetMouseY()))
                {
                    if(!hovered)
                    {
                        PlaySound(SelectFX_AsSound);
                    }
                    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        PlaySound(ClickFX_asSound);
                        TraceLog(LOG_INFO, "Button was clickeddsdsdsd");
                        click();
                    }
                }
                hovered = isHovered(GetMouseX(), GetMouseY());
            }

            void Update() override
            {
                // style->Update();
            }

            void setName(std::string name)
            {
                this->name = name;
            }

            std::string getName() const
            {
                return name;
            }

        private:
            Sound SelectFX_AsSound, ClickFX_asSound;
            //ButtonStyle* style;
            bool hovered;
            int X, Y;
            int width, height;
            int margin;
            std::string name;

            /// @brief Function to find 
            /// @param posX position X of the cursor
            /// @param posY position Y of the cursor
            /// @return true if hovered, false otherwise
            int isHovered(int posX, int posY)
            {
                return (posX < X + width && posX > X && posY < Y + height && posY > Y);
            };
    };
} 
// namespace GUI