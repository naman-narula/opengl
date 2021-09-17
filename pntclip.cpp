#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#define WIDTH 640.0
#define HEIGHT 480.0
int windowcoord[4],pointcoord[2];
int count=0;
bool draw=false,point=false;
void mouse_button_callback(GLFWwindow* window,int button,int action,int mods)
{double xpos,ypos;
    if(!GLFW_RELEASE)
    {static int i=0;
    // std::cout<<i;
        if(button==GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            glfwGetCursorPos(window,&xpos,&ypos);
            windowcoord[i]=(int)xpos;
            i++;
            windowcoord[i]=HEIGHT-(int)ypos;
            i++;
            count++;
        }
        if(count>=2)
        {
            draw=true;
           
        }
        if(button==GLFW_MOUSE_BUTTON_RIGHT && action ==GLFW_PRESS)
        {
           
            glfwGetCursorPos(window,&xpos,&ypos);
           
           pointcoord[0]=(int)xpos;
           pointcoord[1]=HEIGHT-(int)ypos;
            if(xpos<windowcoord[2] && xpos>windowcoord[0])
            {   
                if((HEIGHT-ypos)<windowcoord[3] && (HEIGHT-ypos)>windowcoord[1])
                    point =true;
                     //std::cout<<"right";
                     else 
                     point=false;
            }
            else
            {//std::cout<<"out";
                point=false;
            }
        }
      
    }
}
int main()
{
    glfwInit();
    GLFWwindow* window;
    window=glfwCreateWindow(WIDTH,HEIGHT,"point clip",NULL,NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetMouseButtonCallback(window,mouse_button_callback);
    glViewport(0,0,WIDTH,HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,WIDTH,0.0,HEIGHT,0.0,1.0);
       
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
       if(draw)
       {
           glBegin(GL_LINE_LOOP);
           glColor3f(0.5,0.5,0.0);
           glVertex2i(windowcoord[0],windowcoord[1]);
           glVertex2i(windowcoord[0],windowcoord[3]);
           glVertex2i(windowcoord[2],windowcoord[3]);
           glVertex2i(windowcoord[2],windowcoord[1]);
           glEnd();
           glBegin(GL_POINTS);
           if(point==false)
           glColor3f(1.0,0.0,0.0);
           else
           glColor3f(0.0,1.0,0.0);
           glVertex2i(pointcoord[0],pointcoord[1]);
           glEnd();
            
       }
   
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}