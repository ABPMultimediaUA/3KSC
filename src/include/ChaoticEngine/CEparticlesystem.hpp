#ifndef CE_PARTICLE_SYSTEM
#define CE_PARTICLE_SYSTEM

#include <glew.h>
#include <vector>

#include "CEentity.hpp"
#include "manager/CEresourceTexture.hpp"

struct Particle {
    glm::vec2   Position, Velocity;
    glm::vec4   Color;
    GLfloat     Life;
    Particle() 
        : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};


class CEParticleSystem : public CEEntity{
public:
    CEParticleSystem(const char* p_path, int p_amount, GLuint p_shaderProgram);
    void update(GLfloat dt = 0.025f, GLuint newParticles = 20, glm::vec2 offset = glm::vec2(0.75f, 1.25f));
    void beginDraw();
    void endDraw();
    void loadResource(const char* p_urlSource);

private:
    std::vector<Particle>   m_particles;
    GLuint                  m_amount;
    GLuint                  m_shaderProgram;
    CEResourceTexture*      m_texture;
    GLuint                  m_VAO;
    GLuint                  m_VBO;
    GLuint                  m_EBO;

    void 	init();
    GLuint 	firstUnusedParticle();
    void 	respawnParticle(Particle &particle, glm::vec2 offset);
};

#endif