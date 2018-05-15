
#include <iostream>
#include <glm.hpp>

#include "../../include/ChaoticEngine/fachada/CESceneAnimation.hpp"

CESceneAnimation::CESceneAnimation(CESceneNode* p_parent, const char* p_path, GLuint p_shaderProgram){
	m_rotate    = new CETransform();
	m_scale	    = new CETransform();
	m_translate = new CETransform(); 
	m_animation	= new CEAnimatedMesh(p_shaderProgram);
	
	m_rotate->rotate(0, 0, 0);
	m_scale->scale(1, 1, 1);
	m_translate->translate(0, 0, 0);
	m_animation->loadResource(p_path);

	m_nodeRotate 	 = new CESceneNode(p_parent);
	CESceneNode* t_nodeScale 	 = new CESceneNode(m_nodeRotate);
	CESceneNode* t_nodeTranslate = new CESceneNode(t_nodeScale);
	m_nodeMesh 	 = new CESceneNode(t_nodeTranslate);
	
	m_nodeRotate->setEntity(m_rotate);
	t_nodeScale->setEntity(m_scale);
	t_nodeTranslate->setEntity(m_translate);
	m_nodeMesh->setEntity(m_animation);
}

CESceneAnimation::~CESceneAnimation(){
	delete m_animation;
	m_animation = nullptr;
	
	delete m_translate;
	m_translate = nullptr;
	
	delete m_rotate;
	m_rotate = nullptr;
	
	delete m_scale;
	m_scale = nullptr;
}

void CESceneAnimation::processInput(GLFWwindow* p_window){
	if(glfwGetKey(p_window, GLFW_KEY_R) == GLFW_PRESS)
		setRotation(0,3,0);
	if(glfwGetKey(p_window, GLFW_KEY_W) == GLFW_PRESS)
		setPosition(0,1,0);
	if(glfwGetKey(p_window, GLFW_KEY_S) == GLFW_PRESS)
		setPosition(0,-1,0);
	if(glfwGetKey(p_window, GLFW_KEY_D) == GLFW_PRESS)
		setPosition(1,0,0);
	if(glfwGetKey(p_window, GLFW_KEY_A) == GLFW_PRESS)
		setPosition(-1,0,0);
	if(glfwGetKey(p_window, GLFW_KEY_E) == GLFW_PRESS)
		setPosition(0,0,1);
	if(glfwGetKey(p_window, GLFW_KEY_Q) == GLFW_PRESS)
		setPosition(0,0,-1);
	if(glfwGetKey(p_window, GLFW_KEY_O) == GLFW_PRESS)
		changeCurrentAnimation(0);
	if(glfwGetKey(p_window, GLFW_KEY_L) == GLFW_PRESS)
		changeCurrentAnimation(1);
}

void CESceneAnimation::loadAnimation(const char* p_path){
	m_animation->loadResource(p_path);
}

void CESceneAnimation::changeCurrentAnimation(int p_current){
	m_animation->setCurrentAnimation(p_current);
}

void CESceneAnimation::setScale(float p_x, float p_y, float p_z){
	m_scale->scale(p_x, p_y, p_z);
}

void CESceneAnimation::setRotation(float p_x, float p_y, float p_z){
	m_rotate->rotate(p_x, p_y, p_z);
}

void CESceneAnimation::setPosition(float p_x, float p_y, float p_z){
	m_translate->translate(p_x, p_y, p_z);
}

void CESceneAnimation::setAbsoluteScale(float p_x, float p_y, float p_z){
	m_scale->loadIdentity();
	m_scale->scale(p_x, p_y, p_z);
}

void CESceneAnimation::setAbsoluteRotation(float p_x, float p_y, float p_z){
	m_rotate->loadIdentity();
	m_rotate->rotate(p_x, p_y, p_z);
}

void CESceneAnimation::setAbsolutePosition(float p_x, float p_y, float p_z){
	m_translate->loadIdentity();
	m_translate->translate(p_x, p_y, p_z);	
}
