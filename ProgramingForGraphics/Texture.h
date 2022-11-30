#pragma once

#include <glew.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Texture
{
public:
	GLuint GetTextureID()
	{
		return textureID;
	};
	GLuint LoadTexture(string TextureLocation);
private:
	GLuint textureID;
};

