
#include <gtc/type_ptr.hpp>

#include "../include/ChaoticEngine/CElight.hpp"

//Constructor for Point light
CELight::CELight(float p_attenuation, GLuint p_shaderProgram) : CEEntity(){
	m_shaderProgram = p_shaderProgram;

	m_attenuation 	= p_attenuation;

	setComponents();
}

//constructor for Directional Light
CELight::CELight(glm::vec3 p_direction, GLuint p_shaderProgram) : CEEntity(){
	m_shaderProgram = p_shaderProgram;

	m_direction	= p_direction;

	setComponents();
}

CELight::~CELight(){}

void CELight::setComponents(){
	m_ambient	= glm::vec3(0.1f, 0.1f, 0.1f);
	m_diffuse	= glm::vec3(0.5f, 0.5f, 0.5f);
	m_specular	= glm::vec3(0.2f, 0.2f, 0.2f);
}

void CELight::beginDraw(){
	m_MVP = m_projectionMatrix * m_viewMatrix * m_modelMatrix;
}

void CELight::endDraw(){}