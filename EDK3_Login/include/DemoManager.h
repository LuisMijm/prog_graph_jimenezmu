#pragma once

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
#include "DataStructures.h"



class DemoManager
{
public:
	static void InitScene(EDK3::ref_ptr<EDK3::Node> root);

	static GameState GameState;

	void LoadTextures();
	void LoadMaterials();
	void SetAndAddDrawable(EDK3::Node* root, EDK3::Geometry* geo, EDK3::Material* mat, EDK3::MaterialSettings* settings, GLfloat position[3], GLfloat HPR[3], const char* name);
	void InitTerrain(EDK3::Node* root);
	void InitSphere(EDK3::Node* root);
	void InitQuad(EDK3::Node* root);
	void InitCube24(EDK3::Node* root);
	void InitCube8(EDK3::Node* root);
	void InitObj(EDK3::Node* root);

};

