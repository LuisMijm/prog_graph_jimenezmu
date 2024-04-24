/**
 *
 * @brief Custom quad source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */

#include "geometry_custom_sphere.h"
#include "ESAT/math.h"
#include "EDK3/dev/gpumanager.h"
#include "EDK3/dev/gpumanager.h"
#include "math_helpers.h"

namespace EDK3 {

//IMPORTANT!!!
//TODO constructors, destructor and =operator here!!!
SphereCustom::SphereCustom(){}
SphereCustom::~SphereCustom(){}

void SphereCustom::init(const float sphere_size, const int num_heights,
    const int num_revs) {
  //TODO demand graphic resources to the GPUManager.
  EDK3::dev::GPUManager& GPU = *EDK3::dev::GPUManager::Instance();
  GPU.newBuffer(&elements_buffer);
  GPU.newBuffer(&order_buffer);
  
  num_heights_ = num_heights;
  num_revs_ = num_revs;

  struct MeshVtx {
      ESAT::Vec3 pos;
      ESAT::Vec3 normal;
      ESAT::Vec2 uv;
  };

  EDK3::scoped_array<MeshVtx> mesh_elements;
  EDK3::scoped_array<unsigned int> mesh_order;

  mesh_elements.alloc((num_heights_ + 1) * (num_revs_ + 1));
  mesh_order.alloc(num_heights_ * num_revs_ * 6);

  MeshVtx* mesh_elements_pointer = mesh_elements.get();

  float alpha = 3.14f / num_heights_;
  float omega = 6.28f / num_revs_;

  for (int i=0; i <= num_heights_; i++) {
      for (int j = 0; j <= num_revs_; j++) {
          if (j == num_revs_) {
              mesh_elements_pointer[j + i * (num_revs_ + 1)].pos = {
                cosf(0) * cosf(i * alpha - 1.57f) * sphere_size,
                sinf(alpha * i - 1.57f) * sphere_size,
                sinf(0) * cosf(i * alpha - 1.57f) * sphere_size
              };
          }
          else {
              mesh_elements_pointer[j + i * (num_revs_ + 1)].pos = {
                  cosf(omega * j) * cosf(i * alpha - 1.57f) * sphere_size,
                  sinf(alpha * i - 1.57f) * sphere_size,
                  sinf(omega * j) * cosf(i * alpha - 1.57f) * sphere_size
              };
          }
            //mesh_elements_pointer[j + i * (num_revs_ + 1)].uv = { (float)j,(float)i };
          mesh_elements_pointer[j + i * (num_revs_ + 1)].uv = { (-1.0f*j)/num_revs_,(1.0f*i)/num_heights_ };
          mesh_elements_pointer[j + i * (num_revs_ + 1)].normal =
            Vec3Normalize(mesh_elements_pointer[j + i * (num_revs_ + 1)].pos);
          
      }
  }

  unsigned int* order_elements_pointer = mesh_order.get();
  for (int i = 0; i < num_heights_; i++) {
      for (int j = 0; j < num_revs_; j++) {
          order_elements_pointer[(i * 6 * num_revs_) + (j * 6)] = ((num_revs_ + 1) * i) + j + 1;
          order_elements_pointer[(i * 6 * num_revs_) + (j * 6) + 1] = ((num_revs_ + 1) * i) + j;
          order_elements_pointer[(i * 6 * num_revs_) + (j * 6) + 2] = ((num_revs_ + 1) * i) + j + num_revs_ + 1;
          order_elements_pointer[(i * 6 * num_revs_) + (j * 6) + 3] = ((num_revs_ + 1) * i) + j + num_revs_ + 1;
          order_elements_pointer[(i * 6 * num_revs_) + (j * 6) + 4] = ((num_revs_ + 1) * i) + j + num_revs_ + 2;
          order_elements_pointer[(i * 6 * num_revs_) + (j * 6) + 5] = ((num_revs_ + 1) * i) + j + 1;
      }
  }

  //****** Upload data:
  //TODO initialize and upload data to the "elements_buffer".
  //Size in bytes: 12 data per element * 1 faces * 4 vertices per face * sizeof(float)
  //48 attributes has a face.
  elements_buffer->init(mesh_elements.sizeInBytes());
  elements_buffer->uploadData(mesh_elements.get(), mesh_elements.sizeInBytes(), 0);


  //****** Upload order:
  //TODO initialize and upload data to the "order_buffer".
  //Remember to order triangles in counter clockwise direction!!
  //6 vertices per face * 1 faces * sizeof(short int)
  order_buffer->init(mesh_order.sizeInBytes());
  order_buffer->uploadData(mesh_order.get(), mesh_order.sizeInBytes(), 0);
}

bool SphereCustom::bindAttribute(const Attribute a,
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

void SphereCustom::render() const {
  //TODO
    EDK3::dev::GPUManager::Instance()->drawElements
    (EDK3::dev::GPUManager::DrawMode::kDrawMode_Triangles, order_buffer->size(), order_buffer.get(), EDK3::Type::T_UINT, 0);
}

} //EDK3
