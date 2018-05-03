#include <algorithm>
#include "Game.h"
#include "AssetController.h"
#include "CollisionDetection.h"
#include "Sprite.h"
#include "GameObject.h"
#include "SnowBall.h"
#include "Camera.h"
#include "Light.h"
#include "Cubemap.h"
#include <time.h>

Sprite				*Renderer,
					*Renderer2;
GameObject			*Player,
					*LeftBoundary,
					*RightBoundary,
					*BottomBoundary,
					*TopBoundary,
					*Lives,
					*LivesNumber,
					*GameOver,
					*Score,
					*Tenth,
					*Ones,
					*PowerUp;
SnowBall			*Ball;
Camera				*View;
CollisionDection	*CollisionDetector;
Light				*GameLight;
Cubemap				*Background;

Game::Game(GLuint width, GLuint height) : Width(width), Height(height)
{}

Game::~Game()
{
	delete			Renderer,
					Renderer2,
					Player,
					Ball,
					LeftBoundary,
					RightBoundary,
					BottomBoundary,
					TopBoundary,
					Lives,
					LivesNumber,
					GameOver,
					Score,
					Tenth,
					Ones,
					CollisionDetector,
					View,
					GameLight,
					PowerUp,
					Background;
}

void Game::init()
{
	isRunning = true;
#pragma region
	projection = glm::perspective(glm::radians(45.0f), static_cast<GLfloat>(Width) / static_cast<GLfloat>(Height), 0.1f, 1600.0f);
	projection2 = glm::ortho(0.0f, static_cast<GLfloat>(Width), static_cast<GLfloat>(Height), 0.0f, -1.0f, 1.0f);
	// Create & Configure shaders
	Game::CreateShaders();
	// Load all textures
	Game::CreateTextures();
#pragma endregion **********Shader & Texture Creation**********
	
#pragma region
	// Create levels
	Game::CreateLevels();
#pragma endregion **********Level Creation**********
	
#pragma region
	// Configure game objects
	Game::ConfigureObjects();
#pragma endregion **********GameObject Configuration**********
}

