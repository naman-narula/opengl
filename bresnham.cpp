#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<bits/stdc++.h>
using namespace std;
int x[2], y[2];
int count = 0;
size_t psize;
vector<double> points;
int pattern,thickness;
void bresnham()
{
    for(int i=0;i<thickness;i++)
    {
int dx, dy, P0, Pk, Pkn ,c = 1;

dx = x[1] - x[0];
dy = y[1] - y[0];
int tempx, tempy;
tempx = x[0];
tempy = y[0];
double slope=(double)dy/dx;

//std::cout <<" slope"<<abs(slope)<<" "<<slope << endl;

if (abs(slope) == 1)
{
double ax, ay;
tempx = tempx + 1;
tempy = tempy + 1;

ax = (double)(tempx / 320.0 - 1.0);
ay = -(double)(tempy / 240.0 - 1.0);
points.push_back(ax);
points.push_back(ay);

}

if (slope > 1)
{
P0 = (2 * dx) - dy;
Pk = P0;
int k = 2 * dx - 2 * dy;

//cout << c;
double ax, ay;
int z=0;
for (int i = 1; i <=abs( dy); i++)
{
if (Pk < 0)
{
Pkn = Pk + 2 * dx;
tempy = tempy + c;
ax = (double)(tempx / 320.0 - 1.0);
ay = -(double)(tempy / 240.0 - 1.0);
    
	if ((pattern >> z) & 1)
	{
				

	    points.push_back(ax);
		points.push_back(ay);
				
	}
	z++;
	z = z % 4;

Pk = Pkn;
//cout << tempx << " " << tempy << endl;
continue;
}
Pkn = Pk + k;
Pk = Pkn;
tempx = tempx + 1;
tempy = tempy + 1;
ax = (double)(tempx / 320 - 1.0);
ay = -(double)(tempy / 240 - 1.0);
 
	if ((pattern >> z) & 1)
	{
				

	    points.push_back(ax);
		points.push_back(ay);
				
	}
	z++;
	z = z % 4;

}
}

if(slope<1 && slope>0)
{
P0 = (2 * dy) - dx;
Pk = P0;
int k = 2 * dy - 2 * dx;
//cout << c;

double ax, ay;
int z=0;
for (int i = 1; i <= dx; i++)
{
if (Pk < 0)
{
Pkn = Pk + 2 * dy;
tempx = tempx + 1;

ax = (double)(tempx / 320.0 - 1.0);
ay = -(double)(tempy / 240.0 - 1.0);

	if ((pattern >> z) & 1)
	{
				

	    points.push_back(ax);
		points.push_back(ay);
				
	}
	z++;
	z = z % 4;

Pk = Pkn;
//cout << tempx << " " << tempy << endl;
continue;
}
Pkn = Pk + k;
Pk = Pkn;
tempx = tempx + 1;
tempy = tempy + 1;
ax = (double)(tempx / 320 - 1.0);
ay = -(double)(tempy / 240 - 1.0);
//std::cout<< tempx << " " << tempy << endl;
 
	if ((pattern >> z) & 1)
	{
				

	    points.push_back(ax);
		points.push_back(ay);
				
	}
	z++;
	z = z % 4;

}
}

if (slope > -1 && slope<0)
{
P0 = (2 * dy) - dx;
Pk = P0;
int k = 2 * dy +2 * dx;
//cout << c;

double ax, ay;
int z=0;
for (int i = 1; i <= dx; i++)
{
if (Pk < 0)
{
Pkn = Pk + k;
tempx = tempx + 1;

tempy = tempy - 1;
ax = (double)(tempx / 320.0 - 1.0);
ay = -(double)(tempy / 240.0 - 1.0);
 
 	if ((pattern >> z) & 1)
	{
				

	    points.push_back(ax);
		points.push_back(ay);
				
	}
	z++;
	z = z % 4;

Pk = Pkn;
//cout << tempx << " " << tempy << endl;
continue;
}
Pkn = Pk + 2*dy;
Pk = Pkn;
tempx = tempx + 1;
ax = (double)(tempx / 320 - 1.0);
ay = -(double)(tempy / 240 - 1.0);
// std::cout << tempx << " " << tempy << endl;
 
	if ((pattern >> z) & 1)
	{
				

	    points.push_back(ax);
		points.push_back(ay);
				
	}
	z++;
	z = z % 4;

}
}

if (slope <- 1)
{
P0 = (2 * dx) + dy;
Pk = P0;
int k = 2 * dx + 2 * dy;

//cout << c;
double ax, ay;
int z=0;
for (int i = 1; i <= abs(dy); i++)
{
if (Pk < 0)
{
Pkn = Pk + 2 * dx;
tempy = tempy - 1;

ax = (double)(tempx / 320.0 - 1.0);
ay = -(double)(tempy / 240.0 - 1.0);
 
	if ((pattern >> z) & 1)
	{
				

	    points.push_back(ax);
		points.push_back(ay);
				
	}
	z++;
	z = z % 4;

Pk = Pkn;
//cout << tempx << " " << tempy << endl;
continue;
}
Pkn = Pk + k;
Pk = Pkn;
tempx = tempx + 1;
tempy = tempy- 1;
ax = (double)(tempx / 320 - 1.0);
ay = -(double)(tempy / 240 - 1.0);
 
	if ((pattern >> z) & 1)
	{
				

	    points.push_back(ax);
		points.push_back(ay);
				
	}
	z++;
	z = z % 4;

}
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
x[i % 2] = (int)xpos;
y[i % 2] = (int)ypos;
//cout << xpos << " " << ypos << "\n";
i++;
::count++;

}

if (::count == 2)
{
bresnham();
//cout << "bresnham" << endl;
/*for (int i = 0; i < points.size(); i++)
{
cout << points[i] << "\n";
}*/
glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(double), points.data(),

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
window = glfwCreateWindow(640, 480, "bresnham", NULL, NULL);
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
std::cout<<"pattern and thickness";
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
glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 2*sizeof(double), (const void*)0);
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