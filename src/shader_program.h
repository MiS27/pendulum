#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "GL/glew.h"
#include "stdio.h"
#include "shared.h"

class ShaderProgram {
private:
	GLuint shaderProgram; //Uchwyt reprezentujący program cieniujacy
	GLuint vertexShader; //Uchwyt reprezentujący vertex shader
	GLuint geometryShader; //Uchwyt reprezentujący geometry shader
	GLuint fragmentShader; //Uchwyt reprezentujący fragment shader
	char* readFile(char* fileName); //metoda wczytująca plik tekstowy do tablicy znaków
	GLuint loadShader(GLenum shaderType,char* fileName); //Metoda wczytuje i kompiluje shader, a następnie zwraca jego uchwyt
public:
	ShaderProgram(char* vertexShaderFile,char* geometryShaderFile,char* fragmentShaderFile);
	~ShaderProgram();
	void use(); //Włącza wykorzystywanie programu cieniującego
	GLuint getUniformLocation(char* variableName); //Pobiera numer slotu związanego z daną zmienną jednorodną
	GLuint getAttribLocation(char* variableName); //Pobiera numer slotu związanego z danym atrybutem
	void pass_matrix_to_shader(char *var_string, glm::mat4 &matrix);
	void assign_vbo_to_attribute(char* attribute_name, GLuint buf_vbo, int variable_size);
};



#endif