void Game::handleEvents(SDL_Window* window)
{
	//*****************************
	//SDL handled input
	//Any input to the program is done here

	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT)		//Here we will handle the keyboard events
	{
		isRunning = false;
	}

	if (event.type == SDL_WINDOWEVENT)
	{
		ResizeWindow(window);
	}

	if (isGameOver == false)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)		//By pressing...
			{
			case SDLK_q:
				isRunning = false;
				break;
			case SDLK_a:
				movingLeft = true;
				break;
			case SDLK_d:
				movingRight = true;
				break;
			case SDLK_w:
				movingForward = true;
				break;
			case SDLK_s:
				movingBack = true;
				break;
			case SDLK_u:
			{
				if (autoPlay == false)
					autoPlay = true;
				else if (autoPlay == true)
					autoPlay == false;
				break;
			}
			case SDLK_KP_4:
			{
				//update rotation angle, set new front (direction) vector for camera
				angle -= 1.0f;
				camFront = View->GetCameraFront();
				camFront.x = cos(glm::radians(angle));
				camFront.z = sin(glm::radians(angle));
				camFront.y = sin(glm::radians(yAngle));
				View->SetCameraFront(camFront);
				break;
			}
			case SDLK_KP_6:
			{
				angle += 1.0f;
				camFront = View->GetCameraFront();
				camFront.x = cos(glm::radians(angle));
				camFront.z = sin(glm::radians(angle));
				camFront.y = sin(glm::radians(yAngle));
				View->SetCameraFront(camFront);
				break;
			}
			case SDLK_KP_2:
			{
				yAngle -= 1.0f;
				camFront = View->GetCameraFront();
				camFront.x = cos(glm::radians(angle));
				camFront.z = sin(glm::radians(angle));
				camFront.y = sin(glm::radians(yAngle));
				View->SetCameraFront(camFront);
				break;
			}
			case SDLK_KP_8:
			{
				yAngle += 1.0f;
				camFront = View->GetCameraFront();
				camFront.x = cos(glm::radians(angle));
				camFront.z = sin(glm::radians(angle));
				camFront.y = sin(glm::radians(yAngle));
				View->SetCameraFront(camFront);
				break;
			}
			case SDLK_KP_5:
			{
				yAngle = 0.0f;
				angle = -90.0f;
				camFront = View->GetCameraFront();
				camFront.x = cos(glm::radians(angle));
				camFront.z = sin(glm::radians(angle));
				camFront.y = sin(glm::radians(yAngle));
				View->SetCameraFront(camFront);
				camPosition = View->GetCameraPosition();
				camPosition.x = 400.0f;
				camPosition.y = 300.0f;
				camPosition.z = 790.0f;
				View->SetCameraPosition(camPosition);
				lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
				GameLight->SetLightColour(lightColour);
				colourNumber = 0;
				break;
			}
			case SDLK_KP_7:
			{
				yAngle = -23.0f;
				angle = -75.0f;
				camFront = View->GetCameraFront();
				camFront.x = cos(glm::radians(angle));
				camFront.z = sin(glm::radians(angle));
				camFront.y = sin(glm::radians(yAngle));
				View->SetCameraFront(camFront);
				camPosition = View->GetCameraPosition();
				camPosition.x = 150.0f;
				camPosition.y = 600.0f;
				camPosition.z = 750.0f;
				View->SetCameraPosition(camPosition);
				break;
			}
			case SDLK_KP_9:
			{
				yAngle = -23.0f;
				angle = -107.0f;
				camFront = View->GetCameraFront();
				camFront.x = cos(glm::radians(angle));
				camFront.z = sin(glm::radians(angle));
				camFront.y = sin(glm::radians(yAngle));
				View->SetCameraFront(camFront);
				camPosition = View->GetCameraPosition();
				camPosition.x = 650.0f;
				camPosition.y = 600.0f;
				camPosition.z = 750.0f;
				View->SetCameraPosition(camPosition);
				break;
			}
			case SDLK_KP_1:
			{
				yAngle = 5.0f;
				angle = -75.0f;
				camFront = View->GetCameraFront();
				camFront.x = cos(glm::radians(angle));
				camFront.z = sin(glm::radians(angle));
				camFront.y = sin(glm::radians(yAngle));
				View->SetCameraFront(camFront);
				camPosition = View->GetCameraPosition();
				camPosition.x = 100.0f;
				camPosition.y = 200.0f;
				camPosition.z = 790.0f;
				View->SetCameraPosition(camPosition);
				break;
			}
			case SDLK_KP_3:
			{
				yAngle = 5.0f;
				angle = -107.0f;
				camFront = View->GetCameraFront();
				camFront.x = cos(glm::radians(angle));
				camFront.z = sin(glm::radians(angle));
				camFront.y = sin(glm::radians(yAngle));
				View->SetCameraFront(camFront);
				camPosition = View->GetCameraPosition();
				camPosition.x = 650.0f;
				camPosition.y = 200.0f;
				camPosition.z = 790.0f;
				View->SetCameraPosition(camPosition);
				break;
			}
			case SDLK_KP_0:
			{
				if (colourNumber == 0)
				{			
					lightColour = glm::vec3(0.1f, 0.0f, 0.0f);
					GameLight->SetLightColour(lightColour);

					colourNumber++;
				}
				else if (colourNumber == 1)
				{
					lightColour = glm::vec3(1.0f, 1.0f, 0.0f);
					GameLight->SetLightColour(lightColour);
					colourNumber++;
				}
				else if (colourNumber == 2)
				{
					lightColour = glm::vec3(1.0f, 0.0f, 1.0f);
					GameLight->SetLightColour(lightColour);
					colourNumber++;
				}
				else if (colourNumber == 3)
				{
					lightColour = glm::vec3(0.0f, 1.0f, 1.0f);
					GameLight->SetLightColour(lightColour);
					colourNumber++;
				}
				else if (colourNumber == 4)
				{
					lightColour = glm::vec3(0.0f, 0.0f, 1.0f);
					GameLight->SetLightColour(lightColour);
					colourNumber++;
				}
				else if (colourNumber == 5)
				{
					lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
					GameLight->SetLightColour(lightColour);
					colourNumber = 0;
				}
				break;
			}
			case SDLK_m:
			{
				if (mouseEnabled == false)
				{
					mouseEnabled = true;
					SDL_ShowCursor(SDL_DISABLE);
				}
				else if (mouseEnabled == true)
				{
					mouseEnabled = false;
					SDL_ShowCursor(SDL_ENABLE);
				}
				break;
			}
			case SDLK_SPACE:
			{
				SDL_Log("Game Started!");
				gameStarted = true;
				Ball->Stuck = false;
				break;
			}
			case SDLK_UP:
				if (!gameStarted)
				{
					if (LevelNumber == 4)
						LevelNumber = 1;
					else
						LevelNumber++;

					ChangeLevel();
				}
				break;
			case SDLK_DOWN:
				if (!gameStarted)
				{
					if (LevelNumber == 1)
						LevelNumber = 4;
					else
						LevelNumber--;

					ChangeLevel();
				}
				break;
			case SDLK_LEFT:	
			{		
				lightPosition = GameLight->GetlightDirection();

				lightPosition.y -= 10.01f;
				if (lightPosition.y < -500.0f)
					lightPosition.y = -500.0f;	
				GameLight->SetLightDirection(lightPosition);
				break;
			}
			case SDLK_RIGHT:
			{
				lightPosition = GameLight->GetlightDirection();

				lightPosition.y += 10.01f;
				if (lightPosition.y > 800.0f)
					lightPosition.y = 800.0f;
				GameLight->SetLightDirection(lightPosition);
				break;
			}
			default:
				break;
			}
		}

		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_a)
				movingLeft = false;
			else if (event.key.keysym.sym == SDLK_d)
				movingRight = false;
			else if (event.key.keysym.sym == SDLK_w)
				movingForward = false;
			else if (event.key.keysym.sym == SDLK_s)
				movingBack = false;
		}

		if (mouseEnabled)
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)				
					Ball->Stuck = false;			
			}
		}
		if (event.type == SDL_MOUSEMOTION)
			mouseX = event.motion.x;
	}

	else if (isGameOver == true)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)		//By pressing...
			{
			case SDLK_q:
			{
				isRunning = false;		// The isRunning Boolean will turn false and the next time the game refreshes it will then exit.
				break;
			}
			case SDLK_r:
			{
				isGameOver = false;
				numberOfLives = 3;

				tex = IMG_Load("../content/Texts/Lives/3Text.png");
				AssetController::GetTexture("livesNumberText").Generate(tex);
				SDL_FreeSurface(tex);

				tex = IMG_Load("../content/Texts/GameOver.png");
				AssetController::GetTexture("GameOver").Generate(tex);
				SDL_FreeSurface(tex);

				ChangeLevel();
				break;
			}
			default:
				break;
			}
		}
	}
}

