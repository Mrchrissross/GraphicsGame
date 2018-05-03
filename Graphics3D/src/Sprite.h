#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderClass.h"
#include "TextureClass.h"


class Sprite
{
public:
	Shader shader;
	// Set up Vertex Array Object && Vertex Buffer Object
	GLuint	VAO, 
			VBO;

	// Constructor
	Sprite(Shader &shader){ this->shader = shader; setBuffers(); }
	// Deconstructor
	~Sprite(){ glDeleteVertexArrays(1, &VAO); }

	// Initializes and configures the buffers and vertex attributes
	void setBuffers()
	{
		// Define vertices for the sprite
		GLfloat vertices[] = {
		//	  X     Y     Z		  A		 B		C		 U     V		Location			 triangle
			// back
			 0.0f, 0.0f, 0.0f,	 0.0f,  0.0f, -1.0f,	0.0f, 0.0f,	//bottom-back-left
			 1.0f, 0.0f, 0.0f,   0.0f,  0.0f, -1.0f,	1.0f, 0.0f,	//bottom-back-right			1
			 1.0f, 1.0f, 0.0f,   0.0f,  0.0f, -1.0f,	1.0f, 1.0f,	//top-back-right

			 1.0f, 1.0f, 0.0f,   0.0f,  0.0f, -1.0f,	1.0f, 1.0f,	//top-back-right
			 0.0f, 1.0f, 0.0f,   0.0f,  0.0f, -1.0f,	0.0f, 1.0f,	//top-back-left				2
			 0.0f, 0.0f, 0.0f,   0.0f,  0.0f, -1.0f,	0.0f, 0.0f,	//bottom-back-left

			// front
			 0.0f, 0.0f, 1.0f,   0.0f,  0.0f,  1.0f,	0.0f, 0.0f,	//bottom-front-left
			 1.0f, 0.0f, 1.0f,   0.0f,  0.0f,  1.0f,	1.0f, 0.0f,	//bottom-front-right		1
			 1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,	1.0f, 1.0f,	//top-front-right

			 1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,	1.0f, 1.0f,	//top-front-right
			 0.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,	0.0f, 1.0f,	//top-front-left			2
			 0.0f, 0.0f, 1.0f,   0.0f,  0.0f,  1.0f,	0.0f, 0.0f,	//bottom-front-left

			// left
			 0.0f, 1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,	1.0f, 0.0f,	//top-front-left
		 	 0.0f, 1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,	1.0f, 1.0f,	//top-back-left				1
			 0.0f, 0.0f, 0.0f,   -1.0f,  0.0f,  0.0f,	0.0f, 1.0f,	//bottom-back-left

			 0.0f, 0.0f, 0.0f,   -1.0f,  0.0f,  0.0f,	0.0f, 1.0f,	//bottom-back-left
			 0.0f, 0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,	0.0f, 0.0f,	//bottom-front-left			2
			 0.0f, 1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,	1.0f, 0.0f,	//top-front-left

			// right
			 1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,	1.0f, 0.0f,	//top-front-right
			 1.0f, 1.0f, 0.0f,   1.0f,  0.0f,  0.0f,	1.0f, 1.0f,	//top-back-right			1
			 1.0f, 0.0f, 0.0f,   1.0f,  0.0f,  0.0f,	0.0f, 1.0f,	//bottom-back-right

			 1.0f, 0.0f, 0.0f,   1.0f,  0.0f,  0.0f,	0.0f, 1.0f,	//bottom-back-right
			 1.0f, 0.0f, 1.0f,   1.0f,  0.0f,  0.0f,	0.0f, 0.0f,	//bottom-front-right		2
			 1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,	1.0f, 0.0f,	//top-front-right

			// bottom
			 0.0f, 0.0f, 0.0f,   0.0f, -1.0f,  0.0f,	0.0f, 1.0f,	//bottom-back-left
			 1.0f, 0.0f, 0.0f,   0.0f, -1.0f,  0.0f,	1.0f, 1.0f,	//bottom-back-right			1
			 1.0f, 0.0f, 1.0f,   0.0f, -1.0f,  0.0f,	1.0f, 0.0f,	//bottom-front-right

		 	 1.0f, 0.0f, 1.0f,   0.0f, -1.0f,  0.0f,	1.0f, 0.0f,	//bottom-front-right
			 0.0f, 0.0f, 1.0f,   0.0f, -1.0f,  0.0f,	0.0f, 0.0f,	//bottom-front-left			2
			 0.0f, 0.0f, 0.0f,   0.0f, -1.0f,  0.0f,	0.0f, 1.0f,	//bottom-back-left

			// top
			 0.0f, 1.0f, 0.0f,	 0.0f,  1.0f,  0.0f,	0.0f, 1.0f,	//top-back-left
			 1.0f, 1.0f, 0.0f,   0.0f,  1.0f,  0.0f,	1.0f, 1.0f,	//top-back-right			1
			 1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,	1.0f, 0.0f,	//top-front-right

			 1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,	1.0f, 0.0f,	//top-front-right
			 0.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,	0.0f, 0.0f,	//top-front-left			2
			 0.0f, 1.0f, 0.0f,   0.0f,  1.0f,  0.0f,	0.0f, 1.0f	//top-back-left 	
		};

		//
		// OpenGL buffers
		// Initialization code using Vertex Array Object (VAO) (done once (unless the object frequently changes))
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		// Copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// Bind Vertex Array Object
		glBindVertexArray(VAO);
		//Attributes
		//---------------------------------------------------------------------------- Ver
		glEnableVertexAttribArray(0);			// location = 0 
		glVertexAttribPointer(
			0,									// location = 0
			3,									// 3 components (x, y, z)
			GL_FLOAT, GL_FALSE,
			8 * sizeof(GLfloat),				// stride: 5 * float (x, y, z, u, v)
			(GLvoid*)0);						// offset: 0
		//---------------------------------------------------------------------------- Nor
		glEnableVertexAttribArray(1);			// location = 1 
		glVertexAttribPointer(
			1,									// location = 1
			3,									// 3 components (a, b, c)
			GL_FLOAT, GL_FALSE,
			8 * sizeof(GLfloat),				// stride: 8 * float
			(GLvoid*)(3 * sizeof(GLfloat)));	// offset: 3 * float
		//---------------------------------------------------------------------------- Tex
		glEnableVertexAttribArray(2);			// location = 2 
		glVertexAttribPointer(
			2,									// location = 2 
			2,									// 2 components (u, v) 
			GL_FLOAT, GL_FALSE, 
			8 * sizeof(GLfloat),				// stride: 8 * float 
			(GLvoid *)(6 * sizeof(GLfloat)));	// offset: 6 * float
		//----------------------------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//Unbind the VAO
		glBindVertexArray(0);
	}

	// Renders the sprite
	void DrawSprite(Texture &texture, glm::vec3 position, glm::vec3 size = glm::vec3(10, 10, 10), GLfloat rotate = 0.0f, glm::vec3 colour = glm::vec3(1.0f))
	{
		// Apply the shader
		this->shader.Use();
		
		// Transform the object
		glm::mat4	transformObject,
					normalMatrix;
					transformObject = glm::translate(transformObject, glm::vec3(position));
					transformObject = glm::translate(transformObject, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.5f * size.z));
					transformObject = glm::rotate(transformObject, rotate, glm::vec3(0.0f, 0.0f, 0.1f));
					transformObject = glm::translate(transformObject, glm::vec3(-0.5f * size.x, -0.5f * size.y, -0.5f * size.z));
					transformObject = glm::scale(transformObject, glm::vec3(size));
					normalMatrix = transpose(inverse(transformObject));

		this->shader.SetVector3f("spriteColour", colour);
		this->shader.SetMatrix4("transformObject", transformObject);
		this->shader.SetMatrix4("uNormalMatrix", normalMatrix);

		glActiveTexture(GL_TEXTURE0);
		texture.Bind();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6*2*3);
		glBindVertexArray(0);
	}
};

#endif