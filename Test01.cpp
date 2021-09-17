#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<vector>
#include<bits/stdc++.h>
using namespace std;

/*extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}*/

float colour[3] = { 0.5f,1.0f,0.8f },bound_colour [] ={0.0, 0.0, 1.0};
bool coloured = false;
int x[2], y[2], xi, yi, fillcount = 0, rotation = 1;
float inc = 0.1f, addSpeed = 0.1f;
int count = 0;
size_t psize;
vector<int> points;
char pending[650][650];

void keycallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (!GLFW_RELEASE) {
        if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
            rotation = -1;
        if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
            rotation = 1;
        if (key == GLFW_KEY_UP && action == GLFW_PRESS)
            addSpeed += 2.0;
        if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
            addSpeed -= 2.0;
    }
}

void push(int tempx, int tempy) {
    points.push_back(tempx);
    points.push_back(tempy);
}

void lines(int radius) {
    int tempx, tempy;
    tempx = x[0] - radius;
    tempy = y[0];
    for (int i = 0; i <= (2 * radius); i++)
    {
        push(tempx + i, tempy);
    }
    tempx = x[0];
    tempy = y[0] - radius;
    for (int i = 0; i <= (2 * radius); i++)
    {
        push(tempx, tempy + i);
    }
    float Pi = 3.14159265;
    int limit = radius * cos(Pi / 4);
    tempx = x[0];
    tempy = y[0];
    for (int i = 0; i <= limit; i++)
    {
        push(tempx + i, tempy + i);
        push(tempx - i, tempy - i);
        push(tempx + i, tempy - i);
        push(tempx - i, tempy + i);

    }
}

void midcircle()
{
    int k = 0;
    int modx[] = { 1,1,-1,-1 }, mody[] = { 1,-1,-1,1 };
    vector<int> X, Y;
    int radius = round(sqrt(pow(x[0] - x[1], 2) + pow(y[0] - y[1], 2)));
    pair<int, int> center = make_pair(x[0], y[0]);
    lines(radius);
    int P0 = 1 - radius;
    int tempx = 0, tempy = radius;
    int Pk, Pkn;
    Pk = P0;
    while (tempx <= tempy)
    {

        if (Pk < 0)
        {
            Pkn = Pk + 2 * tempx + 3;

        }
        else
        {
            Pkn = Pk + 2 * tempx - 2 * tempy + 5;
            tempy -= 1;

        }
        Pk = Pkn;
        tempx += 1;

        X.push_back(tempx);
        Y.push_back(tempy);
        X.push_back(tempy);
        Y.push_back(tempx);
    }
    int size = X.size();
    for (int i = 0; i < size; i++)
    {
        for (int z = 0; z < 4; z++)
        {
            push(X[i] * modx[z] + center.first, Y[i] * mody[z] + center.second);
        }
    }

}

void boundaryFill(int X, int Y) {
    float c[3];
    glReadPixels(X, Y, 1.0, 1.0, GL_RGB, GL_FLOAT, c);
    if ((c[2] !=bound_colour[2]  && c[0] != colour[0] && pending[X][Y] == 'd') || (c[2] !=bound_colour[2]  && c[1] != colour[1] && pending[X][Y] == 'd')|| (c[2] !=bound_colour[2]  && c[2] != colour[2] && pending[X][Y] == 'd')) {

        glBegin(GL_POINTS);
        glColor3fv(colour);
        glVertex2i(X, Y);
        glEnd();
        glFlush();
        if (colour[1] == 1.0 && colour[0]==0.5 && colour[2]==0.8)
        {
            pending[X][Y] = 'o';   
        }
        else if (colour[1] == 1.0 )
        {
            pending[X][Y] = 't';  
        }
        boundaryFill(X + 1, Y);
        boundaryFill(X - 1, Y);
        boundaryFill(X, Y + 1);
        boundaryFill(X, Y - 1);
    }

}

void render()
{
    if (coloured)
    {
        glPushMatrix();
        glTranslatef(x[0], y[0], 0.0);
        glRotatef(inc, 0.0, 0.0, 1.0 * rotation);
        glTranslatef(-x[0], -y[0], 0.0);
        glBegin(GL_POINTS);

        glColor3fv(bound_colour);
        for (int i = 0; i < points.size(); i += 2)
        {
            glVertex2i(points[i], points[i + 1]);
        }
        glEnd();
        glPopMatrix();
        glFlush();
    }
    else
    {
        glBegin(GL_POINTS);

        glColor3fv(bound_colour);
        for (int i = 0; i < points.size(); i += 2)
        {

            glVertex2i(points[i], points[i + 1]);

        }

        glEnd();
        glFlush();
    }
}
void rotating()
{
    glPushMatrix();
    glTranslatef(x[0], y[0], 0.0);
    glRotatef(inc, 0.0, 0.0, 1.0 * rotation);
    glTranslatef(-x[0], -y[0], 0.0);
    // draw
    glBegin(GL_POINTS);

    for (int i = 0; i < 650; i++)
    {
        for (int j = 0; j < 650; j++)
        {
            if (pending[i][j] == 'o')
            {
                glColor3f(0.5, 1.0, 0.8);
                glVertex2i(i, j);
            }
            else if (pending[i][j] == 't')
            {
                glColor3f(0.0, 1.0, 0.0);
                glVertex2i(i, j);
            }

        }
    }
    glEnd();
    glPopMatrix();
    glFlush();

}
void mousebuttoncallback(GLFWwindow* window, int button, int action, int mods)
{
    static int i = 0;
    if (!GLFW_RELEASE)
    {
        double px, py;
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            ::count = ::count % 2;
            glfwGetCursorPos(window, &px, &py);
            if (::count == 0)
            {

                memset(x, 0, sizeof(x));
                memset(y, 0, sizeof(y));

            }
            x[i & 1] = (int)px;
            y[i & 1] = 480 - (int)py;
            i++;
            ::count++;
        }

        if (::count == 2)
        {
            midcircle();
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        {
            fillcount++;
            glfwGetCursorPos(window, &px, &py);
            xi = px;
            yi = 480 - py;
            boundaryFill(xi, yi);
            if (fillcount == 8)
                coloured = true;
            if (colour[1] == 1.0 && colour[2]== 0.8 && colour[0]==0.5)
            {
                colour[0] = 0.0f;
                colour[1] = 1.0f;
                colour[2]=  0.0f;
            }
            else if(colour[1]==1.0 && colour[0]==0.0)
            {
                colour[0] = 0.5f;
                colour[1] = 1.0f;
                colour[2] = 0.8f;
            }
        }
    }
}


int main()
{
    memset(pending, 'd', sizeof(pending));
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "Test 01", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mousebuttoncallback);
    glfwSetKeyCallback(window, keycallback);
    glewInit();
    glfwSwapInterval(1);
    glViewport(0, 0, 640, 480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 640, 0.0, 480, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    while (!glfwWindowShouldClose(window))
    {
        inc += addSpeed;
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (coloured)
            rotating();
    }
    glfwTerminate();
}