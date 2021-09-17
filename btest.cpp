#include<GL/glew.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GLFW/glfw3.h>
#include<bits/stdc++.h>
#define WIDTH 640.0
#define HEIGHT 480.0
using namespace std;
vector<int> ictrlPoints;
vector<float> ctrlPoints;
float cpoints[][3]={ {4.0,0.0,0.0},{2.0,8.0,0.0},{8.0,12.0,0.0},{0.0,4.0,0.0}};

float knotvector[8]={0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0};
int cp;
void draw();
void mouse_button_callback(GLFWwindow* window,int button,int action,int mods)
{
    double xpos,ypos;
    if(!GLFW_RELEASE)
    {

        if(button==GLFW_MOUSE_BUTTON_LEFT && action==GLFW_PRESS)
        {
            glfwGetCursorPos(window,&xpos,&ypos);
            ctrlPoints.push_back((int)xpos);
            ctrlPoints.push_back(HEIGHT-(int)ypos);
            ictrlPoints.push_back((int)xpos);
            ictrlPoints.push_back(HEIGHT-(int)ypos);

        }
        if(button==GLFW_MOUSE_BUTTON_RIGHT && action==GLFW_PRESS)
        {
            glfwGetCursorPos(window,&xpos,&ypos);
            ictrlPoints.push_back((int)xpos);
            ictrlPoints.push_back(HEIGHT-(int)ypos);
            ctrlPoints.push_back((int)xpos);
            ctrlPoints.push_back(HEIGHT-(int)ypos);

            cp= ctrlPoints.size();
            
           
        }

    }

}
int main()
{
    
    glfwInit();
    

    GLFWwindow* window;
    window=glfwCreateWindow(WIDTH,HEIGHT,"bspline",NULL,NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetMouseButtonCallback(window,mouse_button_callback);
    glViewport(0,0,WIDTH,HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,WIDTH,0.0,HEIGHT);
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
       glVertex2i(100,200);
       glVertex2i(200,400);
        glEnd();
        draw();
     
       
        
   
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
void nurbsError(GLenum errorCode)
{
   const GLubyte *estring;

   estring = gluErrorString(errorCode);
   fprintf (stderr, "Nurbs Error: %s\n", estring);
   exit (0);
}
void draw()
{
  
    glEnable(GL_MAP1_VERTEX_3);
    GLUnurbsObj *bspline;
    bspline=gluNewNurbsRenderer();
    gluNurbsCallback(bspline,GLU_ERROR,(GLvoid(*)())nurbsError);
    gluBeginCurve(bspline);
    gluNurbsCurve(bspline,8,knotvector,3,&cpoints[0][0],4,GL_MAP1_VERTEX_3);
    gluEndCurve(bspline);
    

}