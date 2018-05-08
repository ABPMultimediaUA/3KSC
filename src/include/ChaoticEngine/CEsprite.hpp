
#ifndef CESPRITE
#define CESPRITE

#include <glew.h>

#include "CEentity.hpp"
#include "manager/CEresourceTexture.hpp"

class CESprite : public CEEntity{
public:
	CESprite(const char* p_urlSource, GLuint p_shaderProgram);
	virtual ~CESprite();

	void loadResource(const char* p_urlSource);

	void beginDraw() override;
	void endDraw()   override;

private:
	GLuint m_shaderProgram;
    GLuint m_VAO;
    GLuint m_VBO;

    CEResourceTexture* m_texture;
};

#endif