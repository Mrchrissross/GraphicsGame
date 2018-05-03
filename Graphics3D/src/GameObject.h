#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "TextureClass.h"
#include "Sprite.h"

// This is the game object class and holds all the information about a game object.

class GameObject
{
public:
	// Veriables consist of:
	glm::vec2	Velocity;		// The game objects velocity/speed.
	glm::vec3   Position,		// The game objects position.
				Size;			// The game objects size.
	GLboolean   IsIce,			// Whether or not the game object is ice.
				Destroyed;		// Whether or not the game object is destroyed.
	glm::vec3   Colour;			// What colour the game object is.
	GLfloat     Rotation;		// What rotation or angle it is at.
	Texture     MySprite;		// The texture that is has been allocated.

	// As the game object is constructed, it is assigned values.
	GameObject() : Position(0, 0, 0), Size(1, 1, 1), Velocity(0.0f), Colour(1.0f), Rotation(0.0f), MySprite(), IsIce(false), Destroyed(false) { }
	GameObject(glm::vec3 position, glm::vec3 size, Texture sprite, glm::vec3 colour = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f)) : Position(position), Size(size), Velocity(velocity), Colour(colour), Rotation(0.0f), MySprite(sprite), IsIce(false), Destroyed(false) { }
	// To successfully render the object, we must draw it to the screen using the Sprite Class, passing all variables.
	virtual void Draw(Sprite &renderer) { renderer.DrawSprite(this->MySprite, this->Position, this->Size, this->Rotation, this->Colour); }
};

#endif