//
//  GameObject.hpp
//  OpenGL
//
//  Created by lvshaohui on 2018/8/7.
//  Copyright © 2018年 lvshaohui. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "BaseInclude.h"
#include "texture.h"
#include "SpriteRender.h"

class GameObject
{
public :
    glm::vec2 Position,Size, Velocity; //对象位置，大小，速率
    glm::vec3 Color; //颜色
    GLfloat Rotation; //旋转
    GLboolean IsSolid; // 是否坚硬
    GLboolean Destroyed; //是否被摧毁
    
    Texture2D Spite; //精灵
    
    GameObject();
    GameObject(glm::vec2 pos,glm::vec2 size,Texture2D sprite, glm::vec3 color = glm::vec3(1.0f),glm::vec2 velocity = glm::vec2(0.0f,0.0f))  ;
    virtual void Draw(SpriteRender &render);
};

#endif /* GameObject_hpp */