void Game::update(GLfloat deltaTime)
{
	GLfloat velocity = playerSpeed * deltaTime;
	GLfloat powerupVelocity = powerupspeed *deltaTime;

	cameraMatrix = View->GetViewMatrix();

	lightPosition = Player->Position;
	lightPosition.x = lightPosition.x + Player->Size.x / 2;
	GameLight->SetLightPosition(lightPosition);

	// Debug purposes
	/*if (temp != colourNumber)
	{
		std::cout << "colourNumber: " << colourNumber << std::endl;
		temp = colourNumber;
	}*/

	// Change ball colour
	if (changeBallColour)
	{
		srand(time(NULL));
		int randNum = rand() % 90 + 10;
		int randNum2 = rand() % 90 + 10;
		int randNum3 = rand() % 90 + 10;
		cout << randNum << endl;
		Ball->Colour = glm::vec3(float(randNum) / 100, float(randNum2) / 100, float(randNum3) / 100);
		changeBallColour = false;
	}

	// If the player scores / hits a block...
	if (score != this->Levels[Level].newScore)
	{
		score = this->Levels[Level].newScore;
		std::cout << "Score: " << this->Levels[Level].newScore << std::endl;

		if (score % PowerUpSpawnCount == 0)
		{
			SpawnPowerUp();
			powerupSpawned = true;
		}	

		if (score % 5 == 0)
		{
			changeBallColour = true;
		}

		shakeCam = 1;

		// Changes the balls speed depending on the players score.
		if (Ball->Velocity.y < 500.f)
			Ball->Velocity.y = Ball->Velocity.y + (this->Levels[Level].newScore * 1.5f);

		if (score % 10 == 0)
		{
			switch (score)
			{
			case 10:
			{
				tex = IMG_Load("../content/Texts/Score/1Score.png");
				AssetController::GetTexture("Tenth").Generate(tex);
				SDL_FreeSurface(tex);
				scoreSeparator = 10;
				break;
			}
			case 20:
			{
				tex = IMG_Load("../content/Texts/Score/2Score.png");
				AssetController::GetTexture("Tenth").Generate(tex);
				SDL_FreeSurface(tex);
				scoreSeparator = 20;
				break;
			}
			case 30:
			{
				tex = IMG_Load("../content/Texts/Score/3Score.png");
				AssetController::GetTexture("Tenth").Generate(tex);
				SDL_FreeSurface(tex);
				scoreSeparator = 30;
				break;
			}
			case 40:
			{
				tex = IMG_Load("../content/Texts/Score/4Score.png");
				AssetController::GetTexture("Tenth").Generate(tex);
				SDL_FreeSurface(tex);
				scoreSeparator = 40;
				break;
			}
			case 50:
			{
				tex = IMG_Load("../content/Texts/Score/5Score.png");
				AssetController::GetTexture("Tenth").Generate(tex);
				SDL_FreeSurface(tex);
				scoreSeparator = 50;
				break;
			}
			case 60:
			{
				tex = IMG_Load("../content/Texts/Score/6Score.png");
				AssetController::GetTexture("Tenth").Generate(tex);
				SDL_FreeSurface(tex);
				scoreSeparator = 60;
				break;
			}
			case 70:
			{
				tex = IMG_Load("../content/Texts/Score/7Score.png");
				AssetController::GetTexture("Tenth").Generate(tex);
				SDL_FreeSurface(tex);
				scoreSeparator = 70;
				break;
			}
			default:
				break;
			}
		}

		switch (score - scoreSeparator)
		{
		case 0:
		{
			tex = IMG_Load("../content/Texts/Score/0Score.png");
			AssetController::GetTexture("Ones").Generate(tex);
			SDL_FreeSurface(tex);
			break;
		}
		case 1:
		{
			tex = IMG_Load("../content/Texts/Score/1Score.png");
			AssetController::GetTexture("Ones").Generate(tex);
			SDL_FreeSurface(tex);
			break;
		}
		case 2:
		{
			tex = IMG_Load("../content/Texts/Score/2Score.png");
			AssetController::GetTexture("Ones").Generate(tex);
			SDL_FreeSurface(tex);
			break;
		}
		case 3:
		{
			tex = IMG_Load("../content/Texts/Score/3Score.png");
			AssetController::GetTexture("Ones").Generate(tex);
			SDL_FreeSurface(tex);
			break;
		}
		case 4:
		{
			tex = IMG_Load("../content/Texts/Score/4Score.png");
			AssetController::GetTexture("Ones").Generate(tex);
			SDL_FreeSurface(tex);
			break;
		}
		case 5:
		{
			tex = IMG_Load("../content/Texts/Score/5Score.png");
			AssetController::GetTexture("Ones").Generate(tex);
			SDL_FreeSurface(tex);
			break;
		}
		case 6:
		{
			tex = IMG_Load("../content/Texts/Score/6Score.png");
			AssetController::GetTexture("Ones").Generate(tex);
			SDL_FreeSurface(tex);
			break;
		}
		case 7:
		{
			tex = IMG_Load("../content/Texts/Score/7Score.png");
			AssetController::GetTexture("Ones").Generate(tex);
			SDL_FreeSurface(tex);
			break;
		}
		case 8:
		{
			tex = IMG_Load("../content/Texts/Score/8Score.png");
			AssetController::GetTexture("Ones").Generate(tex);
			SDL_FreeSurface(tex);
			break;
		}
		case 9:
		{
			tex = IMG_Load("../content/Texts/Score/9Score.png");
			AssetController::GetTexture("Ones").Generate(tex);
			SDL_FreeSurface(tex);
			break;
		}
	defualt:
		break;
		}
	}

	// Camera Shake
	if ((shakeCam == 1) || (shakeCam == 2) || (shakeCam == 3))
	{
		camShake = View->GetCameraFront();
		float shakeSpeed = 0.4f;					// Shake speed I like:	strong :	0.6,   
		float down = shakeSpeed * -2;				//						medium:		0.4,
		float up = shakeSpeed * 2;					//						soft:		0.2,

		if (shakeCam == 1)
		{
			if (yAngle > down)
			{
				yAngle -= shakeSpeed;
				camFront = View->GetCameraFront();
				camFront.x = cos(glm::radians(angle));
				camFront.z = sin(glm::radians(angle));
				camFront.y = sin(glm::radians(yAngle));
				View->SetCameraFront(camFront);
				if(yAngle <= down)
					shakeCam = 2;
			}
		}
		else if (shakeCam == 2)
		{
			if (yAngle < up)
			{
				yAngle += shakeSpeed;
				camFront = View->GetCameraFront();
				camFront.x = cos(glm::radians(angle));
				camFront.z = sin(glm::radians(angle));
				camFront.y = sin(glm::radians(yAngle));
				View->SetCameraFront(camFront);
				if (yAngle >= up)
					shakeCam = 3;
			}
		}
		else if (shakeCam == 3)
		{
			if (yAngle != 0.0f)
			{
				yAngle -= shakeSpeed;
				camFront = View->GetCameraFront();
				camFront.x = cos(glm::radians(angle));
				camFront.z = sin(glm::radians(angle));
				camFront.y = sin(glm::radians(yAngle));
				View->SetCameraFront(camFront);
				if (yAngle < 0.0f)
				{
					shakeCam = 0;
					yAngle = 0;
				}
			}
		}			
	}

	ManagePowerUp(powerupVelocity);

	// Update Players Position
	if (movingLeft)
	{
		if (Player->Position.x >= 0)
		{
			Player->Position.x -= velocity;
			if (Ball->Stuck)
				Ball->Position.x -= velocity;

			camPosition = View->GetCameraPosition();
			camPosition.x -= velocity / 6;
			View->SetCameraPosition(camPosition);
		}
	}
	else if (movingRight)
	{
		if (Player->Position.x <= this->Width - Player->Size.x)
		{
			Player->Position.x += velocity;
			if (Ball->Stuck)
				Ball->Position.x += velocity;

			camPosition = View->GetCameraPosition();
			camPosition.x += velocity / 6;
			View->SetCameraPosition(camPosition);
		}
	}
	
	// Camera update moving in and out
	else if (movingForward)
	{
			camPosition = View->GetCameraPosition();
			camPosition.z -= velocity / 6;
			if (camPosition.z >= 800.0f)
				View->SetCameraPosition(camPosition);
			else if (camPosition.z < 800.0f)
				camPosition.z = 800.0f;
	}
	else if (movingBack)
	{
		camPosition = View->GetCameraPosition();
		camPosition.z += velocity / 6;
		if (camPosition.z <= 900.0f)
			View->SetCameraPosition(camPosition);
		else
			camPosition.z = 900.0f;
	}

	// Check for any collisions
	Ball->Move(deltaTime, this->Width);

	Levels = CollisionDetector->CollisionController(Player, Ball, Levels, Level, ballSpeed);

	if (Ball->Position.y >= this->Height)		// If the ball reaches the bottom edge..	
		this->LoseLife();					// The level, player and ball will all reset.	

	// Here we will check whether the mouse is enabled, if it is then the players position on the x axis becomes the mouse position on the x axis
	if (mouseEnabled)
	{
		if (mouseX > (this->Width - 100))
			mouseX = this->Width - 100;

		Player->Position.x = mouseX;
		if (Ball->Stuck)
			Ball->Position.x = Player->Position.x + 37;

		camPosition = View->GetCameraPosition();
		camPosition.x = mouseX;
		View->SetCameraPosition(camPosition);
	}

	GameAutoPlay(autoPlay);
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	View->Draw();
	GameLight->Draw();
	Background->Draw(cameraMatrix);
	Player->Draw(*Renderer);
	PowerUp->Draw(*Renderer);
	LeftBoundary->Draw(*Renderer);
	RightBoundary->Draw(*Renderer);
	TopBoundary->Draw(*Renderer);
	BottomBoundary->Draw(*Renderer);
	this->Levels[this->Level].Draw(*Renderer);
	Ball->Draw(*Renderer);
	Lives->Draw(*Renderer2);
	LivesNumber->Draw(*Renderer2);
	Score->Draw(*Renderer2);
	Tenth->Draw(*Renderer2);
	Ones->Draw(*Renderer2);
	GameOver->Draw(*Renderer2);
}

