#version 330

out vec4 FragColor;
in vec3 position;
in vec2 uv;
in vec3 normal;
struct Light{
    int type;
    vec3 pos;
    vec3 dir;
    vec3 diff_color;
    vec3 spec_color;
    float linear_att;
    float quad_att;
    float constant_att;
    float shininess;
    float strength;
    float cutOff;
    float outerCutOff;

    int enabled;
};

const int kMaxLights = 9;
uniform sampler2D u_texture;
uniform Light u_lights[kMaxLights];
uniform int u_number_lights;
uniform vec3 u_camera_pos;
uniform vec3 u_ambient;
uniform int u_postprocess;

//vec3 DirectionaLight(Light light){
//  float directionalIncidence = max(dot(normal, light.dir), 0.0);
//  ////Specular
//  vec3 viewDirection = normalize(u_camera_pos - light.pos);
//  vec3 reflectDirection = reflect(-light.dir, normal);

//  float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0), light.shininess);

//  vec3 diffuse = directionalIncidence * light.diff_color;
//  vec3 specular = specularValue * light.spec_color;
//  return (diffuse + specular) * light.strength;
//}


vec3 SpotLight(Light light){
    vec3 lightDir = normalize(light.pos - position.xyz);
    float theta = dot(lightDir, normalize(-light.dir));
    vec3 result = vec3(0.0,0.0,0.0);
    float directionalIncidence = max(dot(normal, lightDir), 0.0);

    //Specular
    vec3 viewDirection = normalize(u_camera_pos - position.xyz);
    vec3 reflectDirection = reflect(-lightDir, normal);

    float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0), light.shininess);

    vec3 diffuse = directionalIncidence * light.diff_color;
    vec3 specular = light.strength * specularValue * light.spec_color;
    //Attenuation
    float distance = length(light.pos - position.xyz);
    float attenuation = 1.0 / (light.constant_att + light.linear_att * distance + light.quad_att * distance * distance);
    
    //Intensity
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);   
    
    result = (diffuse * intensity * attenuation) + (specular * intensity * attenuation);

  return result;

}

vec3 PointLight(Light light){
  vec3 lightDir = normalize(light.pos - position.xyz);
  float directionalIncidence = max(dot(normal, lightDir), 0.0);
  //Specular
  vec3 viewDirection = normalize(u_camera_pos - position.xyz);
  vec3 reflectDirection = reflect(-lightDir, normal);

  float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0), light.shininess);

  vec3 diffuse = directionalIncidence * light.diff_color;
  vec3 specular = light.strength * specularValue * light.spec_color;
  //Attenuation
  float distance = length(light.pos - position.xyz);
  float attenuation = 1.0 / (light.constant_att + light.linear_att * distance + light.quad_att * distance * distance);
  return (diffuse * attenuation) + (specular * attenuation);
}

vec3 DirectionaLight(Light light){
  vec3 lightDir = normalize(light.dir);
  vec3 reflectDirection = reflect(-lightDir, normal);
  vec3 viewDirection = normalize(u_camera_pos - light.pos);

  float diff = max(dot(lightDir, normal), 0.0);
  float spec = pow(max(dot(reflectDirection, viewDirection), 0.0), 2);

  vec3 diffuse = diff * light.diff_color;
  vec3 specular = spec * light.spec_color;
  return (diffuse + specular) * light.strength;
}


void main(){
    vec3 ilumination = vec3(0.0);
    for(int i=0; i<kMaxLights;i++){
      if( i < u_number_lights && 0 != u_lights[i].enabled){

        if(1 == u_lights[i].type){
                                    ilumination += SpotLight(u_lights[i]);
        }
        else if(2 == u_lights[i].type){
                                    ilumination += PointLight(u_lights[i]);
        }else{
                            ilumination += DirectionaLight(u_lights[i]);
        }

                            //ilumination += DirectionaLight(u_lights[i]);


      }
    }
    vec3 final_color = u_ambient;
    final_color += ilumination;


    //if(1 == u_postprocess){
    //    FragColor = vec4(normal, 1.0) * texture(u_texture,uv);
    //}
    //else if(2 == u_postprocess){
    //    FragColor = vec4(uv, 1.0, 1.0);
    //}
    //else if(3 == u_postprocess){
    //    FragColor = vec4(1.0) - vec4(final_color, 1.0) * texture(u_texture,uv);
    //}
    //else{
    //    FragColor = vec4(final_color, 1.0) * texture(u_texture,uv);
    //}
    
    FragColor = vec4(final_color, 1.0) * texture(u_texture,uv);
    
    // another post process
    //FragColor = vec4(normal, 1.0) * texture(u_texture,uv);

    // another post process
    //FragColor = vec4(uv, 1.0, 1.0);

    // first attempt of post process
    //FragColor = vec4(1.0) - vec4(final_color, 1.0) * texture(u_texture,uv);

    //FragColor = vec4(1.0,0.0,0.0, 1.0) * texture(u_texture,uv );
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}