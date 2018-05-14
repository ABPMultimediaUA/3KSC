 
#ifndef CE_SCENE_LIGHT
#define CE_SCENE_LIGHT

#include <glm.hpp>
#include <glew.h>
#include <glfw3.h>

#include "../CElight.hpp"
#include "../CEtransform.hpp"
#include "../CEscenenode.hpp"

class CESceneLight{
public:
	CESceneLight(CESceneNode* p_parent, glm::vec3 p_intensities, float p_attenuation, GLuint p_shaderProgram, bool p_isActive = false);
	~CESceneLight();

	void		processInput(GLFWwindow* p_window);

	bool 		getActive() 			{ return m_isActive; 	}
	void 		setActive(bool active) 	{ m_isActive = active; 	}

	void		setRotation(float p_x, float p_y, float p_z);
	void		setPosition(float p_x, float p_y, float p_z);

	void		setAbsoluteRotation(float p_x, float p_y, float p_z);
	void		setAbsolutePosition(float p_x, float p_y, float p_z);

	glm::vec3	getPosition() { return glm::vec3(glm::inverse(m_light->getMVP())[3]); }

	glm::vec3	getAmbient()	{ return m_light->getAmbient();};
	glm::vec3	getDiffuse()	{ return m_light->getDiffuse();};
	glm::vec3	getSpecular()	{ return m_light->getSpecular();};

	void		setIntensities(float p_x, float p_y, float p_z)	{ m_light->setIntensities(glm::vec3(p_x, p_y, p_z)); }
	void		setAtenuation(float p_attenuation)	{ m_light->setAtenuation(p_attenuation); }

private:
	CELight*		m_light;
	CETransform*	m_rotate;
	CETransform*	m_translate;

	glm::vec3 		m_intensities;
	float			m_attenuation;

	bool			m_isActive;
};

#endif
