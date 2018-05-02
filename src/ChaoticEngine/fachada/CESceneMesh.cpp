
#include <iostream>
#include <glm.hpp>

#include "../../include/ChaoticEngine/fachada/CESceneMesh.hpp"

CESceneMesh::CESceneMesh(CESceneNode* p_parent, const char* p_path, GLuint p_shaderProgram){
	std::cout << "CESceneMesh -> " << p_path << std::endl;
	m_rotate    = new CETransform();
	m_scale	    = new CETransform();
	m_translate = new CETransform(); 
	m_mesh	 	= new CEMesh(p_shaderProgram);
	
	m_rotate->rotate(0, 0, 0);
	m_scale->scale(1, 1, 1);
	m_translate->translate(0, 0, 0);
	m_mesh->loadResource(p_path);

	CESceneNode* t_nodeRotate 	 = new CESceneNode(p_parent);
	CESceneNode* t_nodeScale 	 = new CESceneNode(t_nodeRotate);
	CESceneNode* t_nodeTranslate = new CESceneNode(t_nodeScale);
	CESceneNode* t_nodeMesh 	 = new CESceneNode(t_nodeTranslate);
	t_nodeRotate->setEntity(m_rotate);
	t_nodeScale->setEntity(m_scale);
	t_nodeTranslate->setEntity(m_translate);
	t_nodeMesh->setEntity(m_mesh);
}

CESceneMesh::~CESceneMesh(){
	delete m_mesh;
	m_mesh = nullptr;
	
	delete m_translate;
	m_translate = nullptr;
	
	delete m_rotate;
	m_rotate = nullptr;
	
	delete m_scale;
	m_scale = nullptr;
}

void CESceneMesh::processInput(GLFWwindow* p_window){
	if(glfwGetKey(p_window, GLFW_KEY_R) == GLFW_PRESS)
		setRotation(0,3,0);
	if(glfwGetKey(p_window, GLFW_KEY_W) == GLFW_PRESS)
		setPosition(0,0.1,0);
	if(glfwGetKey(p_window, GLFW_KEY_S) == GLFW_PRESS)
		setPosition(0,-0.1,0);
	if(glfwGetKey(p_window, GLFW_KEY_D) == GLFW_PRESS)
		setPosition(0.1,0,0);
	if(glfwGetKey(p_window, GLFW_KEY_A) == GLFW_PRESS)
		setPosition(-0.1,0,0);
	if(glfwGetKey(p_window, GLFW_KEY_E) == GLFW_PRESS)
		setPosition(0,0,0.1);
	if(glfwGetKey(p_window, GLFW_KEY_Q) == GLFW_PRESS)
		setPosition(0,0,-0.1);
}

void CESceneMesh::setScale(float p_x, float p_y, float p_z){
	m_scale->scale(p_x, p_y, p_z);
}

void CESceneMesh::setRotation(float p_x, float p_y, float p_z){
	m_rotate->rotate(p_x, p_y, p_z);
}

void CESceneMesh::setPosition(float p_x, float p_y, float p_z){
	m_translate->translate(p_x, p_y, p_z);
}

void CESceneMesh::setAbsoluteScale(float p_x, float p_y, float p_z){
	m_scale->loadIdentity();
	m_scale->scale(p_x, p_y, p_z);
}

void CESceneMesh::setAbsoluteRotation(float p_x, float p_y, float p_z){
	m_rotate->loadIdentity();
	m_rotate->rotate(p_x, p_y, p_z);
}

void CESceneMesh::setAbsolutePosition(float p_x, float p_y, float p_z){
	m_translate->loadIdentity();
	m_translate->translate(p_x, p_y, p_z);	
}

void CESceneMesh::getPosition(){
	glm::mat4 t_matrix = m_mesh->getModelMatrix();
	t_matrix = glm::inverse(t_matrix);
	glm::vec3 t_pos = (glm::vec3)t_matrix[3];
	std::cout << "(" << t_pos.x << ", " << t_pos.y << ", " << t_pos.z << ")" << std::endl;
}