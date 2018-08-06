//
//  texture.hpp
//  OpenGL
//
//  Created by lvshaohui on 2018/7/27.
//  Copyright © 2018年 lvshaohui. All rights reserved.
//

#ifndef texture_hpp
#define texture_hpp

#include "BaseInclude.h"

class Texture2D {
public:
    GLuint ID;
    GLuint Width,Height;
    GLuint Internal_Format;
    GLuint Image_Format;
    
    GLuint Wrap_S;
    GLuint Wrap_T;
    GLuint Filter_Min;
    GLuint Filter_Max;
    
    Texture2D();
    void Generate(GLuint width, GLuint height, unsigned char *data);
    void Bind() const;
};
#endif /* texture_hpp */
