
#ifndef CESPRITE
#define CESPRITE

#include <glew.h>

#include "CEentity.hpp"
#include "manager/CEresourceTexture.hpp"

class CESprite : public CEEntity{
public:
	CESprite(const char* p_urlSource, float p_width, float p_height, GLuint p_shaderProgram);
	virtual ~CESprite();

	void 	loadResource(const char* p_urlSource);

	void 	beginDraw() override;
	void 	endDraw()   override;

	void 	setWidth(float p_width)	{	m_width  = p_width;		};
	float 	getWidth() 				{	return m_width;			};

	void 	setHeight(float p_height)	{	m_height = p_height;	};
	float 	getHeight() 				{	return m_height;		};


private:
	GLuint m_shaderProgram;
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;

    CEResourceTexture* m_texture;

    float m_width;
	float m_height;
};

#endif