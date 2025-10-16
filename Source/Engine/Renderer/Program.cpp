#include "EnginePCH.h"
#include "Program.h"

neu::Program::Program()
{
	m_program = glCreateProgram();
}

neu::Program::~Program()
{
	if (m_program) glDeleteProgram(m_program);
}

void neu::Program::AttachShader(const res_t<Shader>& shader)
{
	glAttachShader(m_program, shader->m_shader);
}

bool neu::Program::Link()
{
	glLinkProgram(m_program);

	GLint success = false;
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		std::string infoLog(512, '\0');  // pre-allocate space
		GLsizei length;
		glGetProgramInfoLog(m_program, (GLsizei)infoLog.size(), &length, &infoLog[0]);
		infoLog.resize(length);

		LOG_WARNING("Program link failed: {}", infoLog);

		glDeleteProgram(m_program);
		m_program = 0;

		return false;
	}

	return true;
}

void neu::Program::Use()
{
	glUseProgram(m_program);
}

void neu::Program::SetUniform(const std::string& name, float value)
{
	GLint location = GetUniformLocation(name);
	if (location != -1) glUniform1f(location, value);
}

void neu::Program::SetUniform(const std::string& name, int value)
{
	GLint location = GetUniformLocation(name);
	if (location != -1) glUniform1i(location, value);
}

void neu::Program::SetUniform(const std::string& name, unsigned int value)
{
	GLint location = GetUniformLocation(name);
	if (location != -1) glUniform1ui(location, value);
}

void neu::Program::SetUniform(const std::string& name, bool value)
{
	GLint location = GetUniformLocation(name);
	if (location != -1) glUniform1i(location, (int)value);
}

void neu::Program::SetUniform(const std::string& name, const neu::vec2& value)
{
	GLint location = GetUniformLocation(name);
	if (location != -1) glUniform2f(location, value.x, value.y);
}

void neu::Program::SetUniform(const std::string& name, const neu::vec3& value)
{
	GLint location = GetUniformLocation(name);
	if (location != -1) glUniform3f(location, value.x, value.y, value.z);
}

GLint neu::Program::GetUniformLocation(const std::string& name)
{
	// find uniform location in map
	auto it = m_uniformLocations.find(name);
	// if not found, get uniform in program
	if (it == m_uniformLocations.end())
	{
		// get uniform in program, return -1 if not found
		GLint location = glGetUniformLocation(m_program, name.c_str());
		if (location == -1)
		{
			LOG_WARNING("Could not find uniform: {}", name);
		}
		m_uniformLocations[name] = location;
	}

	return m_uniformLocations[name];
}


