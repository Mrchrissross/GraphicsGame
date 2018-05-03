#version 440 core
in vec2 TexCoords; 	//tex coords from vertex shader
in vec3 lightColour;
in float lightDistance;

out vec4 vertColour;	//output colour of vertex

uniform sampler2D tex;		//uniform holding texture info from main programme
uniform vec3 spriteColour;	//input the Colour values from Vertex shader

void main()
{
	vec4 texColour = vec4(spriteColour, 1.0) * texture(tex, TexCoords);
	vertColour = vec4(  lightDistance * lightColour.x * texColour.x, 
						lightDistance * lightColour.y * texColour.y,      	 		
						lightDistance * lightColour.z * texColour.z, 
						texColour.a);
}