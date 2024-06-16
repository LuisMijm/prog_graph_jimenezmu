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




//float EDK3::MaterialCustom::LightSettings::ambient_color_[3] = { 0.0f,0.0f,0.0f };







void InitLight(int light, int light_type, 
              float pos[3], float dir[3], float diff_color[3], float spec_color[3],
              float linear_att, float quad_att, float const_att, 
              float shininess, float strength, const float cam_pos[3]) {

  Materials.matSettings->lightConf_[light].type_ = light_type;
  memcpy(Materials.matSettings->lightConf_[light].pos_, pos, sizeof(pos));
  memcpy(Materials.matSettings->lightConf_[light].dir_, pos, sizeof(dir));
  memcpy(Materials.matSettings->lightConf_[light].diff_color_, pos, sizeof(diff_color));
  memcpy(Materials.matSettings->lightConf_[light].spec_color_, pos, sizeof(spec_color));
  
  Materials.matSettings->lightConf_[light].linear_att_ = linear_att;
  Materials.matSettings->lightConf_[light].quadratic_att_ = quad_att;
  Materials.matSettings->lightConf_[light].constant_att_ = const_att;
  Materials.matSettings->lightConf_[light].shininess_ = shininess;
  Materials.matSettings->lightConf_[light].strength_ = strength;
  memcpy(Materials.matSettings->lightConf_[light].camera_pos_, pos, sizeof(cam_pos));

  Materials.matSettings->lightConf_[light].enabled_ = true;


  Materials.matSettings_water->lightConf_[light].type_ = light_type;
  memcpy(Materials.matSettings_water->lightConf_[light].pos_, pos, sizeof(pos));
  memcpy(Materials.matSettings_water->lightConf_[light].dir_, pos, sizeof(dir));
  memcpy(Materials.matSettings_water->lightConf_[light].diff_color_, pos, sizeof(diff_color));
  memcpy(Materials.matSettings_water->lightConf_[light].spec_color_, pos, sizeof(spec_color));

  Materials.matSettings_water->lightConf_[light].linear_att_ = linear_att;
  Materials.matSettings_water->lightConf_[light].quadratic_att_ = quad_att;
  Materials.matSettings_water->lightConf_[light].constant_att_ = const_att;
  Materials.matSettings_water->lightConf_[light].shininess_ = shininess;
  Materials.matSettings_water->lightConf_[light].strength_ = strength;
  memcpy(Materials.matSettings_water->lightConf_[light].camera_pos_, pos, sizeof(cam_pos));

  Materials.matSettings_water->lightConf_[light].enabled_ = true;
}

void InitSceneLights() {
  int lightType = 0;
  float pos[3]{ 0.0f,100.0f,0.0f };
  float dir[3]{ -0.9f,0.2f,0.0f };
  float diff_color[3]{ 1.0f,1.0f,0.0f };
  float spec_color[3]{ 1.0f,1.0f,1.0f };
  float linear_att = 1.0f;
  float quad_att = 1.0f;
  float const_att = 1.0f;
  float shininess = 1.0f;
  float strength = 1.0f;

  InitLight(0, lightType, pos, dir, diff_color, spec_color, linear_att, quad_att, const_att, shininess, strength, GameState.camera->position());
  InitLight(1, lightType, pos, dir, diff_color, spec_color, linear_att, quad_att, const_att, shininess, strength, GameState.camera->position());
  InitLight(2, lightType, pos, dir, diff_color, spec_color, linear_att, quad_att, const_att, shininess, strength, GameState.camera->position());
  InitLight(3, lightType, pos, dir, diff_color, spec_color, linear_att, quad_att, const_att, shininess, strength, GameState.camera->position());
}

