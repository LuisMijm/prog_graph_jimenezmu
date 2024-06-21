#version 330
uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;
uniform float u_time;

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
    // normal = a_normal;
}