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



#include "material_custom.h"
#include "geometry_custom_terrain.h"
#include "geometry_custom_sphere.h"
#include "camera_custom.h"
#include "geometry_custom_quad.h"
#include "geometry_custom_cube.h"
#include "geometry_custom_surface.h"




//float EDK3::MaterialCustom::LightSettings::ambient_color_[3] = { 0.0f,0.0f,0.0f };

float EDK3::CustomLightMaterial::Settings::ambient_color_[3] = { 0.5f, 0.5f, 0.0f};

struct {
  EDK3::ref_ptr<EDK3::CustomLightMaterial> mat;
  EDK3::ref_ptr<EDK3::CustomLightMaterial::Settings> matSettings;
} Materials;

struct {
  EDK3::ref_ptr<EDK3::Texture> texture;
  EDK3::ref_ptr<EDK3::CustomGPUTexture> customTexture_;
} Textures;

//Unnamed struct and it's unique instance:
struct {
  EDK3::ref_ptr<EDK3::CameraCustom> camera;
  EDK3::ref_ptr<EDK3::Node> root;
  EDK3::ref_ptr<EDK3::MaterialCustom> mat;
  //EDK3::ref_ptr<EDK3::MaterialCustom::MaterialCustomTextureSettings> mat_settings;
  
} GameState;

const int kWindowWidth = 1024;
const int kWindowHeight = 768;
const int kFigurePoints = 10;
EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> customObjGeometry;


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


}

void InitSceneLights() {
  int lightType = 1;
  float pos[3]{ 0.0f,100.0f,0.0f };
  float dir[3]{ 0.0f,0.0f,0.0f };
  float diff_color[3]{ 1.0f,1.0f,1.0f };
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

    float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    Materials.matSettings->set_color(color);
    Materials.matSettings->set_texture(Textures.texture.get());

}
    

void InitTextures() {
    EDK3::Texture::Load("./textures/sand.png", &Textures.texture);
    if (!Textures.texture) {
        printf("Can't load texture.png\n");
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

void InitTerrain(EDK3::Node* root) {

    EDK3::ref_ptr<EDK3::TerrainCustom> custom_terrain;
    custom_terrain.alloc();
    custom_terrain->init(256, 256, 5.0f, 1.0f, 0.005f, 30.0f, "./textures/south.png", true);


    //Load texture

    /*
    EDK3::ref_ptr<EDK3::Texture> texture;
    EDK3::Texture::Load("./test/T_EDK_Logo.png", &texture);
    if (!texture) {
        printf("Can't load texture");
        exit(-2);
    }
    */

    float pos[3] = { 0.0f, 0.0f, 0.0f };
    float HPR[3] = { 0.0f, 0.0f, 0.0f };
    AddDrawable(root, custom_terrain.get(), Materials.mat.get(), Materials.matSettings.get(), pos, HPR, "terrain_land");
}


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

    /*
    EDK3::ref_ptr<EDK3::Drawable> drawable;
    drawable.alloc();
    drawable->set_geometry(Surface.get());
    drawable->set_material(GameState.mat.get());
    drawable->set_material_settings(GameState.mat_settings.get());
    drawable->set_position(-100.0f, 100.0f, 0.0f);
    drawable->set_HPR(0.0f, 0.0f, 0.0f);
    root->addChild(drawable.get());
    */
}

void InitObj(EDK3::Node* root) {
    EDK3::LoadObj("./obj/SM_Building_03.obj", &customObjGeometry, nullptr);

    float pos[3] = { -200.0f, 100.0f, 0.0f };
    float HPR[3] = { 0.0f, 0.0f, 0.0f };
    AddDrawable(root, customObjGeometry[0].get(), Materials.mat.get(), Materials.matSettings.get(), pos, HPR, "Cube8");

    /*
    EDK3::ref_ptr<EDK3::Drawable> drawable;
    drawable.alloc();
    drawable->set_geometry(customObjGeometry[0].get());
    drawable->set_material(GameState.mat.get());
    drawable->set_material_settings(GameState.mat_settings.get());
    drawable->set_position(-200.0f, 100.0f, 0.0f);
    drawable->set_HPR(0.0f, 0.0f, 0.0f);
    root->addChild(drawable.get());
    */
}

void InitScene() {
  //Allocating root node:
  EDK3::Node* root = GameState.root.alloc();
  
  //Allocating and initializing the camera:
  GameState.camera.alloc();

  InitTextures();
  InitMaterials();
  InitSceneLights();
  InitTerrain(root);
  InitSphere(root);
  InitQuad(root);
  InitCube24(root);
  InitCube8(root);
  //InitSurface(root); --> no usar
  //InitObj(root);
   


  float pos[] = { 0.0f, 80.0f, 100.0f };
  float view[] = { 0.0f, 0.0f, 0.0f };
  GameState.camera->set_position(pos);
  GameState.camera->initViewTarget(kWindowWidth, kWindowHeight);
  GameState.camera->setSensitibity(1.0f);
  //GameState.camera->set_view_direction(view);
  GameState.camera->setSpeed(0.05f);
  GameState.camera->setSpeedModifier(0.01f);
  GameState.camera->setupPerspective(70.0f, 8.0f / 6.0f, 1.0f, 1500.0f);
  
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
