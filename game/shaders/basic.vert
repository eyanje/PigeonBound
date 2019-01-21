#version 330 core

layout(location = 0) in vec2 point_location;
layout(location = 1) in vec2 point_uv;

uniform ivec2 screenSize;
uniform ivec2 subCoords;
uniform ivec2 subSize;
uniform ivec2 objPos;
uniform ivec2 size;

out vec2 uv;

void main() {
    gl_Position = vec4(
        vec2(2, -2) *
        (objPos + point_location * size / subSize) / screenSize
        + vec2(-1, 1),
        0, 1);
    uv = point_uv;
}
