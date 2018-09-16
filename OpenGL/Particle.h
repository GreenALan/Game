//
//  Particle.hpp
//  OpenGL
//
//  Created by lvshaohui on 2018/9/9.
//  Copyright © 2018年 lvshaohui. All rights reserved.
//

#ifndef Particle_h
#define Particle_h

#include <stdio.h>
#include "BaseInclude.h"

#include "shader.h"
#include "texture.h"
#include "GameObject.h"
#include <vector>

struct Particle{
    glm::vec2 Position,Velocity;
    glm::vec4 Color;
    GLfloat Life;
    
    Particle():Position(0.0f),Velocity(0.0f),Color(1.0f),Life(0.0f){}
};

class ParticleGenerator
{
public:
    ParticleGenerator(const Shader &shader,const Texture2D &texture,GLuint amount);
    void update(GLfloat dt,GameObject &object, GLuint newParticles,glm::vec2 offset = glm::vec2(0.0f,0.0f));
    void Draw();
private:
    std::vector<Particle> particles;
    GLuint m_amount;
    Shader m_shader;
    Texture2D m_texture;
    GLuint VAO;
    void init();
    GLuint firstUnusedParticle();
    GLuint lastUsedParticle = 0;
    void respawnParticle(Particle &particle,GameObject &object,glm::vec2 offset = glm::vec2(0.0f,0.0f));
};



#endif /* Particle_hpp */
