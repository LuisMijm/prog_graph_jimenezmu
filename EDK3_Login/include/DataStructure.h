#pragma once

#include "EDK3/geometry.h"


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

/*
struct {
	// Sand
	EDK3::ref_ptr<EDK3::CustomLightMaterial> mat;
	EDK3::ref_ptr<EDK3::CustomLightMaterial::Settings> matSettings;

	// Water
	EDK3::ref_ptr<EDK3::CustomLightMaterial> mat_water;
	EDK3::ref_ptr<EDK3::CustomLightMaterial::Settings> matSettings_water;
} Materials;
*/

struct Material {
    EDK3::ref_ptr<EDK3::CustomLightMaterial> mat;
    EDK3::ref_ptr<EDK3::CustomLightMaterial::Settings> matSettings;
};

enum MaterialName {

};

/*
struct {
	EDK3::ref_ptr<EDK3::Texture> texture;
	EDK3::ref_ptr<EDK3::CustomGPUTexture> customTexture_;


	EDK3::ref_ptr<EDK3::Texture> texture_water;
} Textures;
*/

enum TextureName {

};

//Unnamed struct and it's unique instance:
struct {
	EDK3::ref_ptr<EDK3::CameraCustom> camera;
	EDK3::ref_ptr<EDK3::Node> root;
	EDK3::ref_ptr<EDK3::MaterialCustom> mat;
	//EDK3::ref_ptr<EDK3::MaterialCustom::MaterialCustomTextureSettings> mat_settings;

	//EDK3::scoped_array<Material> 
} GameState;


struct Terrain
{
    EDK3::ref_ptr<EDK3::TerrainCustom> terrain;
    int num_cols;
    int num_rows;
    float height_mult;
    float size;
    float smoothness;
    float heightmap_mult;
    char heightmap_path[256];
    bool use_heightmap;
    bool is_centered;
    float pos[3];
    float HPR[3];
    EDK3::ref_ptr<EDK3::CustomLightMaterial> mat;
    EDK3::ref_ptr<EDK3::CustomLightMaterial::Settings> mat_settings;
    char name[256];

};


float EDK3::CustomLightMaterial::Settings::ambient_color_[3] = { 1.0f, 1.0f, 1.0f };
//const int kWindowWidth = 1024;
const int kWindowWidth = 2048;
//const int kWindowHeight = 768;
const int kWindowHeight = 1536;
const int kFigurePoints = 10;
EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> customObjGeometry;
EDK3::scoped_ptr<Terrain> Terrains[2];
const int num_terrains = 2;
EDK3::scoped_array<EDK3::ref_ptr<EDK3::CustomGPUTexture>> Textures[10];
EDK3::scoped_array<EDK3::ref_ptr<Material>> Materials[10];
