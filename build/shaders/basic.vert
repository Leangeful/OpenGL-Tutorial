#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;
layout (location = 2) in vec2 aUV;

out vec4 vertexCol;
out vec2 uv;

void main(){
    gl_Position = vec4(aPos, 1.0);
    vertexCol = aCol;
    uv = aUV;
}