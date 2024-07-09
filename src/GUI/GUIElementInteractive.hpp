#pragma once

#include <functional>

namespace GUI
{
    class InteractiveElement {
    public:
        virtual ~InteractiveElement() = default;

        void setOnClick(std::function<void()> callback) {
            onClickCallback = callback;
        }

    protected:
        std::function<void()> onClickCallback;
    };
}