#pragma region
void Game::LoseLife()
{
	gameStarted = false;

	// Reset player and ball to exact starting position
	Player->Size = playerSize;
	Player->Position = glm::vec3(this->Width / 2 - playerSize.x / 2, this->Height - playerSize.y, 0);
	Ball->Reset(Player->Position + glm::vec3(playerSize.x / 2 - ballSize, -(ballSize * 2), 0), ballSpeed);

	camPosition = View->GetCameraPosition();
	camPosition.x = 400.0f;
	View->SetCameraPosition(camPosition);

	// Take away a life
	numberOfLives--;
	
	if (numberOfLives >= 0)
	{
		switch (numberOfLives)
		{
			case 3:
			{
				tex = IMG_Load("../content/Texts/Lives/3Text.png");
				AssetController::GetTexture("livesNumberText").Generate(tex);
				SDL_FreeSurface(tex);
				break;
			}
			case 2:
			{
				std::cout << "2 Lives Remaining..." << std::endl;
				tex = IMG_Load("../content/Texts/Lives/2Text.png");
				AssetController::GetTexture("livesNumberText").Generate(tex);
				SDL_FreeSurface(tex);
				break;
			}
			case 1:
			{
				std::cout << "1 Life Remaining..." << std::endl;
				tex = IMG_Load("../content/Texts/Lives/1Text.png");
				AssetController::GetTexture("livesNumberText").Generate(tex);
				SDL_FreeSurface(tex);
				break;
			}
			case 0: 
			{
				SDL_Log("Game Over!");
				isGameOver = true;

				tex = IMG_Load("../content/Texts/_GameOver.png");
				AssetController::GetTexture("GameOver").Generate(tex);
				SDL_FreeSurface(tex);

				tex = IMG_Load("../content/Texts/Lives/0Text.png");
				AssetController::GetTexture("livesNumberText").Generate(tex);
				SDL_FreeSurface(tex);
				break;
			}
			default:
				break;
		}
	}
}

