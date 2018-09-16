//
//  BallObject.hpp
//  OpenGL
//
//  Created by lvshaohui on 2018/8/23.
//  Copyright © 2018年 lvshaohui. All rights reserved.
//

#ifndef BallObject_hpp
#define BallObject_hpp

#include <stdio.h>
#include "GameObject.h"
#include "texture.h"
#include "SpriteRender.h"

class BallObject : public GameObject
{
public:
    GLfloat Radius;
    GLboolean stuck;
    BallObject();
    BallObject(glm::vec2 pos,GLfloat radius,glm::vec2 velocity, Texture2D sprite);
    
    glm::vec2 Move(GLfloat dt, GLuint window_width);
    void Reset(glm::vec2 position,glm::vec2 velocity);
};

#endif /* BallObject_hpp */
