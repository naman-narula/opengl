/*Naman Narula
UE183060
TEST 1
press KEY UP for increasing speed and down for decreasing rotation speed
A for antiCW rotation C for CW ROTATION*/
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<bits/stdc++.h>
#define PI 3.14159265
#define WIDTH 640.0
#define HEIGHT 480.0
/*extern "C" 
{
  __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}*/



using namespace std;
char pending [650][650];


bool filled=false;
int x[2], y[2];
int xi,yi,fillcount=0,direction=1;
float inc=0.1f,addfactor=0.1f;
int count = 0;
size_t psize;
vector<int> points;
float fill_color[3]={0.0f,0.0f,1.0f};



void push(int tempx,int tempy)
{    points.push_back(tempx);
    points.push_back(tempy);  
}

void lines(int radius)
{
    int tempx,tempy;
    tempx=x[0]-radius;
    tempy=y[0];
    for(int i=0;i<=(2*radius);i++)
    {
        push(tempx+i,tempy);

    }
    tempx=x[0];
    tempy=y[0]-radius;
    for(int i=0;i<=(2*radius);i++)
    {
        push(tempx,tempy+i);
    }
    int limit=radius*cos(PI/4);
    tempx=x[0];
    tempy=y[0];
    for(int i=0;i<=limit;i++)
    {
        push(tempx+i,tempy+i);
        push(tempx-i,tempy-i);
        push(tempx+i,tempy-i);
        push(tempx-i,tempy+i);
   
    }
}



void midcircle()
{   int k=0;
    int modx []={1,1,-1,-1},mody []={1,-1,-1,1};
vector<int> X,Y;
    int radius =round(sqrt(pow(x[0]-x[1],2)+pow(y[0]-y[1],2)));
    pair<int,int> center=make_pair(x[0],y[0]);
    lines(radius);
    int P0=1-radius;
    int tempx=0,tempy=radius;
    int Pk,Pkn;
    Pk=P0;
    while(tempx<=tempy)
    {  
    
        if(Pk<0)
        {
            Pkn=Pk+2*tempx+3;

        }
        else
        {
            Pkn=Pk+2*tempx-2*tempy+5;
            tempy-=1;

        }
        Pk=Pkn;
        tempx+=1;
        
            X.push_back(tempx);
            Y.push_back(tempy);
            X.push_back(tempy);
            Y.push_back(tempx);
        
    }
   

        
    int size=X.size();

    for(int i=0;i<size;i++ )
    {   
        for(int z=0;z<4;z++)
        {   
           push(X[i]*modx[z]+center.first,Y[i]*mody[z]+center.second);
        }
    }
    
}


 void boundary_fill(int X, int Y){
        float c[3];
        glReadPixels(X,Y,1.0,1.0,GL_RGB,GL_FLOAT,c);

        if((c[0]!=1.0 &&c[2]!=fill_color[2] && pending[X][Y]=='d')||(c[0]!=1.0 && c[1]!=fill_color[1] && pending[X][Y]=='d')) {
                
           glBegin(GL_POINTS);
              glColor3fv(fill_color);
              glVertex2i(X, Y);
            glEnd();
            glFlush();
            if(fill_color[2]==1.0)
            {
                pending[X][Y]='b';
              //  std::cout<<"filled blue"<<"\n";
            }
            else if(fill_color[1]=1.0)
            {
                pending[X][Y]='g';
                //std::cout<<"filled green"<<"\n";
            }

           boundary_fill(X+1,Y);
            boundary_fill(X-1,Y);
            boundary_fill(X,Y+1);
            boundary_fill(X,Y-1);
        }

    }


