#ifndef ASSET_CONTROLLER_H
#define ASSET_CONTROLLER_H

#include <GL/glew.h>
#include <map>
#include <string>
#include <vector>

#include "ShaderClass.h"
#include "TextureClass.h"

using namespace std;

// This is the header for the Asset controller. This is used to store, sort and apply assets in the game.

class AssetController
{
public:
	// Stores all the shaders and textures
	static std::map<string, Shader> Shaders;
	static std::map<string, Texture> Textures;
	// Here we load the shader program from the input file
	static Shader LoadShader(const char*, string);
	// This allows us get a shader back from storage ready for use.
	static Shader GetShader(string);
	// The same for textures...
	static Texture LoadTexture(const GLchar*, string);
	static Texture GetTexture(string);
	static Texture LoadCubeMapTexture(vector<const GLchar*>, string, string);
	static Texture GetCubeMapTexture(string);
	// This is used to clear up all textures and delete any stored items once the program restarts or ends
	static void Clear();
private:
	// Deconstructor
	AssetController() { }
	// Used to load in a shader from an external source. Information such as a file path is required.
	static Shader loadShaderFromFile(const GLchar*, const GLchar*);
	// Used to load in a texture from an external source. Information such as a file path is required.
	static Texture loadTextureFromFile(const GLchar*);
	static Texture loadCubeMapTextureFromFile(vector<const GLchar*>);
};

#endif