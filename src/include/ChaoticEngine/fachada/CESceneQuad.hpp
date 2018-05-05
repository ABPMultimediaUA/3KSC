 
#ifndef CE_SCENE_QUAD
#define CE_SCENE_QUAD

#include <glew.h>
#include <glfw3.h>

#include "../CEquad.hpp"
#include "../CEtransform.hpp"
#include "../CEscenenode.hpp"

class CESceneQuad{
public:
	CESceneQuad(CESceneNode* p_parent, float p_vertex[4][2], GLuint p_shaderProgram);
	~CESceneQuad();

	void 	setPosition(float p_x, float p_y, float p_z);

	void 	setAbsolutePosition(float p_x, float p_y, float p_z);

private:
	CEQuad*			m_quad;
	CETransform*	m_translate;

};

#endif
