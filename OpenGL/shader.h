//
//  shader.hpp
//  OpenGL
//
//  Created by lvshaohui on 2018/7/26.
//  Copyright © 2018年 lvshaohui. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include <string.h>
#include "BaseInclude.h"



#include <string>

using namespace std;

class Shader
{
public:
    GLuint ID;
    Shader() {};
    Shader &use();
    void Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr);
    
    void setFloat (const GLchar *name, GLfloat value, GLboolean useShader = false);
    void setInteger(const GLchar *name, GLint value, GLboolean useShader = false);
    void setVector2f(const GLchar *name, GLfloat x, GLfloat y,GLboolean useShader = false);
    void setVector2f(const GLchar *name, const glm::vec2 &value,GLboolean useShader = false);
    void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void setVector3f(const GLchar *name, const glm::vec3 &value,GLboolean useShader =false);
    void setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
    void setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
private:
    //check if compilation or linking failed and if so
    void checkCompileErrors(GLuint object, std::string type);
};

#endif /* shader_hpp */
