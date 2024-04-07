#include"qtpch.h"
#include"Shader.h"
#include<glad/glad.h>
namespace Quantum {
	Shader::Shader(std::string& vertexSrc, std::string& fragmentSrc)
	{
	//create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//send the vertex shader source code to GL
		//Note that std::string's.c_str is null chracter terminated.
		const GLchar* source = (const GLchar*)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		//compile the verex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			//the maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			//we don't need the shader anymore.
			glDeleteShader(vertexShader);

			//use the infoLog as you see fit.

			//in this simple program. we'll just leave.
			QT_CORE_ERROR("{0}", infoLog.data());
			QT_CORE_ASSERT(false, "Vertex Shader compilation Failed!");
			return;
		}
		//create an empty fragment shader handle.
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//send the fragment shader source code to GL
		//Note that std::string's.c_sr is NULL character terminated.
		source = (const GLchar*)fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		//compile the fragment shader 
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
			
			//the maxLength includes the NULL character.
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			//we don't need the shader source.
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);
			QT_CORE_ERROR("{0}", infoLog.data());
			QT_CORE_ASSERT(false, "Fragment Shader compilation Failed!");
			return;
		}
		//Vertex and Fragment shaders are successfully cimpiled.
		//Now time to link them together into a program.
		//get a program object
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		//Attach our Shaders to our program.
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		//link our progrm
		glLinkProgram(program);

		//Note the different functions have: glGetProgram* Instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			//the maxLength includes the NULL character.
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			//we don't need the program anymore.
			glDeleteProgram(program);
			QT_CORE_ERROR("{0}", infoLog.data());
			QT_CORE_ASSERT(false, "Shader Link Failed!");
			return;

		}
		//don't leak shader either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}
	void Shader::bind() const
	{
		glUseProgram(m_RendererID);
	}
	void Shader::unBind() const
	{
		glUseProgram(0);
	}
}