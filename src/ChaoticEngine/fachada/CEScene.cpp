
#include <iostream>
#include <glm.hpp>

#include "../../include/ChaoticEngine/fachada/CEScene.hpp"
#include "../../include/ChaoticEngine/fachada/CESceneCamera.hpp"
#include "../../include/ChaoticEngine/fachada/CESceneLight.hpp"
#include "../../include/ChaoticEngine/fachada/CESceneMesh.hpp"
#include "../../include/ChaoticEngine/fachada/CEShader.hpp"
#include "../../include/ChaoticEngine/CEtransform.hpp"

CEScene::CEScene(){
	m_root = new CESceneNode();
	
	CETransform* rootEntity = new CETransform();
	m_root->setEntity(rootEntity);

	m_resourceManager = new CEResourceManager();

	m_shaderProgram = new CEShaderProgram("src/ChaoticEngine/shader/CEvertex.vert", "src/ChaoticEngine/shader/CEfragment.frag");
	m_shaderProgram->getShaderProgram();
	std::cout << m_shaderProgram << std::endl;
	
}

CEScene::~CEScene(){
	delete m_root;
	m_root = nullptr;

	delete m_resourceManager;
	m_resourceManager = nullptr;

	delete m_shaderProgram;
	m_shaderProgram = nullptr;
}

CESceneCamera* CEScene::createCamera(bool p_isActive){
	CESceneCamera* CEcamera = new CESceneCamera(m_root, p_isActive);
	m_cameras.push_back(CEcamera);

	if(p_isActive){
		m_activeCamera = CEcamera;
		m_activeCamera->activateCamera();
	}

	return CEcamera;
}

CESceneLight* CEScene::createLight(){
	glm::vec3 	intensities = glm::vec3(1, 1, 1);
	float 		attenuation = 0.0f;

	CESceneLight* CElight = new CESceneLight(m_root, intensities, attenuation, m_shaderProgram->getShaderProgram());
	m_lights.push_back(CElight);

	return CElight;	
}

CESceneMesh* CEScene::createMesh(const char* p_path){
	std::cout << "createMesh -> " << p_path << std::endl;
	std::cout << m_shaderProgram << std::endl;
	m_shaderProgram->getShaderProgram();
	CESceneMesh* CEmesh = new CESceneMesh(m_root, p_path, m_shaderProgram->getShaderProgram());

	std::cout << "createMesh terminado" << std::endl;
	return CEmesh;	
}

void CEScene::setActiveCamera(CESceneCamera* p_camera){
	m_activeCamera = p_camera;
	m_activeCamera->activateCamera();
}

void CEScene::draw(){
	m_root->draw();
}

void CEScene::release(){
	m_root->removeAllChilds();
	m_resourceManager->deleteResources();

	delete m_resourceManager;
	delete m_root;
}