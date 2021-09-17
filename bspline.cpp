#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<bits/stdc++.h>
#define WIDTH 640.0
#define HEIGHT 480.0
using namespace std;
vector<int> cpx,cpy;
vector<int> pointx,pointy;
vector<int> knot_vector(50);


const int order=4;
int cp;
void calcknot(){


        int n = cpx.size()-1;
        int degree = order-1;
        int m = n+degree+1;
           

        for(int k=0;k<=m;k++){
            if(k<degree+1){
                knot_vector[k] = 0;
            }
            else if(k>=(degree+1) && k<=n){
                knot_vector[k] = k-degree;
            }
            else if(k>n){
                knot_vector[k] = n-degree+1;
            }
        }
       

    }
float bspline(int k, int m,double u){
    float c1 = 0.0, c2 = 0.0;
    if(m ==1){
        if(u>=knot_vector[k] && u<=knot_vector[k+1]){
            
            return 1;
        }
        else{
            
            return 0;
        }
    }
 

    float t1 = knot_vector[k+m-1]-knot_vector[k];
    float t2 = knot_vector[k+m]-knot_vector[k+1];
        if(t1!=0){
                c1 = (((u-knot_vector[k])/(t1))*bspline(k,m-1,u));
        }
        if(t2!=0){
                c2 = (((knot_vector[k+m] - u)/(t2))*bspline(k+1, m-1,u));
        }
    return c1+c2;
}

void draw()
{   
    
   
    double step_size = 0.001, temp;
    for(double j = knot_vector[0]; j<=knot_vector[cpx.size()]; j+=step_size){
       
        double sum_x = 0.0, sum_y = 0.0;
        for(int i = 0;i<=cpx.size()-1;i++){
        temp = bspline(i,order, j);
        sum_x += temp*cpx[i];
        sum_y += temp*cpy[i];
        }
        pointx.push_back((int)sum_x);
        pointy.push_back((int)sum_y);
        
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
            cp=cpx.size();
            calcknot();
            draw();
           for(int i=0;i<cp+order;i++)
           {
               cout<<knot_vector[i]<<"\n";
           }
          
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
    glOrtho(0.0,WIDTH,0.0,HEIGHT,0.0,1.0);
       
    while(!glfwWindowShouldClose(window))
    {   glPointSize(5);
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POINTS);
        glColor3f(1.0,0.0,1.0);
        
        for(int i=0;i<cpx.size();i++)
        {
            glVertex2i(cpx[i],cpy[i]);
        }
        glEnd();
        glPointSize(1);
        glBegin(GL_POINTS);
        glColor3f(1.0,1.0,1.0);
        for(int i=0;i<pointx.size();i++)
        {   
            glVertex2i(pointx[i],pointy[i]);
            
        }
        glEnd();
        
   
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
}