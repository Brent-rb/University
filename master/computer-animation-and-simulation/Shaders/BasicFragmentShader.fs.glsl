#version 330 core

varying vec3 vertexPosition;
varying vec3 vertexNormal;

in vec2 textureCords1;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 cameraPosition;
uniform vec3 cameraForwardVector;

uniform vec3 objectProperties;
uniform vec3 objectColor;
uniform float objectOpacity;

uniform sampler2D texture1;

out vec4 outColor;

void main() {
    vec3 lightDirection = normalize(lightPosition - vertexPosition);
    vec3 viewDirection = normalize(cameraPosition - vertexPosition);
    vec3 reflectDirection = reflect(-lightDirection, vertexNormal);

    vec3 ambientLight = objectProperties.x * lightColor;
    vec3 diffuseLight = max(dot(vertexNormal, lightDirection), 0.0) * objectProperties.y * lightColor;
    vec3 specularLight = objectProperties.z * pow(max(dot(viewDirection, reflectDirection), 0.0), 32) * lightColor;

    outColor = vec4((ambientLight + diffuseLight + specularLight), 1) * texture(texture1, textureCords1) * vec4(objectColor, 1.0f);
    outColor.a *= objectOpacity;
}