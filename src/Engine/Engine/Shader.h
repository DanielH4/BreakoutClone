#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Engine {
	class Shader {
	public:
		Shader(const GLchar* vertexPath, const GLchar* fragmentPath) 
		:	ID(glCreateProgram())
		{
			//1. Retrieve vertex/fragment source code from files
			std::string vertexCode;
			std::string fragmentCode;
			std::ifstream vShaderFile;
			std::ifstream fShaderFile;
		
			vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			try {
				vShaderFile.open(vertexPath);
				fShaderFile.open(fragmentPath);
				//Read file's buffer contents into streams
				std::stringstream vShaderStream, fShaderStream;
				vShaderStream << vShaderFile.rdbuf();
				fShaderStream << fShaderFile.rdbuf();
				//close file handlers
				vShaderFile.close();
				fShaderFile.close();
				//convert stream into string
				vertexCode = vShaderStream.str();
				fragmentCode = fShaderStream.str();
			} 
			catch(std::ifstream::failure e) {
				std::cout << "ERROR::ENGINE::SHADER::UNSUCCESSFUL_FILE_READ" << std::endl;		
			}
			
			const char* vShaderCode = vertexCode.c_str();
			const char* fShaderCode = fragmentCode.c_str();

			//2. Compile shaders
			unsigned int vertex, fragment;
			int success;
			char infolog[512];

			//vertex shader
			vertex = glCreateShader(GL_VERTEX_SHADER);	
			glShaderSource(vertex, 1, &vShaderCode, NULL);
			glCompileShader(vertex);
			
			//print compile errors if any
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
			if(!success) {
				glGetShaderInfoLog(vertex, 512, NULL, infolog);
				std::cout << "ERROR::ENGINE::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
			}
			
			//fragment shader
			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &fShaderCode, NULL);
			glCompileShader(fragment);
			
			//print compile errors if any
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
			if(!success) {
				glGetShaderInfoLog(fragment, 512, NULL, infolog);
				std::cout << "ERROR::ENGINE::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
			}

			//3. Shader program
			glAttachShader(ID, vertex);
			glAttachShader(ID, fragment);
			glLinkProgram(ID);
			glGetProgramiv(ID, GL_LINK_STATUS, &success);
			if(!success) {
				glGetProgramInfoLog(ID, 512, NULL, infolog);
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
			}

			//delete shaders, no longer necessary after linked to program
			glDeleteShader(vertex);
			glDeleteShader(fragment);
		}

		void use() const {
			glUseProgram(ID);
		}

		void setBool(const std::string &name, const bool value) const {
			glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);	
		}
		
		void setInt(const std::string &name, const int value) const {
			glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
		}

		void setFloat(const std::string &name, const float value) const {
			glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
		}

		void setVec3(const std::string &name, const glm::vec3 &vec) const {
			glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec));
		}

		void setMat4(const std::string &name, const glm::mat4 &mat) const {
			glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
		}

	private:
		const unsigned int ID;
	};
}