
#include "../include/ChaoticEngine/CEscenenode.hpp" 
#include "../include/ChaoticEngine/CEtransform.hpp"
#include "../include/ChaoticEngine/CEmesh.hpp"
#include "../include/ChaoticEngine/CElight.hpp"

CESceneNode::CESceneNode(){
	m_father = NULL;
	m_entity = NULL;
}

CESceneNode::CESceneNode(CESceneNode* p_father){
	m_father = p_father;
	m_father->addChild(this);
}

//Si quiero puedo poner todos los atributos a 0 (no es necesario)
CESceneNode::~CESceneNode(){}

void CESceneNode::addChild(CESceneNode* p_child){
	m_childs.push_back(p_child);
	p_child->setFather(this);
}

/*Removes a child, and all the childs of his child.*/
bool CESceneNode::removeChild(CESceneNode* p_child){
	for(int i = 0; i < m_childs.size(); i++){
		if(m_childs[i] == p_child){
			m_childs[i]->removeAllChilds();
			m_childs[i] = 0;
			delete m_childs[i];
			m_childs.erase(m_childs.begin()+(i));
			return true;
		}
	}
	return false;
}

/*Removes all childs of the father and all the childs of his childs*/
void CESceneNode::removeAllChilds(){
	for(int i = 0; i < m_childs.size(); i++){
		m_childs[i]->removeAllChilds();
		m_childs[i] = 0;
		delete m_childs[i];
	}
	m_childs.clear();
}

void CESceneNode::setEntity(CEEntity* p_entity){
	m_entity = p_entity;
}

CEEntity* CESceneNode::getEntity(){
	return m_entity;
}

CESceneNode* CESceneNode::getFather(){
	return m_father;
}

void CESceneNode::setFather(CESceneNode* p_father){
	m_father = p_father;
}

void CESceneNode::draw(){
	m_entity->beginDraw();
	
	for(int i = 0; i < m_childs.size(); i++){
		m_childs[i]->draw();
	}

	m_entity->endDraw();
}

int CESceneNode::getTotalChilds(){
	return m_childs.size();
}

void CESceneNode::setRotation(float p_x, float p_y, float p_z){
	static_cast<CETransform*>(getFather()->getFather()->getFather()->getEntity())->rotate(p_x, p_y, p_z);
}

void CESceneNode::setScale(float p_x, float p_y, float p_z){
	static_cast<CETransform*>(getFather()->getFather()->getEntity())->scale(p_x, p_y, p_z);
}

void CESceneNode::setTranslation(float p_x, float p_y, float p_z){
	static_cast<CETransform*>(getFather()->getEntity())->translate(p_x, p_y, p_z);
}

glm::vec3 CESceneNode::getPosition(){
	glm::mat4 				t_positionMatrix;
	std::stack<glm::mat4>	t_matrixStack;
	CESceneNode* t_node = this->getFather();
	//Go through all the transforms until we reach the root
	while(t_node != NULL){
		if(dynamic_cast<CETransform*>(t_node->getEntity())){
			CETransform* t_tempTransform = (CETransform*)t_node->getEntity();
			t_matrixStack.push(t_tempTransform->getMatrix());
		}
		t_node = t_node->getFather();
	}
	//Calculate the lightmatrix
	while(!t_matrixStack.empty()){
		t_positionMatrix = t_positionMatrix * t_matrixStack.top();
		t_matrixStack.pop();
	}
	t_positionMatrix = glm::inverse(t_positionMatrix);
	glm::vec3 t_pos = (glm::vec3)t_positionMatrix[3];
	std::cout << "(" << t_pos.x << ", " << t_pos.y << ", " << t_pos.z << ")" << std::endl;

/*	
	CETransform* t_translationNode = static_cast<CETransform*>(getFather()->getEntity());
	glm::mat4 t_tempMatrix = glm::inverse(t_translationNode->getMatrix());
	glm::vec3 t_pos = (glm::vec3)t_tempMatrix[3];
	std::cout << "(" << t_pos.x << ", " << t_pos.y << ", " << t_pos.z << ")" << std::endl;
*/
	return t_pos;
}

