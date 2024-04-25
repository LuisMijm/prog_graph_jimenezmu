#version 330
uniform sampler2D u_texture;
uniform sampler2D u_albedo_1;
uniform sampler2D u_albedo_2;
uniform int u_use_texture;
uniform vec4 u_color;
out vec4 fragColor;
in vec2 uv;
in vec3 normal;
void main() {
   if(0 == u_use_texture){
   //  fragColor = u_color;
   fragColor = vec4(normal,1.0);
   }else{
   //  fragColor = texture(u_albedo_2,uv);
    fragColor = texture(u_albedo_2,uv) * u_color;
   }
}