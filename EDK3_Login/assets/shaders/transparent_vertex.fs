#version 330
uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;

out vec3 position;
out vec2 uv;
out vec3 normal;

void main() {
    gl_Position = u_vp_matrix * u_m_matrix * vec4(a_position, 1.0);
    position = (u_m_matrix * vec4(a_position,1.0)).xyz;
    uv = a_uv;
    normal = (u_m_matrix * vec4(a_normal,0.0)).xyz;
}





//#version 330

//layout(location = 0) in vec3 a_position;
//layout(location = 1) in vec3 a_normal;
//layout(location = 2) in vec2 a_uv;

//uniform mat4 u_model_matrix;
//uniform mat4 u_vp_matrix;

//void main()
//{
//    gl_Position = u_vp_matrix * u_model_matrix * vec4(a_position, 1.0);
//}

//#version 330

//layout(location = 0) in vec3 a_position;
//layout(location = 1) in vec3 a_normal;
//layout(location = 2) in vec2 a_uv;

//uniform mat4 u_model_matrix;
//uniform mat4 u_vp_matrix;
//uniform float u_time;

//out vec2 v_uv;
//out vec3 v_position;
//out vec3 v_normal;

//void main()
//{
//    // Calculamos una deformación en ondas
//    float wave = sin(a_position.y * 10.0 + u_time) * 0.1;
//    vec3 position = a_position + a_normal * wave;

//    v_uv = a_uv;
//    v_position = position;
//    v_normal = a_normal;

//    gl_Position = u_vp_matrix * u_model_matrix * vec4(position, 1.0);
//}
