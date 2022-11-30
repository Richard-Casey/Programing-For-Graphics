#version 450

uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform sampler2D texture_spec;
uniform vec3 FragLightColor;
uniform vec3 FragLightPos;
uniform vec3 FragCamPos;
vec3 result;

struct PointLight
{
vec3 position;

float constant;
float linear;
float quadratic;

vec3 ambient;
vec3 diffuse;
vec3 specular;
};

#define NR_POINT_LIGHTS 2
uniform PointLight pointLights[NR_POINT_LIGHTS];

in vec2 FragTextureCoord;
out vec4 frag_colour;
in vec3 FragNormal;
in vec3 FragPos;
in mat3 TBN;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 FragPos, vec3 viewDir)
{
vec3 lightDir = normalize(FragLightPos - FragPos);
float diff = max(dot(normal, lightDir), 0.0);
vec3 reflectDir = normalize( reflect(-lightDir, normal));
float spec = pow(max(dot(reflectDir, viewDir ), 0.0), 128.0);
float distance = length (light.position - FragPos);
float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
vec3 ambient = light.ambient * vec3 (texture (texture_diffuse, FragTextureCoord));
vec3 diffuse  = light.diffuse  * diff * vec3(texture(texture_diffuse, FragTextureCoord));
vec3 specular = light.specular * spec * vec3(texture(texture_spec, FragTextureCoord));
ambient *= attenuation;
diffuse *= attenuation;
specular *= attenuation;
return (ambient + diffuse + specular);
}

void main()
{
float ambientStrength = 0.9;
vec3 ambient = ambientStrength * FragLightColor;


vec3 normal = normalize(texture2D(texture_normal, FragTextureCoord).rgb);
normal = normalize(normal * 2.0-1.0);
normal = normalize(TBN*normal);
vec3 viewDir = normalize( FragPos - FragCamPos);

for (int i=0; i < NR_POINT_LIGHTS; i++)
{
result += CalcPointLight (pointLights[i], normal, FragPos, viewDir);
}

frag_colour = vec4 (result, 1.0);

}

