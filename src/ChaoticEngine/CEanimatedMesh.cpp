
#include <gtc/type_ptr.hpp>
#include <iomanip>
#include <iostream>
#include <glew.h>
#include <glfw3.h>

#include "../include/ChaoticEngine/CEanimatedMesh.hpp"
#include "../include/ChaoticEngine/manager/CEresourceManager.hpp"

/*void showMat(glm::mat4 p_matrix){   
    std::cout << std::fixed;
    std::cout << std::setprecision(6);

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            std::cout << p_matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}*/

CEAnimatedMesh::CEAnimatedMesh(GLuint p_shaderProgram) : CEEntity(){
    m_shaderProgram = p_shaderProgram;
    m_lastTime = glfwGetTime();
    m_currentFrame = 0;
    m_frameTime = 0.041666f;//24 fps
}

CEAnimatedMesh::~CEAnimatedMesh(){}

void CEAnimatedMesh::beginDraw(){
    glUseProgram(m_shaderProgram);
    
	//PRECALCULAMOS LAS MATRICES Y LAS PASAMOS AL SHADER
	m_MVP = m_projectionMatrix * m_viewMatrix * m_modelMatrix;
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(m_MVP));
    
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
    
	glm::mat4 t_modelView = m_viewMatrix * m_modelMatrix;
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(t_modelView));

    glm::mat4 t_viewProj = m_viewMatrix * m_projectionMatrix;
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "ViewProjection"), 1, GL_FALSE, glm::value_ptr(t_viewProj));

    glm::mat3 t_normal = transpose(inverse(m_modelMatrix));
    glUniformMatrix3fv(glGetUniformLocation(m_shaderProgram, "NormalMatrix"), 1, GL_FALSE, glm::value_ptr(t_normal));

    //showMat(m_modelMatrix);

    double t_time = glfwGetTime();
    //m_frameTime = 1.0; //así ira a 1 fps (quitar para aumentar a 25 fps)

    if (t_time - m_lastTime >= m_frameTime){ 
        m_currentFrame++;
        m_lastTime += m_frameTime;
    }
    if(m_currentFrame > m_currentAnimation->getNumFrames() - 1){
        m_currentFrame = 0;
        m_currentAnimation = m_animations[0];
    }
    
    if(m_currentAnimation != NULL){
        m_currentAnimation->draw(m_shaderProgram, m_currentFrame);
    }
}

void CEAnimatedMesh::endDraw(){}

void CEAnimatedMesh::loadResource(const char* p_urlSource){
    CEResourceManager* t_manager = CEResourceManager::instance();
    CEResourceAnimation* t_resource = (CEResourceAnimation*)&t_manager->getResource(p_urlSource);
    if(t_resource != NULL)
        m_animations.push_back(t_resource);
}

void CEAnimatedMesh::setCurrentAnimation(int p_current){
    if(p_current < m_animations.size()){
        m_currentAnimation = m_animations[p_current];
        m_currentFrame = 0;
    }
}