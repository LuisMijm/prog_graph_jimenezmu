/**
 *
 * @brief Basic postprocess material source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */

#include "postprocess_basic.h"
#include <stdio.h>
#include "ESAT/time.h"
#include "EDK3/dev/gpumanager.h"
#include "ESAT/math.h"



namespace EDK3 {
  
  static const char kVertexShader[] =
    "#version 330\n"
    "uniform mat4 u_m_matrix;"
    "uniform mat4 u_vp_matrix;"

    "layout(location = 0) in vec3 a_position;"
    "layout(location = 1) in vec3 a_normal;"
    "layout(location = 2) in vec2 a_uv;"
    "out vec2 uv;"

    "void main() {"
    "    gl_Position = u_vp_matrix * u_m_matrix * vec4(a_position, 1.0);"
    "    uv = a_uv;"
    "}";

//#define GLSL(x) "#version 330\n"#x
//static const char* kFragmentShader = GLSL(
//  //The shader itself.
//);

static const char kFragmentShader[] =
"#version 330\n"
"uniform sampler2D u_texture;\n"
"uniform int u_use_texture;\n"
"uniform vec4 u_color;\n"
"out vec4 fragColor;\n"
"in vec2 uv;\n"
"void main() {\n"
"   if(0 == u_use_texture){"
"    fragColor = u_color;\n"
"   }else{\n"
"    fragColor = u_color * texture(u_texture,uv);\n"
"   }\n"
"}\n";


PostprocessBasic::PostprocessBasic() { }
PostprocessBasic::~PostprocessBasic() { }
PostprocessBasic::PostprocessBasic(const PostprocessBasic& other) {
  program_ = other.program_;
}
PostprocessBasic::PostprocessBasic(PostprocessBasic&& other) {
  program_ = other.program_;
  other.program_.release();
}
PostprocessBasic& PostprocessBasic::operator=(const PostprocessBasic& other) {
  program_ = other.program_;
  return *this;
}

void PostprocessBasic::init() {
  //TODO
  //1: Request at least two shaders and one program to the GPU Manager.
  EDK3::dev::GPUManager& GPU = *EDK3::dev::GPUManager::Instance();
  EDK3::ref_ptr<EDK3::dev::Shader> fragment_shader;
  GPU.newShader(&fragment_shader);
  EDK3::ref_ptr<EDK3::dev::Shader> vertex_vertex;
  GPU.newShader(&vertex_vertex);
  GPU.newProgram(&program_);


  //2: Load the source code to the requested shaders.
  vertex_vertex->loadSource(EDK3::dev::Shader::Type::kType_Vertex, kVertexShader, strlen(kVertexShader));
  fragment_shader->loadSource(EDK3::dev::Shader::Type::kType_Fragment, kFragmentShader, strlen(kFragmentShader));

  EDK3::scoped_array<char> error_log;
  //3: Compile both shaders.
  if (!vertex_vertex->compile(&error_log)) printf("VERTEX: %s\n", error_log.get());
  if (!fragment_shader->compile(&error_log)) printf("FRAGMENT: %s\n", error_log.get());


  //4: Attach shaders to the program.
  program_->attach(vertex_vertex.get());
  program_->attach(fragment_shader.get());
  //5: Finally... link the program!
  program_->link();
}

bool PostprocessBasic::enable(const EDK3::MaterialSettings *mat) const {
  program_->use();
  const PostprocessBasicSettings* ms = dynamic_cast<const PostprocessBasicSettings*>(mat);
  if (ms) {
    unsigned int color_loc = program_->get_uniform_position("u_color");
    program_->set_uniform_value(color_loc, Type::T_FLOAT_4, ms->color());
    
    unsigned int used_texture_loc = program_->get_uniform_position("u_use_texture");
    program_->set_uniform_value(used_texture_loc, Type::T_INT_1, &use_texture_);

    int slot = 0;
    ms->texture()->bind(slot);
    unsigned int texture_loc = program_->get_uniform_position("u_texture");
    program_->set_uniform_value(texture_loc, EDK3::Type::T_INT_1, &slot);
    return true;
    }
  return false;
  }


void PostprocessBasic::setupCamera(const float projection[16], const float view[16]) const {
  //TODO
  ESAT::Mat4 local_projection = ESAT::Mat4FromColumns(projection);
  ESAT::Mat4 local_view = ESAT::Mat4FromColumns(view);
  ESAT::Mat4 m = ESAT::Mat4Multiply(local_projection, local_view);
  program_->set_uniform_value(program_->get_uniform_position("u_vp_matrix"), EDK3::Type::T_MAT_4x4, m.d);

}

void PostprocessBasic::setupModel(const float model[16]) const {
  //TODO
  program_->set_uniform_value(program_->get_uniform_position("u_m_matrix"), EDK3::Type::T_MAT_4x4, model);

}
unsigned int PostprocessBasic::num_attributes_required() const {
  return 3;
}

void PostprocessBasic::set_use_texture(bool texture_active) {
  use_texture_ = texture_active;
}

int PostprocessBasic::use_texture() const {
  return use_texture_;
}

EDK3::Attribute PostprocessBasic::attribute_at_index(const unsigned int attrib_idx) const {
  //TODO
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

EDK3::Type PostprocessBasic::attribute_type_at_index(const unsigned int attrib_idx) const {
  //TODO
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
}


} //EDK3
