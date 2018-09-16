//
//  Game.cpp
//  OpenGL
//
//  Created by lvshaohui on 2018/7/28.
//  Copyright © 2018年 lvshaohui. All rights reserved.
//

#include "Game.h"

//const glm::vec2 INITIAL_BALL_VELOCITY(100.0f-350.0f);

//const GLfloat BALL_RADIUS = 12.5f;

//BallObject *Ball;


Game::Game(GLuint width, GLuint height):State(GAME_ACTIVE),Keys(),Width(width),Height(height)
{
    
}

Game::~Game()
{
    if(Renderer){
        delete Renderer;
    }
    if(player){
        delete player;
    }
}

void Game::Init()
{
    ResourceManager::LoadShader("./shaders/sprite.vs", "./shaders/sprite.frag", nullptr, "sprite");
    ResourceManager::LoadShader("./shaders/particle.vs", "./shaders/particle.frag", nullptr, "particle");

    glm::mat4 projection = glm::ortho(0.0f,static_cast<GLfloat>(this->Width),static_cast<GLfloat>(this->Height),0.0f,-1.0f,1.0f);
    ResourceManager::GetShader("sprite").use().setInteger("image", 0); 
    ResourceManager::GetShader("sprite").setMatrix4("projection", projection);
    ResourceManager::GetShader("particle").use().setInteger("sprite", 0);
    ResourceManager::GetShader("particle").setMatrix4("projection", projection);
    string str = "sprite";
    static Shader shader1 = ResourceManager::GetShader(str);
    Renderer = new SpriteRender(shader1);
   // ResourceManager::LoadTexture("./textures/awesomeface.png", GL_TRUE, "face");
    //加载纹理
    ResourceManager::LoadTexture("textures/background.jpg", GL_FALSE, "background");
    ResourceManager::LoadTexture("textures/awesomeface.png", GL_TRUE, "face");
    ResourceManager::LoadTexture("textures/block.png", GL_FALSE, "block");
    ResourceManager::LoadTexture("textures/block_solid.png", GL_FALSE, "block_solid");
    ResourceManager::LoadTexture("textures/paddle.png", true, "paddle");
    ResourceManager::LoadTexture("textures/particle.png", true, "particle");
    
    //加载关卡
    GameLevel one;
    one.Load("levels/one.lvl", this->Width, this->Height * 0.5);
    GameLevel two;
    two.Load("levels/two.lvl", this->Width, this->Height * 0.5);
    GameLevel three;
    three.Load("levels/three.lvl", this->Width, this->Height * 0.5);
    GameLevel four;
    four.Load("levels/four.lvl", this->Width, this->Height * 0.5);
    this->levels.push_back(one);
    this->levels.push_back(two);
    this->levels.push_back(three);
    this->levels.push_back(four);
    this->level = 0;
    glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x /2, this->Height - PLAYER_SIZE.y);
    player = new GameObject(playerPos,PLAYER_SIZE,ResourceManager::GetTexture("paddle"));
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x/2 - BALL_RADIUS,-BALL_RADIUS * 2);
    ball = new BallObject(ballPos,BALL_RADIUS,INITIAL_BALL_VELOCITY,ResourceManager::GetTexture("face"));
    if(ball != nullptr){
        ball->stuck = false;
    }
    
    particles = new ParticleGenerator(ResourceManager::GetShader("particle"),ResourceManager::GetTexture("particle"),500);
}

void Game::Update(GLfloat dt)
{
    ball->Move(dt, this->Width);
    this->DoCollisions();
    
    if(ball->Position.y >= this->Height)
    {
        this->ResetLevel();
        this->ResetPlayer();
    }
    particles->update(dt, *ball, 2,glm::vec2(ball->Radius / 2 ));
}

void Game::ProcessInput(GLfloat dt)
{
    if(this->State == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        if(this->Keys[GLFW_KEY_A])
        {
            if(player->Position.x >= 0)
            player->Position.x -= velocity;
        }
        if(this->Keys[GLFW_KEY_D])
        {
            if(player->Position.x <= this->Width - player->Size.x)
            player->Position.x += velocity;
        }
        if(this->Keys[GLFW_KEY_SPACE]){
            ball->stuck = !ball->stuck;
        }
        
    }
}

void Game::Render()
{
   // static Texture2D temp = ResourceManager::GetTexture("face");Ø
   // Renderer->DrawSprite(temp,glm::vec2(200,200),glm::vec2(300,400),45.0f,glm::vec3(0.0f,1.0f,0.0f));
    if(this->State == GAME_ACTIVE)
    {
        //绘制背景
        static Texture2D temp = ResourceManager::GetTexture("background");
        Renderer->DrawSprite(temp,glm::vec2(0,0),glm::vec2(this->Width,this->Height),0.0f);
        this->levels[this->level].Draw(*Renderer);
        player->Draw(*Renderer);
        //draw particles
        particles->Draw();
        ball->Draw(*Renderer);
    }
   
}

