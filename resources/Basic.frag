#version 450

uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform sampler2D texture_spec;
uniform vec3 FragLightColor;
uniform vec3 FragLightPos;
uniform vec3 FragCamPos;

//uniform DirLight dirLight;

in vec2 FragTextureCoord;
out vec4 frag_colour;
in vec3 FragNormal;
in vec3 FragPos;
in mat3 TBN;

//struct Light
//{
//vec3 direction;
//
//vec3 ambient;
//vec3 diffuse;
//vec3 specular;
//};

//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);


void main()
{
float ambientStrength = 0.9;
vec3 ambient = ambientStrength * FragLightColor;


vec3 normal = normalize(texture2D(texture_normal, FragTextureCoord).rgb);
normal = normalize(normal * 2.0-1.0);
normal = normalize(TBN*normal);

vec3 lightDir = normalize(FragLightPos - FragPos);
float diff = max(dot(normal, lightDir), 0.0);
vec3 diffuse = diff * FragLightColor;

//Specular
float specularStrength = 10f;
vec3 viewDir = normalize( FragPos - FragCamPos);
vec3 reflectDir = normalize( reflect(-lightDir, normal));
float spec = pow(max(dot(reflectDir, viewDir ), 0.0), 128.0);
vec3 specular = vec3(specularStrength * spec)*texture2D(texture_spec, FragTextureCoord). rgb;

vec4 result = vec4(texture2D(texture_diffuse, FragTextureCoord).rgb * (ambient + diffuse + specular), 1);



frag_colour = result;

}

