#version 330 core

layout(location = 0) in vec2 point_location;
layout(location = 1) in vec2 point_uv;

uniform vec2 screenSize;
unifrom vec2 subCoords;
uniform vec2 subSize;
uniform ve2 objPos;
uniform vec2 size;

out vec2 uv;

void main() {
    gl_Position = point_location;
}