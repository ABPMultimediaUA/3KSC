
#include <iostream>
#include <glm.hpp>

#include "../../include/ChaoticEngine/fachada/CEScene.hpp"
#include "../../include/ChaoticEngine/fachada/CESceneCamera.hpp"
#include "../../include/ChaoticEngine/fachada/CESceneLight.hpp"
#include "../../include/ChaoticEngine/fachada/CESceneMesh.hpp"
#include "../../include/ChaoticEngine/fachada/CESceneQuad.hpp"
#include "../../include/ChaoticEngine/fachada/CESceneSprite.hpp"
#include "../../include/ChaoticEngine/fachada/CEShader.hpp"
#include "../../include/ChaoticEngine/CEtransform.hpp"

CEScene::CEScene(){
	m_root = new CESceneNode();
	
	CETransform* rootEntity = new CETransform();
	m_root->setEntity(rootEntity);

	m_resourceManager = new CEResourceManager();

	//[ 0 ] - Main shader
	m_shaderProgram = new CEShaderProgram("src/ChaoticEngine/shader/CEvertex.vert", "src/ChaoticEngine/shader/CEfragment.frag");
	//[ 1 ] - Shader for the debug quads
	m_shaderProgram->loadShader("src/ChaoticEngine/shader/CEvertQuad.vert", "src/ChaoticEngine/shader/CEfragQuad.frag");
	//[ 2 ] - Shader for the sprites
	m_shaderProgram->loadShader("src/ChaoticEngine/shader/CEvertSprite.vert", "src/ChaoticEngine/shader/CEfragSprite.frag");
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

CESceneLight* CEScene::createLight(float p_lightIntensity[3], float p_lightAtenuation){
	glm::vec3 	intensities = glm::vec3(p_lightIntensity[0], p_lightIntensity[1], p_lightIntensity[2]);
	float 		attenuation = p_lightAtenuation;

	CESceneLight* CElight = new CESceneLight(m_root, intensities, attenuation, m_shaderProgram->getShaderProgram(0));
	m_lights.push_back(CElight);

	return CElight;	
}

CESceneMesh* CEScene::createMesh(const char* p_path){
	std::cout << "Cargamos malla: " << p_path << std::endl;
	CESceneMesh* CEmesh = new CESceneMesh(m_root, p_path, m_shaderProgram->getShaderProgram(0));

	std::cout << "Malla cargada!"<< std::endl;
	return CEmesh;	
}

CESceneQuad* CEScene::createQuad(float p_vertex[4][2]){
	std::cout << "Cremos Quad" << std::endl;
	CESceneQuad* CEquad = new CESceneQuad(m_root, p_vertex, m_shaderProgram->getShaderProgram(1));

	return CEquad;	
}

CESceneSprite* CEScene::createSprite(const char* p_path, float p_vertex[4][2]){
	std::cout << "Cargamos Sprite" << std::endl;
	CESceneSprite* CEsprite = new CESceneSprite(m_root, p_path, p_vertex, m_shaderProgram->getShaderProgram(2));
	std::cout << "Sprite cargado!" << std::endl;

	return CEsprite;
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