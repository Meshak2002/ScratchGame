#pragma once
#include "vendor/imgui/imgui.h"

class GameHUD
{
public:
    GameHUD(struct GLFWwindow* window);
    ~GameHUD();

    void NewFrame();
    void RenderFrame();
};