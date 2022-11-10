#pragma once
#include <glew.h>
#include <string>
#include <fstream>
#include "Transform.h"
#include "Camera.h"

using namespace std;


class Shader
{
public:
	Shader(const string FileLocation, Camera& camera);
	~Shader();

	void Update(Transform& transform);
	void Bind();

	static GLuint CreateShader(const string& ShaderSource, GLenum shaderType);
	static string LoadShader(const string& fileName);

	GLuint GetProgram()
	{
		return m_Program;
	}

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
		NUM_UNIFORMS
	};

	GLuint m_Uniforms[NUM_UNIFORMS];

	

};

