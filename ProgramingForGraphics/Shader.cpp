#include "Shader.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include "stb_image.h"

using namespace std;

GLuint textureID;

void LoadTexture(string TextureLocation)
{
	int width, height, numComponents;

	unsigned char* ImageData = stbi_load(TextureLocation.c_str(), &width, &height, &numComponents, STBI_rgb_alpha);

	if (ImageData == NULL)
	{
		cerr << "Texture loading failed for the texture: " << TextureLocation << endl;
	}

	GLenum format;
	if (numComponents == 1)
		format = GL_RED;
	if (numComponents == 3)
		format = GL_RGB;
	if (numComponents == 4)
		format = GL_RGBA;

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImageData);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(ImageData);


}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		cerr << errorMessage << "; '" << error << " ' " << endl;
	}

}


Shader::Shader(const string FileLocation, Camera &camera)
{
	m_Camera = &camera;
	Name = FileLocation;
	m_Program = glCreateProgram();

	m_Shaders[VERTEX] = CreateShader(LoadShader(FileLocation + ".vert"), GL_VERTEX_SHADER);
	m_Shaders[FRAGMENT] = CreateShader(LoadShader(FileLocation + ".frag"), GL_FRAGMENT_SHADER);

	for (GLuint i = 0; i < NUM_SHADER_TYPES; i++)
	{
		glAttachShader(m_Program, m_Shaders[i]);
	}

	glLinkProgram(m_Program);
	CheckShaderError(m_Program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(m_Program);
	CheckShaderError(m_Program, GL_VALIDATE_STATUS, true, "Error: Program linking invalid: ");

	m_Uniforms[MODEL_U] =		glGetUniformLocation(m_Program, "model");
	m_Uniforms[PROJECTION_U] =	glGetUniformLocation(m_Program, "projection");
	m_Uniforms[VIEW_U] =		glGetUniformLocation(m_Program, "view");

	for (GLuint i = 0; i < NUM_UNIFORMS; i++)
	{
		if (m_Uniforms[i] == GL_INVALID_INDEX)
			cout << "Shader " << Name << " Uniform invalid index:" << static_cast<UniformNames>(i)
			<< " (Might be optimized out if not used)" << endl;
	}

}


 GLuint Shader::CreateShader(const string& ShaderSource, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		cerr << "Error: Shader creation failed!" << endl;
	}

	//needed to convert from string to const char* which ghShaderSource wants.
	const char* tempSourceCode = ShaderSource.c_str();

	glShaderSource(shader, 1, &tempSourceCode, NULL);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");
	return shader;

}


string Shader::LoadShader(const string& fileName)
{
	ifstream file;
	const char* fileNameChar = fileName.c_str();
	file.open(fileNameChar, ifstream::in);

	string output;
	string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		cerr << "Unable to load shader: " << fileName << endl;
	}
	return output;
}

void Shader::Bind()
{
	glUseProgram(m_Program);
}

void Shader::Update(Transform& transform)
{
	mat4 projection = m_Camera->GetPerspective();
	mat4 view = m_Camera->GetViewMatrix();
	mat4 model = transform.GetModel();

	glUniformMatrix4fv(m_Uniforms[MODEL_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_Uniforms[PROJECTION_U], 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(m_Uniforms[VIEW_U], 1, GL_FALSE, &view[0][0]);
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADER_TYPES; i++)
	{
		glDetachShader(m_Program, m_Shaders[i]);
		glDeleteShader(m_Shaders[i]);
	}
	glDeleteProgram(m_Program);
	
}

