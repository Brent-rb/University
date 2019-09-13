#version 330 core

in vec2 textureCords1;
in vec4 particleColor;
out vec4 color;

uniform sampler2D sprite;

void main() {
    color = (texture(sprite, textureCords1) * particleColor);
}
