#include "Game.h"
#include "AssetController.h"

#include <iostream>

int main(int argc, char *argv[])
{
	const GLuint	width = 800,
					height = 600;

	GLuint			currentFrame = 0.0f,
					lastFrame = 0.0f;

	GLboolean		restart = true,					// Looping Variables
					programmeRunning = true;					
	
	GLfloat			deltaTime = 0.0f;
	SDL_GLContext	glcontext;

	Game Breakout(width, height);

		#pragma region
			// **********SDL initialise**********
			if (SDL_Init(SDL_INIT_EVERYTHING) != 0)			
				SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s\n", SDL_GetError());
			
			SDL_Log("SDL initialised OK!\n");

			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());

			// **********Window Creation - modified for OpenGL**********
			SDL_Window *window = nullptr;
			window = SDL_CreateWindow("Interstellar BreakOut! - By Christopher Ross ROS16626280 - CMP2012M Graphics Assessment Item 2", 100, 100, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
			
			if (window == nullptr)			
				SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow init error: %s\n", SDL_GetError());
		
			// **********Window Modification**********

			SDL_DisplayMode displayMode;
			SDL_GetCurrentDisplayMode(0, &displayMode);
			int SetWidth = displayMode.w;
			int SetHeight = displayMode.h;
			SDL_SetWindowSize(window, SetWidth / 2, SetHeight / 2);
			SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

			//Initialize SDL_ttf
			if (TTF_Init() == -1)		
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			
			// **********OpenGL Context Creation - associated with the window**********
			glcontext = SDL_GL_CreateContext(window);	// Pointer(*) called glcontext of type SDL_GLContext
														
			// **********OpenGL Alpha Creation - telling OPenGL how to blend alpha into the image**********
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// **********OpenGL specific values - OpenGL calls**********
			GLenum err = glewInit();

		#pragma endregion **********SDL/OpenGL initialisation**********

		Breakout.init();							// Give our game its title.

		while (Breakout.running())				// Game is now running. Can be restarted by breaking out of this loop.
		{
			GLfloat currentFrame = SDL_GetTicks();	// CurrentTime is the amount of seconds since initialisation.
			deltaTime = (currentFrame - lastFrame) / 1000.0f;			// Get DeltaTime from both the currentFrame minus the LastFrame
			lastFrame = currentFrame;						// Frametime is the current time minus the last frame.

			Breakout.handleEvents(window);							// Event menu has been intiated to watch for events. keyboard or 'x' button.
			Breakout.update(deltaTime);									// the update function where the main functions happen.
			
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			// Background Colour

			Breakout.render();									// render the content to the screen.

			SDL_GL_SwapWindow(window);
		}
	
	// *************Clean up*************
	// Delete all resources as loaded using the resource manager
	AssetController::Clear();
	SDL_Log("Finished. Cleaning up and closing down\n");
	// Once finished with OpenGL functions, the SDL_GLContext can be deleted.
	SDL_GL_DeleteContext(glcontext);
	// Quit
	SDL_Quit();

	return 0;
}