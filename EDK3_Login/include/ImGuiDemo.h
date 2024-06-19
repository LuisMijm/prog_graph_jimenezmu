#pragma once


#include "ESAT_extra/imgui.h"

struct GameState;

class ImGuiDemo
{

public:
    int selectedTerrain;

    int num_lights;
    int num_materials;

public:
    ImGuiDemo();
    ~ImGuiDemo();

    //void DrawImGuiTerrain();
    //void LightManager();

    //void ImGuiLights();
    //void ImGuiPostprocess();

}IMGUI;

