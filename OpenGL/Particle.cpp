//
//  Particle.cpp
//  OpenGL
//
//  Created by lvshaohui on 2018/9/9.
//  Copyright © 2018年 lvshaohui. All rights reserved.
//

#include "Particle.h"

ParticleGenerator::ParticleGenerator(const Shader& shader,const Texture2D &texture,GLuint amount):m_shader(shader),m_texture(texture),m_amount(amount){
    init();
}

void ParticleGenerator::init(){
    GLuint VBO;
    GLfloat particle_quad[] = {
        0.0f,1.0f,0.0f,1.0f,
        1.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,0.0f,0.0f,
        
        0.0f,1.0f,0.0f,1.0f,
        1.0f,1.0f,0.0f,1.0f,
        1.0f,0.0f,1.0f,0.0f
    };
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(particle_quad),particle_quad,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,4 * sizeof(GLfloat),(GLvoid*)0);
    glBindVertexArray(0);
    
    for(GLuint i=0; i < m_amount; i++){
        particles.push_back(Particle());
    }
}

void ParticleGenerator::update(GLfloat dt, GameObject &object, GLuint newParticles,glm::vec2 offset){
    for(GLuint i=0; i < newParticles; ++i){
        int unusedParticle = firstUnusedParticle();
        respawnParticle(particles[unusedParticle], object,offset);
    }
    for(GLuint i=0; i < m_amount; ++i){
        Particle &p = particles[i];
        p.Life -= dt;
        if(p.Life > 0.0f){
            p.Position -= p.Velocity * dt;
            p.Color -= dt * 2.5;
        }
    }
}

void ParticleGenerator::Draw(){
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    m_shader.use();
    for(Particle particle : particles){
        m_shader.setVector2f("offset", particle.Position);
        m_shader.setVector4f("color", particle.Color);
        m_texture.Bind();
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_TRIANGLES,0,6);
        glBindVertexArray(0);
    }
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_ALPHA);
}

GLuint ParticleGenerator::firstUnusedParticle(){
    for(GLuint i=lastUsedParticle; i < m_amount; ++i){
        if(particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    
    for(GLuint i=0; i < lastUsedParticle; ++i){
        if(particles[i].Life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    
    lastUsedParticle = 0;
    return 0;
}

void ParticleGenerator::respawnParticle(Particle &particle, GameObject &object,glm::vec2 offset){
    GLfloat random = ((rand() % 100) - 50) / 10.0f;
    GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
    
    particle.Position = object.Position + random + offset;
    particle.Color = glm::vec4(rColor,rColor,rColor,1.0f);
    particle.Life = 1.0f;
    particle.Velocity = object.Velocity * 0.1f;
}
