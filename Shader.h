#pragma once

#include <GL/glew.h>

#include <stdexcept>
#include <string>

struct Shader
{
private:
	int program = 0, vertex_shader = 0, fragment_shader = 0;
	[[noreturn]] void ShaderError(int shd, std::string const& wht = "")
	{
		char buf[1024];
		GLint mlen = 0;
		glGetShaderInfoLog(shd, sizeof(buf) - 1, &mlen, buf);
		this->~Shader();
		throw std::runtime_error(((wht + buf).c_str()));
	}

public:
	Shader(std::string const& verts, std::string const& pixs)
	{
		char const* vert = verts.c_str();
		char const* pix = pixs.c_str();
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, &vert, nullptr);
		glCompileShader(vertex_shader);
		{
			GLint success = 0;
			glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
			if (success != 1)
				ShaderError(vertex_shader, "vert\n");
		}
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &pix, nullptr);
		glCompileShader(fragment_shader);
		{
			GLint success = 0;
			glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
			if (success != 1)
				ShaderError(fragment_shader, "frag\n");
		}
		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);
		if (program == 0)
			throw std::exception();
	}
	Shader(Shader const&) = delete;
	Shader(Shader&& r) noexcept { *this = std::move(r); }
	Shader& operator=(Shader&& r) noexcept
	{
		this->~Shader();
		program = r.program;
		vertex_shader = r.vertex_shader;
		fragment_shader = r.fragment_shader;
		r.program = r.vertex_shader = r.fragment_shader = 0;
		return *this;
	}
	~Shader()
	{
		if (program != 0)
			glDeleteProgram(program);
		if (vertex_shader != 0)
			glDeleteShader(vertex_shader);
		if (fragment_shader != 0)
			glDeleteShader(fragment_shader);
	}
	void Apply() { glUseProgram(program); }
	static void ApplyDflt() { glUseProgram(0); }
	auto GetUniformLocation(std::string const& v) { return glGetUniformLocation(program, v.c_str()); }
};
