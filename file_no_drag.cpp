    #include<gl/glut.h>
    #include<math.h>
    #include<iostream>
    #include<bits/stdc++.h>
    #define screen_height 480
    #define screen_breadth 640
    #define PI 3.14159265
    using namespace std;
    vector<vector<float>> v, result;
    vector<float> v1;
    vector<int> points;
    double ver1x, ver1y, ver2x, ver2y, angle=0;
    int but_x, but_y, coun;
    float colour[3] = {0.9f, 0.2f, 0.3f};
    float colour_after[3] = {0.7f, 1.0f, 0.7f};
    int touch = 0, temp_x = 0, temp_y = 0;
    bool check = true, change = false, pause = false, done = true;
    char ch, trans;

    void coordinates();


    int transformation(int x, int y){

        vector<float> mat1;
        vector<vector<float>> mat;
        vector<float> res;
        result.clear();

        float sum = 0;
        float par_x = (float)x;
        float par_y = (float)y;

        if(trans == 't'){
            vector<float> mat1 = {1,0,par_x};
            mat.push_back(mat1);
            mat1.clear();
            mat1 = {0,1,par_y};
            mat.push_back(mat1);
            mat1.clear();
            mat1 = {0,0,1};
            mat.push_back(mat1);
        }
        else
        if(trans == 's'){
            par_x = par_x/50.0;
            par_y = par_y/50.0;
            vector<float> mat1 = {par_x,0,0};
            mat.push_back(mat1);
            mat1.clear();
            mat1 = {0,par_y,0};
            mat.push_back(mat1);
            mat1.clear();
            mat1 = {0,0,1};
            mat.push_back(mat1);
        }
        else
        if( trans == 'r'){
            float denom = sqrt(pow(par_y,2)+pow(par_x,2));
            float cos = par_x/denom;
            float sin = par_y/denom;
            if(asin(sin)<angle){
                sin = -sin;
            }
            vector<float> mat1 = {cos,-sin,0};
            mat.push_back(mat1);
            mat1.clear();
            mat1 = {sin,cos,0};
            mat.push_back(mat1);
            mat1.clear();
            mat1 = {0,0,1};
            mat.push_back(mat1);
            angle = acos(cos);
        }
        else{
            return 0;
        }

        for(auto i = 0u; i<v.size(); i++){
            res.clear();
            for(int j = 0; j<3; j++){
                sum = mat[j][0]*v[i][0] + mat[j][1]*v[i][1] + mat[j][2]*v[i][2];

                res.push_back(sum);
            }

            result.push_back(res);
        }
        glClear(GL_COLOR_BUFFER_BIT);
        coordinates();

        if(ch =='c'){
            glColor3fv(colour_after);
            glBegin(GL_POINTS);
        }
        else{
            glColor3fv(colour_after);
            glBegin(GL_POLYGON);
        }
            for(auto i = 0u; i<result.size();i++){
                glVertex2f(result[i][0],result[i][1]);
            }
            glEnd();
            glFlush();

            return 0;
}


    int choice(){
        int chx, chy;
        if(trans == 't'){
        cout<<"Enter tx\n";
        cin>>chx;
        cout<<"Enter ty\n";
        cin>>chy;
        }
        else
        if(trans == 'r'){
        cout<<"For TAN(Angle) = y/x\n";
        cout<<"Enter x ";
        cin>>chx;
        cout<<"Enter y\n";
        cin>>chy;
        }
        else
        if(trans == 's'){
        cout<<"Enter sx\n";
        cin>>chx;
        cout<<"Enter sy\n";
        cin>>chy;
        }
        else{
            cout<<"Go to drawing window and press \n1. 't' for translation\n2. 'r' for rotation\n3. 's' for scaling\n";
            return 0;
        }
        transformation(chx, chy);



    }

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

        void input(){
        do{
        cout<<"Enter 'c' for circle\nEnter 'p' for polygon\n";
        cin>>ch;
        if(ch !='c' && ch!='p'){
            cout<<"Wrong Input\nPlease exit and try again\n";
        }
        }while(ch != 'c' && ch != 'p');


    }

    void print(int x_cord, int y_cord){
        int arr[4] = {1,1,-1,-1};
        int x_coeff = (int)ver1x;
        int y_coeff = (int)ver1y;
        int xx, yy;
        glBegin(GL_POINTS);
        for(int i = 0;i<8;i++){
                if(i<4){
                    xx = ((arr[i%4]*x_cord) + x_coeff);
                    yy = ((arr[(i+1)%4]* y_cord) + y_coeff);

                }
                else{
                    xx = ((arr[i%4]*y_cord) + x_coeff);
                    yy = ((arr[(i+1)%4]* x_cord) + y_coeff);
                }
                v1.clear();
                v1.push_back(xx);
                v1.push_back(yy);
                v1.push_back(1);
                v.push_back(v1);
                glVertex2i(xx,yy);

        }
}


    void circle(float r){
        r = floor(r);
        int p_k = 1-(int)r;
        int x_cord = 0, y_cord = r, coun = 1;
        print(x_cord, y_cord);
        do{
            x_cord++;
            if(p_k >= 0){
                    y_cord--;
                    p_k += (2*x_cord) - (2*y_cord) + 1;
                }
        else if(p_k < 0){
            p_k += (2*x_cord) + 1;
        }

            print(x_cord, y_cord);

        coun++;

    }while(x_cord <= y_cord);

}
    void plot_vector(){
        glClear(GL_COLOR_BUFFER_BIT);
        coordinates();

        if(ch =='c'){
            glBegin(GL_POINTS);
        }
        else{
            glColor3fv(colour_after);
            glBegin(GL_POLYGON);
        }
            for(auto i = 0u; i<result.size();i++){
                glVertex2f(result[i][0],result[i][1]);
            }
            glEnd();
            glFlush();
    }


    void plot_point(int cord_x, int cord_y, float col[], int siz){
        glPointSize(siz);
        glColor3fv(col);
        glBegin(GL_POINTS);
          glVertex2f(cord_x, cord_y);
        glEnd();
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

    void keyboard(unsigned char key, int x, int y){
        if(key == 't'){
            trans = 't';
            change = true;
        }
        else
        if(key == 's'){
            trans = 's';
            change = true;
        }
        else
        if(key == 'r'){
            trans = 'r';
            change = true;
        }
        else{
            trans = 'q';
            v.clear();
            check = true;
            change = false;
            touch = 0;
            done = true;
            glClear(GL_COLOR_BUFFER_BIT);
            coordinates();
            input();

        }
    }



    void mouse(int button, int state, int mousex, int mousey){
        but_x = mousex - (screen_breadth/2) ;
        but_y = (screen_height/2) - mousey;
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        v1.clear();
        v1.push_back(but_x);
        v1.push_back(but_y);
        v1.push_back(1);
        v.push_back(v1);
            check = true;

            touch++;
            plot_point(but_x, but_y, colour, 3);

        }
        else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN )//undo(clear)the drawing
        {
            v1.clear();
            v1.push_back(but_x);
            v1.push_back(but_y);
            v1.push_back(1);
            v.push_back(v1);
            check = false;
            touch = 0;
         }
         else
            if(button==GLUT_LEFT_BUTTON && state==GLUT_UP && !change && !done ){
                change = true;
            }


         glutPostRedisplay();
    }

    void render(void){

        if(change){
            choice();
            //transformation(points[0], points[1]);
        }
        if(done)
        {
        if((but_x != temp_x && but_y != temp_y) || (but_x == temp_x && but_y != temp_y) || (but_x != temp_x && but_y == temp_y)){

            if(ch =='c'){

                if(touch == 2 && check == true){

                        ver2x = (float) but_x;
                        ver2y = (float) but_y;
                        float r = sqrt(pow(ver2y - ver1y, 2) + pow(ver2x - ver1x, 2));
                        glColor3fv(colour_after);
                        circle(r);
                        glEnd();
                        glFlush();
                        done = false;
                        change = true;
                }
                if(touch == 1){
                    ver1x = (float) but_x;
                    ver1y = (float) but_y;

                }


            }
            if(ch == 'p'){
                if(check == false && touch == 0){
                    glClear(GL_COLOR_BUFFER_BIT);
                    coordinates();
                    glColor3fv(colour_after);
                    glBegin(GL_POLYGON);
                        for(auto i = 0u; i<v.size(); i++){
                            glVertex2f(v[i][0], v[i][1]);
                        }
                        glEnd();
                        glFlush();
                        done = false;
                        change = true;
                }
            }
        temp_x = but_x;
        temp_y = but_y;
        }
    }
}


        int main(int argc, char** argv)
        {
            input();
            glutInit(&argc,argv);
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutInitWindowPosition(100, 100);
            glutInitWindowSize(screen_breadth, screen_height);
            glutCreateWindow("Transformation");
            init(0.0, 0.0, 0.0);

            glutDisplayFunc(render);
            glutMouseFunc(mouse);
            glutKeyboardFunc(keyboard);
            glutMainLoop();
        }

