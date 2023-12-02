#version 460 core

layout (location = 0) in vec3 posAttrib;
layout (location = 1) in vec4 colAttrib;

out vec4 vertexCol;

void main(){
    gl_Position = vec4(posAttrib.x, posAttrib.y, posAttrib.z, .5);
    vertexCol = colAttrib;
}