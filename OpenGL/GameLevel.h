//
//  GameLevel.hpp
//  OpenGL
//
//  Created by lvshaohui on 2018/8/7.
//  Copyright © 2018年 lvshaohui. All rights reserved.
//

#ifndef GameLevel_hpp
#define GameLevel_hpp

#include "BaseInclude.h"
#include "GameObject.h"
#include "SpriteRender.h"
#include "ResourceManager.h"
#include <vector>

class GameLevel
{
public:
   // std::vector<GameObject> Bricks;
    std::vector<GameObject> Bricks;
    GameLevel() {}
    void Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
    void Draw(SpriteRender &renderer);
    GLboolean IsCompleted();
private:
    void init(std::vector<std::vector<GLuint>> tileData,GLuint levelWidth, GLuint levelHeight);
}; 

#endif /* GameLevel_hpp */
