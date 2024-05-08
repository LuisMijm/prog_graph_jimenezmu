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

#include "material_custom.h"
#include "geometry_custom_terrain.h"
#include "geometry_custom_sphere.h"
#include "camera_custom.h"
#include "geometry_custom_quad.h"
#include "geometry_custom_cube.h"
#include "geometry_custom_surface.h"




float EDK3::MaterialCustom::LightSettings::ambient_color_[3] = { 0.0f,0.0f,0.0f };

//Unnamed struct and it's unique instance:
struct {
  EDK3::ref_ptr<EDK3::CameraCustom> camera;
  EDK3::ref_ptr<EDK3::Node> root;
  EDK3::ref_ptr<EDK3::MaterialCustom> mat;
  EDK3::ref_ptr<EDK3::MaterialCustom::MaterialCustomTextureSettings> mat_settings;
  EDK3::ref_ptr<EDK3::Texture> texture;

} GameState;

const int kWindowWidth = 1024;
const int kWindowHeight = 768;
const int kFigurePoints = 10;
EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> customObjGeometry;

void InitMaterials() {
    EDK3::scoped_array<char> error_log;
    GameState.mat.alloc();
    GameState.mat_settings.alloc();

    GameState.mat->init(error_log, "./shaders/basicVertex.vs", "./shaders/basicFragment.fs");
    GameState.mat_settings.alloc();
    float color[] = { 0.5f, 0.5f, 0.25f, 1.0f };
    GameState.mat_settings->set_color(color);
}

void InitTextures() {
    EDK3::Texture::Load("./test/T_EDK_Logo.png", &GameState.texture);
    if (!GameState.texture) {
        printf("Can't load texture.png\n");
        exit(-2);
    }
}


void InitTerrain(EDK3::Node* root) {

    EDK3::ref_ptr<EDK3::TerrainCustom> custom_terrain;
    custom_terrain.alloc();
    custom_terrain->init(256, 256, 5.0f, 1.0f, 0.005f, 30.0f, "./textures/south.png", true);


    //Load texture

    
    EDK3::ref_ptr<EDK3::Texture> texture;
    EDK3::Texture::Load("./test/T_EDK_Logo.png", &texture);
    if (!texture) {
        printf("Can't load texture");
        exit(-2);
    }


    EDK3::ref_ptr<EDK3::Drawable> drawable;
    drawable.alloc();
    drawable->set_geometry(custom_terrain.get());
    drawable->set_material(GameState.mat.get());
    drawable->set_material_settings(GameState.mat_settings.get());
    drawable->set_position(0.0f, 0.0f, 0.0f);
    drawable->set_HPR(0.0f, 0.0f, 0.0f);
    drawable->set_name("Terrain");
    root->addChild(drawable.get());
}


void InitSphere(EDK3::Node* root) {
  EDK3::ref_ptr<EDK3::SphereCustom> sphere;
  sphere.alloc();
  sphere->init(10.0f);

  EDK3::ref_ptr<EDK3::Drawable> drawable;
  drawable.alloc();
  drawable->set_geometry(sphere.get());
  drawable->set_material(GameState.mat.get());
  drawable->set_material_settings(GameState.mat_settings.get());
  drawable->set_position(0.0f, 100.0f, 0.0f);
  drawable->set_HPR(0.0f, 0.0f, 0.0f);
  drawable->set_name("Sphere");
  root->addChild(drawable.get());
}

void InitQuad(EDK3::Node* root) {
    EDK3::ref_ptr<EDK3::QuadCustom> quad;
    quad.alloc();
    quad->init(10.0f);

    EDK3::ref_ptr<EDK3::Drawable> drawable;
    drawable.alloc();
    drawable->set_geometry(quad.get());
    drawable->set_material(GameState.mat.get());
    drawable->set_material_settings(GameState.mat_settings.get());
    drawable->set_position(-50.0f, 100.0f, 0.0f);
    drawable->set_HPR(0.0f, 0.0f, 0.0f);
    drawable->set_name("Quad");
    root->addChild(drawable.get());
}

void InitCube24(EDK3::Node* root) {
    EDK3::ref_ptr<EDK3::CubeCustom> cube;
    cube.alloc();
    cube->init24v(10.0f);

    EDK3::ref_ptr<EDK3::Drawable> drawable;
    drawable.alloc();
    drawable->set_geometry(cube.get());
    drawable->set_material(GameState.mat.get());
    drawable->set_material_settings(GameState.mat_settings.get());
    drawable->set_position(50.0f, 100.0f, 0.0f);
    drawable->set_HPR(0.0f, 0.0f, 0.0f);
    drawable->set_name("Cube24");
    root->addChild(drawable.get());
}

void InitCube8(EDK3::Node* root) {
    EDK3::ref_ptr<EDK3::CubeCustom> cube;
    cube.alloc();
    cube->init8v(10.0f);

    EDK3::ref_ptr<EDK3::Drawable> drawable;
    drawable.alloc();
    drawable->set_geometry(cube.get());
    drawable->set_material(GameState.mat.get());
    drawable->set_material_settings(GameState.mat_settings.get());
    drawable->set_position(100.0f, 100.0f, 0.0f);
    drawable->set_HPR(0.0f, 0.0f, 0.0f);
    drawable->set_name("Cube8");
    root->addChild(drawable.get());
}

void InitSurface(EDK3::Node* root) {
    // no usar faltan los puntos de la figura

    Vec2 figure_points[kFigurePoints];
    EDK3::ref_ptr<EDK3::SurfaceCustom> Surface;
    Surface.alloc();
    Surface->init(figure_points, kFigurePoints, 10, 1.0f, 1.0f);

    EDK3::ref_ptr<EDK3::Drawable> drawable;
    drawable.alloc();
    drawable->set_geometry(Surface.get());
    drawable->set_material(GameState.mat.get());
    drawable->set_material_settings(GameState.mat_settings.get());
    drawable->set_position(-100.0f, 100.0f, 0.0f);
    drawable->set_HPR(0.0f, 0.0f, 0.0f);
    root->addChild(drawable.get());
}

void InitObj(EDK3::Node* root) {
    EDK3::LoadObj("./obj/Couch/couch.obj", &customObjGeometry, nullptr);

    EDK3::ref_ptr<EDK3::Drawable> drawable;
    drawable.alloc();
    drawable->set_geometry(customObjGeometry[0].get());
    drawable->set_material(GameState.mat.get());
    drawable->set_material_settings(GameState.mat_settings.get());
    drawable->set_position(-200.0f, 100.0f, 0.0f);
    drawable->set_HPR(0.0f, 0.0f, 0.0f);
    root->addChild(drawable.get());
}

void InitScene() {
  //Allocating root node:
  EDK3::Node* root = GameState.root.alloc();
  
  InitMaterials();
  InitTerrain(root);
  InitSphere(root);
  InitQuad(root);
  InitCube24(root);
  InitCube8(root);
  //InitSurface(root); --> no usar
  //InitTextures();
  //InitObj(root);
   

  //Allocating and initializing the camera:
  GameState.camera.alloc();
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
