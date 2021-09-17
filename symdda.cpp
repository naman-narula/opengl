#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<bits/stdc++.h>
int count = 0;
int x[2], y[2];
std::vector<float> points;
int pattern,thickness;
int psize = 0;
unsigned int nextPowerOf2(unsigned int n)
{
int count = 0;

if (n && !(n & (n - 1)))
return n;

while (n != 0)
{
n >>= 1;
count += 1;
}

return 1 << count;
}
void DDA()
{
   for(int i=0;i<thickness;i++)
   { 
    float dx = x[1] - x[0];
    float dy = y[1] - y[0];
    int step = nextPowerOf2(std::max(abs(dx), abs(dy)));
    //cout << dx << " " << dy << endl;
    dx = dx / step;
    dy = dy / step;
    float x1 = x[0];
    float y1 = y[0];
    float x2 = x[1];
    float y2 = y[1];
    x1 = (x1 / 320 - 1.0);
    y1 = -(y1 / 240 - 1.0);
    x2 = (x2 / 320 - 1.0);
    y2 = -(y2 / 240 - 1.0);
    float currentx = x[0];
    float currenty = y[0];
   int z=0;
    for (long long k = 0; k <= step; k++)
    {
    currentx = (currentx + dx);
    currenty = (currenty + dy);
    x1 = (currentx / 320 - 1.0);
    y1 = -(currenty / 240 - 1.0);


    if((pattern>>z)&1)
    {
    points.push_back(x1);
    points.push_back(y1);

    }
    z++;
    z=z%4;
    }
    if (dy < 0)
		{
			x[0]++; x[1]++;
		}
		else
		{
			x[0]--; x[1]--;
		}
		y[0]++; y[1]++;
   }

}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
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
x[i % 2] = (int)xpos;
y[i % 2] = (int)ypos;

i++;
::count++;

}
if (::count >= 2)
{
DDA();
glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(),

GL_DYNAMIC_DRAW);

psize = points.size();
points.clear();

}

}
}
int main()
{
GLFWwindow* window;

/* Initialize the library */
if (!glfwInit())
return -1;

/* Create a windowed mode window and its OpenGL context */
window = glfwCreateWindow(640, 480, "SymDDA", NULL, NULL);
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
std::cout<<"enter pattern and thickness";
std::cin>>std::hex>>pattern;
std::cin>>thickness;

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

"FragColor = vec4(0.2f, 1.8f, 0.8f, 1.0f);\n"
"}\0";
glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
glCompileShader(fragmentShader);
ShaderProgram = glCreateProgram();
glAttachShader(ShaderProgram, vertexShader);
glAttachShader(ShaderProgram, fragmentShader);
glLinkProgram(ShaderProgram);
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);
glEnableVertexAttribArray(0);

while (!glfwWindowShouldClose(window))
{

glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_LINES);
	glVertex2f(-1.0,0.0);
	glVertex2f(1.0,0.0);
	glVertex2f(0.0,1.0);
	glVertex2f(0.0,-1.0);
	glEnd();
glUseProgram(ShaderProgram);
if (::count >= 2)
{

glDrawArrays(GL_POINTS, 0, psize);
}
glfwSwapBuffers(window);
glfwPollEvents();

}
glDeleteBuffers(1, &VBO);
glDeleteProgram(ShaderProgram);
glfwTerminate();
}