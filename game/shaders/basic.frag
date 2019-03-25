#version 330 core

uniform sampler2D textureSampler;
in vec2 uv;

uniform ivec2 subCoords;
uniform ivec2 subSize;
uniform ivec2 texSize;

out vec4 color;

void main() {
    color = texture(textureSampler, (subCoords + (uv) * subSize) / texSize);
}
