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
#include "GameLevel.h"
#include "BallObject.h"
#include "Particle.h"

enum GameState{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};


enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef std::tuple<GLboolean,Direction,glm::vec2> Collision;

const glm::vec2 PLAYER_SIZE(100,20);
const GLfloat PLAYER_VELOCITY(500.0f);
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f,-350.0f);

const GLfloat BALL_RADIUS = 12.5f;

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
    std::vector<GameLevel> levels;
    GLuint level;
    
    void DoCollisions();
    void ResetLevel();
    void ResetPlayer();
private:
    SpriteRender *Renderer;
    GameObject *player;
    BallObject *ball;
    ParticleGenerator *particles;
    
};

#endif /* Game_hpp */
