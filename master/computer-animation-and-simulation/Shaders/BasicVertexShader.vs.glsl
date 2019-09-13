#version 330 core

in vec3 position;
in vec3 normal;
in vec2 inTexture1;

varying vec3 vertexPosition;
varying vec3 vertexNormal;

out vec2 textureCords1;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

uniform float opacity;

void main() {
    vec4 tempVector = modelMatrix * vec4(position.x, position.y, position.z, 1.0);
    gl_Position = projectionMatrix * viewMatrix * tempVector;

    textureCords1 = inTexture1;

    vertexPosition = vec3(tempVector.x, tempVector.y, tempVector.z);
    vertexNormal = (inverse(transpose(modelMatrix)) * vec4(normal, 0.0)).xyz;
}