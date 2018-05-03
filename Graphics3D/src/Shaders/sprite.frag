#version 440 core

in vec2 TexCoords;

out vec4 vertColour;

uniform sampler2D tex;
uniform vec3 spriteColour;

void main()
{    
    vertColour = vec4(spriteColour, 1.0) * texture(tex, TexCoords);
} 