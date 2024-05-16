#version 330

out vec4 FragColor;
in vec2 uv;
struct Light{
    int type;
    vec3 pos;
    vec3 dir;
    vec3 diff_color;
    vec3 spec_color;
    vec3 camera_pos;
    float linear_att;
    float quad_att;
    float constant_att;
    float shininess;
    float strength;
};

const int kMaxLights = 8;
uniform Sampler2D u_texture;
uniform Light u_lights[kMaxLights];
uniform int u_number_lights;
//uniform vec3 u_camera_pos;
uniform vec3 u_ambient;

vec3 DirectionaLight(){
  float directionalIncidence = max(dot(normal.xyz, conf.lightDirection), 0.0);
  //Specular
  vec3 viewDirection = normalize(u_camera_position - position.xyz);
  vec3 reflectDirection = reflect(-conf.lightDirection, normal.xyz);

  float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0), conf.specularShininess);

  vec3 diffuse = directionalIncidence * conf.lightColor;
  vec3 specular = conf.specularStrength * specularValue * conf.lightColor;
  return step(0.5,use_diffuse) * diffuse + step(0.5,use_specular) * specular;

}

vec3 SpotLight(){
  conf.lightDirection = normalize(conf.lightPosition - position.xyz);
  float theta = dot(conf.lightDirection,normalize(-conf.spotDirection));
  vec3 result = vec3(0.0,0.0,0.0);
    float directionalIncidence = max(dot(normal.xyz, conf.lightDirection), 0.0);
    //Specular
    vec3 viewDirection = normalize(u_camera_position - position.xyz);
    vec3 reflectDirection = reflect(-conf.lightDirection, normal.xyz);

    float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0), conf.specularShininess);

    vec3 diffuse = directionalIncidence * conf.lightColor;
    vec3 specular = conf.specularStrength * specularValue * conf.lightColor;
    //Attenuation
    float distance = length(conf.lightPosition - position.xyz);
    float attenuation = 1.0 / (conf.attenuation.constant + conf.attenuation.linear * distance + conf.attenuation.quadratic * distance * distance);
    
    //Intensity
    float epsilon   = conf.cutOff - conf.outerCutOff;
    float intensity = clamp((theta - conf.outerCutOff) / epsilon, 0.0, 1.0);   
    
    result = (diffuse * intensity  * attenuation) + (specular * intensity * attenuation);

  return result;

}

vec3 PointLight(){
  conf.lightDirection = normalize(conf.lightPosition - position.xyz);
  float directionalIncidence = max(dot(normal.xyz, conf.lightDirection), 0.0);
  //Specular
  vec3 viewDirection = normalize(u_camera_position - position.xyz);
  vec3 reflectDirection = reflect(-conf.lightDirection, normal.xyz);

  float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0), conf.specularShininess);

  vec3 diffuse = directionalIncidence * conf.lightColor;
  vec3 specular = conf.specularStrength * specularValue * conf.lightColor;
  //Attenuation
  float distance = length(conf.lightPosition - position.xyz);
  float attenuation = 1.0 / (conf.attenuation.constant + conf.attenuation.linear * distance + conf.attenuation.quadratic * distance * distance);
  return step(0.5,use_diffuse)*(diffuse * attenuation) + step(0.5,use_specular)*(specular * attenuation);
}

void main(){
    vec3 final_color = vec3(0.0, 0.0, 0.0);
    for(int i=0; i<kMaxLights;i++){
        if( i < u_number_lights){
            switch(u_lights[i].type){
                case 0: {
                    final_color = DirectionaLight();
                    break;
                }
                case 1: {
                    final_color = SpotLight();
                    break;
                }
                case 2: {
                    final_color = PointLight();
                    break;
                }

            }
        }
    }
    FragColor = vec4(1.0,0.0,0.0, 1.0) * texture(u_texture,uv );
}