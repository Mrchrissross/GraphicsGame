#ifndef GAME_H
#define GAME_H

// // GLEW - OpenGL Extension Wrangler - http://glew.sourceforge.net/
// // NOTE: include before SDL.h
#include <GL/glew.h>
#include "windows.h"

// SDL - Simple DirectMedia Layer - https://www.libsdl.org/
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

// // - OpenGL Mathematics - https://glm.g-truc.net/
#define GLM_FORCE_RADIANS // force glm to use radians
// // NOTE: must do before including GLM headers
// // NOTE: GLSL uses radians, so will do the same, for consistency
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Headers
#include "LevelController.h"
#include <vector>

const GLfloat			playerSpeed = 500.0f,
						ballSize = 11.5f;
				
const glm::vec2			ballSpeed(100.0f, -350.0f);

const glm::vec3			playerSize(100, 20, 50),
						powerUpSize(35, 35, 35),
						lrBoundarySize(50, 600, 50),
						tbBoundarySize(900, 50, 50),
						livesTextSize(880 / 5.5, 470 / 5.5, 0.1),
						livesNumberTextSize(159 / 4.5, 212 / 4.5, 0.1),
						GameOverTextSize(2001 / 5, 790 / 5, 0.1),
						ScoreTextSize((1005 / 6.5), (470 / 6.5), 0.1),
						TenthTextSize((140 / 3), (195 / 3), 0.1),
						OnesTextSize((140 / 3), (195 / 3), 0.1);

class Game
{
public:
	GLboolean			movingLeft = false,
						movingRight = false,
						movingForward = false,
						movingBack = false,
						mouseEnabled = false,
						autoPlay = false,
						autoPlay2 = false,
						autoPlayClick = true,
						powerupSpawned = false,
						isRunning,
						trueFullscreen = false,
						gameStarted = false,
						powerupActivated = false,
						fifthPowerUp = false,
						changeBallColour = false,
						isGameOver = false;

	GLfloat				powerupspeed = 100.0f,
						autoPilot = 0.f,
						temp = 0.0f,
						angle = -90.0f,			// This will control the angle at which the camera will be.
						yAngle = 0.0f,
						zAxis = 0.0f;

	GLuint				LevelNumber = 1,
						PowerUpSpawnCount = 3,
						Width,
						Height,
						Level,
						mouseX = 0,
						numberOfLives = 3,
						score = 0,
						scoreSeparator = 0,
						colourNumber = 0,
						startTime,
						currentTime,
						shakeCam = 0,
						rNumber;

	glm::vec3			camPosition,
						camFront,
						camShake,
						lightPosition = glm::vec3(0.0f, 0.0f, 0.9f),
						lightColour;

	glm::mat4			projection,
						projection2,
						cameraMatrix;

	std::vector<LevelController> Levels;

	SDL_Surface* tex;
	SDL_Color textColour = { 255, 255, 255 };
	
	GLboolean running() { return isRunning; }

	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	
	// Game Loop
	void init();
	void handleEvents(SDL_Window*);
	void update(GLfloat);
	void render();	
	
	// Reset
	void LoseLife();
	void ChangeLevel();
	
	// Object Creation & Configuation
	void CreateShaders();
	void CreateTextures();
	void CreateLevels();
	void ConfigureObjects();

	void ResizeWindow(SDL_Window*);

	void SpawnPowerUp();
	void ManagePowerUp(GLfloat);
	void GameAutoPlay(GLboolean);
	void SetScore(GLuint newScore){ newScore = score; }

	GLuint GetScore() const { return score; }
};

#endif