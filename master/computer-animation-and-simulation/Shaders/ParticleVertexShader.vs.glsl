#version 330 core

in vec3 position;
in vec3 normal;
in vec2 inTexture1;

varying vec3 vertexPosition;
varying vec3 vertexNormal;

out vec2 textureCords1;
out vec4 particleColor;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 offset;

uniform vec4 color;

void main() {
    vec3 camRight = vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);
    vec3 camUp = vec3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);

    vec4 tempVector = vec4(position + offset + camRight + camUp, 1);
    gl_Position = projectionMatrix * viewMatrix * tempVector;
    textureCords1 = inTexture1;
    vertexPosition = vec3(tempVector.x, tempVector.y, tempVector.z);
    particleColor = color;
}