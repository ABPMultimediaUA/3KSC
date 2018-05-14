#ifndef CELIGHT
#define CELIGHT

#include <glew.h>

#include "CEentity.hpp"

class CELight : public CEEntity{
public:
	CELight(glm::vec3 m_intensities, float m_attenuation, GLuint p_shaderProgram);
	virtual ~CELight();

	void setIntensities(glm::vec3 p_intensities);
	void setAtenuation(float p_attenuation);

	void beginDraw() override;
	void endDraw() override;

	glm::mat4 getMVP()	{ return m_MVP; }

	
	glm::vec3 getAmbient()	{ return glm::vec3(m_intensities.x/4, m_intensities.y/4, m_intensities.z/4); }
	glm::vec3 getDiffuse()	{ return m_intensities; }
	glm::vec3 getSpecular()	{ return m_intensities; }

private:
    glm::vec3 m_intensities; //(0-1)red, green and blue intensities 
    GLuint m_shaderProgram;
    float m_attenuation;

	glm::mat4	m_MVP;
};

#endif