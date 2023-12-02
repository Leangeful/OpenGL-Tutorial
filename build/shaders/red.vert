#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;
layout (location = 2) uniform float xOffset;

out vec4 vertexCol;
out vec4 vertPos;

void main(){
    vertPos = vec4(aPos.x + xOffset, aPos.yz, 1.0);
    gl_Position = vertPos;
    vertexCol = aCol;
}