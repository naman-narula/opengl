#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<GL/glu.h>
#include<bits/stdc++.h>
#define WIDTH 640.0
#define HEIGHT 480.0
using namespace std;
vector<int> pointx,pointy;
vector<int> cpx,cpy;
bool ok=false;
int factorial(int n) 
{ 

    return (n==1 || n==0) ? 1: n * factorial(n - 1);  
} 
int coefficent(int n,int k)
{
    return(factorial(n)/(factorial(k)*factorial(n-k)));

}
void draw()
{
    int totalcp=cpx.size();
    int bx[totalcp],by[totalcp];
    int temp;
    for(int i=0;i<totalcp;i++)
    {
        temp=coefficent(totalcp-1,i);
        bx[i]=cpx[i]*temp;
        by[i]=cpy[i]*temp;
    }
    double temp1=0,ans1=0,ans2=0;
    for(float i=0.00;i<=1.00;i+=0.01)
    {
        for(int j=0;j<totalcp;j++)
        {
            temp1=pow(i,j)*pow(1.00-i,totalcp-1-j);
            //cout<<temp1<<"\n";
            ans1+=bx[j]*temp1;
            ans2+=by[j]*temp1;
        }
       // cout<<ans1<<" "<<ans2<<"\n";
       
        pointx.push_back((int)ans1);
        pointy.push_back((int)ans2);
         ans1=ans2=0;
    }
    


    
}

void mouse_button_callback(GLFWwindow* window,int button,int action,int mods)
{
    double xpos,ypos;
    if(!GLFW_RELEASE)
    {

        if(button==GLFW_MOUSE_BUTTON_LEFT && action==GLFW_PRESS)
        {
            glfwGetCursorPos(window,&xpos,&ypos);
            cpx.push_back((int)xpos);
            cpy.push_back(HEIGHT-(int)ypos);

        }
        if(button==GLFW_MOUSE_BUTTON_RIGHT && action==GLFW_PRESS)
        {
            glfwGetCursorPos(window,&xpos,&ypos);
            cpx.push_back((int)xpos);
            cpy.push_back(HEIGHT-(int)ypos);
            draw();
            ok=true;

        }

    }

}
int main()
{
    glfwInit();
    GLFWwindow* window;
    window=glfwCreateWindow(WIDTH,HEIGHT,"bezier",NULL,NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetMouseButtonCallback(window,mouse_button_callback);
    glViewport(0,0,WIDTH,HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,WIDTH,0.0,HEIGHT,0.0,1.0);
       
    while(!glfwWindowShouldClose(window))
    {   glPointSize(5);
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POINTS);
        glColor3f(1.0,0.0,0.0);
        for(int i=0;i<cpx.size();i++)
        {
            glVertex2i(cpx[i],cpy[i]);
        }
        glEnd();
        glPointSize(1);
        if(ok)
        {
        glBegin(GL_LINES);
        glColor3f(0.0,0.0,1.0);
        for(int i=0;i<pointx.size()-1;i++)
        {
            glVertex2i(pointx[i],pointy[i]);
            glVertex2i(pointx[i+1],pointy[i+1]);
        }
        glEnd();
        }
   
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}