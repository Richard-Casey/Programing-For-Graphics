#pragma once
#include <glew.h>
#include <string>
#include <fstream>
#include "Transform.h"
#include "Camera.h"
#include "Lightbase.h"
#include <vector>
#include "Texture.h"
#include <iostream>
#include <stdio.h>

using namespace std;

class Shader
{
public:
	Shader(const string FileLocation, Camera& camera, string& AmbiantLoc, string& DiffuseLoc, string& SpecLoc, string& NormalLoc);
	~Shader();

	void Update(Transform& transform, vector <Lightbase*> lights);
	void Bind();

	static GLuint CreateShader(const string& ShaderSource, GLenum shaderType);
	static string LoadShader(const string& fileName);

	GLuint GetProgram()
	{
		return m_Program;
	}

	GLuint AmbiantTextureID;
	GLuint DiffuseTextureID;
	GLuint SpeculerTextureID;
	GLuint NormalTextureID;

	//GLuint textureID;

private:
	string Name;
	GLuint m_Program;
	Camera* m_Camera;

	enum ShaderTypes
	{
		VERTEX,
		FRAGMENT,
		NUM_SHADER_TYPES
	};

	GLuint m_Shaders[NUM_SHADER_TYPES];

	enum UniformNames
	{
		MODEL_U,
		PROJECTION_U,
		VIEW_U,
		FRAG_LIGHTCOLOR_U,
		FRAG_LIGHTPOS_U,
		FRAG_CAMERAPOS_U,
		NUM_UNIFORMS
	};

	GLuint m_Uniforms[NUM_UNIFORMS];

	string AmbiantLoc;
	string DiffuseLoc;
	string SpecLoc;
	string NormalLoc;

};

