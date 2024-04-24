/**
 *
 * @brief Custom quad source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */

#include "geometry_custom_quad.h"
#include "ESAT/math.h"
#include "EDK3/dev/gpumanager.h"
#include "EDK3/dev/gpumanager.h"

namespace EDK3 {

//IMPORTANT!!!
//TODO constructors, destructor and =operator here!!!
QuadCustom::QuadCustom(){}
QuadCustom::~QuadCustom(){}

void QuadCustom::init(const float quad_size) {
  //TODO demand graphic resources to the GPUManager.
  EDK3::dev::GPUManager& GPU = *EDK3::dev::GPUManager::Instance();
  GPU.newBuffer(&elements_buffer);
  GPU.newBuffer(&order_buffer);
  /**
   The quad face is like this:
         3          2
         ------------
         |\        |
         | \       |
         |  \      |
         |   \     |
         |    \    |
         |     \   |
         |      \  |
         |       \ |
         |        \|
         ------------
        0           1
    That's the order of its face.
   */

  //****** Positions:
  float size = quad_size * 0.5f;
  ESAT::Vec3 pos[4] = {-size, -size, 0.0f,
                        size, -size, 0.0f,
                        size,  size, 0.0f,
                       -size,  size, 0.0f};

  //****** Normals:
  ESAT::Vec3 normal[4] = { 0.0f, 0.0f, 1.0f,
                           0.0f, 0.0f, 1.0f,
                           0.0f, 0.0f, 1.0f,
                           0.0f, 0.0f, 1.0f };

  //****** UVs:
  ESAT::Vec2 uv[4] = { 0.0f, 0.0f,
                       1.0f, 0.0f,
                       1.0f, 1.0f,
                       0.0f, 1.0f };


  struct MeshVtx {
      ESAT::Vec3 pos;
      ESAT::Vec3 normal;
      ESAT::Vec2 uv;
  };

  MeshVtx mesh[4];
  mesh[0] = { pos[0], normal[0], uv[0] };
  mesh[1] = { pos[1], normal[1], uv[1] };
  mesh[2] = { pos[2], normal[2], uv[2] };
  mesh[3] = { pos[3], normal[3], uv[3] };

  /*unsigned int order[6]{

  }*/
  //****** Colors:
  //TODO


  //****** Upload data:
  //TODO initialize and upload data to the "elements_buffer".
  //Size in bytes: 12 data per element * 1 faces * 4 vertices per face * sizeof(float)
  //48 attributes has a face.
  elements_buffer->init(sizeof(mesh));
  elements_buffer->uploadData(mesh, sizeof(mesh),0);


  //****** Upload order:
  //TODO initialize and upload data to the "order_buffer".
  //Remember to order triangles in counter clockwise direction!!
  //6 vertices per face * 1 faces * sizeof(short int)
  unsigned int order[6]{
      0,1,3,
      1,2,3
  };
  order_buffer->init(sizeof(order));
  order_buffer->uploadData(order, sizeof(order),0);
}

bool QuadCustom::bindAttribute(const Attribute a,
                               unsigned int where_to_bind_attribute) const {
  //TODO
  //EDK3::dev::GPUManager::Instance()->enableVertexAttribute
  switch (a){
    case Attribute::A_POSITION:
        EDK3::dev::GPUManager::Instance()->enableVertexAttribute(elements_buffer.get(),
            0, EDK3::T_FLOAT_3, false, 0, 8 * sizeof(float));
        break;
    case Attribute::A_NORMAL:
        EDK3::dev::GPUManager::Instance()->enableVertexAttribute(elements_buffer.get(),
            1, EDK3::T_FLOAT_3, false, 3 * sizeof(float), 8 * sizeof(float));
        break;
    case Attribute::A_UV:
        EDK3::dev::GPUManager::Instance()->enableVertexAttribute(elements_buffer.get(),
            2, EDK3::T_FLOAT_2, false, 6 * sizeof(float), 8 * sizeof(float));
        break;
    default:
        break;
  }
  return true;
}

void QuadCustom::render() const {
  //TODO
    EDK3::dev::GPUManager::Instance()->drawElements
    (EDK3::dev::GPUManager::DrawMode::kDrawMode_Triangles, 6, order_buffer.get(), EDK3::Type::T_UINT, 0);
}

} //EDK3
