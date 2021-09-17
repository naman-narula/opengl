
    #include<gl/glut.h>
    #include<math.h>
    #include<iostream>
    #include<bits/stdc++.h>
    #define screen_height 480
    #define screen_breadth 640
    using namespace std;
    vector<vector<double>> v;
    int but_x, but_y, point_x[1000], point_y[1000], coun;
    float colour[3] = {0.9f, 0.2f, 0.3f};
    float colour_after[3] = {0.7f, 1.0f, 0.7f};
    int touch = 0, temp_x = 0, temp_y = 0, m_main=4;
    bool check = true;



    void coordinates(){
        glColor3f(0.9,0.4,0.7);
        glBegin(GL_LINES);
          glVertex2i(0,-screen_height/2);
          glVertex2i(0, screen_height/2);
        glEnd();
        glBegin(GL_LINES);
          glVertex2i(-screen_breadth/2,0);
          glVertex2i(screen_breadth/2,0);
        glEnd();
        glFlush();
    }

    int* knot(){
/*
        int n = coun-1;
        int degree = m_main-1;
        int m = n+degree+1;
        int *t = new int[m+1];
        for(int i=0;i<=m;i++){
            t[i] = i;
        }
*/

        int n = coun-1;
        int degree = m_main-1;
        int m = n+degree+1;
        int *t = new int[m+1];   //k = degree+1    nptel_n= n+1

        for(int k=0;k<=m;k++){
            if(k<degree+1){
                t[k] = 0;
            }
            else if(k>=(degree+1) && k<=n){
                t[k] = k-degree;
            }
            else if(k>n){
                t[k] = n-degree+1;
            }
        }
        return t;

    }

    float bspline_coeff(int k, int m, int t[], double u){
        float coeff1 = 0.0, coeff2 = 0.0;
        if(m ==1){
            if(u>=t[k] && u<t[k+1]){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            float t1 = t[k+m-1]-t[k];
            float t2 = t[k+m]-t[k+1];
                if(t1!=0){
                     coeff1 = (((u-t[k])/(t1))*bspline_coeff(k,m-1, t, u));
                }
                if(t2!=0){
                     coeff2 = (((t[k+m] - u)/(t2))*bspline_coeff(k+1, m-1, t, u));
                }
        float coeff = ( coeff1+ coeff2 );
        return coeff;
        }
    }

    void curve(int *t){
        double step_size = 0.005, multi;
        for(double j = t[m_main-1]; j<=t[coun]; j+=step_size){
            vector<double> v1;
           double sum_x = 0.0, sum_y = 0.0;
           for(int i = 0;i<=coun-1;i++){
            multi = bspline_coeff(i, m_main, t, j);
            sum_x += multi*point_x[i];
            sum_y += multi*point_y[i];
           }
           v1.push_back(sum_x);
           v1.push_back(sum_y);
           v.push_back(v1);
        }
    }


    void plot_point(int cord_x, int cord_y, float col[], int siz){
        glPointSize(siz);
        glColor3fv(col);
        glBegin(GL_POINTS);
          glVertex2f(cord_x, cord_y);
        glEnd();
        glFlush();
    }

    void rough_line(){
    glLineWidth(3);
    glColor3fv(colour);
    for(int i = 0;i<coun-1; i++){
        glBegin(GL_LINES);
          glVertex2f(point_x[i],point_y[i]);
          glVertex2f(point_x[i+1],point_y[i+1]);
        glEnd();
    }
    glFlush();
}

    void init(float r, float g, float b){
        glClearColor(r, g, b, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-screen_breadth/2.0, screen_breadth/2.0, -screen_height/2.0, screen_height/2.0);
        coordinates();
    }


    void mouse(int button, int state, int mousex, int mousey){
        but_x = mousex - (screen_breadth/2) ;
        but_y = (screen_height/2) - mousey;
        point_x[coun] = but_x;
        point_y[coun] = but_y;
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            check = true;
            touch++;
            plot_point(but_x, but_y, colour, 3);
        }
        else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//undo(clear)the drawing
        {
            check = false;
            touch = 0;
         }
         glutPostRedisplay();
    }

    void render(void){
        if((but_x != temp_x && but_y != temp_y) || (but_x == temp_x && but_y != temp_y) || (but_x != temp_x && but_y == temp_y)){
                coun++;
                if(check == false && touch == 0){
                    double a, b;
                    glClear(GL_COLOR_BUFFER_BIT);
                    for(int i = 0;i<coun; i++){
                        plot_point(point_x[i], point_y[i], colour_after, 9);
                     }
                    rough_line();
                /*int x_temp[coun], y_temp[coun];
                for(int i = 0;i<coun; i++ ){
                    x_temp[i] = point_x[i];
                    y_temp[i] = point_y[i];
                }
                int l = 0;
                for(int j = 0;j<(coun+(2*m_main));j++){
                    if(j<m_main){
                        point_x[j] = x_temp[0];
                        point_y[j] = y_temp[0];
                    }
                    else
                    if(j>=coun+m_main){
                        point_x[j] = x_temp[coun-1];
                        point_y[j] = y_temp[coun-1];
                    }
                    else{
                        point_x[j] = x_temp[l];
                        point_y[j] = y_temp[l];
                        l++;
                    }
                }
                coun = coun+(2*m_main);
                */
                int *t = knot();
                curve(t);
                coordinates();
                glColor3f(0.2, 0.7, 0.4);
                for (int i = 0; i < v.size(); i++) {
                        if(i==0){
                            a = v[i][0];
                            b = v[i][1];
                        }
                        else{
                        glLineWidth(2);
                        glBegin(GL_LINES);
                            glVertex2f(a, b);
                            glVertex2f(v[i][0], v[i][1]);
                        glEnd();
                        a = v[i][0];
                        b = v[i][1];
                        }
                    }
                    glFlush();
                }
                temp_x = but_x;
                temp_y = but_y;
        }
}


        int main(int argc, char** argv)
        {
            glutInit(&argc,argv);
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutInitWindowPosition(100, 100);
            glutInitWindowSize(screen_breadth, screen_height);
            glutCreateWindow("Bspline Curve");
            init(0.0, 0.0, 0.0);

            glutDisplayFunc(render);
            glutMouseFunc(mouse);
            glutMainLoop();
        }

