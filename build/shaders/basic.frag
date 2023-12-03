#version 460 core

in vec4 vertexCol;
in vec2 uv;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
    //FragColor = vertexCol;//vec4(vertexCol.x, vertexCol.y, vertexCol.z, vertexCol.w);
    FragColor = texture(tex, uv);
}