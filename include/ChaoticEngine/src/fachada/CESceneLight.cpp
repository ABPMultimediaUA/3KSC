
#include <iostream>

#include "../../include/fachada/CESceneLight.hpp"

CESceneLight::CESceneLight(CESceneNode* p_parent, glm::vec3 p_intensities, float p_attenuation, GLuint p_shaderProgram, bool p_isActive){
	m_intensities = p_intensities;
	m_attenuation = p_attenuation;
	m_isActive	  = p_isActive;

	m_rotate    = new CETransform();
	m_translate = new CETransform();
	m_light 	= new CELight(p_intensities, p_attenuation, p_shaderProgram);
	
	m_rotate->rotate(0, 0, 0);
	m_translate->translate(0, 0, 0);

	CESceneNode* t_nodeRotate 	 = new CESceneNode(p_parent);
	CESceneNode* t_nodeTranslate = new CESceneNode(t_nodeRotate);
	CESceneNode* t_nodeLight 	 = new CESceneNode(t_nodeTranslate);
	t_nodeRotate->setEntity(m_rotate);
	t_nodeTranslate->setEntity(m_translate);
	t_nodeLight->setEntity(m_light);
}

CESceneLight::~CESceneLight(){
	delete m_light;
	m_light = nullptr;
	
	delete m_translate;
	m_translate = nullptr;
	
	delete m_rotate;
	m_rotate = nullptr;
}

void CESceneLight::processInput(GLFWwindow* p_window){
	if(glfwGetKey(p_window, GLFW_KEY_UP) == GLFW_PRESS)
		setPosition(0,0.1,0);
	if(glfwGetKey(p_window, GLFW_KEY_DOWN) == GLFW_PRESS)
		setPosition(0,-0.1,0);
	if(glfwGetKey(p_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		setPosition(0.1,0,0);
	if(glfwGetKey(p_window, GLFW_KEY_LEFT) == GLFW_PRESS)
		setPosition(-0.1,0,0);
}

void CESceneLight::setIntensities(float p_x, float p_y, float p_z){
	m_light->setIntensities(glm::vec3(p_x, p_y, p_z));
}

void CESceneLight::setAtenuation(float p_attenuation){
	m_light->setAtenuation(p_attenuation);
}

void CESceneLight::setRotation(float p_x, float p_y, float p_z){
	m_rotate->rotate(p_x, p_y, p_z);
}

void CESceneLight::setPosition(float p_x, float p_y, float p_z){
	m_translate->translate(p_x, p_y, p_z);
}

void CESceneLight::setAbsoluteRotation(float p_x, float p_y, float p_z){
	m_rotate->loadIdentity();
	m_rotate->rotate(p_x, p_y, p_z);
}

void CESceneLight::setAbsolutePosition(float p_x, float p_y, float p_z){
	m_translate->loadIdentity();
	m_translate->translate(p_x, p_y, p_z);	
}

void CESceneLight::getPosition(){
	glm::mat4 t_matrix = m_translate->getMatrix();
	t_matrix = glm::inverse(t_matrix);
	glm::vec3 t_pos = (glm::vec3)t_matrix[3];
	std::cout << "(" << t_pos.x << ", " << t_pos.y << ", " << t_pos.z << ")" << std::endl;
}