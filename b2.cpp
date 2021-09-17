#include<GL/glew.h>
#include<GLFW/glfw3.h>
//#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#define WIDTH 640.0
#define HEIGHT 480.0
using namespace std;
vector<int> cpx, cpy;
vector<int> pointx, pointy;
vector<int> knot_vector(50);


const int order = 4;
int cp;
void calcknot()
{

    int n = cp - 1;
    int degree = order - 1;
    int m = n + order + 1;

    for (int i = 0; i < m; i++)
    {
        knot_vector[i] = i;
    }
}
float bspline_coeff(int k, int m, double u) {

    if (m == 1) {
        if (u >= knot_vector[k] && u <= knot_vector[k + 1]) {

            return 1;
        }
        else {

            return 0;
        }
    }


    float coeff = ((((u - knot_vector[k]) / (knot_vector[k + m - 1] - knot_vector[k])) * bspline_coeff(k, m - 1, u)) + (((knot_vector[k + m] - u) / (knot_vector[k + m] - knot_vector[k + 1])) * bspline_coeff(k + 1, m - 1, u)));

    return coeff;
}

void draw()
{


    for (float j = knot_vector[0]; j < knot_vector[cp + order - 1]; j += 0.001)
    {

        int sumx = 0, sumy = 0;
        for (int i = 0; i < cpx.size(); i++)
        {
            float temp = bspline_coeff(i, order, j);

            sumx += int(temp * cpx[i]);
            sumy += int(temp * cpy[i]);
        }
        pointx.push_back(sumx);
        pointy.push_back(sumy);
    }

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    if (!GLFW_RELEASE)
    {

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            glfwGetCursorPos(window, &xpos, &ypos);
            cpx.push_back((int)xpos);
            cpy.push_back(HEIGHT - (int)ypos);

        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        {
            glfwGetCursorPos(window, &xpos, &ypos);
            cpx.push_back((int)xpos);
            cpy.push_back(HEIGHT - (int)ypos);
            cp = cpx.size();
            calcknot();
            draw();
            for (int i = 0; i < cp + order; i++)
            {
                cout << knot_vector[i] << "\n";
            }

        }

    }

}
int main()
{

    glfwInit();
    GLFWwindow* window;
    window = glfwCreateWindow(WIDTH, HEIGHT, "bezier", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIDTH, 0.0, HEIGHT, 0.0, 1.0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        for (int i = 0; i < cpx.size(); i++)
        {
            glVertex2i(cpx[i], cpy[i]);
        }
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0, 1.0, 1.0);
        for (int i = 0; i < pointx.size(); i++)
        {
            glVertex2i(pointx[i], pointy[i]);
            glVertex2i(pointx[i + 1], pointy[i+1]);
        }
        glEnd();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}