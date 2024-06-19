/**
 *
 * @brief Basic material source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#include "material_custom.h"

#include "EDK3/dev/gpumanager.h"
#include "EDK3/dev/shader.h"

//#include "DataStructure.h"

namespace EDK3 {

  CustomLightMaterial::CustomLightMaterial() {}

  //void CustomLightMaterial::init(EDK3::scoped_array<char>& error_log, const char* vertex_path, const char* fragment_path, int useTexture)
  void CustomLightMaterial::init(EDK3::scoped_array<char>& error_log, const char* vertex_path, const char* fragment_path, int useTexture)
  {
    //1: Request at least two shaders and one program to the GPU Manager.
    EDK3::dev::GPUManager& GPU = *EDK3::dev::GPUManager::Instance();
    EDK3::ref_ptr<EDK3::dev::Shader> fragment_shader;
    GPU.newShader(&fragment_shader);
    EDK3::ref_ptr<EDK3::dev::Shader> vertex_vertex;
    GPU.newShader(&vertex_vertex);
    GPU.newProgram(&program_);


    //2: Load the source code to the requested shaders.
    if (!loadVertexShaderFile(&vertex_vertex, vertex_path)) printf("Error loading vertex shader path: %s\n", vertex_path);
    if (!loadFragmentShaderFile(&fragment_shader, fragment_path)) printf("Error loading fragment shader path: %s\n", fragment_path);
    // bool loadFragmentShaderFile(ref_ptr<dev::Shader> *output, const char* file_path);

  //3: Compile both shaders.
    if (!vertex_vertex->compile(&error_log)) printf("VERTEX: %s\n", error_log.get());
    if (!fragment_shader->compile(&error_log)) printf("FRAGMENT: %s\n", error_log.get());


    //4: Attach shaders to the program.
    program_->attach(vertex_vertex.get());
    program_->attach(fragment_shader.get());
    //5: Finally... link the program!
    program_->link();

    useTexture_ = useTexture;
  }

  CustomLightMaterial::CustomLightMaterial(const CustomLightMaterial&){
    
  }

  bool CustomLightMaterial::enable(const EDK3::MaterialSettings* mat) const
  {
    const Settings* settings = dynamic_cast<const Settings*>(mat);
    if (settings) {
      program_->use();
      int num_lights = 3;
      char aux_name[60] = { '\0' };
      int loc;

      unsigned int color_loc = program_->get_uniform_position("u_color");
      program_->set_uniform_value(color_loc, Type::T_FLOAT_4, settings->color());

      int slot = 0;
      settings->texture()->bind(slot); //settings->texture(0)->bind(slot);
      unsigned int texture_loc = program_->get_uniform_position("u_texture");
      program_->set_uniform_value(texture_loc, EDK3::Type::T_INT_1, &slot);

      for (int i = 0; i < num_lights; i++) {
        //Position
        sprintf(aux_name, "u_lights[%d].pos\0", i);
        loc = program_->get_uniform_position(aux_name);
        if (loc != -1) {
          program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_3, settings->lightConf_[i].pos_);
        }
        else {
          printf("Error uniform %s\n", aux_name);
        }

        //Direction
        sprintf(aux_name, "u_lights[%d].dir\0", i);
        loc = program_->get_uniform_position(aux_name);
        if (loc != -1) {
          program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_3, settings->lightConf_[i].dir_);
        }
        else {
          printf("Error uniform %s\n", aux_name);
        }

        //Diffuse color
        sprintf(aux_name, "u_lights[%d].diff_color\0", i);
        loc = program_->get_uniform_position(aux_name);
        if (loc != -1) {
          program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_3, settings->lightConf_[i].diff_color_);
        }
        else {
          printf("Error uniform %s\n", aux_name);
        }

        //Specular color
        sprintf(aux_name, "u_lights[%d].spec_color\0", i);
        loc = program_->get_uniform_position(aux_name);
        if (loc != -1) {
          program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_3, settings->lightConf_[i].spec_color_);
        }
        else {
          printf("Error uniform %s\n", aux_name);
        }

        //Linear attenuation
        sprintf(aux_name, "u_lights[%d].linear_att\0", i);
        loc = program_->get_uniform_position(aux_name);
        if (loc != -1) {
          program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_1, &settings->lightConf_[i].linear_att_);
        }
        else {
          printf("Error uniform %s\n", aux_name);
        }

        //Quadratic attenuation
        sprintf(aux_name, "u_lights[%d].quad_att\0", i);
        loc = program_->get_uniform_position(aux_name);
        if (loc != -1) {
          program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_1, &settings->lightConf_[i].quadratic_att_);
        }
        else {
          printf("Error uniform %s\n", aux_name);
        }

        //Constant attenuation
        sprintf(aux_name, "u_lights[%d].constant_att\0", i);
        loc = program_->get_uniform_position(aux_name);
        if (loc != -1) {
          program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_1, &settings->lightConf_[i].constant_att_);
        }
        else {
          printf("Error uniform %s\n", aux_name);
        }

        //Shininess attenuation
        sprintf(aux_name, "u_lights[%d].shininess\0", i);
        loc = program_->get_uniform_position(aux_name);
        if (loc != -1) {
          program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_1, &settings->lightConf_[i].shininess_);
        }
        else {
          printf("Error uniform %s\n", aux_name);
        }

        //Strength 
        sprintf(aux_name, "u_lights[%d].strength\0", i);
        loc = program_->get_uniform_position(aux_name);
        if (loc != -1) {
          program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_1, &settings->lightConf_[i].strength_);
        }
        else {
          printf("Error uniform %s\n", aux_name);
        }

        //Enabled
        sprintf(aux_name, "u_lights[%d].enabled\0", i);
        loc = program_->get_uniform_position(aux_name);
        if (loc != -1) {
            program_->set_uniform_value(loc, EDK3::Type::T_INT_1, &settings->lightConf_[i].enabled_);
        }
        else {
            printf("Error uniform %s\n", aux_name);
        }


        //Type
        sprintf(aux_name, "u_lights[%d].type\0", i);
        loc = program_->get_uniform_position(aux_name);
        if (loc != -1) {
            program_->set_uniform_value(loc, EDK3::Type::T_INT_1, &settings->lightConf_[i].type_);
        }
        else {
            printf("Error uniform %s\n", aux_name);
        }


        sprintf(aux_name, "u_lights[%d].cutOff\0", i);
        loc = program_->get_uniform_position(aux_name);
        if (loc != -1) {
            program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_1, &settings->lightConf_[i].cutOff_);
        }
        else {
            printf("Error uniform %s\n", aux_name);
        }

        sprintf(aux_name, "u_lights[%d].outerCutOff\0", i);
        loc = program_->get_uniform_position(aux_name);
        if (loc != -1) {
            program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_1, &settings->lightConf_[i].outerCutOff_);
        }
        else {
            printf("Error uniform %s\n", aux_name);
        }


        //Camera position
        //sprintf(aux_name, "u_lights[%d].camera_pos\0", i);
        //loc = program_->get_uniform_position(aux_name);
        //if (loc != -1) {
        //  program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_3, settings->lightConf_[i].camera_pos_);
        //}
        //else {
        //  printf("Error uniform %s\n", aux_name);
        //}
      }

      //Number lights
      sprintf(aux_name, "u_number_lights\0");
      loc = program_->get_uniform_position(aux_name);
      if (loc != -1) {
        program_->set_uniform_value(loc, EDK3::Type::T_INT, &num_lights);
      }
      else {
        printf("Error uniform %s\n", aux_name);
      }

      //Ambient color
      sprintf(aux_name, "u_ambient\0");
      loc = program_->get_uniform_position(aux_name);
      if (loc != -1) {
        program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_3, settings->ambient_color_);
      }
      else {
        printf("Error uniform %s\n", aux_name);
      }

      //PostProcess
  /*    sprintf(aux_name, "u_postprocess\0");
      loc = program_->get_uniform_position(aux_name);
      if (loc != -1) {
          program_->set_uniform_value(loc, EDK3::Type::T_INT, &GS.Postprocess );
      }
      else {
          printf("Error uniform %s\n", aux_name);
      }*/

      /*
      slot = 1;
      settings->normal()->bind(slot);
      texture_loc = program_->get_uniform_position("u_normal");
      program_->set_uniform_value(texture_loc, EDK3::Type::T_INT_1, &slot);

      */
      int use_texture = useTexture_;
      unsigned int used_texture_loc = program_->get_uniform_position("u_use_texture");
      program_->set_uniform_value(used_texture_loc, Type::T_INT_1, &use_texture);
      return true;
    }
    else {
      return false;
    }
  }

  void CustomLightMaterial::setupCamera(const float projection[16], const float view[16]) const
  {
    ESAT::Mat4 local_projection = ESAT::Mat4FromColumns(projection);
    ESAT::Mat4 local_view = ESAT::Mat4FromColumns(view);
    ESAT::Mat4 m = ESAT::Mat4Multiply(local_projection, local_view);
    program_->set_uniform_value(program_->get_uniform_position("u_vp_matrix"), EDK3::Type::T_MAT_4x4, m.d);
  }

  void CustomLightMaterial::setupModel(const float model[16]) const
  {
    program_->set_uniform_value(program_->get_uniform_position("u_m_matrix"), EDK3::Type::T_MAT_4x4, model);
  }

  unsigned int CustomLightMaterial::num_attributes_required() const
  {

    return 3;
  }

  EDK3::Attribute CustomLightMaterial::attribute_at_index(const unsigned int attrib_idx) const
  {
    switch (attrib_idx) {
    case 0:
      return EDK3::Attribute::A_POSITION;
      break;
    case 1:
      return EDK3::Attribute::A_NORMAL;
      break;
    case 2:
      return EDK3::Attribute::A_UV;
      break;
    default:
      return EDK3::Attribute::A_NONE;
      break;
    }
  }

  EDK3::Type CustomLightMaterial::attribute_type_at_index(const unsigned int attrib_index) const
  {
    switch (attrib_index) {
    case 0:
      return EDK3::Type::T_FLOAT_3;
      break;
    case 1:
      return EDK3::Type::T_FLOAT_3;
      break;
    case 2:
      return EDK3::Type::T_FLOAT_2;
      break;
    default:
      return EDK3::Type::T_NONE;
      break;
    }
  }



