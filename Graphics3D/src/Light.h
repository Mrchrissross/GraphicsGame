#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// This is the Camera Class, this will control everything to do will the camera and position within the world space.
class Light
{
private:
	// First of all we need to create a shader object as the camera will not work without the shader.
	Shader		shader;
	// These vector's will control every aspect of the camera's postion.
	glm::vec3   lightPosition,
				lightDirection,
				lightColour;				

	// Default constructor
	void defaultNew()
	{
		// As the light is created these default variables will be assigned...
		lightPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		lightDirection = glm::vec3(400.0f, -200.0f, 0.0f);
		lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
	}

public:
	// Constructors
	Light() { defaultNew(); }
	Light(Shader &shader) { this->shader = shader; defaultNew(); }

	// Here are the get functions, which allow us to easy get the camera's current position ready to be updated.
	glm::vec3 GetLightPosition() const { return lightPosition; }
	glm::vec3 GetlightColour() const { return lightColour; }
	glm::vec3 GetlightDirection() const { return lightDirection; }

	// Here are the set functions, this allows us to easily change the light's position within the game's world space.
	void SetLightPosition(glm::vec3 position){ lightPosition = position; }
	void SetLightColour(glm::vec3 colour){ lightColour = colour; }
	void SetLightDirection(glm::vec3 direction) { lightDirection = direction; }

	// Here we draw the shaders which allow our light to work.
	virtual void Draw()
	{
		this->shader.Use();
		this->shader.SetVector3f("lightPosition", lightPosition);
		this->shader.SetVector3f("viewPosition", lightDirection);
		this->shader.SetVector3f("uLightColour", lightColour);
	}
};

// Light Colours:
//light colour setting 
// Candle:  r:1.0 g:0.57 b:0.16 
// 100W bulb: r:1.0 g:0.84 b:0.66 
// direct sunlight: r:1.0 g:1.0 b:0.98