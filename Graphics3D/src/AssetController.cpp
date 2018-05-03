#include "AssetController.h"

#include <iostream>
#include <sstream>
#include <fstream>

// This is the Asset Manager CPP. This is the source code used to store, sort and apply assets in the game.

// First, we create "Surface Object", using this allows us to load in an image using SDL. 
SDL_Surface* tex;

// Here is where we will store all our textures and shaders.
map<string, Texture> AssetController::Textures;
map<string, Shader> AssetController::Shaders;

// This is used to load a shader in to the program and store the shader.
Shader AssetController::LoadShader(const char *path, string ID)
{
	string		fileName(path),
				vSh = "../src/Shaders/" + fileName + ".vert",
				fSh = "../src/Shaders/" + fileName + ".frag";

	// Here we will add a shader to storage and assign it by passing it on to the load shader method. This will then Load it into the system using the shader class.
	Shaders[ID] = loadShaderFromFile(vSh.c_str(), fSh.c_str());
	// Then we return the shader to the its source.
	return Shaders[ID];
}

//This is used specifically to load a shader from an external source. 
Shader AssetController::loadShaderFromFile(const GLchar *vSh, const GLchar *fSh)
{
	// First, we open the files and retrieve all information from within.
	ifstream			vertexShaderFile(vSh),
						fragmentShaderFile(fSh);
	stringstream		vShStream, 
						fShStream;
	vShStream << vertexShaderFile.rdbuf();
	fShStream << fragmentShaderFile.rdbuf();
	// Now we close the ifstreams as they are no longer needed.
	vertexShaderFile.close(); fragmentShaderFile.close();
	// Then we will create two empty string variables...
	string				vertexCode,
						fragmentCode;
	// And we will convert all streams into strings,
	vertexCode = vShStream.str(); fragmentCode = fShStream.str();
	// then into chars...
	const GLchar		*vShCode = vertexCode.c_str(), 
						*fShCode = fragmentCode.c_str();
	// Then create our shader object...
	Shader shader;
	// And compile our shaders to that shader object.
	shader.Compile(vShCode, fShCode);
	return shader;
}

// This is used to get our shader, this is extremely helpful if we want to add something to our shader.
Shader AssetController::GetShader(string ID)
{
	// Returns the shader.
	return Shaders[ID];
}

// This is used to load a texture in to the program and store it.
Texture AssetController::LoadTexture(const GLchar *path, string ID)
{
	string		fileName(path),
				texture = "../content/" + fileName;

	// Here we will add a texture to storage and assign it by passing it on to the load texture method. This will then Load it into the system using the texture class.
	Textures[ID] = loadTextureFromFile(texture.c_str());
	// Then we return the texture to the its source.
	return Textures[ID];
}

// Here we actually assign the texture.
Texture AssetController::loadTextureFromFile(const GLchar *file)
{
	// We first create a texture object
	Texture texture;
	// The we load the image to a surface
	tex = IMG_Load(file);
	// And we generate our texture, passing the SDL Surface through to the texture class.
	texture.Generate(tex);
	// Finally we free surface image data.
	SDL_FreeSurface(tex);
	// And return the texture to its source
	return texture;
}

// This is used to get our specific texture, this is extremely helpful if we want to replace the image stored within it.
Texture AssetController::GetTexture(string ID)
{
	// Returns the texture.
	return Textures[ID];
}

// This is used to load a texture in to the program and store it.
Texture AssetController::LoadCubeMapTexture(vector<const GLchar*> faces, string env, string ID)
{
	vector<string> textures;

	for (GLuint i = 0; i < faces.size(); i++)
	{
		string	fileName(faces[i]);
				textures.push_back("../content/skybox/" + env + "/" + fileName + ".jpg");
				faces[i] = textures[i].c_str();
	}

	// Here we will add a texture to storage and assign it by passing it on to the load texture method. This will then Load it into the system using the texture class.
	Textures[ID] = loadCubeMapTextureFromFile(faces);

	// Then we return the texture to the its source.
	return Textures[ID];
}

// Here we actually assign the texture.
Texture AssetController::loadCubeMapTextureFromFile(vector<const GLchar*> faces)
{
	// We first create a texture object
	Texture texture;
	// Bind the cubemap texture
	texture.BindCubeMap();

	for (GLuint i = 0; i < faces.size(); i++)
	{
		// The we load the image to a surface
		tex = IMG_Load(faces[i]);
		if (tex)
		{
			// If the data is there then we preceed to generate
			texture.GenerateCubeMap(tex, i);
			SDL_FreeSurface(tex);
		}
		else
		{	
			//If not, then we report the error
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			SDL_FreeSurface(tex);
		}
	}
	// And return the texture to its source
	return texture;
}

// This is used to get our specific texture, this is extremely helpful if we want to replace the image stored within it.
Texture AssetController::GetCubeMapTexture(string ID)
{
	// Returns the texture.
	return Textures[ID];
}


// this is used to clear all the shaders and textures that exist.
void AssetController::Clear()
{	
	// Here we go through each of our stored shaders...
	for (auto x : Shaders)
		// And we delete them and their identity using the glDeleteProgram tool.
		glDeleteProgram(x.second.ID);
	// Here we go through each of our stored textures...
	for (auto y : Textures)
		// And we delete them and their identity using the glDeleteProgram tool.
		glDeleteTextures(1, &y.second.ID);
}