void render()
{   if(filled)
    {
        glPushMatrix();
        glTranslatef(x[0],y[0],0.0);
        glRotatef(inc,0.0,0.0,1.0*direction);
        glTranslatef(-x[0],-y[0],0.0);
        glBegin(GL_POINTS);

        glColor3f(1.0,0.0,0.0);
        for(int i=0;i<points.size();i+=2)
        {
       
            glVertex2i(points[i],points[i+1]);
        
        }
    
        glEnd();
        glPopMatrix();
        glFlush();
    }
    else
    {
         glBegin(GL_POINTS);

        glColor3f(1.0,0.0,0.0);
        for(int i=0;i<points.size();i+=2)
        {
       
            glVertex2i(points[i],points[i+1]);
        
        }
    
        glEnd();
        glFlush();
    }
}
void render2()
{
   glPushMatrix();
    glTranslatef(x[0],y[0],0.0);
    glRotatef(inc,0.0,0.0,1.0*direction);
    glTranslatef(-x[0],-y[0],0.0);
    // draw
    glBegin(GL_POINTS);
    
    for(int i=0;i<650;i++)
    {
        for(int j=0;j<650;j++)
        {
            if(pending[i][j]=='b')
            {
                glColor3f(0.0,0.0,1.0);
                glVertex2i(i,j);
                }
            else if(pending[i][j]=='g')
            {
                glColor3f(0.0,1.0,0.0);
                glVertex2i(i,j);
            }
            
        }
    }
    glEnd();
   glPopMatrix();
    glFlush();

}
void mouse_button_callback(GLFWwindow* window, int button, int action,int mods)
{
    static int i = 0;
    if (!GLFW_RELEASE)
    {
        double xpos, ypos;
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            ::count = ::count % 2;
            glfwGetCursorPos(window, &xpos, &ypos);
            if (::count == 0)
            {

                memset(x, 0, sizeof(x));
                memset(y, 0, sizeof(y));

            }
            x[i&1] = (int)xpos;
            y[i&1] = HEIGHT-(int)ypos;
            i++;
            ::count++;
           

        }

        if (::count == 2)
        {
            
           midcircle();
        }
        if(button==GLFW_MOUSE_BUTTON_RIGHT && action==GLFW_PRESS)
        { fillcount++;
            glfwGetCursorPos(window,&xpos,&ypos);
            xi=xpos;
            yi=HEIGHT-ypos;
            boundary_fill(xi,yi);
            if(fillcount==8)
            filled=true;
            if(fill_color[2]==1.0)
            {
                fill_color[1]=1.0f;
                fill_color[2]=0.0f;
            }
            else
            {
                fill_color[1]=0.0f;
                fill_color[2]=1.0f;
            }
            

        }
    }
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{if(!GLFW_RELEASE)
    {
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        addfactor+=0.5;
    }
    if(key==GLFW_KEY_DOWN && action ==GLFW_PRESS)
    {
        addfactor-=0.5;
    }
    if(key==GLFW_KEY_C && action == GLFW_PRESS)
    {
        direction=-1;
    }
    if(key==GLFW_KEY_A && action == GLFW_PRESS)
    {
        direction=1;
       
    }

    }
}


int main()
{
    memset(pending,'d',sizeof(pending));
  

GLFWwindow* window;

/* Initialize the library */
if (!glfwInit())
return -1;

/* Create a windowed mode window and its OpenGL context */
window = glfwCreateWindow(WIDTH, HEIGHT, "circle", NULL, NULL);
if (!window)
{
glfwTerminate();
return -1;
}


glfwMakeContextCurrent(window);
glfwSetMouseButtonCallback(window, mouse_button_callback);
glfwSetKeyCallback(window, key_callback);
glewInit();
glfwSwapInterval(0);
glViewport(0,0,WIDTH,HEIGHT);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0.0,WIDTH,0.0,HEIGHT,0.0,1.0);

while (!glfwWindowShouldClose(window))
{

 
   inc+=addfactor;
   render();
    glfwSwapBuffers(window);
    glfwPollEvents();
    
    if(filled)
    render2();
   

}


std::cout<<glGetString(GL_VENDOR);
glfwTerminate();
}