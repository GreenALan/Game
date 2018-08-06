//
//  Game.cpp
//  OpenGL
//
//  Created by lvshaohui on 2018/7/28.
//  Copyright © 2018年 lvshaohui. All rights reserved.
//

#include "Game.h"


Game::Game(GLuint width, GLuint height):State(GAME_ACTIVE),Keys(),Width(width),Height(height)
{
    
}

Game::~Game()
{
    
}

void Game::Init()
{
    ResourceManager::LoadShader("./shaders/sprite.vs", "./shaders/sprite.frag", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f,static_cast<GLfloat>(this->Width),static_cast<GLfloat>(this->Height),0.0f,-1.0f,1.0f);
    ResourceManager::GetShader("sprite").use().setInteger("image", 0); 
    ResourceManager::GetShader("sprite").setMatrix4("projection", projection);
   // Renderer = new SpriteRender(ResourceManager::GetShader("sprite"));
    //Renderer = new SpriteRender((ResourceManager::GetShader("sprite")));
    string str = "sprite";
    static Shader shader1 = ResourceManager::GetShader(str);
    Renderer = new SpriteRender(shader1);
    ResourceManager::LoadTexture("./textures/awesomeface.png", GL_TRUE, "face");
    
}

void Game::Update(GLfloat dt)
{
    
}

void Game::ProcessInput(GLfloat dt)
{
    
}

void Game::Render()
{
    static Texture2D temp = ResourceManager::GetTexture("face");
    Renderer->DrawSprite(temp,glm::vec2(200,200),glm::vec2(300,400),45.0f,glm::vec3(0.0f,1.0f,0.0f));
}
