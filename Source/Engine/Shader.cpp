#include "EnginePCH.h"
#include "Shader.h"

neu::Shader::~Shader()
{
	if (m_shader) glDeleteShader(m_shader);
}

bool neu::Shader::Load(const std::string& filename, GLuint shaderType)
{
	std::string source;
	neu::file::ReadTextFile(filename, source);
	const char* source_cstr = source.c_str();

	m_shader = glCreateShader(shaderType);
	glShaderSource(m_shader, 1, &source_cstr, NULL);
	glCompileShader(m_shader);
	GLint success;
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::string infoLog(512, '\0');
		GLsizei length;
		glGetShaderInfoLog(m_shader, (GLsizei)infoLog.size(), &length, &infoLog[0]);
		infoLog.resize(length);
		LOG_WARNING("Shader Compilation failed {}", infoLog);

		glDeleteShader(m_shader);
		return false;
	}
	return true;
}
