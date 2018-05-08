
#include <gtc/type_ptr.hpp>
#include <iostream>

#include "../include/ChaoticEngine/CEquad.hpp"

CEQuad::CEQuad(float p_vertex[4][2], GLuint p_shaderProgram) : CEEntity(){
    m_shaderProgram = p_shaderProgram;

    for(int i = 0; i < 4; i++){
        m_vertices[i*3]   = p_vertex[i][0];
        m_vertices[i*3+1] = p_vertex[i][1];
        m_vertices[i*3+2] = 0.0f;
    }

    m_indices[0] = 0; //First Triangle
    m_indices[1] = 1;
    m_indices[2] = 3;
    m_indices[3] = 1; //Second Triangle
    m_indices[4] = 2;
    m_indices[5] = 3;
    
    /*m_indices = {
        0, 1, 3,  // First Triangle
        1, 2, 3   // Second Triangle
    };*/

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0);
}

CEQuad::~CEQuad(){}

void CEQuad::updatePositions(float p_vertex[4][2]){
    for(int i = 0; i < 4; i++){
        m_vertices[i*3]   = p_vertex[i][0];
        m_vertices[i*3+1] = p_vertex[i][1];
        m_vertices[i*3+2] = 0.0f;
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
}

void CEQuad::beginDraw(){
    glUseProgram(m_shaderProgram);

	//PRECALCULAMOS LAS MATRICES Y LAS PASAMOS AL SHADER
	glm::mat4 t_MVP = m_projectionMatrix * m_viewMatrix * m_modelMatrix;
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(t_MVP));

    //Draw the quad
    glBindVertexArray(m_VAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0); // no need to unbind it every time 
}

void CEQuad::endDraw(){}