#ifndef SNOWBALL_H
#define SNOWBALL_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "TextureClass.h"
#include "Sprite.h"
#include "GameObject.h"

// This is the snowball object, eg. the ball. This class defines how the ball moves and what happens when it collides with the borders of the screen.
class SnowBall : public GameObject
{
public:	
	GLfloat   Radius;
	GLboolean Stuck;
	// Initialize our ball with the specified variables in the constructor.
	SnowBall() : GameObject(), Radius(12.5f), Stuck(GL_TRUE) { }
	SnowBall(glm::vec3 position, GLfloat radius, glm::vec2 velocity, Texture sprite) : GameObject(position, glm::vec3(radius * 2, radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity), Radius(radius), Stuck(GL_TRUE) { }
	// This is used to move the ball.
	glm::vec3 Move(GLfloat deltaTime, GLuint windowWidth)
	{
		if (!this->Stuck)
		{
			// Giving the ball velocity to move
			this->Position.x += this->Velocity.x * deltaTime;
			this->Position.y += this->Velocity.y * deltaTime;
			// If the ball hits the top of the screen,
			if (this->Position.y <= 0.0f)								
			{
				// the ball was reverse it .y velocity making it go downwards
				this->Velocity.y = -this->Velocity.y;					
				this->Position.y = 0.0f;
			}
			// If the ball hits the left of the screen (position 0.0 on the x axis),
			if (this->Position.x <= 0.0f)								
			{
				// it will reverse its .x velocity and go right
				this->Velocity.x = -this->Velocity.x;					
				this->Position.x = 0.0f;
			}
			// If the ball hits the right side of the screen (position screen width (800.0)
			else if (this->Position.x + this->Size.x >= windowWidth)	
			{
				// Reverse the velocity to go left.
				this->Velocity.x = -this->Velocity.x;					
				this->Position.x = windowWidth - this->Size.x;
			}		
		}
		return this->Position;
	}
	// Reset the balls position and stick it to the players board
	void Reset(glm::vec3 ballPosition, glm::vec2 velocity)				
	{ 
		this->Position = ballPosition;
		this->Velocity = velocity; 
		this->Stuck = GL_TRUE; 
	}
};

#endif