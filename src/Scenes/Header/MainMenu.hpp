#pragma once

#include <vector>

#include <raylib.h>

#include "../Scene.hpp"
#include "../../GUI/Button.hpp"
#include "../../GUI/Layout.hpp"


class MainMenu : public Scene
{
public:
    MainMenu(/* args */) = default;
    ~MainMenu() override = default;

    void init() override {
        layout = GUI::Layout(0, 0, GetScreenWidth(), GetScreenHeight());
        layout.add(std::make_shared<GUI::Button>("Play", 0, 0));
        layout.add(std::make_shared<GUI::Button>("Options", 0, 0));
        layout.add(std::make_shared<GUI::Button>("Exit", 0, 0));
        layout.Init();
        

        // buttons.push_back(GUI::Button("Play", 0, 0, 100, 50));
        // buttons.push_back(GUI::Button("Options", 0, 0, 100, 50));
        // buttons.push_back(GUI::Button("Exit", 0, 0, 100, 50));
        

        // for(auto &button : buttons) {
        //     button.Init();
        // }
    };

    void input() override {
        layout.Input();
        // for(auto &button : buttons) {
        //     button.Input();
        // }
    };

    void update() override {
        layout.Update();
        // for(auto &button : buttons) {
        //     button.Update();
        // }
    };

    void render() override {
        layout.Render();
        // for(auto &button : buttons) {
        //     button.Render();
        // }
    };

    void deInit() override {}
protected:

private:
    std::vector<GUI::Button> buttons;
    GUI::Layout layout;

};