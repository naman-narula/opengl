#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<math.h>
using namespace std;
int x=150 ,y=150;
#define WIDTH 700
#define HEIGHT 700
bool mousedown =false;
char type ='n';
float scalex=1.0,scaley=1.0;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(!GLFW_RELEASE)
    {
    if (key == GLFW_KEY_T && action == GLFW_PRESS)
    {
        type ='t';
    }
    if(key==GLFW_KEY_S && action ==GLFW_PRESS)
    {
        type='s';
    }
    if(key==GLFW_KEY_R && action == GLFW_PRESS)
    {
        type='r';
    }
    if(key==GLFW_KEY_UP && action == GLFW_PRESS)
    {
        scaley=scaley+0.1;
    }
    if(key==GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        scaley=scaley-0.1;
    }
    if(key==GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        scalex=scalex+0.1;
    }
    if(key==GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        scalex=scalex-0.1;
    }
    if(key==GLFW_KEY_C && action == GLFW_PRESS)
    {
        type='c';
    }

    

    }
}
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(mousedown)
    {
         glfwGetCursorPos(window,&xpos,&ypos);
         x=xpos;
         y=HEIGHT-ypos;
         //cout<<x<<" "<<y<<endl;

    }
}
void mouse_button_callback(GLFWwindow* window, int button, int action,int mods)
{

if(button == GLFW_MOUSE_BUTTON_LEFT)
{
    if(action==GLFW_PRESS)
    {
    mousedown=true;
   
    }
    
  
    
    else if(action==GLFW_RELEASE)
    {
    mousedown=false;
   
    }
     
}
}

// glPushMatrix();
//     glTranslatef(x[0],y[0],0.0);
//     glRotatef(inc,0.0,0.0,1.0*direction);
//     glTranslatef(-x[0],-y[0],0.0);
//      glPopMatrix();
int main()
{

    glfwInit();
    GLFWwindow* window;
    window = glfwCreateWindow(WIDTH, HEIGHT, "Transformation", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetKeyCallback(window, key_callback);
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIDTH, 0.0, HEIGHT, 0.0, 1.0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_QUADS);
        glColor3f(1.0,0.0,0.0);
        glVertex2i(100,200);
        glVertex2i(200,200);
        glVertex2i(200,100);
        glVertex2i(100,100);
        glEnd();
        switch(type)
        {
            case 't':
                    {glPushMatrix();
                    glTranslatef(x-150,y-150,0.0);//translate by distance of differnce between click and centre of square
                    glBegin(GL_QUADS);
                    glColor3f(0.0,1.0,0.0);
                    glVertex2i(100,200);
                    glVertex2i(200,200);
                    glVertex2i(200,100);
                    glVertex2i(100,100);
                    glEnd();
                    glPopMatrix();
                    glFlush();
                    break;
                    }
            case 's':
                    {
                    glPushMatrix();
                    
                   glTranslatef(150,150,0.0);
                    glScalef(scalex,scaley,0.0);
                   glTranslatef(-150,-150,0.0);
                    glBegin(GL_QUADS);
                    glColor3f(0.0,1.0,0.0);
                    glVertex2i(100,200);
                    glVertex2i(200,200);
                    glVertex2i(200,100);
                    glVertex2i(100,100);
                    glEnd();
                    glPopMatrix();
                    glFlush();
                    break;
                    }
            case 'r': {
                    float angle=atan2((y-150),(x-150))*57.2957795131;
                    glPushMatrix();
                    glTranslatef(150,150,0.0);
                    glRotatef(angle,0.0,0.0,1.0);
                    glTranslatef(-150,-150,0.0);
                    glBegin(GL_QUADS);
                    glColor3f(0.0,1.0,0.0);
                    glVertex2i(100,200);
                    glVertex2i(200,200);
                    glVertex2i(200,100);
                    glVertex2i(100,100);
                    glEnd();
                    glPopMatrix();
                    glFlush();
                     break;
            }

            case 'c': 
                    {float angle=atan2((y-150),(x-150))*57.2957795131;
                    glPushMatrix();
                    glTranslatef(x-150,y-150,0.0);//translate by distance of differnce between click and centre of square
                    glTranslatef(150,150,0.0);
                    glScalef(scalex,scaley,0.0);
                    // glTranslatef(-150,-150,0.0);
                    // glTranslatef(150,150,0.0);
                    glRotatef(angle,0.0,0.0,1.0);
                    glTranslatef(-150,-150,0.0);
                    glBegin(GL_QUADS);
                    glColor3f(0.0,1.0,0.0);
                    glVertex2i(100,200);
                    glVertex2i(200,200);
                    glVertex2i(200,100);
                    glVertex2i(100,100);
                    glEnd();
                    glPopMatrix();
                    glFlush();
                    break;
                    }
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
