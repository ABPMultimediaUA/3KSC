
#include <gtc/type_ptr.hpp>

#include "../include/ChaoticEngine/CElight.hpp"

CELight::CELight(glm::vec3 p_intensities, float p_attenuation, GLuint p_shaderProgram) : CEEntity(){
	m_intensities 	= p_intensities;
	m_attenuation 	= p_attenuation;
	m_shaderProgram = p_shaderProgram;
}

CELight::~CELight(){}

void CELight::setIntensities(glm::vec3 p_intensities){
	m_intensities.x = p_intensities.x;
	m_intensities.y = p_intensities.y;
	m_intensities.z = p_intensities.z;
}

void CELight::setAtenuation(float p_attenuation){
	m_attenuation = p_attenuation;
}

void CELight::beginDraw(){
    glUseProgram(m_shaderProgram);
    
	glm::mat4 t_modelView = m_viewMatrix * m_modelMatrix;
	t_modelView = glm::inverse(t_modelView);
	glm::vec3 t_pos = (glm::vec3)t_modelView[3];
    glUniform3fv(glGetUniformLocation(m_shaderProgram, "Light.Position"), 1, glm::value_ptr(t_pos));

    glm::vec3 t_ambient = glm::vec3(m_intensities.x/4, m_intensities.y/4, m_intensities.z/4);
    glUniform3fv(glGetUniformLocation(m_shaderProgram, "Light.Ambient"), 1, glm::value_ptr(t_ambient));

    glm::vec3 t_diffuse = glm::vec3(m_intensities.x, m_intensities.y, m_intensities.z);
    glUniform3fv(glGetUniformLocation(m_shaderProgram, "Light.Diffuse"), 1, glm::value_ptr(t_diffuse));
    glUniform3fv(glGetUniformLocation(m_shaderProgram, "Light.Specular"), 1, glm::value_ptr(m_intensities));
}

void CELight::endDraw(){}