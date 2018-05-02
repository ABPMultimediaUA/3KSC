
#include <iostream>

#include "../../include/ChaoticEngine/manager/CEshader.hpp"
#include "../../include/ChaoticEngine/fachada/CEShader.hpp"

CEShaderProgram::CEShaderProgram(const char* p_pathVertex, const char* p_pathFragment){
	m_shader = new CEShader();

	m_pathVertex 	= p_pathVertex;
	m_pathFragment 	= p_pathFragment;

	m_shaderProgram = 0;

	loadShader();
}

CEShaderProgram::~CEShaderProgram(){}

void CEShaderProgram::loadShader(){
	m_shaderProgram = m_shader->LoadShader(m_pathVertex, m_pathFragment);
	std::cout << "m_shaderProgram: " << m_shaderProgram << std::endl;
}

GLuint CEShaderProgram::getShaderProgram(){
	std::cout << "getShaderProgram() = " << m_shaderProgram << std::endl;
	return m_shaderProgram;
}
