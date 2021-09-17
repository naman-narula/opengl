#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<bits/stdc++.h>
using namespace std;
int x[2], y[2];
int count = 0;
size_t psize;
vector<float> points;
int pattern,thickness;


void push(int tempx,int tempy)
{
    
    
    float ax,ay;
    ax = (float)(tempx / 320.0 - 1.0);
    ay = -(float)(tempy / 240.0 - 1.0);
    points.push_back(ax);
    points.push_back(ay);
    
    
}


void midcircle()
{   
    for(int t=0;t<thickness;t++)
    {


        int k=0;
        int modx []={1,1,-1,-1},mody []={1,-1,-1,1};
        vector<int> X,Y;
        int radius =round(sqrt(pow(x[0]-x[1],2)+pow(y[0]-y[1],2)))-t;
        pair<int,int> center=make_pair(x[0],y[0]);
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
            if((pattern>>k)&1)
            {    X.push_back(tempx);
                Y.push_back(tempy);
                X.push_back(tempy);
                Y.push_back(tempx);
            }
            k++;
            k=k%4;
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

}
void mouse_button_callback(GLFWwindow* window, int button, int action,int mods)
{
static int i = 0;
if (!GLFW_RELEASE)
{
//cout << i << endl;
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
y[i&1] = (int)ypos;
//cout << xpos << " " << ypos << "\n";
i++;
::count++;

}

if (::count == 2)
{
midcircle();
//cout << "bresnham" << endl;
/*for (int i = 0; i < points.size(); i++)
{
cout << points[i] << "\n";
}*/
glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(),GL_DYNAMIC_DRAW);

psize = points.size();

points.clear();

}
}
}
int main()
{
    std::cout<<"enter pattern in hex digits and thickness";
    cin>>hex>>pattern;
    cin>>thickness;

  

GLFWwindow* window;

/* Initialize the library */
if (!glfwInit())
return -1;

/* Create a windowed mode window and its OpenGL context */
window = glfwCreateWindow(640, 480, "circle", NULL, NULL);
if (!window)
{
glfwTerminate();
return -1;
}

/* Make the window's context current */
glfwMakeContextCurrent(window);
glfwSetMouseButtonCallback(window, mouse_button_callback);
glewInit();
GLuint ShaderProgram;
GLuint VBO;
glGenBuffers(1, &VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);

const char* vShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vShaderSource, NULL);
glCompileShader(vertexShader);

GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
const char* fShaderSource = "#version 330 core\n"
" out vec4 FragColor;\n"

"void main()\n"
"{\n"

"FragColor = vec4(0.0f, 0.0f, 0.8f, 1.0f);\n"
"}\0";
glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
glCompileShader(fragmentShader);
ShaderProgram = glCreateProgram();
glAttachShader(ShaderProgram, vertexShader);
glAttachShader(ShaderProgram, fragmentShader);
glLinkProgram(ShaderProgram);
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (const void*)0);
glEnableVertexAttribArray(0);

while (!glfwWindowShouldClose(window))
{

glClear(GL_COLOR_BUFFER_BIT);
glUseProgram(ShaderProgram);
	glBegin(GL_LINES);
	glVertex2f(-1.0,0.0);
	glVertex2f(1.0,0.0);
	glVertex2f(0.0,1.0);
	glVertex2f(0.0,-1.0);
	glEnd();
if (::count >= 2)
{

glDrawArrays(GL_POINTS, 0, psize);
}
glfwSwapBuffers(window);
glfwPollEvents();

}

glDeleteBuffers(1, &VBO);
glDeleteProgram(ShaderProgram);
std::cout<<glGetString(GL_VENDOR);
glfwTerminate();
}