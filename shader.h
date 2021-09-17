#ifndef SHADER_H
#define SHADER_H
#include<glm/glm.hpp>
#include<Gl/glew.h>
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
class Shader
{
    public :
    unsigned int ProgramID;
    Shader(const char* vertexsource,const char*fragmentsource)
    {
        std::stringstream vbuffer,fbuffer;
        std::string vertex,fragment;
        std::ifstream vshader,fshader;
        vshader.open(vertexsource,std::ios::in);
        fshader.open(fragmentsource,std::ios::in);
       vbuffer<<vshader.rdbuf();
       fbuffer<<fshader.rdbuf();
       vshader.close();
       fshader.close();
       vertex=vbuffer.str();
       fragment=fbuffer.str();
       const char* vShaderCode=vertex.c_str();
       const char* fShaderCode=fragment.c_str();
       unsigned int vertexID,fragmentID;
       vertexID=glCreateShader(GL_VERTEX_SHADER);
       fragmentID=glCreateShader(GL_FRAGMENT_SHADER);
       glShaderSource(vertexID,1,&vShaderCode,NULL);
       glShaderSource(fragmentID,1,&fShaderCode,NULL);
       glCompileShader(vertexID);
       checkCompileError(vertexID,"Vertex");
       glCompileShader(fragmentID);
       checkCompileError(fragmentID,"fragment");
       ProgramID=glCreateProgram();
       glAttachShader(ProgramID,vertexID);
       glAttachShader(ProgramID,fragmentID);
       glLinkProgram(ProgramID);
       checkCompileError(ProgramID,"PROGRAM");
       glDeleteShader(vertexID);
       glDeleteShader(fragmentID);


    }
    void use()
    {
        glUseProgram(ProgramID);
    }
    void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ProgramID, name.c_str()), (int)value); 
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ProgramID, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ProgramID, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const
    { 
        glUniform2fv(glGetUniformLocation(ProgramID, name.c_str()), 1, &value[0]); 
    }
    void setVec2(const std::string &name, float x, float y) const
    { 
        glUniform2f(glGetUniformLocation(ProgramID, name.c_str()), x, y); 
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(ProgramID, name.c_str()), 1, &value[0]); 
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    { 
        glUniform3f(glGetUniformLocation(ProgramID, name.c_str()), x, y, z); 
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(ProgramID, name.c_str()), 1, &value[0]); 
    }
    void setVec4(const std::string &name, float x, float y, float z, float w) 
    { 
        glUniform4f(glGetUniformLocation(ProgramID, name.c_str()), x, y, z, w); 
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    private:
    void checkCompileError(GLuint shader,std::string type)
    {
        GLint Success;
        GLchar infoLog [512];
        if(type!="PROGRAM")
        {
            glGetShaderiv(shader,GL_COMPILE_STATUS,&Success);
            if(!Success)
            {
                glGetShaderInfoLog(shader,512,NULL,infoLog);
                std::cout<<type<<"shader failed to compile"<<"\n";
            }
        }
        else
        {
            glGetProgramiv(shader,GL_LINK_STATUS,&Success);
            if(!Success)
            {
                glGetProgramInfoLog(shader,512,NULL,infoLog);
                std::cout<<type<<"failed to link"<<"\n";
            }
        }
        
    }
    
};
#endif