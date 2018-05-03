#version 440 core
layout (location = 0) in vec3 Position; //vertex positions
layout (location = 2) in vec2 texCoord;	//texture coordinates

out vec2 TexCoords;

uniform mat4 transformObject;
uniform mat4 projection;

void main()
{
    TexCoords = vec2(texCoord.x, texCoord.y);
    gl_Position = projection * transformObject * vec4(Position.x, -Position.y, 0, 1.0); 
}