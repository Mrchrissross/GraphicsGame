#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "LevelController.h"
#include "SnowBall.h"

// Here is the collision detection class, this allows us to detect any collisions that may occur during game player, between either the player and the ball or the ball and the player.

// These are the directions at which the ball could collide with a block, this allowes us to easily calculate what should happen to ball for each direction that the collision happens.
enum ImpactArea 
{
	Left,
	Right,
	Top,
	Bottom
};
// This is a simple struct, to tell the game when the game object has collided, which direction it collided, and the difference between the two objects.
struct Collision
{
    bool collided;
	ImpactArea impactArea;
    glm::vec2 difference;
};

class CollisionDection
{
public:
	// Constructor
	CollisionDection() {}
	// This is the main collision controller, this will check for collisions and tell the game what to do in the event of collision.
	std::vector<LevelController> CollisionController(GameObject *Player, SnowBall *Ball, std::vector<LevelController> Levels, GLuint Level, const glm::vec2 ballSpeed)
	{
		// Here we go through checking each snowblock.
		for (GameObject &SnowBlock : Levels[Level].Bricks)
		{
			// From this we find the snowblcoks that are not destroyed.
			if (!SnowBlock.Destroyed)
			{
				// Then we check for any collsion that may occur, between the snowblock and the ball. 
				Collision collision = CheckCollision(*Ball, SnowBlock);
				// If the ball has collided with a snowblock.
				if (collision.collided)
				{
					// Destroy the SnowBlock if it is not ice and raise the score by one
					if (!SnowBlock.IsIce)
					{
						Levels[Level].newScore++;
						SnowBlock.Destroyed = GL_TRUE;
					}				
					// As the ball has collided with an object, it will bounce.
					// So we find the direction that the impact occured.
					ImpactArea dir = collision.impactArea;
					// Then we find the difference between the objects.
					glm::vec2 diff_vector = collision.difference;
					// If it has collided horizontally
					if (dir == Left || dir == Right)	
					{
						// We reverse the horizontal velocity
						Ball->Velocity.x = -Ball->Velocity.x;
						GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
						if (dir == Left)
							Ball->Position.x += penetration;
						else
							Ball->Position.x -= penetration;
					}
					// Vertical collision is exactly the same but with vertical velocity
					else								
					{
						Ball->Velocity.y = -Ball->Velocity.y;
						GLfloat penetration = Ball->Radius - std::abs(diff_vector.y);

						if (dir == Top)
							Ball->Position.y -= penetration;
						else
							Ball->Position.y += penetration;
					}
				}
			}
		}
		// If the ball has not collided with a SnowBlock and has collided with the player instead...
		// A new collision object has been created.
		Collision result = CheckCollision(*Ball, *Player);
		// And we check if the ball is not stuck and if it has collided with the player.
		if (!Ball->Stuck && result.collided)
		{
			// We will check where it hit, and change the direction of the ball based on where it hit the players pad.
			GLfloat		center = Player->Position.x + Player->Size.x / 2,
						distanceFromCenter = (Ball->Position.x + Ball->Radius) - center,
						percentage = distanceFromCenter / (Player->Size.x / 2),
						strength = 2.0f;
			glm::vec2 oldVelocity = Ball->Velocity;
			Ball->Velocity.x = ballSpeed.x * percentage * strength;
			// This will keep the speed the same over both x, and y axis.
			Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
			Ball->Velocity.y = -1 * abs(Ball->Velocity.y);
		}
		// Then we return Levels to the source in order to update the score.
		return Levels;
	}
	// AABB - Ball collision
	Collision CheckCollision(SnowBall &one, GameObject &two) 
	{		
		glm::vec2	center(one.Position + one.Radius),														// Get center point circle first				
					AABB_HalfWayPoint(two.Size.x / 2, two.Size.y / 2),										// From this we will calculate the AABB info 
					ObjectCenter(two.Position.x + AABB_HalfWayPoint.x, two.Position.y + AABB_HalfWayPoint.y),
					difference = center - ObjectCenter,
					clamped = glm::clamp(difference, -AABB_HalfWayPoint, AABB_HalfWayPoint),
					closest = ObjectCenter + clamped;														// Here we will find the snowblock that is closest to the ball					
					difference = closest - center;															// and then find deistance from the both points
		// Then from this we can gather whether or not a collision has happened.
		// By calculating if the difference is lower than the balls radius.
		if (glm::length(difference) < one.Radius)
		{
			// If true, we create another collision object and set:
			Collision collisions;
			collisions.collided = GL_TRUE;								// Collided to true as the ball has collided.
			collisions.impactArea = DirectionCalculation(difference);	// The impact area to the impact area of the snowblock.
			collisions.difference = difference;							// And finally the difference between objects.
			// then we return the item to the collision controller.
			return collisions;				
		}
		// If the ball has not collided, then we:
		else
		{
			// Create another collision object and set.
			Collision collisions;
			collisions.collided = GL_FALSE;								// Collided to false as the ball has not collided.
			collisions.impactArea = Top;								// The impact area to top as the direction of the ball is defaulted.
			collisions.difference = glm::vec2(0, 0);					// And the difference to null.
			// then we return the item to the collision controller.
			return collisions;
		}
	}

	// This is used to calculate the Direction ball will impact.
	ImpactArea DirectionCalculation(glm::vec2 target)
	{	
		// Regions are the directions, possible impact areas.
		glm::vec2 region[] = {
					glm::vec2(-1.0f, 0.0f),	// left-side
					glm::vec2(1.0f, 0.0f),	// right-side
					glm::vec2(0.0f, 1.0f),	// top
					glm::vec2(0.0f, -1.0f)	// bottom
					
		};
		// Then calculate the difference
		GLfloat max = 0.0f;
		GLuint bestMatch = -1;
		for (GLuint i = 0; i < 4; i++)
		{
			GLfloat Target = glm::dot(glm::normalize(target), region[i]);
			if (Target > max)
			{
				// Always updating the target.
				max = Target;
				bestMatch = i;
			}
		}
		// Then we return the difference.
		return (ImpactArea)bestMatch;
	}
};

#endif