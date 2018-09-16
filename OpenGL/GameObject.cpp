//
//  GameObject.cpp
//  OpenGL
//
//  Created by lvshaohui on 2018/8/7.
//  Copyright © 2018年 lvshaohui. All rights reserved.
//

#include "GameObject.h"

GameObject::GameObject():
    Position(0,0),
    Size(1,1),
    Velocity(0.0f),
    Color(1.0f),
    Rotation(0.0f),
    IsSolid(false),
    Destroyed(false)
{
    
}

GameObject::GameObject(glm::vec2 pos,glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity):
    Position(pos),
    Size(size),
    Velocity(velocity),
    Color(color),
    Rotation(0.0f),
    Spite(sprite),
    IsSolid(false),
    Destroyed(false)
{
    
}

void GameObject::Draw(SpriteRender &render)
{
    render.DrawSprite(this->Spite, this->Position,this->Size,this->Rotation,this->Color);
}
