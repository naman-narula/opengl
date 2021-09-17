#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<bits/stdc++.h>
#define WIDTH 640.0
#define HEIGHT 480.0

/*extern "C"
{
__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}*/

int x,y;

float colour[3] = {1.0, 0.0, 0.0}, fill_colour[3] = {0.0,0.0, 1.0};
void setpixel(int tempx,int tempy)
{

glBegin(GL_POINTS);
glColor3f(0.0,0.0,1.0);

glVertex2i(tempx,tempy);
glEnd();
glFlush();
}
void boundary_fill(int X, int Y){
float c[3];
glReadPixels(X,Y,1.0,1.0,GL_RGB,GL_FLOAT,c);

if(c[0]!=1.0 && c[2]!=1.0) {

glBegin(GL_POINTS);
glColor3fv(fill_colour);
glVertex2i(X, Y);
glEnd();

glFlush();
boundary_fill(X+1,Y);
boundary_fill(X-1,Y);
boundary_fill(X,Y+1);
boundary_fill(X,Y-1);
}

}

void mouse_button_callback(GLFWwindow* window, int button, int action,int mods)
{
if(button == GLFW_MOUSE_BUTTON_LEFT && action ==GLFW_RELEASE )
{
double xpos,ypos;
glfwGetCursorPos(window,&xpos,&ypos);

x=xpos;
y=ypos;
boundary_fill(x,HEIGHT-y);
}
}
int main()
{GLFWwindow* window;
float pixel[3];
/* Initialize the library */
if (!glfwInit())

return -1;

/* Create a windowed mode window and its OpenGL context */
window = glfwCreateWindow(WIDTH, HEIGHT, "boundfill", NULL, NULL);
if (!window)
{
glfwTerminate();
return -1;
}

/* Make the window's context current */
glfwSetMouseButtonCallback(window, mouse_button_callback);
glfwMakeContextCurrent(window);
glewInit();
glfwSwapInterval(1);
glViewport(0,0,WIDTH,HEIGHT);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0.0,WIDTH,0.0,HEIGHT,0.0,1.0);

float inc=1.0;
while (!glfwWindowShouldClose(window))
{

//glClear(GL_COLOR_BUFFER_BIT);

glBegin(GL_LINES);

glColor3fv(colour);
glVertex2i(100,300); // top left
glVertex2i(130, 300); // top right
glVertex2i(100, 270); // bottom right
glVertex2i(130, 270);
glVertex2i(100,300);
glVertex2i(100,270);
glVertex2i(130,300);
glVertex2i(130,270);
glEnd();

glfwSwapBuffers(window);
glfwPollEvents();

}
glfwTerminate();

}