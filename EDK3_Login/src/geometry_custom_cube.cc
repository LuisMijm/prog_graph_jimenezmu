/**
 *
 * @brief Custom quad source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */

#include "geometry_custom_cube.h"
#include "ESAT/math.h"
#include "EDK3/dev/gpumanager.h"
#include "EDK3/dev/gpumanager.h"

namespace EDK3 {

    //IMPORTANT!!!
    //TODO constructors, destructor and =operator here!!!
    CubeCustom::CubeCustom() {}
    CubeCustom::~CubeCustom() {}

    void CubeCustom::init8v(const float cube_size) {
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
              1           0
          That's the order of its face.
         */

         //****** Positions:
        float size = cube_size * 0.5f;

        ESAT::Vec3 pos[8] = {
                               cube_size, -cube_size,  cube_size,
                              -cube_size, -cube_size,  cube_size,
                              -cube_size,  cube_size,  cube_size,
                               cube_size,  cube_size,  cube_size,
                               cube_size, -cube_size, -cube_size,
                              -cube_size, -cube_size, -cube_size,
                              -cube_size,  cube_size, -cube_size,
                               cube_size,  cube_size, -cube_size };

        //****** Normals:
        ESAT::Vec3 normal[8] = {
              0.57f, -0.57f, 0.57f,
              -0.57f, -0.57f,  0.57f ,
              -0.57f,  0.57f,  0.57f ,
              0.57f ,  0.57f,  0.57f ,
              0.57f , -0.57f, -0.57f ,
              -0.57f, -0.57f, -0.57f ,
              -0.57f,  0.57f, -0.57f ,
              0.57f ,  0.57f, -0.57f };

        //****** UVs:
        ESAT::Vec2 uv[8] = { 1.0f, 0.0f,
                             0.0f, 0.0f,
                             0.0f, 1.0f,
                             1.0f, 1.0f,

                             1.0f, 0.0f,
                             0.0f, 0.0f,
                             0.0f, 1.0f,
                             1.0f, 1.0f };


        struct MeshVtx {
            ESAT::Vec3 pos;
            ESAT::Vec3 normal;
            ESAT::Vec2 uv;
        };

        MeshVtx mesh[8];
        mesh[0] = { pos[0], normal[0], uv[0] };
        mesh[1] = { pos[1], normal[1], uv[1] };
        mesh[2] = { pos[2], normal[2], uv[2] };
        mesh[3] = { pos[3], normal[3], uv[3] };
        mesh[4] = { pos[4], normal[4], uv[4] };
        mesh[5] = { pos[5], normal[5], uv[5] };
        mesh[6] = { pos[6], normal[6], uv[6] };
        mesh[7] = { pos[7], normal[7], uv[7] };

        /*unsigned int order[6]{

        }*/
        //****** Colors:
        //TODO


        //****** Upload data:
        //TODO initialize and upload data to the "elements_buffer".
        //Size in bytes: 12 data per element * 1 faces * 4 vertices per face * sizeof(float)
        //48 attributes has a face.
        elements_buffer->init(sizeof(mesh));
        elements_buffer->uploadData(mesh, sizeof(mesh), 0);


        //****** Upload order:
        //TODO initialize and upload data to the "order_buffer".
        //Remember to order triangles in counter clockwise direction!!
        //6 vertices per face * 1 faces * sizeof(short int)
        unsigned int order[]{
            1,0,3,
            1,3,2,

            0,1,5,
            5,4,0,

            6,7,4,
            4,5,6,

            2,3,7,
            7,6,2,

            6,5,1,
            1,2,6,

            3,0,4,
            4,7,3
        };
        order_buffer->init(sizeof(order));
        order_buffer->uploadData(order, sizeof(order), 0);
    }

