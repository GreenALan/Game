//
//  SpriteRender.hpp
//  OpenGL
//
//  Created by lvshaohui on 2018/8/4.
//  Copyright © 2018年 lvshaohui. All rights reserved.
//

#ifndef SpriteRender_hpp
#define SpriteRender_hpp

#include <stdio.h>
#include "BaseInclude.h"
#include "texture.h"
#include "shader.h"
#include "SpriteRender.h"

class SpriteRender
{
public:
    SpriteRender(Shader &shader);
    ~SpriteRender();
    void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10,10), GLfloat rotate = 0.0f,glm::vec3 color = glm::vec3(1.0f));
private:
    Shader shader;
    GLuint quadVAO;
    void initRenderData();
};

#endif /* SpriteRender_hpp */
