#version 440 core
layout (location = 0) in vec3 Position; //vertex positions
layout (location = 1) in vec2 texCoord;	//texture coordinates

out vec2 TexCoords;
out vec3 lightColour;
out float lightDistance;

uniform mat4 transformObject;
uniform mat4 view;
uniform mat4 projection;
uniform float uLightDistance; //light distance uniform
uniform vec3 uLightColour;	//light colour uniform


void main()
{
	gl_Position = projection * view * transformObject * vec4(Position.x, Position.y, Position.z, 1.0);
	lightColour = uLightColour;
	lightDistance = uLightDistance;
	TexCoords = vec2(texCoord.x, texCoord.y);
}