void Game::ChangeLevel()
{
	gameStarted = false;
	this->Levels[Level].newScore = 0;
	this->Level = LevelNumber - 1;

	camPosition = View->GetCameraPosition();
	camPosition.x = 400.0f;
	View->SetCameraPosition(camPosition);

	tex = IMG_Load("../content/Texts/Score/0Score.png");
	AssetController::GetTexture("Tenth").Generate(tex);
	SDL_FreeSurface(tex);

	tex = IMG_Load("../content/Texts/Score/0Score.png");
	AssetController::GetTexture("Ones").Generate(tex);
	SDL_FreeSurface(tex);

	switch (this->Level)
	{
	case 0:
	{
		std::cout << "Loading level 1" << std::endl;
		this->Levels[0].Load("1", this->Width, this->Height * 0.5f);
		break;
	}
	case 1:
	{
		std::cout << "Loading level 2" << std::endl;
		this->Levels[1].Load("2", this->Width, this->Height * 0.5f);
		break;
	}
	case 2:
	{
		std::cout << "Loading level 3" << std::endl;
		this->Levels[2].Load("3", this->Width, this->Height * 0.5f);
		break;
	}
	case 3:
	{
		std::cout << "Loading level 4" << std::endl;
		this->Levels[3].Load("4", this->Width, this->Height * 0.5f);
		break;
	}
	default:
		break;
	}

	// Reset player and ball to exact starting position
	Player->Size = playerSize;
	Player->Position = glm::vec3(this->Width / 2 - playerSize.x / 2, this->Height - playerSize.y, zAxis);
	Ball->Reset(Player->Position + glm::vec3(playerSize.x / 2 - ballSize, -(ballSize * 2), zAxis), ballSpeed);
}
#pragma endregion ******************Reset Level******************

