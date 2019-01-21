#version 330 core

uniform sampler2D textureSampler;

uniform ivec4 textColor;

in vec2 uv;

out vec4 color;

void main() {
    color = vec4(vec3(1), texture(textureSampler, uv).r) * (textColor / vec4(255));
}
