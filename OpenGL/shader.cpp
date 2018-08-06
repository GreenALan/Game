//
//  shader.cpp
//  OpenGL
//
//  Created by lvshaohui on 2018/7/26.
//  Copyright © 2018年 lvshaohui. All rights reserved.
//

#include "shader.h"
#include <iostream>

Shader &Shader::use()
{
    glUseProgram(this->ID);
    return *this;
}

void Shader::Compile(const char *vertexSource, const char * fragmentSource, const char* geometrySource)
{
    GLuint sVertex, sFragment, gShader;
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex,1,&vertexSource,NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment,1,&fragmentSource,NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    
    if(geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader,1,&geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }
    this->ID = glCreateProgram();
    glAttachShader(this->ID,sVertex);
    glAttachShader(this->ID,sFragment);
    if(geometrySource != nullptr)
    {
        glAttachShader(this->ID,gShader);
    }
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if(geometrySource != nullptr)
        glDeleteShader(gShader);
}


void Shader::setFloat(const GLchar *name, GLfloat value, GLboolean useShader)
{
    if(useShader)
        this->use();
    glUniform1f(glGetUniformLocation(this->ID,name),value);
}

void Shader::setInteger(const GLchar *name, GLint value,GLboolean useShader)
{
    if(useShader)
        this->use();
    glUniform1i(glGetUniformLocation(this->ID,name),value);
}

void Shader::setVector2f(const GLchar *name, GLfloat x, GLfloat y,GLboolean useShader)
{
    if(useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->ID,name),x,y);
}

void Shader::setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader)
{
    if(useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->ID,name),value.x,value.y);
}

void Shader::setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z,GLboolean useShader)
{
    if(useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->ID,name),x,y,z);
}

void Shader::setVector3f(const GLchar *name, const glm::vec3 &value,GLboolean useShader)
{
    if(useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->ID,name),value.x,value.y,value.z);
}

void Shader::setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w,GLboolean useShader)
{
    if(useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->ID,name),x,y,z,w);
}

void Shader::setVector4f(const GLchar *name, const glm::vec4 &value,GLboolean useShader)
{
    if(useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->ID,name),value.x,value.y,value.z,value.w);
}

void Shader::setMatrix4(const GLchar *name, const glm::mat4 &matrix,GLboolean useShader)
{
    if(useShader)
        this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID,name),1,GL_FALSE,glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(GLuint object, std::string type)
{
    
}
