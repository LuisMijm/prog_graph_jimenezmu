
#include "DemoManager.h"

#include "EDK3/geometry.h"
#include "EDK3/camera.h"
#include "EDK3/drawable.h"
#include "EDK3/matdiffusetexture.h"
#include "EDK3/texture.h"
#include "EDK3/dev/gpumanager.h"



enum TextureIndex {
    sand,
    water,
    building,
    none,
};

struct {
    int texture_index;

    EDK3::ref_ptr<EDK3::Texture> texture;
    EDK3::ref_ptr<EDK3::Texture> texture_obj_albedo;
    EDK3::ref_ptr<EDK3::Texture> texture_obj_specular;
    EDK3::ref_ptr<EDK3::Texture> texture_obj_normals;

} Textures;

struct {
    EDK3::ref_ptr<EDK3::MaterialCustom> mat;
    //EDK3::ref_ptr<EDK3::MaterialCustom::MaterialCustomTextureSettings> mat_settings;
    EDK3::ref_ptr<EDK3::MaterialCustom::MaterialCustomSettings> mat_settings;

    EDK3::ref_ptr<EDK3::MaterialCustom> mat_obj;
    EDK3::ref_ptr<EDK3::MaterialCustom::MaterialCustomTextureSettings> mat_settings_obj;
} Materials;

void DemoManager::LoadTextures()
{
    EDK3::Texture::Load("./textures/sand.png", &Textures.texture);
    if (!Textures.texture) {
        printf("Can't load texture.png\n");
        exit(-2);
    }
    else
    {
        printf("init texture loaded\n");
    }

    EDK3::Texture::Load("./textures/T_building_03_Dif.png", &Textures.texture_obj_albedo);
}

void DemoManager::LoadMaterials(GameState gamestate)
{
    EDK3::scoped_array<char> error_log;
    GameState.mat.alloc();
    GameState.mat_settings.alloc();

    GameState.mat->init(error_log, "./shaders/basicVertex.vs", "./shaders/basicFragment.fs");
    GameState.mat_settings.alloc();
    //float color[] = { 0.5f, 0.5f, 0.25f, 1.0f };
    float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    GameState.mat_settings->set_color(color);
    GameState.mat->set_useTexture(0);

    GameState.mat_obj.alloc();
    GameState.mat_settings_obj.alloc();

    GameState.mat_obj->init(error_log, "./shaders/basicVertex.vs", "./shaders/basicFragment.fs");
    GameState.mat_settings_obj.alloc();

    GameState.mat_settings_obj->set_color(color);
    GameState.mat_obj->set_useTexture(1);
    GameState.mat_settings_obj->set_albedo_texture(Textures.texture_obj_albedo.get());
    //GameState.mat_settings_obj->set_specular_texture(GameState.texture_obj_specular);
    //GameState.mat_settings_obj->set_normals_texture(GameState.texture_obj_normals);
}







////////////////////////////////////////////

void DemoManager::SetAndAddDrawable(EDK3::Node* root, EDK3::Geometry* geo, EDK3::Material* mat, EDK3::MaterialSettings* settings, GLfloat position[3], GLfloat HPR[3], const char* name) {
    EDK3::ref_ptr<EDK3::Drawable> drawable;
    drawable.alloc();

    drawable->set_geometry(geo);
    drawable->set_material(mat);
    drawable->set_material_settings(settings);
    drawable->set_position(position[0], position[1], position[2]);
    drawable->set_HPR(HPR[0], HPR[1], HPR[2]);
    drawable->set_name(name);


    root->addChild(drawable.get());

}

void DemoManager::InitTerrain(EDK3::Node* root) {

    EDK3::ref_ptr<EDK3::TerrainCustom> custom_terrain;
    custom_terrain.alloc();
    custom_terrain->init(256, 256, 5.0f, 1.0f, 0.005f, 30.0f, "./textures/south.png", true);


    //Load texture

    /*
    EDK3::Texture::Load("./test/T_EDK_Logo.png", &GameState.texture);
    if (!GameState.texture) {
        printf("Can't load texture");
        exit(-2);
    }
    else {
        printf("terrain texture loaded");
    }
    */


    GLfloat position[3]{ 0.0f, 0.0f, 0.0f };
    GLfloat HPR[3]{ 0.0f, 0.0f, 0.0f };

    SetAndAddDrawable(root, custom_terrain.get(), GameState.mat.get(), GameState.mat_settings.get(), position, HPR, "Terrain");

}


void DemoManager::InitSphere(EDK3::Node* root) {
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

void DemoManager::InitQuad(EDK3::Node* root) {
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

void DemoManager::InitCube24(EDK3::Node* root) {
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

void DemoManager::InitCube8(EDK3::Node* root) {
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

void DemoManager::InitSurface(EDK3::Node* root) {
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

void DemoManager::InitObj(EDK3::Node* root) {
    //EDK3::LoadObj("./obj/SM_Building_00.obj", &customObjGeometry, nullptr);
    EDK3::LoadObj("./obj/SM_Building_03.obj", &customObjGeometry, nullptr);

    EDK3::ref_ptr<EDK3::Drawable> drawable;
    drawable.alloc();
    drawable->set_geometry(customObjGeometry[0].get());
    drawable->set_material(GameState.mat_obj.get());
    drawable->set_material_settings(GameState.mat_settings_obj.get());
    drawable->set_position(-200.0f, 100.0f, 0.0f);
    drawable->set_HPR(0.0f, 0.0f, 0.0f);
    root->addChild(drawable.get());
}

void DemoManager::InitScene(EDK3::ref_ptr<EDK3::Node> root) {
    //Allocating root node:
    EDK3::Node* root = root.alloc();

    DM_.LoadTextures();
    DM_.LoadMaterials();
    InitTerrain(root);
    InitSphere(root);
    InitQuad(root);
    InitCube24(root);
    InitCube8(root);
    //InitSurface(root); --> no usar
    InitObj(root);


    //Allocating and initializing the camera:
    GameState.camera.alloc();
    float pos[] = { 0.0f, 80.0f, 100.0f };
    float view[] = { 0.0f, 0.0f, 0.0f };
    GameState.camera->set_position(pos);
    GameState.camera->initViewTarget(kWindowWidth, kWindowHeight);
    GameState.camera->setSensitibity(1.0f);
    //GameState.camera->set_view_direction(view);
    GameState.camera->setSpeed(0.05f);
    GameState.camera->setSpeedModifier(0.1f);
    GameState.camera->setupPerspective(70.0f, 8.0f / 6.0f, 1.0f, 1500.0f);

    EDK3::dev::GPUManager::CheckGLError("Prepare END");
}