#pragma region
void Game::CreateShaders()
{
	AssetController::LoadShader("lighting", "light");
	AssetController::LoadShader("sprite", "sprite");
	AssetController::LoadShader("skybox", "skybox");
	AssetController::GetShader("light").Use().SetInteger("tex", 0);
	AssetController::GetShader("light").SetMatrix4("projection", projection);
	AssetController::GetShader("sprite").Use().SetInteger("tex", 0);
	AssetController::GetShader("sprite").SetMatrix4("projection", projection2);
	AssetController::GetShader("skybox").Use().SetInteger("skybox", 0);
	AssetController::GetShader("skybox").SetMatrix4("projection", projection);
}

void Game::CreateTextures()
{
	AssetController::LoadTexture("Boundary.png", "boundary");
	AssetController::LoadTexture("LaserBall.png", "ball");
	AssetController::LoadTexture("Crate.jpg", "snowblock");
	AssetController::LoadTexture("Steel.jpg", "ice");
	AssetController::LoadTexture("Paddle.jpg", "paddle");
	AssetController::LoadTexture("PowerUpInv.png", "powerup");
	AssetController::LoadTexture("Texts/Lives/LivesText.png", "livesText");
	AssetController::LoadTexture("Texts/Lives/3Text.png", "livesNumberText");
	AssetController::LoadTexture("Texts/GameOver.png", "GameOver");
	AssetController::LoadTexture("Texts/Score/ScoreText.png", "Score");
	AssetController::LoadTexture("Texts/Score/0Score.png", "Tenth");
	AssetController::LoadTexture("Texts/Score/0Score.png", "Ones");

	Renderer = new Sprite(AssetController::GetShader("light"));
	Renderer2 = new Sprite(AssetController::GetShader("sprite"));
	View = new Camera(AssetController::GetShader("light"));
	GameLight = new Light(AssetController::GetShader("light"));
	Background = new Cubemap(AssetController::GetShader("skybox"));
}

void Game::CreateLevels()
{
	// Read the level files
	LevelController one;	one.Load("1", this->Width, this->Height * 0.5);		this->Levels.push_back(one);
	LevelController two;	two.Load("2", this->Width, this->Height * 0.5);		this->Levels.push_back(two);
	LevelController three;	three.Load("3", this->Width, this->Height * 0.5);	this->Levels.push_back(three);
	LevelController four;	four.Load("4", this->Width, this->Height * 0.5);	this->Levels.push_back(four);
	// Load the chosen level
	this->Level = LevelNumber - 1;
}

