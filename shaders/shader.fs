#version 330 core

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;


void main(){
    
    //calculating ambient light
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    //calculating diffused light
    vec3 norm = normalize(Normal);
    //wecalculate light directinon with this
    vec3 lightDir = normalize(lightPos - FragPos);
    //in dot product the larger the angle the lower value it returns
    //we take the max value because value after 90deg becomes negetive in dot product
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //calculating specular lighting
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    //The reflect function expects the first vector to
    //point from the light source towards the fragment’s position, but the lightDir vector is currently
    //pointing the other way around: from the fragment towards the light source
    //second argument is expected to be the normal vector
    vec3 reflectDir = reflect(-lightDir, norm);
    //similar to diffuse we calculate the light angle with dot product
    //we then raise it to the power of 32 that is the shininess value of highlight
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}