/**
 *
 * @brief Basic material source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#include "material_basic.h"
#include "EDK3/dev/gpumanager.h"

namespace EDK3 {

static const char kExampleVertexShader1[] =
  "#version 330\n"
  "uniform...";

static const char kVertexShader[] =
"#version 330\n"
"uniform mat4 u_m_matrix;"
"uniform mat4 u_vp_matrix;"
"uniform float u_time;"

"layout(location = 0) in vec3 a_position;"
"layout(location = 1) in vec3 a_normal;"
"layout(location = 2) in vec2 a_uv;"
"out vec2 uv;"

"void main() {"
"    gl_Position = u_vp_matrix * u_m_matrix * vec4(a_position, 1.0);"
"    uv = a_uv;"
"}";

static const char kFragmentShader[] =
"#version 330\n"
"uniform sampler2D u_texture;\n"
"uniform sampler2D u_albedo_1;\n"
"uniform sampler2D u_albedo_2;\n"
"uniform int u_use_texture;\n"
"uniform vec4 u_color;\n"
"out vec4 fragColor;\n"
"in vec2 uv;\n"
"void main() {\n"
"   if(0 == u_use_texture){"
"    fragColor = u_color;\n"
"   }else{\n"
"    fragColor = u_color * texture(u_albedo_2,uv);\n"
"   }\n"
"}\n";



#define GLSL(x) "#version 330\n"#x
static const char* kExampleVertexShader2 = GLSL(
  //The shader itself.
);


MaterialBasic::MaterialBasic() {}
MaterialBasic::~MaterialBasic() {}
MaterialBasic::MaterialBasic(const MaterialBasic& mat) {}

MaterialBasic& MaterialBasic::operator=(const MaterialBasic& mat) {
    return *this;
}
//IMPORTANT!!!
//Type the constructors, destructor and operator= here, just in this point!!!
//If you don't do it, it won't compile!!!

void MaterialBasic::init(EDK3::scoped_array<char> &error_log){
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


  //3: Compile both shaders.
    if(!vertex_vertex->compile(&error_log)) printf("VERTEX: %s\n", error_log.get());
    if(!fragment_shader->compile(&error_log)) printf("FRAGMENT: %s\n", error_log.get());


  //4: Attach shaders to the program.
    program_->attach(vertex_vertex.get());
    program_->attach(fragment_shader.get());
  //5: Finally... link the program!
    program_->link();
}

bool MaterialBasic::enable(const EDK3::MaterialSettings *mat) const {
  //Enable the material...
  //... and use the uniforms located in the material settings!
    const MaterialBasicSettings* ms = dynamic_cast<const MaterialBasicSettings*>(mat);
    if (ms){
        program_->use();
        unsigned int color_loc = program_->get_uniform_position("u_color");
        program_->set_uniform_value(color_loc, Type::T_FLOAT_4, ms->color());

        int use_texture = 0;
        unsigned int used_texture_loc = program_->get_uniform_position("u_use_texture");
        program_->set_uniform_value(used_texture_loc, Type::T_INT_1, &use_texture);
        return true;
    }
    else {
        const MaterialBasicTextureSettings* ms2 = dynamic_cast<const MaterialBasicTextureSettings*>(mat);
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

            int use_texture = 1;
            unsigned int used_texture_loc = program_->get_uniform_position("u_use_texture");
            program_->set_uniform_value(used_texture_loc, Type::T_INT_1, &use_texture);
            return true;
        }
    }
    return false;
}

void MaterialBasic::setupCamera(const float projection[16],
                                const float view[16]) const {
  //Set the projection and view matrices as uniforms here!
    ESAT::Mat4 local_projection = ESAT::Mat4FromColumns(projection);
    ESAT::Mat4 local_view = ESAT::Mat4FromColumns(view);
    ESAT::Mat4 m = ESAT::Mat4Multiply(local_projection, local_view);
    program_->set_uniform_value(program_->get_uniform_position("u_vp_matrix"), EDK3::Type::T_MAT_4x4, m.d);

}

void MaterialBasic::setupModel(const float model[16]) const {
  //Set the model matrix as uniform here!
    program_->set_uniform_value(program_->get_uniform_position("u_m_matrix"), EDK3::Type::T_MAT_4x4, model);
}

unsigned int MaterialBasic::num_attributes_required() const {
  //Depending on how attributes the geometry has.
    return 3;
}

EDK3::Attribute MaterialBasic::attribute_at_index(const unsigned int attrib_idx) const {
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

EDK3::Type MaterialBasic::attribute_type_at_index(const unsigned int attrib_idx) const {
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
}

} //EDK3







