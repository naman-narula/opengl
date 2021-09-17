#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<bits/stdc++.h>
#define WIDTH 640.0
#define HEIGHT 480.0
int windowcoord[4],pointcoordx[2],pointcoordy[2],line[4];
int count=0,pcount=0;
bool draw=false;
bool visible=true;
void liang()
{
    int p[5],q[5];float u[5];
    p[2]=pointcoordx[1]-pointcoordx[0];
    p[1]=-p[2];
    p[4]=pointcoordy[1]-pointcoordy[0];
    p[3]=-p[4];
    q[1]=pointcoordx[0]-std::min(windowcoord[0],windowcoord[2]);
    q[2]=std::max(windowcoord[0],windowcoord[2])-pointcoordx[0];
    q[3]=pointcoordy[0]-std::min(windowcoord[1],windowcoord[3]);
    q[4]=std::max(windowcoord[3],windowcoord[1])-pointcoordy[0];
    for(int i=1;i<=4;i++)
    {
       
        {
            u[i]=(float)q[i]/(float)p[i];
            //std::cout<<u[i]<<" "<<i<<"cal"<<"\n";
        }
    }
    if(visible)
    {
    float r1=-1,r2=INT_MAX;
    for(int i=1;i<=4;i++)
    {
        if(p[i]<0)
        {
            r1=std::max((float)0.0,std::max(r1,u[i]));
        }
        if(p[i]>0)
        {
            r2=std::min((float)1.0,std::min(r2,u[i]));
        }
    }
    //std::cout<<r1<<" "<<r2<<"\n";
    line[0]=int(pointcoordx[0]+r1*p[2]);
    line[1]=int(pointcoordy[0]+r1*p[4]);
    line[2]=int(pointcoordx[0]+r2*p[2]);
    line[3]=int(pointcoordy[0]+r2*p[4]);

     q[1]=  line[0]-std::min(windowcoord[0],windowcoord[2]);
     q[2]=std::max(windowcoord[0],windowcoord[2])-line[0];
     q[3]=line[1]-std::min(windowcoord[1],windowcoord[3]);
     q[4]=std::max(windowcoord[3],windowcoord[1])-line[1];
     for(int i=1;i<=4;i++)
    {
        if(q[i]<0)
        {
            visible=false;
            std::cout<<q[i]<<" "<<i;
        }   
    
    }
    }
}
void mouse_button_callback(GLFWwindow* window,int button,int action,int mods)
{double xpos,ypos;
    if(!GLFW_RELEASE)
    {static int i=0,j=0;
    //std::cout<<i;
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
           
           pointcoordx[j]=(int)xpos;
           pointcoordy[j]=HEIGHT-(int)ypos;
           pcount++;
           j++;
        }
        if(pcount>=2)
        {
            liang();
        }
      
    }
}
int main()
{
    glfwInit();
    GLFWwindow* window;
    window=glfwCreateWindow(WIDTH,HEIGHT,"line clip",NULL,NULL);
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
           if(pcount>=2)
           {
           glBegin(GL_LINES);
           glColor3f(1.0,0.0,0.0);
           glVertex2i(pointcoordx[0],pointcoordy[0]);
           glVertex2i(pointcoordx[1],pointcoordy[1]);
           if(visible==true)
           {
           glColor3f(0.0,1.0,0.0);
           glVertex2i(line[0],line[1]);
           glVertex2i(line[2],line[3]);
           }
           glEnd();
           }
       }
   
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}