void InitMaterials() {
    EDK3::scoped_array<char> error_log;
    Materials.mat.alloc();
    Materials.matSettings.alloc();

    Materials.mat->init(error_log, "./shaders/basicVertex.vs", "./shaders/light_shader.fs");
    Materials.mat->useTexture_ = 1;

    float color[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    Materials.matSettings->set_color(color);
    Materials.matSettings->set_texture(Textures.texture.get());

    // Sea 

    Materials.mat_water.alloc();
    Materials.matSettings_water.alloc();

    Materials.mat_water->init(error_log, "./shaders/basicVertex.vs", "./shaders/light_shader.fs");
    Materials.mat_water->useTexture_ = 1;

    //color[0] = {1.0f, 1.0f, 1.0f, 0.0f};
    Materials.matSettings_water->set_color(color);
    Materials.matSettings_water->set_texture(Textures.texture_water.get());
}
    

void InitTextures() {
    EDK3::Texture::Load("./textures/sand.png", &Textures.texture);
    if (!Textures.texture) {
        printf("Can't load texture.png\n");
        exit(-2);
    }    
    EDK3::Texture::Load("./textures/water2.png", &Textures.texture_water);
    if (!Textures.texture_water) {
        printf("Can't load water.png\n");
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
    Terrains[0].alloc();
    Terrains[1].alloc();

    EDK3::Node* root = GameState.root.get();

    // Initialize Land
    strncpy(Terrains[0]->name, "Land", sizeof(Terrains[0]->name));
    Terrains[0]->num_cols = 256;
    Terrains[0]->num_rows = 256;
    Terrains[0]->height_mult = 5.0f;
    Terrains[0]->size = 1.0f;
    Terrains[0]->smoothness = 0.5f;
    Terrains[0]->heightmap_mult = 30.0f;
    strncpy(Terrains[0]->heightmap_path, "./textures/south.png", sizeof(Terrains[0]->heightmap_path));
    Terrains[0]->use_heightmap = true;
    Terrains[0]->is_centered = true;
    Terrains[0]->pos[0] = 0.0f;
    Terrains[0]->pos[1] = 0.0f;
    Terrains[0]->pos[2] = 0.0f;
    Terrains[0]->HPR[0] = 0.0f;
    Terrains[0]->HPR[1] = 0.0f;
    Terrains[0]->HPR[2] = 0.0f;
    Terrains[0]->mat = Materials.mat;
    Terrains[0]->mat_settings = Materials.matSettings;
    

    
    // Initialize Water
    strncpy(Terrains[1]->name, "Water", sizeof(Terrains[1]->name));
    Terrains[1]->num_cols = 64;
    Terrains[1]->num_rows = 64;
    Terrains[1]->height_mult = 1.0f;
    Terrains[1]->size = 100.0f;
    Terrains[1]->smoothness = 0.005f;
    Terrains[1]->heightmap_mult = 100.0f;
    strncpy(Terrains[1]->heightmap_path, "./textures/water_heightmap.png", sizeof(Terrains[1]->heightmap_path));
    Terrains[1]->use_heightmap = true;
    Terrains[1]->is_centered = true;
    Terrains[1]->pos[0] = 0.0f;
    Terrains[1]->pos[1] = 10.0f;
    Terrains[1]->pos[2] = 0.0f;
    Terrains[1]->HPR[0] = 0.0f;
    Terrains[1]->HPR[1] = 0.0f;
    Terrains[1]->HPR[2] = 0.0f;
    Terrains[1]->mat = Materials.mat_water;
    Terrains[1]->mat_settings = Materials.matSettings_water;
    



    // Give attributes and add to the root system
    for (int i = 0; i < num_terrains; ++i) {
        Terrains[i]->terrain.alloc();
        Terrains[i]->terrain->init(Terrains[i]->num_cols, Terrains[i]->num_rows, Terrains[i]->height_mult, Terrains[i]->size, Terrains[i]->smoothness, Terrains[i]->heightmap_mult, Terrains[i]->heightmap_path, Terrains[i]->use_heightmap);
        AddDrawable(root, Terrains[i]->terrain.get(), Terrains[i]->mat.get(), Terrains[i]->mat_settings.get(), Terrains[i]->pos, Terrains[i]->HPR, Terrains[i]->name);
    }
}

/*
void InitTerrain() {

    EDK3::Node* root = GameState.root.get();
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

  float pos[3] = { 0.0f, 100.0f, 0.0f };
  float HPR[3] = { 0.0f, 0.0f, 0.0f };
  AddDrawable(root, sphere.get(), Materials.mat.get(), Materials.matSettings.get(), pos, HPR, "sphere");
}

void InitQuad(EDK3::Node* root) {
    EDK3::ref_ptr<EDK3::QuadCustom> quad;
    quad.alloc();
    quad->init(10.0f);

    float pos[3] = { -50.0f, 100.0f, 0.0f };
    float HPR[3] = { 0.0f, 0.0f, 0.0f };
    AddDrawable(root, quad.get(), Materials.mat.get(), Materials.matSettings.get(), pos, HPR, "quad");
}

void InitCube24(EDK3::Node* root) {
    EDK3::ref_ptr<EDK3::CubeCustom> cube;
    cube.alloc();
    cube->init24v(10.0f);

    float pos[3] = { 50.0f, 100.0f, 0.0f };
    float HPR[3] = { 0.0f, 0.0f, 0.0f };
    AddDrawable(root, cube.get(), Materials.mat.get(), Materials.matSettings.get(), pos, HPR, "Cube24");

}

void InitCube8(EDK3::Node* root) {
    EDK3::ref_ptr<EDK3::CubeCustom> cube;
    cube.alloc();
    cube->init8v(10.0f);

    float pos[3] = { 100.0f, 100.0f, 0.0f };
    float HPR[3] = { 0.0f, 0.0f, 0.0f };
    AddDrawable(root, cube.get(), Materials.mat.get(), Materials.matSettings.get(), pos, HPR, "Cube8");
}

void InitSurface(EDK3::Node* root) {
    // no usar faltan los puntos de la figura

    Vec2 figure_points[kFigurePoints];
    EDK3::ref_ptr<EDK3::SurfaceCustom> Surface;
    Surface.alloc();
    Surface->init(figure_points, kFigurePoints, 10, 1.0f, 1.0f);


    float pos[3] = { -100.0f, 100.0f, 0.0f };
    float HPR[3] = { 0.0f, 0.0f, 0.0f };
    AddDrawable(root, Surface.get(), Materials.mat.get(), Materials.matSettings.get(), pos, HPR, "Surface");

}

void InitObj(EDK3::Node* root) {
    EDK3::LoadObj("./obj/SM_Building_03.obj", &customObjGeometry, nullptr);

    float pos[3] = { -200.0f, 100.0f, 0.0f };
    float HPR[3] = { 0.0f, 0.0f, 0.0f };
    AddDrawable(root, customObjGeometry[0].get(), Materials.mat.get(), Materials.matSettings.get(), pos, HPR, "Cube8");
}

void InitCamera() 
{
    //Allocating and initializing the camera:
    GameState.camera.alloc();

    float pos[] = { 0.0f, 80.0f, 100.0f };
    float view[] = { 0.0f, 0.0f, 0.0f };
    GameState.camera->set_position(pos);
    GameState.camera->initViewTarget(kWindowWidth, kWindowHeight);
    GameState.camera->setSensitibity(1.0f);
    //GameState.camera->set_view_direction(view);
    GameState.camera->setSpeed(5.0f);
    GameState.camera->setSpeedModifier(0.1f);
    GameState.camera->setupPerspective(70.0f, 8.0f / 6.0f, 1.0f, 1500.0f);

}

void InitScene() {
  //Allocating root node:
  EDK3::Node* root = GameState.root.alloc();
  
  InitCamera();

  InitTextures();
  InitMaterials();
  InitSceneLights();
  InitTerrain();
  InitSphere(root);
  InitQuad(root);
  InitCube24(root);
  InitCube8(root);
  //InitSurface(root); --> no usar
  //InitObj(root);
   



  
  EDK3::dev::GPUManager::CheckGLError("Prepare END");
}






void UpdateFn() {
  GameState.camera->set_clear_color(0.94f, 1.0f, 0.94f, 1.0f);
  GameState.camera->update(0.0f, GameState.camera->window_size().x, GameState.camera->window_size().y);
  
}

void RenderFn() {
  //For every frame... determine what's visible:
  GameState.camera->doCull(GameState.root.get());

  //Rendering the scene:
  EDK3::dev::GPUManager::CheckGLError("begin Render-->");
  GameState.camera->doRender();
  EDK3::dev::GPUManager::CheckGLError("end Render-->");
}

void ImGuiFn(double dt) {
  ImGui::Begin("FPS Window");
  ImGui::Text("FPS: %0.1f", 1000.0 / dt);
  ImGui::Text("Delta time: %0.3f ms", dt);
  ImGui::End();
  IMGUI.DrawImGuiTerrain();
  IMGUI.LightManager();
  ImGui::ShowTestWindow();
  ImGui::Render();
}

int ESAT::main(int argc, char** argv) {
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
