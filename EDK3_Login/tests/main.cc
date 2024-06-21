//
// main.cc
// Ivan Sancho, Escuela Superior de Arte y Tecnologia
// Programacion Grafica
// ESAT 2022-2023
//

#include <stdio.h>
#include <math.h>
#include "ESAT/window.h"
#include "ESAT/input.h"
#include "ESAT/draw.h"
#include "ESAT/time.h"

#include "EDK3/geometry.h"
#include "EDK3/camera.h"
#include "EDK3/drawable.h"
#include "EDK3/matdiffusetexture.h"
#include "EDK3/texture.h"
#include "EDK3/dev/gpumanager.h"
#include "EDK3/rendertarget.h"

#include "ESAT_extra/imgui.h"
#include "EDK3/dev/opengl.h"


#include "math_library/vector_2.h"
#include "math_library/vector_3.h"


#include "dev/custom_gpu_program.h"
#include "dev/custom_gpu_buffer.h"
#include "dev/custom_gpu_camera.h"
#include "dev/custom_gpu_manager.h"
#include "dev/custom_gpu_shader.h"
#include "dev/custom_gpu_texture.h"


#include "DataStructure.h"
#include "material_custom.h"
#include "geometry_custom_terrain.h"
#include "geometry_custom_sphere.h"
#include "camera_custom.h"
#include "geometry_custom_quad.h"
#include "geometry_custom_cube.h"
#include "geometry_custom_surface.h"
//#include "ImGuiDemo.h"


//float EDK3::MaterialCustom::LightSettings::ambient_color_[3] = { 0.1f,0.1f,0.1f };

