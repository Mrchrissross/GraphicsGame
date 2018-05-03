#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// This is the Camera Class, this will control everything to do will the camera and position within the world space.
class Camera
{
private:
	// First of all we need to create a shader object as the camera will not work without the shader.
	Shader		shader;
	// These vector's will control every aspect of the camera's postion.
	glm::vec3   cameraFront,
				cameraPosition,
				cameraUp;
	// This is the view matrix which will be used to update the camera's position.
	glm::mat4   viewMatrix;

	// This is used to recompute the view matrix from the camera variables.
	void updateMatrix(){ viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp); }

	// Default constructor
	void defaultNew()
	{
		// As the camera is created these default variables will be assigned...
		cameraPosition = glm::vec3(400.0f, 300.0f, 820.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		// Then updated to the view matrix, to update the camera.
		updateMatrix();
	}

public:
	// Constructors
	Camera() { defaultNew(); }
	Camera(Shader &shader) { this->shader = shader; defaultNew(); }

	// Here are the get functions, which allow us to easy get the camera's current position ready to be updated.
	glm::vec3 GetCameraPosition() const { return cameraPosition; }
	glm::vec3 GetCameraFront() const { return cameraFront; }
	glm::vec3 GetCameraUp() const { return cameraUp; }
	// This can be used to directly get our view matrix to add anything else. This is possible as the view matrix is always up-to-date due to the way we set variables.
	glm::mat4 GetViewMatrix() const { return viewMatrix; }

	// Here are the set functions, this allows us to easily change the camera's position within the game's world space.
	// Note: We call updateMatrix every time a variable is updated.
	void SetCameraPosition(glm::vec3 pos)
	{
		cameraPosition = pos;
		updateMatrix(); 
	}
	// This is where we change the angle of the camera.
	void SetCameraFront(glm::vec3 pos)
	{
		cameraFront = pos;
		cameraFront = glm::normalize(cameraFront);
		updateMatrix();
	}
	void SetCameraUp(glm::vec3 pos)
	{
		cameraUp = pos;
		updateMatrix();
	}

	// Here we draw the shaders whihc allow our camera to work efficiently.
	virtual void Draw()
	{
		this->shader.Use();
		this->shader.SetMatrix4("view", viewMatrix);	
	}
};