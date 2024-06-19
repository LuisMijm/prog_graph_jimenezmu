#include "ImguiDemo.h"


#include "ESAT_extra/imgui.h"

//#include "DataStructure.h"
//#include "material_custom.h"


ImGuiDemo::ImGuiDemo()
{
}

ImGuiDemo::~ImGuiDemo()
{
}

/*
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
                
                //if (ImGui::MenuItem("Save", "Ctrl+S")) {
                //    // Acción al hacer click en Save
                //}
                

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

*/

/*
void ImGuiDemo::ImGuiLights(){

    static int selected_material = 0;
    static int selected_light = 0;
    static float temp_pos[3];
    static float temp_dir[3];
    static float temp_diff_color[3];
    static float temp_spec_color[3];
    static bool temp_enabled;

    ImGui::Begin("LIGHT MANAGER");
    
    const char* mat_names[] = { "Mat 1", "Mat 2" };
    if (ImGui::Combo("Select Material", &selected_material, mat_names, sizeof(mat_names))) {

        for (int i = 0; i < num_materials; i++) {
            bool is_selected = (selected_material == i);
            if (ImGui::Selectable("Material %d", is_selected)) {
                selected_material = i;
                selected_light = 0; 
            }
            //if (is_selected) {
                //ImGui::SetItemDefaultFocus();
            //}
        }
    }

    // Selección de luz dentro del material seleccionado
    const char* light_names[]= {"Light 1", "Light 2"};
    if (ImGui::Combo("Select Light", &selected_light, light_names, sizeof(light_names))) {
        for (int i = 0; i < num_lights; i++) {
            bool is_selected = (selected_light == i);
            if (ImGui::Selectable("Light %d", is_selected)) {
                selected_light = i;
            }
            //if (is_selected) {
            //    ImGui::SetItemDefaultFocus();
            //}
        }
    }

    //if (GS.Materials->lightConf_ != nullptr) {
    //    
    //    EDK3::ref_ptr<EDK3::MaterialCustom::LightConf>* light = GS.Materials->lightConf_[selected_light];

    //    ImGui::InputInt("Type", &light.type_);
    //    ImGui::DragFloat3("Position", light.pos_, 0.01f);
    //    ImGui::DragFloat3("Direction", light.dir_, 0.01f, -1.0f, 1.0f);
    //    ImGui::ColorEdit3("Diffuse Color", light.diff_color_);
    //    ImGui::ColorEdit3("Specular Color", light.spec_color_);
    //    ImGui::SliderFloat("Linear Attenuation", &light.linear_att_, 0.0f, 1.0f);
    //    ImGui::SliderFloat("Quadratic Attenuation", &light.quadratic_att_, 0.0f, 1.0f);
    //    ImGui::SliderFloat("Constant Attenuation", &light.constant_att_, 0.0f, 1.0f);
    //    ImGui::SliderFloat("Shininess", &light.shininess_, 0.0f, 128.0f);
    //    ImGui::SliderFloat("Strength", &light.strength_, 0.0f, 10.0f);
    //    ImGui::Checkbox("Enabled", &light.enabled_);
    //}

    if (ImGui::Button(" ")) {
        
    }

    ImGui::End();


}
*/


//void ImGuiDemo::ImGuiPostprocess()
//{
//    ImGui::Begin("General Manager");
//
//    //ImGui::SliderInt("Postprocess", &GS.Postprocess, 0, 3);
//    //ImGui::Checkbox("Wireframe", &GS.wireframe);
//
//    ImGui::End();
//}