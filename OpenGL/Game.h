//
//  Game.hpp
//  OpenGL
//
//  Created by lvshaohui on 2018/7/28.
//  Copyright © 2018年 lvshaohui. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <stdio.h>

#include "BaseInclude.h"
#include "ResourceManager.h"
#include "shader.h"
#include "SpriteRender.h"

enum GameState{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
    GameState State;
    GLboolean Keys[1024];
    GLuint Width,Height;
    Game(GLuint width,GLuint height);
    ~Game();
    void Init();
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
private:
    SpriteRender *Renderer;
};

#endif /* Game_hpp */