void Game::ConfigureObjects()
{
				// max width 800, max height 600
	glm::vec3	playerPos = glm::vec3(400 - playerSize.x / 2, 600 - playerSize.y, zAxis),
				ballPos = playerPos + glm::vec3(playerSize.x / 2 - ballSize, -ballSize * 2, zAxis),
				ppUpPos	= glm::vec3(this->Width / 2, this->Height / 2, zAxis),
				livesPos = glm::vec3(40, this->Height - 450, zAxis),
				livesNumberPos = glm::vec3(livesPos.x + livesTextSize.x + 10, livesPos.y - 15, zAxis),
				GameOverPos = glm::vec3(livesTextSize.x + 20, livesPos.y + 160, zAxis),
				ScorePos = glm::vec3(this->Width - 300, livesPos.y, zAxis),
				TenthPos = glm::vec3((ScorePos.x + ScoreTextSize.x) + 12.5, livesPos.y + 2.5, zAxis),
				OnesPos = glm::vec3((ScorePos.x + ScoreTextSize.x + TenthTextSize.x) + 10, livesPos.y + 2.5, zAxis);

	Player = new GameObject(playerPos, playerSize, AssetController::GetTexture("paddle"));
	Ball = new SnowBall(ballPos, ballSize, ballSpeed, AssetController::GetTexture("ball"));
	PowerUp = new GameObject(ppUpPos, powerUpSize, AssetController::GetTexture("powerup"));
	LeftBoundary = new GameObject(glm::vec3(-50, 0, zAxis), lrBoundarySize, AssetController::GetTexture("boundary"));
	RightBoundary = new GameObject(glm::vec3(this->Width, 0, zAxis), lrBoundarySize, AssetController::GetTexture("boundary"));
	TopBoundary = new GameObject(glm::vec3(-50, -50, zAxis), tbBoundarySize, AssetController::GetTexture("boundary"));
	BottomBoundary = new GameObject(glm::vec3(-50, 600, zAxis), tbBoundarySize, AssetController::GetTexture("boundary"));
	Lives = new GameObject(livesPos, livesTextSize, AssetController::GetTexture("livesText"));
	LivesNumber = new GameObject(livesNumberPos, livesNumberTextSize, AssetController::GetTexture("livesNumberText"));
	GameOver = new GameObject(GameOverPos, GameOverTextSize, AssetController::GetTexture("GameOver"));
	Score = new GameObject(ScorePos, ScoreTextSize, AssetController::GetTexture("Score"));
	Tenth = new GameObject(TenthPos, TenthTextSize, AssetController::GetTexture("Tenth"));
	Ones = new GameObject(OnesPos, OnesTextSize, AssetController::GetTexture("Ones"));

	Ball->Colour = glm::vec3(0.7f, 0.8f, 0.9f);
}
#pragma endregion ******************Object Creation & Configuation******************

void Game::ResizeWindow(SDL_Window* window)
{
	GLint	w, 
			h;

	SDL_GetWindowSize(window, &w, &h);
	if (trueFullscreen == false)
	{
		GLint	trueWidth = w,
				trueHeight = h;

		if (w > ((h / 3) * 4))
			w = ((h / 3) * 4);

		if (h > ((w / 4) * 3))
			h = ((w / 4) * 3);

		glViewport(((trueWidth - w) / 2), ((trueHeight - h) / 2), w, h);
	}
	else if (trueFullscreen == true)
		glViewport(0, 0, w, h);
}

void Game::SpawnPowerUp()
{
	PowerUp->Position = Ball->Position;
	srand(time(NULL));
	rNumber = rand() % 5 + 1;

	switch (rNumber)
	{
	case 1:
	{
		tex = IMG_Load("../content/PowerUpSize.jpg");
		AssetController::GetTexture("powerup").Generate(tex);
		SDL_FreeSurface(tex);

		PowerUp->Colour = glm::vec3(0.1f, 0.8f, 0.6f);
		break;
	}
	case 2:
	{
		tex = IMG_Load("../content/PowerUpSlowBall.jpg");
		AssetController::GetTexture("powerup").Generate(tex);
		SDL_FreeSurface(tex);

		PowerUp->Colour = glm::vec3(0.9f, 0.3f, 0.6f);
		break;
	}
	case 3:
	{
		tex = IMG_Load("../content/PowerUpLives.jpg");
		AssetController::GetTexture("powerup").Generate(tex);
		SDL_FreeSurface(tex);

		PowerUp->Colour = glm::vec3(0.9f, 0.3f, 0.3f);
		break;
	}
	case 4:
	{
		tex = IMG_Load("../content/PowerUpSize.jpg");
		AssetController::GetTexture("powerup").Generate(tex);
		SDL_FreeSurface(tex);

		PowerUp->Colour = glm::vec3(0.5f, 0.2f, 0.6f);
		break;
	}
	case 5:
	{
		tex = IMG_Load("../content/PowerUpBlack.jpg");
		AssetController::GetTexture("powerup").Generate(tex);
		SDL_FreeSurface(tex);

		PowerUp->Colour = glm::vec3(0.7f, 0.8f, 0.9f);
		break;
	}
	default:
		break;
	}
}

