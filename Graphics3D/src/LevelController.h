#ifndef LEVEL_CONTROLLER_H
#define LEVEL_CONTROLLER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <fstream>
#include <sstream>
#include <vector>

#include "Game.h"
#include "GameObject.h"
#include "Sprite.h"
#include "AssetController.h"

// This is the level controller and controls all aspects of the levels and where blocks are will be assigned to depending on how we have initilized the levels.
class LevelController
{
public:
	// Here we intialize the class with a score of zero. The score will go up each time a block is detected as destroyed through the collision class.
	GLuint newScore = 0;
	// Then we set empty variables that we can later use.
	glm::vec3 colour;
	std::vector<GameObject> Bricks;

	// Constructor.
	LevelController() { }

	// Here is where we load the level, loading colours and placement from a file.
	void Load(const GLchar *path, GLuint width, GLuint height)
	{
		string		fileName(path),
					level = "../src/Levels/" + fileName + ".lvl";
					
		// To start we destroy any snowblocks that exist in the scene, leaving an empty scene.
		this->Bricks.clear();
		// Then we load in the level file.
		GLuint tileCode; std::string line;
		std::ifstream fstream(level.c_str());
		// Now we can start finding out all of the tile data from the file.
		std::vector<std::vector<GLuint>> tileData;
		if (fstream)
		{
			while (std::getline(fstream, line)) // Read every line from the level document
			{
				std::istringstream sstream(line);
				std::vector<GLuint> row;
				while (sstream >> tileCode) // Read each word seperated by spaces
					row.push_back(tileCode);
				tileData.push_back(row);
			}
			if (tileData.size() > 0)
				this->init(tileData, width, height);
		}
	}

	// This will be called to render the level and all of its objects, i.e. snowblocks and ice.
	void Draw(Sprite &renderer)
	{
		// We go through each block.
		for (GameObject &tile : this->Bricks)
			// And if the block is not destroyed we can render it.
			if (!tile.Destroyed)
				tile.Draw(renderer);
	}

private:
	// Here we initialize our level.
	void init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight)
	{
		// Here we find the width and height of all our snowblock.
		GLuint height = tileData.size(), width = tileData[0].size();
		GLfloat box_width = levelWidth / static_cast<GLfloat>(width), box_height = levelHeight / height, box_depth = 50.0f;
		
		// We initialize all the snowblockes and their colours based on the file that we loaded		
		for (GLuint y = 0; y < height; ++y)
		{
			for (GLuint x = 0; x < width; ++x)
			{				
				switch (tileData[y][x])
				{
					case 1:
					{
						glm::vec3 pos(box_width * x, box_height * y, 0.0f), size(box_width, box_height, box_depth);
						GameObject obj(pos, size, AssetController::GetTexture("ice"), glm::vec3(0.2f));
						obj.IsIce = GL_TRUE;
						this->Bricks.push_back(obj);
						break;
					}
					case 2:
						colour = glm::vec3(1.0f);
						break;
					case 3:
						colour = glm::vec3(0.9f, 0.2f, 0.3f);
						break;
					case 4:
						colour = glm::vec3(0.7f, 0.6f, 0.9f);
						break;
					case 5:					
						colour = glm::vec3(0.1f, 0.8f, 0.6f);
						break;		
					default:
						break;
				}
				// if the number on the file is higher than 1, this means that snow will be drawn to the current tile
				if (tileData[y][x] > 1)		
				{
					glm::vec3 pos(box_width * x, box_height * y, 0.0f), size(box_width, box_height, box_depth);
					this->Bricks.push_back(GameObject(pos, size, AssetController::GetTexture("snowblock"), colour));
				}
			}
		}
	}
};

#endif