void Game::ResetLevel()
{
    if(this->level == 0)
    {
        this->levels[0].Load("levels/one.lvl", this->Width, this->Height * 0.5f);
    }
    else if(this->level == 1){
        this->levels[1].Load("levels/two.lv1", this->Width, this->Height * 0.5f);
    }
    else if(this->level == 2){
        this->levels[2].Load("levels/three.lvl", this->Width, this->Height * 0.5f);
    }
    else if(this->level == 3){
        this->levels[3].Load("levels/four.lvl", this->Width, this->Height * 0.5f);
    }
}

void Game::ResetPlayer()
{
    player->Size = PLAYER_SIZE;
    player->Position = glm::vec2(this->Width /2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
    ball->Reset(player->Position + glm::vec2(PLAYER_SIZE.x /2 - BALL_RADIUS, -(BALL_RADIUS * 2)),INITIAL_BALL_VELOCITY);
}

GLboolean checkCollision(GameObject &one, GameObject &two);
Collision checkCollision(BallObject &one, GameObject &two);
Direction vectorDirection(glm::vec2 closest);

void Game::DoCollisions()
{
    for(GameObject &box : this->levels[this->level].Bricks)
    {
        if(!box.Destroyed)
        {
            Collision collision = checkCollision(*ball, box);
            if(std::get<0>(collision))
            {
                if(!box.IsSolid)
                box.Destroyed = GL_TRUE;
                
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if(dir == LEFT || dir == RIGHT){
                    ball->Velocity.x = -ball->Velocity.x;
                    //碰撞过程中 计算便宜量： 这里是圆 与AABB碰撞
                    GLfloat penetration = ball->Radius - std::abs(diff_vector.x);
                    if(dir == LEFT)
                        ball->Position.x += penetration;
                    else
                    ball->Position.x -= penetration;
                }
                else
                {
                    ball->Velocity.y = - ball->Velocity.y;
                    GLfloat penetration = ball->Radius - std::abs(diff_vector.y);
                    if(dir == UP)
                        ball->Position.y -= penetration;
                    else
                        ball->Position.y += penetration;
                }
            }
        }
    }
    //检查 player pad
    Collision result = checkCollision(*ball, *player);
    if(!ball->stuck && std::get<0>(result))
    {
        GLfloat centerBoard = player->Position.x + player->Size.x /2;
        GLfloat distance = (ball->Position.x + ball->Radius) - centerBoard;
        GLfloat percentage = distance / (player->Size.x / 2 );
        
        GLfloat strength = 2.0f;
        glm::vec2 oldVelocity = ball->Velocity;
        ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
        ball->Velocity = glm::normalize(ball->Velocity) * glm::length(oldVelocity);
        ball->Velocity.y = -1 * abs(ball->Velocity.y);
    }
}

//AABB AABB 碰撞算法
GLboolean checkCollision(GameObject &one,GameObject &two)
{
    //AABB 碰撞算法 : 右下相互穿插
    bool collisionX = (one.Position.x + one.Size.x >= two.Position.x) && (two.Position.x + two.Size.x >= one.Position.x);
    bool collisionY = (one.Position.y + one.Size.y >= two.Position.y) && (two.Position.y + two.Size.y >= one.Position.y);
    return (collisionX && collisionY);
}

Collision checkCollision(BallObject &one, GameObject &two)
{
    //radius 碰AABB 算法
    glm::vec2 center(one.Position + one.Radius);
    glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y /2);
    glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x,two.Position.y + aabb_half_extents.y);
    
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    glm::vec2 closest = aabb_center + clamped;
    difference = closest - center;
    
    if(glm::length(difference) < one.Radius){
        return std::make_tuple(GL_TRUE,vectorDirection(difference),difference);
    }
    else{
        return std::make_tuple(GL_FALSE,UP,glm::vec2(0,0));
    }
}

//利用点积来求的对应的方向
Direction vectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f,1.0f),
        glm::vec2(1.0f,0.0f),
        glm::vec2(0.0f,-1.0f),
        glm::vec2(-1.0f,0.0f)
    };
    GLfloat max = 0.0f;
    GLuint best_match = -1;
    for(GLuint i=0; i < 4; i++){
        GLfloat dot_product = glm::dot(glm::normalize(target),compass[i]);
        if(dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}
