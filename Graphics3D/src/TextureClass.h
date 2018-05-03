#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "SDL_image.h"
#include <GL/glew.h>
#include <iostream>

class Texture
{
public:						  
	GLuint	ID, 
			Mode;
					   
	Texture() { glGenTextures(1, &this->ID); }

	// Generates texture from the SDL Surface
	void Generate(SDL_Surface* data)
	{
		Mode = GL_RGB;

		if (data->format->BytesPerPixel == 4)		
			Mode = GL_RGBA;
		
		// Create Texture
		glBindTexture(GL_TEXTURE_2D, this->ID);
		glTexImage2D(GL_TEXTURE_2D, 0, Mode, data->w, data->h, 0, Mode, GL_UNSIGNED_BYTE, data->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		// Set Texture wrap and filter modes
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);
	} 

	// Generates texture from the SDL Surface
	void GenerateCubeMap(SDL_Surface* data, GLuint i)
	{
		// Create Texture
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, data->w, data->h, 0, GL_RGB, GL_UNSIGNED_BYTE, data->pixels);

		// Set Texture wrap and filter modes
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	// Binds it
	void Bind() const { glBindTexture(GL_TEXTURE_2D, this->ID); }
	void BindCubeMap() const { glBindTexture(GL_TEXTURE_CUBE_MAP, this->ID); }
};

#endif