 
#ifndef CE_SCENE_PARTICLE_SYSTEM
#define CE_SCENE_PARTICLE_SYSTEM

#include <glew.h>
#include <glfw3.h>

#include "../CEparticlesystem.hpp"
#include "../CEtransform.hpp"
#include "../CEscenenode.hpp"

class CESceneParticleSystem{
public:
	CESceneParticleSystem(CESceneNode* p_parent, const char* p_path, int p_amount, GLuint p_shaderProgram);
	~CESceneParticleSystem();

	void	update();

	void 	setScale(float p_x, float p_y, float p_z);
	void 	setRotation(float p_x, float p_y, float p_z);
	void 	setPosition(float p_x, float p_y, float p_z);

	void 	setAbsoluteScale(float p_x, float p_y, float p_z);
	void 	setAbsoluteRotation(float p_x, float p_y, float p_z);
	void 	setAbsolutePosition(float p_x, float p_y, float p_z);

private:
	CETransform*	m_rotate;
	CETransform*	m_scale;
	CETransform*	m_translate;
	
	CEParticleSystem*		m_system;

};

#endif
