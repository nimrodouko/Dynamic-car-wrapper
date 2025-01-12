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
	};
	void use();
	void setbool(const std::string& name, bool value);
	void setfloat(const std::string& name, float value);
	void setint(const std::string& name, int value);

};
