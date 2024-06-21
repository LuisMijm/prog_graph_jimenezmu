#pragma once

#ifndef _DATASTRUCTURE_H__
#define _DATASTRUCTURE_H__ 1

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
#include "EDK3/node.h"
#include <postprocess_basic.h>

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

/*
struct {
	EDK3::ref_ptr<EDK3::Texture> texture;
	EDK3::ref_ptr<EDK3::CustomGPUTexture> customTexture_;


	EDK3::ref_ptr<EDK3::Texture> texture_water;
} Textures;
*/



struct Material {
    EDK3::ref_ptr<EDK3::CustomLightMaterial> mat;
    EDK3::ref_ptr<EDK3::CustomLightMaterial::Settings> matSettings;
};

enum MaterialName {
    sand,
    water,
    volcano,
};

//enum class TextureName {
//    sand,
//    water,
//};

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

//#define GS GameState
//Unnamed struct and it's unique instance:
struct GameState {
	EDK3::ref_ptr<EDK3::CameraCustom> camera;
    EDK3::ref_ptr<EDK3::Node> root;
    EDK3::ref_ptr<EDK3::Node> transparents;

    EDK3::scoped_array<EDK3::ref_ptr<EDK3::Texture>> Textures;
    EDK3::scoped_array<Material> Materials;
    EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> customObjGeometry;
    EDK3::scoped_array<Terrain> Terrains;
    
    EDK3::ref_ptr<EDK3::RenderTarget> render_target;
    EDK3::ref_ptr<EDK3::PostprocessBasic> mat_postprocess;
    EDK3::ref_ptr<EDK3::PostprocessBasic::PostprocessBasicSettings> mat_postprocess_settings;

    EDK3::ref_ptr<EDK3::TransparentMaterial> mat_transparent;
    EDK3::ref_ptr<EDK3::TransparentMaterial::Settings> mat_transparent_settings;

    int Postprocess = 0;
    bool wireframe;
} GS;




const int kWindowWidth = 2048;
const int kWindowHeight = 1536;
//const int kWindowWidth = 1024;
//const int kWindowHeight = 768;
const int kFigurePoints = 10;

const int num_terrains = 2;
float EDK3::CustomLightMaterial::Settings::ambient_color_[3] = { 0.3f,0.3f,0.3f };


#endif