    void CubeCustom::init24v(const float cube_size) {
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
              1           0
          That's the order of its face.
         */

         //****** Positions:
        float size = cube_size * 0.5f;

        ESAT::Vec3 pos[24] = {
            +cube_size, +cube_size, +cube_size, // 0
            +cube_size, -cube_size, +cube_size, // 1
            -cube_size, -cube_size, +cube_size, // 2
            -cube_size, +cube_size, +cube_size, // 3

            +cube_size, +cube_size, -cube_size, // 4
            +cube_size, -cube_size, -cube_size, // 5
            -cube_size, -cube_size, -cube_size, // 6
            -cube_size, +cube_size, -cube_size, // 7

            +cube_size, +cube_size, +cube_size, // 8  (0)
            +cube_size, -cube_size, +cube_size, // 9  (1)
            +cube_size, -cube_size, -cube_size, // 10 (5)
            +cube_size, +cube_size, -cube_size, // 11 (4)

            -cube_size, -cube_size, +cube_size, // 12 (2)
            -cube_size, +cube_size, +cube_size, // 13 (3)
            -cube_size, +cube_size, -cube_size, // 14 (7)
            -cube_size, -cube_size, -cube_size, // 15 (6)

            +cube_size, +cube_size, +cube_size, // 16 (0)
            -cube_size, +cube_size, +cube_size, // 17 (3)
            -cube_size, +cube_size, -cube_size, // 18 (7)
            +cube_size, +cube_size, -cube_size, // 19 (4)

            +cube_size, -cube_size, +cube_size, // 20 (1)
            -cube_size, -cube_size, +cube_size, // 21 (2)
            -cube_size, -cube_size, -cube_size, // 22 (6)
            +cube_size, -cube_size, -cube_size // 23 (5)
        };

        //****** Normals:
        ESAT::Vec3 normal[24] = {
            +0.0f, +0.0f, +1.0f, // 0
            +0.0f, +0.0f, +1.0f, // 1
            +0.0f, +0.0f, +1.0f, // 2
            +0.0f, +0.0f, +1.0f, // 3

            +0.0f, +0.0f, -1.0f, // 4
            +0.0f, +0.0f, -1.0f, // 5
            +0.0f, +0.0f, -1.0f, // 6
            +0.0f, +0.0f, -1.0f, // 7

            +1.0f, +0.0f, +0.0f, // 8  (0)
            +1.0f, +0.0f, +0.0f, // 9  (1)
            +1.0f, +0.0f, +0.0f, // 10 (5)
            +1.0f, +0.0f, +0.0f, // 11 (4)

            -1.0f, +0.0f, +0.0f, // 12 (2)
            -1.0f, +0.0f, +0.0f, // 13 (3)
            -1.0f, +0.0f, +0.0f, // 14 (7)
            -1.0f, +0.0f, +0.0f, // 15 (6)

            +0.0f, +1.0f, +0.0f, // 16 (0)
            +0.0f, +1.0f, +0.0f, // 17 (3)
            +0.0f, +1.0f, +0.0f, // 18 (7)
            +0.0f, +1.0f, +0.0f, // 19 (4)

            +0.0f, -1.0f, +0.0f, // 20 (1)
            +0.0f, -1.0f, +0.0f, // 21 (2)
            +0.0f, -1.0f, +0.0f, // 22 (6)
            +0.0f, -1.0f, +0.0f // 23 (5)
        };

        //****** UVs:
        ESAT::Vec2 uv[24] = {
                             1.0f, 1.0f,
                             1.0f, 0.0f,
                             0.0f, 0.0f,
                             0.0f, 1.0f,

                             1.0f, 1.0f,
                             1.0f, 0.0f,
                             0.0f, 0.0f,
                             0.0f, 1.0f,
                             
                             1.0f, 1.0f,
                             1.0f, 0.0f,
                             0.0f, 0.0f,
                             0.0f, 1.0f, 
        
                             0.0f, 0.0f,
                             0.0f, 1.0f,
                             1.0f, 1.0f,
                             1.0f, 0.0f,
        
                             1.0f, 1.0f,
                             1.0f, 0.0f,
                             0.0f, 0.0f,
                             0.0f, 1.0f, 

                             1.0f, 0.0f,
                             1.0f, 1.0f,
                             0.0f, 1.0f, 
                             0.0f, 0.0f,
        };


        struct MeshVtx {
            ESAT::Vec3 pos;
            ESAT::Vec3 normal;
            ESAT::Vec2 uv;
        };

        MeshVtx mesh[24];
        for (int i = 0; i < 24; i++) {
            mesh[i] = { pos[i], normal[i], uv[i] };
        }

        /*unsigned int order[6]{

        }*/
        //****** Colors:
        //TODO


        //****** Upload data:
        //TODO initialize and upload data to the "elements_buffer".
        //Size in bytes: 12 data per element * 1 faces * 4 vertices per face * sizeof(float)
        //48 attributes has a face.
        elements_buffer->init(sizeof(mesh));
        elements_buffer->uploadData(mesh, sizeof(mesh), 0);


        //****** Upload order:
        //TODO initialize and upload data to the "order_buffer".
        //Remember to order triangles in counter clockwise direction!!
        //6 vertices per face * 1 faces * sizeof(short int)
        unsigned int order[]{
            2, 1, 0, 0, 3, 2,
            4, 5, 6, 6, 7, 4,
            10, 11, 9, 11, 8, 9,
            15, 12, 14, 12, 13, 14,
            16, 19, 18, 18, 17, 16,
            23, 20, 21, 21, 22, 23,
        };
        order_buffer->init(sizeof(order));
        order_buffer->uploadData(order, sizeof(order), 0);
    }

    bool CubeCustom::bindAttribute(const Attribute a,
        unsigned int where_to_bind_attribute) const {
        //TODO
        //EDK3::dev::GPUManager::Instance()->enableVertexAttribute
        switch (a) {
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

    void CubeCustom::render() const {
        //TODO
        EDK3::dev::GPUManager::Instance()->drawElements
        (EDK3::dev::GPUManager::DrawMode::kDrawMode_Triangles, order_buffer->size(), order_buffer.get(), EDK3::Type::T_UINT, 0);
    }

} //EDK3