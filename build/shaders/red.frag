#version 460 core

in vec4 vertexCol;
in vec4 vertPos;
out vec4 FragColor;

void main()
{
    FragColor = vertPos;
    //FragColor = vec4(1.0, .0, .0, .0);
}