void Game::ManagePowerUp(GLfloat powerupVelocity)
{
	if (powerupSpawned)
	{
		PowerUp->Position.y += powerupVelocity;

		if (((PowerUp->Position.x + PowerUp->Size.x) > Player->Position.x) && (PowerUp->Position.x < (Player->Position.x + Player->Size.x)))
		{
			if (((PowerUp->Position.y + PowerUp->Size.y) > Player->Position.y) && (PowerUp->Position.y < (Player->Position.y + Player->Size.y)))
			{
				powerupSpawned = false;
				powerupActivated = true;

				switch (rNumber)
				{
				case 1:
				{
					cout << "Powerup Caught: Player Size Increased! " << endl;
					Player->Size.x = 150;
					break;
				}
				case 2:
				{
					cout << "Powerup Caught: Ball Velocity Decreased! " << endl;
					Ball->Velocity.y = Ball->Velocity.y / 2;
					break;
				}
				case 3:
				{
					if (numberOfLives < 3)
					{
						cout << "Powerup Caught: One Life Added! " << endl;
						numberOfLives += 1;
					}

					switch (numberOfLives)
					{
					case 3:
					{
						tex = IMG_Load("../content/Texts/Lives/3Text.png");
						AssetController::GetTexture("livesNumberText").Generate(tex);
						SDL_FreeSurface(tex);
						break;
					}
					case 2:
					{
						std::cout << "2 Lives Remaining..." << std::endl;
						tex = IMG_Load("../content/Texts/Lives/2Text.png");
						AssetController::GetTexture("livesNumberText").Generate(tex);
						SDL_FreeSurface(tex);
						break;
					}
					default:
						break;
					}
					break;
				}
				case 4:
				{
					cout << "Powerup Caught: Player Size Decreased! " << endl;
					Player->Size.x = 75;
					break;
				}
				case 5:
				{
					cout << "Powerup Caught: Darkness! " << endl;
					fifthPowerUp = true;
					break;
				}
				default:
					break;
				}

				startTime = SDL_GetTicks() / 1000;
			}
		}

		if (PowerUp->Position.y > this->Height)
		{
			powerupSpawned = false;
		}
	}
	else
	{
		tex = IMG_Load("../content/PowerUpInv.png");
		AssetController::GetTexture("powerup").Generate(tex);
		SDL_FreeSurface(tex);

		PowerUp->Position = glm::vec3(-100, this->Height / 2, zAxis);
	}

	if (fifthPowerUp)
	{
		lightColour = glm::vec3(0.1f, 0.0f, 0.0f);
		GameLight->SetLightColour(lightColour);
	}

	if (powerupActivated)
	{
		currentTime = SDL_GetTicks() / 1000 - startTime;

		if (currentTime >= 7)
		{
			switch (rNumber)
			{
			case 1:
			{
				Player->Size.x = 100;
				powerupActivated = false;
				break;
			}
			case 2:
			{
				Ball->Velocity.y = Ball->Velocity.y * 2;
				powerupActivated = false;
				break;
			}
			case 4:
			{
				Player->Size.x = 100;
				powerupActivated = false;
				break;
			}
			case 5:
			{
				fifthPowerUp = false;
				lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
				GameLight->SetLightColour(lightColour);
				powerupActivated = false;
				break;
			}
			default:
				break;
			}
			currentTime = 0;
		}
	}
	else if (!powerupActivated)
	{
		if (fifthPowerUp)
		{
			lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
			GameLight->SetLightColour(lightColour);
		}
		fifthPowerUp = false;		
	}
}

void Game::GameAutoPlay(GLboolean autoplay)
{
	if (autoPlay && !gameStarted)
	{
		autoPlay2 = true;
		Ball->Velocity.y = -1100.f;
		Ball->Position.x = Player->Position.x + ((Player->Size.x / 2) - (Ball->Size.x / 2));
	}
	else if (autoPlay == false)
	{
		autoPlay2 = false;
	}

	if (autoPlay2)
	{
		if (gameStarted)
		{
			if (score > 0)
			{
				if (score % 2 == 0)
				{
					autoPilot = 15.f;
					autoPlayClick = false;
				}
				else if (score % 2 == 1)
				{
					autoPilot = -85.f;
					autoPlayClick = false;
				}
			}
			else
				autoPilot = 0.f;

			if (!autoPlayClick)
			{
				if (Player->Position.x <= Ball->Position.x + autoPilot)
				{
					movingLeft = false;
					movingRight = true;

					if (((int)Player->Position.x <= (int)Ball->Position.x + autoPilot + 2) && ((int)Player->Position.x >= (int)Ball->Position.x + autoPilot - 2))					
						autoPlayClick = true;					
				}
				else if (Player->Position.x >= Ball->Position.x + autoPilot)
				{
					movingRight = false;
					movingLeft = true;

					if (((int)Player->Position.x <= (int)Ball->Position.x + autoPilot + 2) && ((int)Player->Position.x >= (int)Ball->Position.x + autoPilot - 2))					
						autoPlayClick = true;					
				}
			}
			if (autoPlayClick)
			{
				Player->Position.x = Ball->Position.x + autoPilot;
				movingRight = false;
				movingLeft = false;
			}
		}
	}
}