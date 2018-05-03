#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// This is the shader class, it is used to properly compile shaders to the program and store its id. 
class Shader
{
public:
	GLuint	ID,
			sVertex,
			sFragment;

	Shader() { }	
	Shader &Use(){ glUseProgram(this->ID); return *this; }

	void Compile(const GLchar *vSh, const GLchar *fSh)
	{		
		// Implement the Vertex Shader
		sVertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(sVertex, 1, &vSh, NULL);
		glCompileShader(sVertex);
		// Implement the Fragment Shader
		sFragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(sFragment, 1, &fSh, NULL);
		glCompileShader(sFragment);
		// Create the shader program
		this->ID = glCreateProgram();
		glAttachShader(this->ID, sVertex);
		glAttachShader(this->ID, sFragment);
		glLinkProgram(this->ID);
		// These shaders are no longer needed so we can now delete them
		glDeleteShader(sVertex);
		glDeleteShader(sFragment);
	}
		
	void SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false)
	{ if (useShader)this->Use(); glUniform1f(glGetUniformLocation(this->ID, name), value); }
	void SetInteger(const GLchar *name, GLint value, GLboolean useShader = false)
	{ if (useShader)this->Use(); glUniform1i(glGetUniformLocation(this->ID, name), value); }
	void SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false)
	{ if (useShader)this->Use(); glUniform2f(glGetUniformLocation(this->ID, name), x, y); }
	void SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false)
	{ if (useShader)this->Use(); glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y); }
	void SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false)
	{ if (useShader)this->Use(); glUniform3f(glGetUniformLocation(this->ID, name), x, y, z); }
	void SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false)
	{ if (useShader)this->Use(); glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z); }
	void SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false)
	{ if (useShader)this->Use(); glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w); }
	void SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false)
	{ if (useShader)this->Use(); glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w); }
	void SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false)
	{ if (useShader)this->Use(); glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix)); }
};

#endif