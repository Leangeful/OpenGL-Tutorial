#version 460 core

in vec4 vertexCol;
out vec4 FragColor;

void main()
{
    FragColor = vertexCol;//vec4(vertexCol.x, vertexCol.y, vertexCol.z, vertexCol.w);
}