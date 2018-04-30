
#include <gtc/type_ptr.hpp>

#include "../include/CEmesh.hpp"
#include "../include/manager/CEresourceManager.hpp"

CEMesh::CEMesh(GLuint p_shaderProgram) : CEEntity(){
    m_shaderProgram = p_shaderProgram;
}

CEMesh::~CEMesh(){}

void CEMesh::beginDraw(){
	//PRECALCULAMOS LAS MATRICES Y LAS PASAMOS AL SHADER

	glm::mat4 t_MVP = m_projectionMatrix * m_viewMatrix * m_modelMatrix;
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(t_MVP));
    
	glm::mat4 t_modelView = m_viewMatrix * m_modelMatrix;
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(t_modelView));

    glm::mat3 t_normal = transpose(inverse(m_modelMatrix));
    glUniformMatrix3fv(glGetUniformLocation(m_shaderProgram, "NormalMatrix"), 1, GL_FALSE, glm::value_ptr(t_normal));

    if(m_mesh != NULL)
        m_mesh->draw(m_shaderProgram);
}

void CEMesh::endDraw(){}

void CEMesh::loadResource(const char* p_urlSource){
    CEResourceManager* t_manager = CEResourceManager::instance();
    CEResource* t_resource = t_manager->getResource(p_urlSource);
    if(t_resource != NULL)
        m_mesh = (CEResourceMesh*)t_resource;
}