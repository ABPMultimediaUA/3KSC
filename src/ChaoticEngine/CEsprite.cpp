
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

#include "../include/ChaoticEngine/CEsprite.hpp"
#include "../include/ChaoticEngine/manager/CEresourceManager.hpp"

CESprite::CESprite(const char* p_urlSource, GLuint p_shaderProgram) : CEEntity(){
    m_shaderProgram = p_shaderProgram;

    loadResource(p_urlSource);

    GLfloat t_vertices[] = { 
        // Pos      // Tex
        0.0f, 10.0f, 0.0f, 1.0f,
        10.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 10.0f, 0.0f, 1.0f,
        10.0f, 10.0f, 1.0f, 1.0f,
        10.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(t_vertices), t_vertices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
    std::cout << "CESprite creado" << std::endl;
}

CESprite::~CESprite(){}

void CESprite::beginDraw(){
    glUseProgram(m_shaderProgram);

    //PRECALCULAMOS LAS MATRICES Y LAS PASAMOS AL SHADER
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
    
    glm::mat4 t_projection = glm::ortho(20.0f, -20.0f, -20.0f, 20.0f, -15.0f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(t_projection));
    //glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));

    glm::vec3 t_color = glm::vec3(1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(m_shaderProgram, "spriteColor"), t_color.x, t_color.y, t_color.z);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture->getTextureId());

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void CESprite::endDraw(){}

void CESprite::loadResource(const char* p_urlSource){
    CEResourceManager* t_manager = CEResourceManager::instance();
    CEResource* t_resource = t_manager->getResource(p_urlSource);
    if(t_resource != NULL)
        m_texture = (CEResourceTexture*)t_resource;
}