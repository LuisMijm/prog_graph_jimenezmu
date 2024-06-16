#include "ImguiDemo.h"


ImGuiDemo::ImGuiDemo()
{
}

ImGuiDemo::~ImGuiDemo()
{
}

void ImGuiDemo::DrawImGuiTerrain() {
    ImGui::Begin("Terrain Settings");

    const char* terrainNames[2] = { Terrains[0]->name, Terrains[1]->name };
    ImGui::Combo("Select Terrain", &IMGUI.selectedTerrain, terrainNames, num_terrains);

    Terrain& t = *Terrains[IMGUI.selectedTerrain];


    ImGui::InputInt("Number of Columns", &Terrains[IMGUI.selectedTerrain]->num_cols);
    ImGui::InputInt("Number of Rows", &Terrains[IMGUI.selectedTerrain]->num_rows);
    ImGui::SliderFloat("Height Multiplier", &Terrains[IMGUI.selectedTerrain]->height_mult, 0.0f, 100.0f);
    ImGui::SliderFloat("Size", &Terrains[IMGUI.selectedTerrain]->size, 0.0f, 200.0f);
    ImGui::SliderFloat("Smoothness", &Terrains[IMGUI.selectedTerrain]->smoothness, 0.0f, 1.0f);
    ImGui::SliderFloat("Heightmap Multiplier", &Terrains[IMGUI.selectedTerrain]->heightmap_mult, 0.0f, 200.0f);
    //ImGui::InputText("Heightmap Path", t.heightmap_path, sizeof(t.heightmap_path));
    ImGui::Checkbox("Use Heightmap", &Terrains[IMGUI.selectedTerrain]->use_heightmap);
    ImGui::Checkbox("Is Centered", &Terrains[IMGUI.selectedTerrain]->is_centered);
    ImGui::InputFloat3("Position", Terrains[IMGUI.selectedTerrain]->pos);
    ImGui::InputFloat3("HPR", Terrains[IMGUI.selectedTerrain]->HPR);


    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Window")) {
            if (ImGui::BeginMenu("Game Object"))
            {

                if (ImGui::MenuItem("Terrain", "")) {

                }
                /*
                if (ImGui::MenuItem("Save", "Ctrl+S")) {
                    // Acción al hacer click en Save
                }
                */

                ImGui::EndMenu();
            }
            ImGui::EndMenu();

        }
        ImGui::EndMainMenuBar();
    }


    ImGui::End();
}

void ImGuiDemo::LightManager() {
    static float directional_light_dir[]{ -1.0f, 0.2f, 0.0f };
    static float directional_light_color[]{ 0.8f, 0.7f, 0.1f };

    ImGui::Begin("LIGHT MANAGER");

    ImGui::Text("Directional Light");
    ImGui::DragFloat3("Direction", directional_light_dir, 0.01f, -1.0, 1.0f);
    ImGui::ColorEdit3("Color", directional_light_color);

    memcpy(Materials.matSettings->lightConf_[0].dir_, directional_light_dir, sizeof(directional_light_dir));
    memcpy(Materials.matSettings->lightConf_[0].diff_color_, directional_light_color, sizeof(directional_light_color));

    memcpy(Materials.matSettings_water->lightConf_[0].dir_, directional_light_dir, sizeof(directional_light_dir));
    memcpy(Materials.matSettings_water->lightConf_[0].diff_color_, directional_light_color, sizeof(directional_light_color));

    ImGui::End();
}