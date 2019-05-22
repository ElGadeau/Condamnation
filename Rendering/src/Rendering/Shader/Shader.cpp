#include "stdafx.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Rendering/Shader/Shader.h>
#include <Rendering/LowRenderer/Camera.h>
#include <Rendering/LowRenderer/Transform.h>
#include <Rendering/LowRenderer/Light.h>

#include <GL/glew.h>
#include <fstream>
#include <math.h>
#include <sstream>

Rendering::Shaders::Shader::Shader()
{
	shaderProgram = glCreateProgram();
}

Rendering::Shaders::Shader::~Shader()
{
	glDeleteProgram(shaderProgram);
}

void Rendering::Shaders::Shader::Unbind()
{
    glUseProgram(0);
}

GLuint Rendering::Shaders::Shader::CreateShader(const GLuint & p_type, const std::string & p_source)
{

	const char* m_shaderSource = p_source.c_str();
	GLuint m_shaderID = glCreateShader(p_type);

	glShaderSource(m_shaderID, 1, &m_shaderSource, nullptr);
	glCompileShader(m_shaderID);

	int success;
	char infoLog[512];
	glGetShaderInfoLog(m_shaderID, 512, nullptr, infoLog);
	glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		//std::cout << "Error, shader compilation failed\n" << infoLog << std::endl;
	}

	return m_shaderID;
}

std::string Rendering::Shaders::Shader::GetSource(const std::string p_filePath)
{
	std::string code;
	std::ifstream file;
	std::stringstream dataStream;

	try
	{
		file.open(p_filePath);
		dataStream << file.rdbuf();
		code = dataStream.str();
		file.close();
	}
	catch (std::ifstream::failure& exception)
	{
		//std::cout << "Issue occured with specified file\n";
		//std::cout << exception.what() << '\n';

	}

    return code;
}

void Rendering::Shaders::Shader::Load(const std::string & p_Shader, const GLuint& p_type, const std::string & p_pathf, const GLuint& p_typef)
{
	GLuint m_shaderTypeID = CreateShader(p_type, GetSource(p_Shader));
	GLuint m_shaderTypeIDA = CreateShader(p_typef, GetSource(p_pathf));

	glAttachShader(shaderProgram, m_shaderTypeID);
	glAttachShader(shaderProgram, m_shaderTypeIDA);

	glLinkProgram(shaderProgram);

	glDeleteShader(m_shaderTypeID);
	glDeleteShader(m_shaderTypeIDA);

	m_data[0] = glGetUniformLocation(shaderProgram, "ProjectionMatrix");
	m_data[1] = glGetUniformLocation(shaderProgram, "CameraMatrix");
	m_data[2] = glGetUniformLocation(shaderProgram, "ModelMatrix");
	m_data[3] = glGetUniformLocation(shaderProgram, "viewPos");

}

void Rendering::Shaders::Shader::Update(LowRenderer::Camera& cam, Rendering::LowRenderer::Transform& trans, std::vector<Rendering::LowRenderer::Light>& p_lights)
{
	glUniformMatrix4fv(m_data[0], 1, GL_FALSE, glm::value_ptr(cam.GetPerspectiveMatrix()));
	glUniformMatrix4fv(m_data[1], 1, GL_FALSE, glm::value_ptr(cam.GetViewMatrix()));
	glUniformMatrix4fv(m_data[2], 1, GL_FALSE, glm::value_ptr(trans.m_transMat));
	glUniform3f(m_data[3], cam.m_position.x, cam.m_position.y, cam.m_position.z);

    for (int i = 0; i < p_lights.size(); ++i)
    {
        std::string isDirectionnalS = "pointLights[" + std::to_string(i) + "].isDirectionnal";
        std::string intensityS = "pointLights[" + std::to_string(i) + "].intensity";
        std::string positionS = "pointLights[" + std::to_string(i) + "].LightPos";
        std::string colorS = "pointLights[" + std::to_string(i) + "].LightColor";
        std::string lightShader = "lightColor";

        if (trans.GetPosition() == p_lights[i].m_pos)
            glUniform3f(glGetUniformLocation(shaderProgram, lightShader.c_str()), p_lights[i].m_color.x, p_lights[i].m_color.y, p_lights[i].m_color.z);
        
        glUniform1i(glGetUniformLocation(shaderProgram, isDirectionnalS.c_str()), p_lights[i].isDirectionnal);
        glUniform1f(glGetUniformLocation(shaderProgram, intensityS.c_str()), p_lights[i].intensity);
        glUniform3f(glGetUniformLocation(shaderProgram, positionS.c_str()), p_lights[i].m_pos.x, p_lights[i].m_pos.y, p_lights[i].m_pos.z);
        glUniform3f(glGetUniformLocation(shaderProgram, colorS.c_str()), p_lights[i].m_color.x, p_lights[i].m_color.y, p_lights[i].m_color.z);

    }
    
}

void Rendering::Shaders::Shader::ApplyShader()
{
	glUseProgram(shaderProgram);
}