/*
MaterialCustom::MaterialCustom() {}
MaterialCustom::~MaterialCustom() {}
MaterialCustom::MaterialCustom(const MaterialCustom& mat) {}

MaterialCustom& MaterialCustom::operator=(const MaterialCustom& mat) {
    return *this;
}
//IMPORTANT!!!
//Type the constructors, destructor and operator= here, just in this point!!!
//If you don't do it, it won't compile!!!

void MaterialCustom::init(EDK3::scoped_array<char> &error_log, 
                          const char* vertex_path,
                          const char* fragment_path){
  //1: Request at least two shaders and one program to the GPU Manager.
    EDK3::dev::GPUManager& GPU = *EDK3::dev::GPUManager::Instance();
    EDK3::ref_ptr<EDK3::dev::Shader> fragment_shader;
    GPU.newShader(&fragment_shader);
    EDK3::ref_ptr<EDK3::dev::Shader> vertex_vertex;
    GPU.newShader(&vertex_vertex);
    GPU.newProgram(&program_);
    

  //2: Load the source code to the requested shaders.
  if(!loadVertexShaderFile(&vertex_vertex, vertex_path)) printf("Error loading vertex shader path: %s\n", vertex_path);
  if(!loadFragmentShaderFile(&fragment_shader, fragment_path)) printf("Error loading fragment shader path: %s\n", fragment_path);
	// bool loadFragmentShaderFile(ref_ptr<dev::Shader> *output, const char* file_path);

  //3: Compile both shaders.
    if(!vertex_vertex->compile(&error_log)) printf("VERTEX: %s\n", error_log.get());
    if(!fragment_shader->compile(&error_log)) printf("FRAGMENT: %s\n", error_log.get());


  //4: Attach shaders to the program.
    program_->attach(vertex_vertex.get());
    program_->attach(fragment_shader.get());
  //5: Finally... link the program!
    program_->link();
}

bool MaterialCustom::enable(const EDK3::MaterialSettings *mat) const {
  //Enable the material...
  //... and use the uniforms located in the material settings!
    const MaterialCustomSettings* ms = dynamic_cast<const MaterialCustomSettings*>(mat);
    if (ms){
        program_->use();
        unsigned int color_loc = program_->get_uniform_position("u_color");
        program_->set_uniform_value(color_loc, Type::T_FLOAT_4, ms->color());

        int use_texture = 1;
        unsigned int used_texture_loc = program_->get_uniform_position("u_use_texture");
        program_->set_uniform_value(used_texture_loc, Type::T_INT_1, &use_texture);
        return true;
    }
    const MaterialCustomTextureSettings* ms2 = dynamic_cast<const MaterialCustomTextureSettings*>(mat);
    if (ms2) {
      program_->use();

      unsigned int color_loc = program_->get_uniform_position("u_color");
      program_->set_uniform_value(color_loc, Type::T_FLOAT_4, ms2->color());

      int slot = 0;
      ms2->texture(0)->bind(slot);
      unsigned int albedo_loc = program_->get_uniform_position("u_albedo_1");
      program_->set_uniform_value(albedo_loc, EDK3::Type::T_INT_1, &slot);

      slot = 1;
      ms2->texture(1)->bind(slot);
      albedo_loc = program_->get_uniform_position("u_albedo_2");
      program_->set_uniform_value(albedo_loc, EDK3::Type::T_INT_1, &slot);

      int use_texture = 0;
      unsigned int used_texture_loc = program_->get_uniform_position("u_use_texture");
      program_->set_uniform_value(used_texture_loc, Type::T_INT_1, &use_texture);
      return true;
    }
    const LightSettings* light_set = dynamic_cast<const LightSettings*>(mat);
    if(light_set){
      program_->use();
      int lights_counter;
      char name[60] = {'\0'};
      int loc;
      for(int i=0; i < 8; i++){
        if(light_set->light_confs_[i].enabled_){
          lights_counter++;
          
          //Position
          sprintf(name, "u_lights[%d].pos\0");
          loc = program_->get_uniform_position(name);
          if(loc != -1){
            program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_3, light_set->light_confs_[i].pos_);
          }else{
            printf("Error uniform %s\n", name);
          }

          //Direction
          sprintf(name, "u_lights[%d].dir\0");
          loc = program_->get_uniform_position(name);
          if (loc != -1) {
              program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_3, light_set->light_confs_[i].dir_);
          }
          else {
              printf("Error uniform %s\n", name);
          }

          //Diffuse color
          sprintf(name, "u_lights[%d].diff_color\0");
          loc = program_->get_uniform_position(name);
          if (loc != -1) {
              program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_3, light_set->light_confs_[i].diff_color_);
          }
          else {
              printf("Error uniform %s\n", name);
          }

          //Specular color
          sprintf(name, "u_lights[%d].spec_color\0");
          loc = program_->get_uniform_position(name);
          if (loc != -1) {
              program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_3, light_set->light_confs_[i].spec_color_);
          }
          else {
              printf("Error uniform %s\n", name);
          }
          
          //Linear attenuation
          sprintf(name, "u_lights[%d].linear_att\0");
          loc = program_->get_uniform_position(name);
          if (loc != -1) {
              program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_1, &light_set->light_confs_[i].linear_att_);
          }
          else {
              printf("Error uniform %s\n", name);
          }

          //Quadratic attenuation
          sprintf(name, "u_lights[%d].quad_att\0");
          loc = program_->get_uniform_position(name);
          if (loc != -1) {
              program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_1, &light_set->light_confs_[i].quadratic_att_);
          }
          else {
              printf("Error uniform %s\n", name);
          }

          //Constant attenuation
          sprintf(name, "u_lights[%d].constant_att\0");
          loc = program_->get_uniform_position(name);
          if (loc != -1) {
              program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_1, &light_set->light_confs_[i].constant_att_);
          }
          else {
              printf("Error uniform %s\n", name);
          }

          //Shininess attenuation
          sprintf(name, "u_lights[%d].shininess\0");
          loc = program_->get_uniform_position(name);
          if (loc != -1) {
              program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_1, &light_set->light_confs_[i].shininess_);
          }
          else {
              printf("Error uniform %s\n", name);
          }

          //Strength 
          sprintf(name, "u_lights[%d].strength\0");
          loc = program_->get_uniform_position(name);
          if (loc != -1) {
              program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_1, &light_set->light_confs_[i].strength_);
          }
          else {
              printf("Error uniform %s\n", name);
          }

          //Camera position
          sprintf(name, "u_lights[%d].camera_pos\0");
          loc = program_->get_uniform_position(name);
          if (loc != -1) {
              program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_3, light_set->light_confs_[i].camera_pos_);
          }
          else {
              printf("Error uniform %s\n", name);
          }
          
        }
      }
      
      //Number lights
      sprintf(name, "u_number_lights\0");
      loc = program_->get_uniform_position(name);
      if (loc != -1) {
          program_->set_uniform_value(loc, EDK3::Type::T_INT, &lights_counter);
      }
      else {
          printf("Error uniform %s\n", name);
      }

      //Ambient color
      sprintf(name, "u_ambient\0");
      loc = program_->get_uniform_position(name);
      if (loc != -1) {
          program_->set_uniform_value(loc, EDK3::Type::T_FLOAT_3, light_set->ambient_color_);
      }
      else {
          printf("Error uniform %s\n", name);
      }

      int slot = 0;
      light_set->texture()->bind(slot);
      unsigned int albedo_loc = program_->get_uniform_position("u_texture");
      if (loc != -1) {
        program_->set_uniform_value(albedo_loc, EDK3::Type::T_INT_1, &slot);
      }
      else {
        printf("Error uniform %s\n", name);
      }
      return true;
    }
    return false;
}

void MaterialCustom::setupCamera(const float projection[16],
                                const float view[16]) const {
  //Set the projection and view matrices as uniforms here!
    ESAT::Mat4 local_projection = ESAT::Mat4FromColumns(projection);
    ESAT::Mat4 local_view = ESAT::Mat4FromColumns(view);
    ESAT::Mat4 m = ESAT::Mat4Multiply(local_projection, local_view);
    program_->set_uniform_value(program_->get_uniform_position("u_vp_matrix"), EDK3::Type::T_MAT_4x4, m.d);

}

void MaterialCustom::setupModel(const float model[16]) const {
  //Set the model matrix as uniform here!
    program_->set_uniform_value(program_->get_uniform_position("u_m_matrix"), EDK3::Type::T_MAT_4x4, model);
}

unsigned int MaterialCustom::num_attributes_required() const {
  //Depending on how attributes the geometry has.
    return 3;
}

EDK3::Attribute MaterialCustom::attribute_at_index(const unsigned int attrib_idx) const {
  //Search on "EDK3::Attribute" enum.
  //Depending on how attributes are stored in the geometry buffer.
  //unsigned int id = program_->get_attrib_location(attrib_idx);
  switch (attrib_idx){
    case 0:
        return EDK3::Attribute::A_POSITION;
        break;
    case 1:
        return EDK3::Attribute::A_NORMAL;
        break;
    case 2:
        return EDK3::Attribute::A_UV;
        break;
    default:
        return EDK3::Attribute::A_NONE;
        break;
  }
}

EDK3::Type MaterialCustom::attribute_type_at_index(const unsigned int attrib_idx) const {
  //Search on "EDK3::Type" enum.
  //Depending on how attributes are stored in the geometry buffer.
    //unsigned int id = program_->get_attrib_location(attrib_idx);
    switch (attrib_idx) {
    case 0:
        return EDK3::Type::T_FLOAT_3;
        break;
    case 1:
        return EDK3::Type::T_FLOAT_3;
        break;
    case 2:
        return EDK3::Type::T_FLOAT_2;
        break;
    default:
        return EDK3::Type::T_NONE;
        break;
    }
}*/






} //EDK3
