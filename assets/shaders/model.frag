#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material1;
uniform PointLight light;
uniform vec3 view_pos;

void main() {

    // ambient
    vec3 ambient = light.ambient * texture(material1.diffuse, TexCoords).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 light_dir = normalize(light.position - FragPos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material1.diffuse, TexCoords).rgb;

    // specular
    vec3 view_dir = normalize(view_pos - FragPos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float shininess = 64.0f;
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), shininess);
    vec3 specular = light.specular * spec * texture(material1.specular, TexCoords).rgb;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}