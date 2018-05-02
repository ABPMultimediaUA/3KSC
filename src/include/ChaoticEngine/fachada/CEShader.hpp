 
#ifndef CE_SHADER
#define CE_SHADER

#include <glew.h>

class CEShader;

class CEShaderProgram{
public:
	CEShaderProgram(const char*	p_pathVertex, const char* p_pathFragment);
	~CEShaderProgram();

	void	loadShader();

	GLuint	getShaderProgram();

private:
	CEShader*	m_shader;
	GLuint		m_shaderProgram;

	const char*	m_pathVertex;
	const char*	m_pathFragment;
};

#endif
