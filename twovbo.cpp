#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"shader.h"
#define WIDTH 1024.0
#define HEIGHT 768.0
  int main()
  { float vertices1[]={
      0.7,0.5,0.0,
      0.2,0.2,0.0,
      0.9,0.2,0.0
  };
  float vertices2[]={
      -0.7,0.5,0.0,
      -0.2,0.2,0.0,
      -0.9,0.2,0.0
  };
  glfwInit();
      GLFWwindow* window;
      window=glfwCreateWindow(WIDTH,HEIGHT,"TWO TRIANGLES",NULL,NULL);
      glfwMakeContextCurrent(window);
      glewInit();
      Shader ourshader("vshader.shader","yfshader.shader");
      unsigned int VBO[2],VAO[2];
        glGenVertexArrays(2,VAO);
      glGenBuffers(2,VBO);
      glBindVertexArray(VAO[0]);
        glBindBuffer(GL_ARRAY_BUFFER,VBO[0]);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
      glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(const void*)0);
      glEnableVertexAttribArray(0);
    glBindVertexArray(VAO[1]);
     glBindBuffer(GL_ARRAY_BUFFER,VBO[1]);
      glBufferData(GL_ARRAY_BUFFER,sizeof(vertices2),vertices2,GL_STATIC_DRAW);
      glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
      glEnableVertexAttribArray(0);
     // glBindVertexArray(0);
      ourshader.use();
     // ourshader.setVec4("u_color",1.0f, 1.0f, 0.0f, 1.0f);  
     Shader shader2("vshader.shader","fshader.shader");
      shader2.use();
      //shader2.setVec4("u_color",0.0f, 1.0f, 0.0f, 1.0f);
      while(!glfwWindowShouldClose(window))
      {
          glClear(GL_COLOR_BUFFER_BIT);
          glBindVertexArray(VAO[0]);
            ourshader.use();
          glDrawArrays(GL_TRIANGLES,0,3);
          glBindVertexArray(VAO[1]);
          shader2.use();
        //  shader2.setFloat("offset",0.0);
         glDrawArrays(GL_TRIANGLES,0,3);
          glfwSwapBuffers(window);
          glfwPollEvents();
      }
      glDeleteVertexArrays(2,VAO);
      glDeleteBuffers(2,VBO);
      glfwTerminate();


      
      
  }