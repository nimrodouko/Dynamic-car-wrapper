#pragma once
#include <glad/glad.h>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class Shader {
public:
	unsigned int ID;
	Shader(const char* vertexpath, const char* fragmentpath) {
		std::string vertexcode;
		std::string fragmentcode;
		std::ifstream vshaderfile;
		std::ifstream fshaderfile;


		vshaderfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fshaderfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vshaderfile.open(vertexpath);
			fshaderfile.open(fragmentpath);
			std::stringstream vshaderstream, fshaderstream;
			vshaderstream << vshaderfile.rdbuf();
			fshaderstream << fshaderfile.rdbuf();

			vshaderfile.close();
			fshaderfile.close();

			vertexcode = vshaderstream.str();
			fragmentcode = fshaderstream.str();



		}
		catch (std::ifstream::failure& e) {
			std::cout << "shader file not read succefully" << e.what() << std::endl;
		}
		const char* vshadercode = vertexcode.c_str();
		const char* fshadercode = fragmentcode.c_str();
		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vshadercode, NULL);
		glCompileShader(vertex);
	
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fshadercode, NULL);
		glCompileShader(fragment);


		ID = glCreateProgram();
		glAttachShader(ID, fragment);
		glAttachShader(ID, vertex);
		glLinkProgram(ID);


		glDeleteShader(vertex);
		glDeleteShader(fragment);
	};
	void use() {
		glUseProgram(ID);
	};
	void setbool(const std::string& name, bool value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	};
	void setfloat(const std::string& name, float value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()),value);
	};
	void setint(const std::string& name, int value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()),value);
	};

};