void ImGuiLights() {
    static int num_materials = 3;
    static int num_lights = 9;

    //static int selected_material = 0;
    static int selected_light = 0;
    static float temp_pos[3];
    static float temp_dir[3];
    static float temp_diff_color[3];
    static float temp_spec_color[3];
    static bool temp_enabled;

    ImGui::Begin("LIGHT MANAGER");


    // Selección de luz dentro del material seleccionado
    const char* light_names[] = { "Light directional", 
                                  "Light spotlight 1", "Light spotlight 2", "Light spotlight 3", "Light spotlight 4", 
                                  "Light pointlight 1", "Light pointlight 2", "Light pointlight 3", "Light pointlight 4"};
    if (ImGui::Combo("Select Light", &selected_light, light_names, num_lights)) {
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

    if (GS.Materials.get()->matSettings->lightConf_ != nullptr) {
        
        EDK3::CustomLightMaterial::LightConf* light = &GS.Materials[0].matSettings->lightConf_[selected_light];

        //ImGui::InputInt("Type", &light->type_);
        ImGui::ColorEdit3("Diffuse Color", light->diff_color_);
        ImGui::ColorEdit3("Specular Color", light->spec_color_);
        if (0 == light->type_) {
            ImGui::DragFloat3("Direction", light->dir_, 0.01f, -1.0f, 1.0f);
        }
        else {
            if (1 == light->type_) {
                ImGui::DragFloat3("Direction", light->dir_, 0.01f, -1.0f, 1.0f);
                ImGui::SliderFloat("Cutoff", &light->cutOff_, 0.0f, 1.0f);
                ImGui::SliderFloat("outer Cutoff", &light->outerCutOff_, 0.0f, 1.0f);
            }
            ImGui::DragFloat3("Position", light->pos_, 0.01f);
            ImGui::SliderFloat("Linear Attenuation", &light->linear_att_, 0.0f, 1.0f);
            ImGui::SliderFloat("Quadratic Attenuation", &light->quadratic_att_, 0.0f, 1.0f);
            ImGui::SliderFloat("Constant Attenuation", &light->constant_att_, 0.0f, 1.0f);
            ImGui::SliderFloat("Shininess", &light->shininess_, 0.1f, 128.0f);
            ImGui::SliderFloat("Strength", &light->strength_, 0.1f, 50.0f);
        }
        
       


        static bool temp = true;
        ImGui::Checkbox("Enabled", &temp);
        light->enabled_ = temp == true ? 1: 0;

        for (int i = 0; i < num_materials; i++)
        {
            memcpy(GS.Materials[i].matSettings->lightConf_[selected_light].pos_, &light->pos_, sizeof(float) * 3);
            memcpy(GS.Materials[i].matSettings->lightConf_[selected_light].dir_, &light->dir_, sizeof(float) * 3);
            memcpy(GS.Materials[i].matSettings->lightConf_[selected_light].diff_color_, &light->diff_color_, sizeof(float) * 3);
            memcpy(GS.Materials[i].matSettings->lightConf_[selected_light].spec_color_, &light->spec_color_, sizeof(float) * 3);
            GS.Materials[i].matSettings->lightConf_[selected_light].linear_att_ = light->linear_att_;
            GS.Materials[i].matSettings->lightConf_[selected_light].quadratic_att_ = light->quadratic_att_;
            GS.Materials[i].matSettings->lightConf_[selected_light].constant_att_ = light->constant_att_;
            GS.Materials[i].matSettings->lightConf_[selected_light].shininess_ = light->shininess_;
            GS.Materials[i].matSettings->lightConf_[selected_light].strength_ = light->strength_;

            GS.Materials[i].matSettings->lightConf_[selected_light].cutOff_ = light->cutOff_;
            GS.Materials[i].matSettings->lightConf_[selected_light].outerCutOff_ = light->outerCutOff_;
            GS.Materials[i].matSettings->lightConf_[selected_light].enabled_ = light->enabled_;
        }
    }

    //if (ImGui::Button(" ")) {

    //}

    ImGui::End();


}


void ImGuiGeneral() {
    ImGui::Begin("General Manager");

    ImGui::SliderInt("Postprocess", &GS.Postprocess, 0, 3);
    GS.mat_postprocess_settings.get()->set_postprocess_type(GS.Postprocess);

    ImGui::Checkbox("Wireframe", &GS.wireframe);

    ImGui::End();
}


void InitLight(int light, int light_type, 
              const float* pos, const float* dir, const float* diff_color, const float* spec_color,
              float linear_att, float quad_att, float const_att, 
              float shininess, float strength, const float* cam_pos) {

    for (int i = 0; i < 3; i++)
    {
        GS.Materials[i].matSettings->lightConf_[light].type_ = light_type;
        memcpy(GS.Materials[i].matSettings->lightConf_[light].pos_, pos, sizeof(float) * 3);
        memcpy(GS.Materials[i].matSettings->lightConf_[light].dir_, dir, sizeof(float) * 3);
        memcpy(GS.Materials[i].matSettings->lightConf_[light].diff_color_, diff_color, sizeof(float) * 3);
        memcpy(GS.Materials[i].matSettings->lightConf_[light].spec_color_, spec_color, sizeof(float) * 3);

        GS.Materials[i].matSettings->lightConf_[light].linear_att_ = linear_att;
        GS.Materials[i].matSettings->lightConf_[light].quadratic_att_ = quad_att;
        GS.Materials[i].matSettings->lightConf_[light].constant_att_ = const_att;
        GS.Materials[i].matSettings->lightConf_[light].shininess_ = shininess;
        GS.Materials[i].matSettings->lightConf_[light].strength_ = strength;
        memcpy(GS.Materials[i].matSettings->lightConf_[light].camera_pos_, cam_pos, sizeof(cam_pos));

        GS.Materials[i].matSettings->lightConf_[light].cutOff_ = 0.78f;
        GS.Materials[i].matSettings->lightConf_[light].outerCutOff_ = 0.75f;


        GS.Materials[i].matSettings->lightConf_[light].enabled_ = 1;
    }
}

void InitSceneLights() {

  static float pos[]{ 0.0f ,115.0f, 0.0f };
  static float dir[]{ 0.05f, 1.0f, 0.05f };
  static float diff_color[]{ 1.0f,1.0f,1.0f };
  static float spec_color[]{ 1.0f,1.0f,1.0f };
  float linear_att = 1.0f;
  float quad_att = 1.0f;
  float const_att = 1.0f;
  float shininess = 1.0f;
  float strength = 0.7f;
  InitLight(0, 0, pos, dir, diff_color, spec_color, linear_att, quad_att, const_att, shininess, strength, GS.camera->position());

  pos[0] = 0.0f; pos[1] = 115.0f; pos[2] = 0.0f;
  dir[0] = 0.05f; dir[1] = 1.0f; dir[2] = 0.05f;
  diff_color[0] = 0.05f; diff_color[1] = 1.0f; diff_color[2] = 0.05f;
  spec_color[0] = 1.0f; spec_color[1] = 1.0f; spec_color[2] = 1.0f;
  linear_att = 1.0f;
  quad_att = 1.0f;
  const_att = 1.0f;
  shininess = 1.0f;
  strength = 0.7f;
  InitLight(1, 1, pos, dir, diff_color, spec_color, linear_att, quad_att, const_att, shininess, strength, GS.camera->position());
  
  pos[0] = 0.0f; pos[1] = 115.0f; pos[2] = 0.0f;
  dir[0] = 0.05f; dir[1] = 1.0f; dir[2] = 0.05f;
  diff_color[0] = 0.05f; diff_color[1] = 1.0f; diff_color[2] = 0.05f;
  spec_color[0] = 1.0f; spec_color[1] = 1.0f; spec_color[2] = 1.0f;
  linear_att = 1.0f;
  quad_att = 1.0f;
  const_att = 1.0f;
  shininess = 1.0f;
  strength = 0.7f;
  InitLight(2, 1, pos, dir, diff_color, spec_color, linear_att, quad_att, const_att, shininess, strength, GS.camera->position());
  
  pos[0] = 0.0f; pos[1] = 115.0f; pos[2] = 0.0f;
  dir[0] = 0.05f; dir[1] = 1.0f; dir[2] = 0.05f;
  diff_color[0] = 0.05f; diff_color[1] = 1.0f; diff_color[2] = 0.05f;
  spec_color[0] = 1.0f; spec_color[1] = 1.0f; spec_color[2] = 1.0f;
  linear_att = 1.0f;
  quad_att = 1.0f;
  const_att = 1.0f;
  shininess = 1.0f;
  strength = 0.7f;
  InitLight(3, 1, pos, dir, diff_color, spec_color, linear_att, quad_att, const_att, shininess, strength, GS.camera->position());
  
  pos[0] = 0.0f; pos[1] = 115.0f; pos[2] = 0.0f;
  dir[0] = 0.05f; dir[1] = 1.0f; dir[2] = 0.05f;
  diff_color[0] = 0.05f; diff_color[1] = 1.0f; diff_color[2] = 0.05f;
  spec_color[0] = 1.0f; spec_color[1] = 1.0f; spec_color[2] = 1.0f;
  linear_att = 1.0f;
  quad_att = 1.0f;
  const_att = 1.0f;
  shininess = 1.0f;
  strength = 0.7f; 
  InitLight(4, 1, pos, dir, diff_color, spec_color, linear_att, quad_att, const_att, shininess, strength, GS.camera->position());
  
  pos[0] = 0.0f; pos[1] = 115.0f; pos[2] = 0.0f;
  dir[0] = 0.05f; dir[1] = 1.0f; dir[2] = 0.05f;
  diff_color[0] = 0.05f; diff_color[1] = 1.0f; diff_color[2] = 0.05f;
  spec_color[0] = 1.0f; spec_color[1] = 1.0f; spec_color[2] = 1.0f;
  linear_att = 1.0f;
  quad_att = 1.0f;
  const_att = 1.0f;
  shininess = 1.0f;
  strength = 0.7f; 
  InitLight(5, 2, pos, dir, diff_color, spec_color, linear_att, quad_att, const_att, shininess, strength, GS.camera->position());
  
  pos[0] = 0.0f; pos[1] = 115.0f; pos[2] = 0.0f;
  dir[0] = 0.05f; dir[1] = 1.0f; dir[2] = 0.05f;
  diff_color[0] = 0.05f; diff_color[1] = 1.0f; diff_color[2] = 0.05f;
  spec_color[0] = 1.0f; spec_color[1] = 1.0f; spec_color[2] = 1.0f;
  linear_att = 1.0f;
  quad_att = 1.0f;
  const_att = 1.0f;
  shininess = 1.0f;
  strength = 0.7f; 
  InitLight(6, 2, pos, dir, diff_color, spec_color, linear_att, quad_att, const_att, shininess, strength, GS.camera->position());
  
  pos[0] = 0.0f; pos[1] = 115.0f; pos[2] = 0.0f;
  dir[0] = 0.05f; dir[1] = 1.0f; dir[2] = 0.05f;
  diff_color[0] = 0.05f; diff_color[1] = 1.0f; diff_color[2] = 0.05f;
  spec_color[0] = 1.0f; spec_color[1] = 1.0f; spec_color[2] = 1.0f;
  linear_att = 1.0f;
  quad_att = 1.0f;
  const_att = 1.0f;
  shininess = 1.0f;
  strength = 0.7f; 
  InitLight(7, 2, pos, dir, diff_color, spec_color, linear_att, quad_att, const_att, shininess, strength, GS.camera->position());
  
  pos[0] = 0.0f; pos[1] = 115.0f; pos[2] = 0.0f;
  dir[0] = 0.05f; dir[1] = 1.0f; dir[2] = 0.05f;
  diff_color[0] = 0.05f; diff_color[1] = 1.0f; diff_color[2] = 0.05f;
  spec_color[0] = 1.0f; spec_color[1] = 1.0f; spec_color[2] = 1.0f;
  linear_att = 1.0f;
  quad_att = 1.0f;
  const_att = 1.0f;
  shininess = 1.0f;
  strength = 0.7f; 
  InitLight(8, 2, pos, dir, diff_color, spec_color, linear_att, quad_att, const_att, shininess, strength, GS.camera->position());
}

void InitMaterials() {
    EDK3::scoped_array<char> error_log;

    // Land

    GS.Materials[sand].mat.alloc();
    GS.Materials[sand].matSettings.alloc();

    GS.Materials[sand].mat->init(error_log, "./shaders/basicVertex.vs", "./shaders/light_shader.fs");
    GS.Materials[sand].mat->useTexture_ = 1;

    float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GS.Materials[sand].matSettings->set_color(color);
    GS.Materials[sand].matSettings->set_texture(GS.Textures[sand].get());


    // Sea 

    GS.Materials[water].mat.alloc();
    GS.Materials[water].matSettings.alloc();

    GS.Materials[water].mat->init(error_log, "./shaders/basicVertex.vs", "./shaders/light_shader.fs");
    GS.Materials[water].mat->useTexture_ = 1;

    //color[0] = {1.0f, 1.0f, 1.0f, 0.0f};
    GS.Materials[water].matSettings->set_color(color);
    GS.Materials[water].matSettings->set_texture(GS.Textures[water].get());


    // Volcano 

    GS.Materials[volcano].mat.alloc();
    GS.Materials[volcano].matSettings.alloc();

    GS.Materials[volcano].mat->init(error_log, "./shaders/basicVertex.vs", "./shaders/light_shader.fs");
    GS.Materials[volcano].mat->useTexture_ = 1;

    //color[0] = {1.0f, 1.0f, 1.0f, 0.0f};
    GS.Materials[volcano].matSettings->set_color(color);
    GS.Materials[volcano].matSettings->set_texture(GS.Textures[volcano].get());


    // Transparent

    GS.mat_transparent.alloc();
    GS.mat_transparent_settings.alloc();

    GS.mat_transparent->init(error_log, "./shaders/transparent_vertex.vs", "./shaders/transparent_shader.fs");
    GS.mat_transparent->useTexture_ = 1;

    GS.mat_transparent_settings->set_color(color);
    GS.mat_transparent_settings->set_texture(GS.Textures[3].get());
    GS.mat_transparent_settings->set_alpha(1.0f);
}
    

void InitTextures() {
    EDK3::Texture::Load("./textures/sand.png", &GS.Textures[sand]);
    if (!GS.Textures[sand].get()) {
        printf("Can't load sand.png\n");
        exit(-2);
    }    
    EDK3::Texture::Load("./textures/water2.png", &GS.Textures[water]);
    if (!GS.Textures[water].get()) {
        printf("Can't load water.png\n");
        exit(-2);
    }

    EDK3::Texture::Load("./textures/main_volcano.png", &GS.Textures[volcano]);
    if (!GS.Textures[volcano].get()) {
        printf("Can't load volcano.png\n");
        exit(-2);
    }

    EDK3::Texture::Load("./textures/window_transparency.png", &GS.Textures[3]);
    if (!GS.Textures[3].get()) {
        printf("Can't load window.png\n");
        exit(-2);
    }
}

void AddDrawable(EDK3::Node* root, EDK3::Geometry *g, EDK3::Material *m, EDK3::MaterialSettings *ms, float pos[3], float HPR[3], const char* name) {
  EDK3::ref_ptr<EDK3::Drawable> drawable;
  drawable.alloc();
  drawable->set_geometry(g);
  drawable->set_material(m);
  drawable->set_material_settings(ms);
  drawable->set_position(pos[0], pos[1], pos[2]);
  drawable->set_HPR(HPR[0], HPR[1], HPR[2]);
  drawable->set_name(name);
  root->addChild(drawable.get());
}




void InitTerrain() {

    

    // Init Terrains variable
    GS.Terrains[sand].terrain.alloc();
    GS.Terrains[water].terrain.alloc();

    EDK3::Node* root = GS.root.get();

    // Initialize Land
    strncpy(GS.Terrains[sand].name, "Land", sizeof(GS.Terrains[sand].name));
    GS.Terrains[sand].num_cols = 1024;
    GS.Terrains[sand].num_rows = 1024;
    GS.Terrains[sand].height_mult = 10.0f;
    GS.Terrains[sand].size = 3.5f;
    GS.Terrains[sand].smoothness = 0.5f;
    GS.Terrains[sand].heightmap_mult = 300.0f;
    strncpy(GS.Terrains[sand].heightmap_path, "./textures/heightmap_2.png", sizeof(GS.Terrains[sand].heightmap_path));
    GS.Terrains[sand].use_heightmap = true;
    GS.Terrains[sand].is_centered = true;
    GS.Terrains[sand].pos[0] = 0.0f;
    GS.Terrains[sand].pos[1] = 0.0f;
    GS.Terrains[sand].pos[2] = 0.0f;
    GS.Terrains[sand].HPR[0] = 0.0f;
    GS.Terrains[sand].HPR[1] = 0.0f;
    GS.Terrains[sand].HPR[2] = 0.0f;
    GS.Terrains[sand].mat = GS.Materials[sand].mat;
    GS.Terrains[sand].mat_settings = GS.Materials[sand].matSettings;
    

    
    // Initialize Water
    strncpy(GS.Terrains[water].name, "Water", sizeof(GS.Terrains[water].name));
    GS.Terrains[water].num_cols = 64;
    GS.Terrains[water].num_rows = 64;
    GS.Terrains[water].height_mult = 50.0f;
    GS.Terrains[water].size = 150.0f;
    GS.Terrains[water].smoothness = 0.005f;
    GS.Terrains[water].heightmap_mult = 100.0f;
    strncpy(GS.Terrains[water].heightmap_path, "./textures/water_heightmap.png", sizeof(GS.Terrains[water].heightmap_path));
    GS.Terrains[water].use_heightmap = true;
    GS.Terrains[water].is_centered = true;
    GS.Terrains[water].pos[0] = 0.0f;
    GS.Terrains[water].pos[1] = -5.0f;
    GS.Terrains[water].pos[2] = 0.0f;
    GS.Terrains[water].HPR[0] = 0.0f;
    GS.Terrains[water].HPR[1] = 0.0f;
    GS.Terrains[water].HPR[2] = 0.0f;
    GS.Terrains[water].mat = GS.Materials[water].mat;
    GS.Terrains[water].mat_settings = GS.Materials[water].matSettings;
    



    // Give attributes and add to the root system
    for (int i = 0; i < num_terrains; ++i) {
        //Terrains[i]->terrain.alloc();
        GS.Terrains[i].terrain->init(GS.Terrains[i].num_cols, GS.Terrains[i].num_rows, GS.Terrains[i].height_mult, GS.Terrains[i].size, GS.Terrains[i].smoothness, GS.Terrains[i].heightmap_mult, GS.Terrains[i].heightmap_path, GS.Terrains[i].use_heightmap);
        AddDrawable(root, GS.Terrains[i].terrain.get(), GS.Terrains[i].mat.get(), GS.Terrains[i].mat_settings.get(), GS.Terrains[i].pos, GS.Terrains[i].HPR, GS.Terrains[i].name);
    }
}

/*
void InitTerrain() {

    EDK3::Node* root = GS.root.get();
    // Land
    EDK3::ref_ptr<EDK3::TerrainCustom> custom_terrain;
    custom_terrain.alloc();
    custom_terrain->init(256, 256, 5.0f, 1.0f, 0.5f, 30.0f, "./textures/south.png", true);

    float pos[3] = { 0.0f, 0.0f, 0.0f };
    float HPR[3] = { 0.0f, 0.0f, 0.0f };
    AddDrawable(root, custom_terrain.get(), Materials.mat.get(), Materials.matSettings.get(), pos, HPR, "terrain_land");
    
    // Sea
    EDK3::ref_ptr<EDK3::TerrainCustom> CT_water;
    CT_water.alloc();
    CT_water->init(64, 64, 1.0f, 100.0f, 0.005f, 100.0f, "./textures/water_heightmap.png", true);
    pos[1] = 10.0f;
    AddDrawable(root, CT_water.get(), Materials.mat_water.get(), Materials.matSettings_water.get(), pos, HPR, "terrain_water");


}
*/


void InitSphere(EDK3::Node* root) {
  EDK3::ref_ptr<EDK3::SphereCustom> sphere;
  sphere.alloc();
  sphere->init(10.0f);

  float pos[3] = { 0.0f, 300.0f, 0.0f };
  float HPR[3] = { 0.0f, 0.0f, 0.0f };
  AddDrawable(root, sphere.get(), GS.Materials[sand].mat.get(), GS.Materials[sand].matSettings.get(), pos, HPR, "sphere");


  pos[1] = 400.0f;
  AddDrawable(root, sphere.get(), GS.mat_transparent.get(), GS.mat_transparent_settings.get(), pos, HPR, "sphere trasnparent");
}

void InitQuad(EDK3::Node* root) {
    EDK3::ref_ptr<EDK3::QuadCustom> quad;
    quad.alloc();
    quad->init(10.0f);

    float pos[3] = { -50.0f, 300.0f, 0.0f };
    float HPR[3] = { 0.0f, 0.0f, 0.0f };
    AddDrawable(root, quad.get(), GS.Materials[sand].mat.get(), GS.Materials[sand].matSettings.get(), pos, HPR, "quad");
}

void InitCube24(EDK3::Node* root) {
    EDK3::ref_ptr<EDK3::CubeCustom> cube;
    cube.alloc();
    cube->init24v(10.0f);

    float pos[3] = { 50.0f, 300.0f, 0.0f };
    float HPR[3] = { 0.0f, 0.0f, 0.0f };
    AddDrawable(root, cube.get(), GS.Materials[sand].mat.get(), GS.Materials[sand].matSettings.get(), pos, HPR, "Cube24");

    pos[1] = 400.0f;
    AddDrawable(root, cube.get(), GS.mat_transparent.get(), GS.mat_transparent_settings.get(), pos, HPR, "Cube transparent");

}

void InitCube8(EDK3::Node* root) {
    EDK3::ref_ptr<EDK3::CubeCustom> cube;
    cube.alloc();
    cube->init8v(10.0f);

    float pos[3] = { 100.0f, 300.0f, 0.0f };
    float HPR[3] = { 0.0f, 0.0f, 0.0f };
    AddDrawable(root, cube.get(), GS.Materials[sand].mat.get(), GS.Materials[sand].matSettings.get(), pos, HPR, "Cube8");
}

void InitSurface(EDK3::Node* root) {
    // no usar faltan los puntos de la figura

    Vec2 figure_points[kFigurePoints];
    EDK3::ref_ptr<EDK3::SurfaceCustom> Surface;
    Surface.alloc();
    Surface->init(figure_points, kFigurePoints, 10, 1.0f, 1.0f);


    float pos[3] = { -100.0f, 300.0f, 0.0f };
    float HPR[3] = { 0.0f, 0.0f, 0.0f };
    AddDrawable(root, Surface.get(), GS.Materials[sand].mat.get(), GS.Materials[sand].matSettings.get(), pos, HPR, "Surface");

}

void InitObj(EDK3::Node* root) {
    EDK3::LoadObj("./obj/lava_land.obj", &GS.customObjGeometry, nullptr);

    float pos[3] = { -200.0f, 300.0f, 0.0f };
    float HPR[3] = { 0.0f, 0.0f, 0.0f };
    AddDrawable(root, GS.customObjGeometry[0].get(), GS.Materials[volcano].mat.get(), GS.Materials[volcano].matSettings.get(), pos, HPR, "Volcano");
}

void InitTransparent(EDK3::Node* root) {
    EDK3::ref_ptr<EDK3::SphereCustom> sphere;
    sphere.alloc();
    sphere->init(10.0f);

    float pos[3] = { 0.0f, 400.0f, 0.0f };
    float HPR[3] = { 0.0f, 0.0f, 0.0f };

    AddDrawable(root, sphere.get(), GS.mat_transparent.get(), GS.mat_transparent_settings.get(), pos, HPR, "sphere trasnparent");

    EDK3::ref_ptr<EDK3::CubeCustom> cube;
    cube.alloc();
    cube->init24v(10.0f);
    pos[1] = 400.0f;
    pos[0] = 100.0f;

    AddDrawable(root, cube.get(), GS.mat_transparent.get(), GS.mat_transparent_settings.get(), pos, HPR, "Cube transparent");
}

void InitCamera() 
{
    //Allocating and initializing the camera:
    GS.camera.alloc();

    float pos[] = { 0.0f, 80.0f, 100.0f };
    float view[] = { 0.0f, 0.0f, 0.0f };
    GS.camera->set_position(pos);
    GS.camera->initViewTarget(kWindowWidth, kWindowHeight);
    GS.camera->setSensitibity(1.0f);
    //GS.camera->set_view_direction(view);
    GS.camera->setSpeed(5.0f);
    GS.camera->setSpeedModifier(0.1f);
    GS.camera->setupPerspective(70.0f, 8.0f / 6.0f, 1.0f, 3000.0f);

}

void InitPostProcesses()
{
    GS.render_target.alloc()->init((float)kWindowWidth,(float)kWindowHeight, 1);
    GS.mat_postprocess.alloc();
    GS.mat_postprocess_settings.alloc();

    GS.mat_postprocess->init();

    float pink[4] = { 0.65f, 0.0f, 0.95f, 1.0f };
    GS.mat_postprocess->set_use_texture(true);
    //Aqui le asociamos la textura del render target y se la asociamos al material de postproceso
    GS.mat_postprocess_settings->set_texture(GS.render_target->color_texture(0));
    GS.mat_postprocess_settings->set_color(pink);
}

void InitScene() {
  //Allocating root node:
  EDK3::Node* root = GS.root.alloc();
  //EDK3::Node* transparents = GS.transparents.alloc();
  InitCamera();
  GS.Textures.alloc(10);
  GS.Materials.alloc(10);
  GS.customObjGeometry.alloc(10);
  GS.Terrains.alloc(2);

  InitTextures();
  InitMaterials();
  InitPostProcesses();
  InitSceneLights();

  InitTerrain();
  InitObj(root);
  InitSphere(root);
  InitQuad(root);
  InitCube24(root);
  InitCube8(root);
  //InitSurface(root); --> no usar
  
  //InitTransparent(transparents);
  //root->addChild(transparents);
  
  EDK3::dev::GPUManager::CheckGLError("Prepare END");
}






void UpdateFn() {
  GS.camera->set_clear_color(0.94f, 1.0f, 0.94f, 1.0f);
  GS.camera->update(0.0f, GS.camera->window_size().x, GS.camera->window_size().y);
  
}

void RenderFn() {
  //For every frame... determine what's visible:
  GS.camera->doCull(GS.root.get());

  //Rendering the scene:
  EDK3::dev::GPUManager::CheckGLError("begin Render-->");

  if (GS.Postprocess != 0) GS.render_target->begin();
  if (GS.wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  GS.camera->doRender();

  if (GS.wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  if (GS.Postprocess != 0) {
      GS.render_target->end();
      GS.mat_postprocess->drawFullScreenQuad(GS.mat_postprocess_settings.get());
  }
  
  EDK3::dev::GPUManager::CheckGLError("end Render-->");
}

void ImGuiFn(double dt) {
  ImGui::Begin("FPS Window");
  ImGui::Text("FPS: %0.1f", 1000.0 / dt);
  ImGui::Text("Delta time: %0.3f ms", dt);
  ImGui::End();
  //IMGUI.DrawImGuiTerrain();
  //IMGUI.LightManager();
  ImGui::ShowTestWindow();
  ImGuiGeneral();
  ImGuiLights();
  ImGui::Render();
}

int ESAT::main(int argc, char** argv) {
  //EDK3::dev::CustomGPUManager GPU;
  //EDK3::dev::CustomGPUManager::ReplaceGPUManagerImplementation(&GPU);

  //GPU.disableDepthTest();
  //GPU.enableDepthTest(EDK3::dev::GPUManager::kCompareFunc_Always);
  
  ESAT::WindowInit(kWindowWidth, kWindowHeight);
  InitScene();
  double dt = 0.0;
  double last_time = ESAT::Time();
  while (!ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape) && 
         ESAT::WindowIsOpened()) {
    UpdateFn();
    RenderFn();
    
    dt = ESAT::Time() - last_time;
    last_time = ESAT::Time();
    ImGuiFn(dt);
    ESAT::WindowFrame();
  }
  return 0;
}
