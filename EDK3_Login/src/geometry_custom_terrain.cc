/**
 *
 * @brief Custom quad source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */

#include "geometry_custom_terrain.h"

#include "ESAT/math.h"
#include "EDK3/dev/gpumanager.h"
#include "EDK3/dev/gpumanager.h"
#include "Perlin/SimplexNoise.h"
#include "math_helpers.h"
#include "math_library/vector_3.h"
#include "math_library/vector_2.h"
//#define STB_IMAGE_IMPLEMENTATION
#include "stbi_image.h"

namespace EDK3 {

//IMPORTANT!!!
//TODO constructors, destructor and =operator here!!!
    TerrainCustom::TerrainCustom(){}
    TerrainCustom::~TerrainCustom(){}

void TerrainCustom::init(const int num_cols, const int num_rows,
    const float height_mult, const float size,const float smoothness,
    const float heightmap_mult, const char* heightmap_path, const bool use_heightmap,
    const bool is_centered){
  //TODO demand graphic resources to the GPUManager.
  EDK3::dev::GPUManager& GPU = *EDK3::dev::GPUManager::Instance();
  GPU.newBuffer(&elements_buffer);
  GPU.newBuffer(&order_buffer);

  struct MeshVtx {
      Vec3 pos;
      Vec3 normal;
      Vec2 uv;

      //ESAT::Vec3 pos;
      //ESAT::Vec3 normal;
      //ESAT::Vec2 uv;
  };
              
  EDK3::scoped_array<MeshVtx> mesh_elements;
  EDK3::scoped_array<unsigned int> mesh_order;

  mesh_elements.alloc((num_cols + 1)* (num_rows + 1));
  mesh_order.alloc(num_cols * num_rows * 6);

  //Create vertexes values

  //float terrain_size = size / 2.0f;
  //float delta_x = size / (float)num_cols;
  //float delta_y = size / (float)num_rows;
  Vec3 up_vector;
  Vec3 right_vector;
  Vec3 left_vector;
  Vec3 bottom_vector;

  Vec3 cross_right_up;
  Vec3 cross_up_left;
  Vec3 cross_left_bottom;
  Vec3 cross_bottom_right;

  unsigned char* data;
  int heightmap_width, heightmap_height, heightmap_nChannels;
  
  if (use_heightmap) {
      //Load heightmap file
      data = stbi_load(heightmap_path,
          &heightmap_width, &heightmap_height, &heightmap_nChannels,
          0);
  }

  printf("Elements\n");
  MeshVtx* mesh_elements_pointer = mesh_elements.get();
  for (int i = 0; i < (num_rows+1); i++) {
    for (int j = 0; j < (num_cols+1); j++){
        float texel_value = GetTexelValue(data, heightmap_nChannels, heightmap_width, heightmap_height, j, i, num_cols, num_rows);
        if (texel_value > 1.0f) texel_value = 1.0f;
        if (is_centered) {
            mesh_elements_pointer[j + i * (num_cols + 1)].pos = Vec3(size * j - ((size * num_cols) / 2),
                                                                     texel_value * heightmap_mult +  SimplexNoise::noise(size * j * smoothness ,size * i * smoothness) * height_mult,
                                                                     size * i - ((size * num_rows) / 2));
        }
        else {
            mesh_elements_pointer[j + i * (num_cols + 1)].pos =  Vec3(size * j , 
                                                                      SimplexNoise::noise(size * j * smoothness ,size * i * smoothness) * height_mult,
                                                                      size * i);
        }
     
      mesh_elements_pointer[j + i * (num_cols+1)].uv = Vec2((float)j,(float)i);
      /*printf("%f %f %f \n ", mesh_elements_pointer[j + i * (num_cols + 1)].pos.x,
        mesh_elements_pointer[j + i * (num_cols + 1)].pos.y,
        mesh_elements_pointer[j + i * (num_cols + 1)].pos.z);*/
    }
  }
  printf("\n");

  for (int i = 0; i < (num_rows + 1); i++) {
      for (int j = 0; j < (num_cols + 1); j++) {
          // Calculate normals


      //check up neighbour
          if (i < num_rows - 1) {
              up_vector =  Vec3(mesh_elements_pointer[j + (i + 1) * (num_cols + 1)].pos.x - mesh_elements_pointer[j + i * (num_cols + 1)].pos.x,
                                mesh_elements_pointer[j + (i + 1) * (num_cols + 1)].pos.y - mesh_elements_pointer[j + i * (num_cols + 1)].pos.y,
                                mesh_elements_pointer[j + (i + 1) * (num_cols + 1)].pos.z - mesh_elements_pointer[j + i * (num_cols + 1)].pos.z);
          }
          else {
              up_vector =  Vec3(0.0f,0.0f, 0.0f);
          }
          //if down available
          if (i != 0) {
              bottom_vector = Vec3(mesh_elements_pointer[j + (i - 1) * (num_cols + 1)].pos.x - mesh_elements_pointer[j + i * (num_cols + 1)].pos.x,
                                   mesh_elements_pointer[j + (i - 1) * (num_cols + 1)].pos.y - mesh_elements_pointer[j + i * (num_cols + 1)].pos.y,
                                   mesh_elements_pointer[j + (i - 1) * (num_cols + 1)].pos.z - mesh_elements_pointer[j + i * (num_cols + 1)].pos.z);
          }
          else {
              bottom_vector = Vec3(0.0f, 0.0f, 0.0f);
          }
          //if right available
          if (j < num_cols - 1) {
              right_vector = Vec3(mesh_elements_pointer[j+1 + i * (num_cols + 1)].pos.x - mesh_elements_pointer[j + i * (num_cols + 1)].pos.x,
                                  mesh_elements_pointer[j+1 + i * (num_cols + 1)].pos.y - mesh_elements_pointer[j + i * (num_cols + 1)].pos.y,
                                  mesh_elements_pointer[j+1 + i * (num_cols + 1)].pos.z - mesh_elements_pointer[j + i * (num_cols + 1)].pos.z);
          }
          else {
              right_vector = Vec3(0.0f, 0.0f, 0.0f);
          }

          if (j != 0) {
              left_vector = Vec3(mesh_elements_pointer[j-1  + i * (num_cols + 1)].pos.x - mesh_elements_pointer[j + i * (num_cols + 1)].pos.x,
                                 mesh_elements_pointer[j-1  + i * (num_cols + 1)].pos.y - mesh_elements_pointer[j + i * (num_cols + 1)].pos.y,
                                 mesh_elements_pointer[j-1  + i * (num_cols + 1)].pos.z - mesh_elements_pointer[j + i * (num_cols + 1)].pos.z);
          }
          else {
              left_vector = Vec3(0.0f, 0.0f, 0.0f);
          }

          up_vector.Normalize();
          bottom_vector.Normalize();
          right_vector.Normalize();
          left_vector.Normalize();

          cross_right_up = Vec3::CrossProduct(right_vector, up_vector);
          cross_up_left = Vec3::CrossProduct(up_vector, left_vector);
          cross_left_bottom = Vec3::CrossProduct(left_vector, bottom_vector);
          cross_bottom_right = Vec3::CrossProduct(bottom_vector, right_vector);

          Vec3 cross_sum =  Vec3(cross_right_up.x + cross_up_left.x + cross_left_bottom.x + cross_bottom_right.x,
                                 cross_right_up.y + cross_up_left.y + cross_left_bottom.y + cross_bottom_right.y,
                                 cross_right_up.z + cross_up_left.z + cross_left_bottom.z + cross_bottom_right.z);


          // mesh_elements_pointer[j + i * (num_cols+1)].normal = { 0.0f , 1.0f, 0.0f};
          mesh_elements_pointer[j + i * (num_cols + 1)].normal = cross_sum.Normalized();
          mesh_elements_pointer[j + i * (num_cols + 1)].normal.x *= -1.0f;
          mesh_elements_pointer[j + i * (num_cols + 1)].normal.y *= -1.0f;
          mesh_elements_pointer[j + i * (num_cols + 1)].normal.z *= -1.0f;

          //printf("Normal %f %f %f \n ", mesh_elements_pointer[j + i * (num_cols + 1)].normal.x,
          //    mesh_elements_pointer[j + i * (num_cols + 1)].normal.y,
          //    mesh_elements_pointer[j + i * (num_cols + 1)].normal.z);
      }
  }

  // Z is inverted in EDK3, why?
  // Vertex order
  unsigned int* order_elements_pointer = mesh_order.get();
  for (int i = 0; i < num_rows ; i++) {
    for(int j = 0; j < num_cols; j++) {
      order_elements_pointer[(i * 6 * num_cols) + (j * 6)]     = ((num_cols + 1) * i) + j + 1;
      order_elements_pointer[(i * 6 * num_cols) + (j * 6) + 1] = ((num_cols + 1) * i) + j;
      order_elements_pointer[(i * 6 * num_cols) + (j * 6) + 2] = ((num_cols + 1) * i) + j + num_cols + 1;
      order_elements_pointer[(i * 6 * num_cols) + (j * 6) + 3] = ((num_cols + 1) * i) + j + num_cols + 1;
      order_elements_pointer[(i * 6 * num_cols) + (j * 6) + 4] = ((num_cols + 1) * i) + j + num_cols + 2;
      order_elements_pointer[(i * 6 * num_cols) + (j * 6) + 5] = ((num_cols + 1) * i) + j + 1;
    }
  }


  //****** Upload data:
  //TODO initialize and upload data to the "elements_buffer".
  //Size in bytes: 12 data per element * 1 faces * 4 vertices per face * sizeof(float)
  //48 attributes has a face.
  elements_buffer->init(mesh_elements.sizeInBytes());
  elements_buffer->uploadData(mesh_elements.get(), mesh_elements.sizeInBytes(),0);


  //****** Upload order:
  //TODO initialize and upload data to the "order_buffer".
  //Remember to order triangles in counter clockwise direction!!
  //6 vertices per face * 1 faces * sizeof(short int)

  order_buffer->init(mesh_order.sizeInBytes());
  order_buffer->uploadData(mesh_order.get(), mesh_order.sizeInBytes(),0);
}

bool TerrainCustom::bindAttribute(const Attribute a,
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

void TerrainCustom::render() const {
  //TODO
    EDK3::dev::GPUManager::Instance()->drawElements
    (EDK3::dev::GPUManager::DrawMode::kDrawMode_Triangles, order_buffer->size(), order_buffer.get(), EDK3::Type::T_UINT, 0);
}

} //EDK3
