# TORTUGA
En el presente trabajo se trabajo con algoritmos creados por mi, usando los siguientes headers:
+ MATRIX.h
+ PRIMITIVAS.h

dentro de Matrix.h se encuentra la creacion de la matriz para poder marcar los puntos pintados.

    #ifndef MATRIX_H
    #define MATRIX_H
    #include <GL/glut.h>
    #include <iostream>
    #include <algorithm>
    #include <cmath>

    using namespace std;

    struct Window{
        int width;
        int height;
    };


    class Matrix{
    public:
        Matrix(){};
        Matrix(Window window);
        Matrix operator+(Matrix b);

        bool ** matrix;
        Window size;
        GLint yMax;
        GLint yMin;
        GLint xMax;
        GLint xMin;
    };


    Matrix::Matrix(Window window){
        size = window;
        matrix = new bool*[window.height];
        for(int i = 0; i < window.height; i++){
            matrix[i] = new bool[window.width];
            for(int j = 0; j < window.width; j++){
                matrix[i][j] = 0;
            }
        }
    }

    Matrix Matrix::operator+(Matrix b){
        for(int i = this->yMax; i >= this->yMin; i--){
            int y = abs(i - this->size.height - 1);
            for(int j = this->xMin; j <= this->xMax; j++){
                if(this->matrix[y][j] == 1) b.matrix[y][j] = 1;
            }
        }
        b.xMax = max(this->xMax,b.xMax);
        b.xMin = min(this->xMin,b.xMin);
        b.yMax = max(this->yMax,b.yMax);
        b.yMin = min(this->yMin,b.yMin);
        return b;
    }

    #endif
    
Dentro de PRIMITIVAS.h se encuentran funciones creadas por mi.


    #ifndef PRIMITIVAS_H
    #define PRIMITIVAS_H

    #include <GL/glut.h>
    #include <stdlib.h>
    #include <iostream>
    #include <cmath>
    #include <algorithm>
    #include <vector>
    #include <tuple>
    #include "matrix.h"

    using namespace std;

    enum COLORS {ROJO,AZUL,VERDE,NEGRO,BLANCO};
    enum DIR{UP,DOWN,RIGHT,LEFT};

    struct Point
    {
        GLint x;
        GLint y;
    };

    void drawLine(Point a,Point b){
        glBegin(GL_LINES);
            glVertex2i(a.x,a.y);
            glVertex2i(b.x,b.y);
        glEnd();
    }
    /////////////////////////////////////////////////////////////////
    void setPixel(GLint x, GLint y){
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
    }

    void setPixel(GLint x, GLint y, Matrix &resMatrix){
        if(y < resMatrix.size.height and x < resMatrix.size.width){
            resMatrix.matrix[abs(y - resMatrix.size.height - 1)][x] = 1;
        }
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
    }

    ////////////////////////////////////////////////////////////////

    tuple<int,int> getDir(int x1, int y1, int x2, int y2){
        int dirX = -1;
        int dirY = -1;
        if(x1 < x2) dirX = RIGHT;
        else dirX = LEFT;
        if(y1 < y2) dirY = UP;
        else dirY = DOWN;
        return make_tuple(dirX,dirY);
    }

    void circlePlotPoints(Point circCtr, Point circPt, Matrix &resMatrix){
        setPixel(circCtr.x + circPt.x,circCtr.y + circPt.y, resMatrix);
        setPixel(circCtr.x - circPt.x,circCtr.y + circPt.y, resMatrix);
        setPixel(circCtr.x + circPt.x,circCtr.y - circPt.y, resMatrix);
        setPixel(circCtr.x - circPt.x,circCtr.y - circPt.y, resMatrix);
        setPixel(circCtr.x + circPt.y,circCtr.y + circPt.x, resMatrix);
        setPixel(circCtr.x - circPt.y,circCtr.y + circPt.x, resMatrix);
        setPixel(circCtr.x + circPt.y,circCtr.y - circPt.x, resMatrix);
        setPixel(circCtr.x - circPt.y,circCtr.y - circPt.x, resMatrix);
    }

    Matrix circleMidPoint(Point circCtr, GLint radius, Window window){
        Matrix resMatrix(window);
        resMatrix.yMax = circCtr.y + radius;
        resMatrix.yMin = circCtr.y - radius;
        resMatrix.xMax = circCtr.x + radius;
        resMatrix.xMin = circCtr.x - radius;

        Point circPt;
        GLint p = 1 - radius;
        circPt.x = 0;
        circPt.y = radius;
        circlePlotPoints(circCtr, circPt, resMatrix);
        while(circPt.x < circPt.y){
            circPt.x++;
            if(p < 0) p += 2 * circPt.x + 1;
            else{
                circPt.y--;
                p += 2 * (circPt.x - circPt.y) + 1;
            }
            circlePlotPoints(circCtr, circPt, resMatrix);
        }
        return resMatrix;
    }


    void elipcePlotPoints(Point center, Point actual, Matrix &resMatrix){
        setPixel(center.x + actual.x, center.y + actual.y, resMatrix);
        setPixel(center.x - actual.x, center.y + actual.y, resMatrix);
        setPixel(center.x + actual.x, center.y - actual.y, resMatrix);
        setPixel(center.x - actual.x, center.y - actual.y, resMatrix);
    }

    Matrix elipceMidPoint(Point center, GLint radiusX, GLint radiusY, Window window){
        Matrix resMatrix(window);
        resMatrix.yMax = center.y + radiusY;
        resMatrix.yMin = center.y - radiusY;
        resMatrix.xMax = center.x + radiusX;
        resMatrix.xMin = center.x - radiusX;

        GLdouble p1, p2;
        GLint rX2, rY2;
        Point actual;
        actual.x = 0;
        actual.y = radiusY;
        rX2 = pow(radiusX,2);
        rY2 = pow(radiusY,2);
        p1 = rY2 - (rX2 * radiusY) + (0.25 * rX2);
        while((rY2 * actual.x) < (rX2 * actual.y)){
            actual.x++;
            if(p1 < 0) p1 += (2 * rY2 * actual.x) + rY2;
            else{
                actual.y--;
                p1 += (2 * rY2 * actual.x) - (2 * rX2 * actual.y) + rY2;
            }
            elipcePlotPoints(center,actual, resMatrix);
        }
        p2 = (rY2) * pow((actual.x + 0.5), 2) + (rX2) * pow((actual.y - 1), 2) - (rX2 * rY2);
        while(actual.y > 0){
            actual.y--;
            if(p2 > 0) p2 -= (2 * rX2 * actual.y) + rX2;
            else{
                actual.x++;
                p2 += (2 * rY2 * actual.x) - (2 * rX2 * actual.y) + rX2;
            }
            elipcePlotPoints(center,actual, resMatrix);
        }
        return resMatrix;
    }
    #endif

En Main.cpp encontraremos la funcion DrawTurtleSphere la cual crea la tortuga usando la funcion sphere creada con puntos medios, funcion implementada por mi.
    
    #include <iostream>
    #include "primitivas.h"

    using namespace std;

    #define PI 3.14159265

    GLsizei winWidth = 600, winHeight = 500;

    Window window;

    int xr=0,yr=0;
    void init(void){
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(-winWidth, winWidth, -winHeight, winHeight);
    }

    void drawSphereTurtle(Point centro,GLint radio_cuerpo){

        GLint radiocuerpo=radio_cuerpo;
        GLint radiocabeza=radiocuerpo/2;
        GLint radiopatas=radiocuerpo/3;
        Point centro_patas_up_d=centro;
        Point centro_patas_up_i=centro;
        Point centro_patas_down_d=centro;
        Point centro_patas_down_i=centro;


        centro_patas_up_d.x+=radiocuerpo-radiopatas/2;
        centro_patas_up_d.y+=radiocuerpo-radiopatas/2;
        centro_patas_up_i.x-=radiocuerpo-radiopatas/2;
        centro_patas_up_i.y+=radiocuerpo-radiopatas/2;

        centro_patas_down_d.x+=radiocuerpo-radiopatas/2;
        centro_patas_down_d.y-=radiocuerpo-radiopatas/2;
        centro_patas_down_i.x-=radiocuerpo-radiopatas/2;
        centro_patas_down_i.y-=radiocuerpo-radiopatas/2;

        Point centro_cabeza=centro;
        centro_cabeza.y+=radiocuerpo+radiocabeza/2;
        circleMidPoint(centro,radiocuerpo,window);
        circleMidPoint(centro_cabeza,radiocabeza,window);
        circleMidPoint(centro_patas_up_d,radiopatas,window);
        circleMidPoint(centro_patas_up_i,radiopatas,window);
        circleMidPoint(centro_patas_down_d,radiopatas,window);
        circleMidPoint(centro_patas_down_i,radiopatas,window);	
    }

    void keyboard(unsigned char key, int x, int y){
        switch (key) {
            case 'w':
                yr=yr+1;
                cout<<y<<endl;
                glutPostRedisplay();
                break;
            case 's':
                yr--;
                cout<<y<<endl;
                glutPostRedisplay();
                break;
            case 'a':
                xr--;
                cout<<x<<endl;
                glutPostRedisplay();
                break;
            case 'd':
                xr++;
                //glTranslatef(dest.getOrigin().x, dest.getOrigin().y, 0);
                cout<<x<<endl;
                glutPostRedisplay();
                break;
            case 'e':
                //xr++;

                cout<<x<<endl;

                glRotatef(-1.0,0.,0.,0.1);

                glutPostRedisplay();

                break;
            case 'q':
                //xr++;
                glRotatef(1,0.,0.,0.1);
                cout<<x<<endl;
                glutPostRedisplay();
                break;		
        }
    }


    void display(){

        Point centro;
        centro.x = winWidth/2+xr;
        centro.y = winHeight/2+yr;
        GLint radio = 200;
        GLint radioy=100;

        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.0, 0.0, 0.0);
        //estrella(centro, radio);
        //circleMidPoint(centro, radio, window);
        //elipceMidPoint(centro, radio, radioy, window);
        drawSphereTurtle(centro,100);
        glFlush();
        glutPostRedisplay();
        glutSwapBuffers();
    }

    int main(int argc, char **argv){
        window.width = winWidth;
        window.height = winHeight;
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition(0,0);
        glutInitWindowSize(winWidth, winHeight);
        glutCreateWindow("Dibujo");
        glTranslatef(-300, -250, 0.0);
        glutDisplayFunc(display);
        init();

        glutKeyboardFunc(keyboard);

        glutMainLoop();
      }

##RESULTADOS DE EJECUCION

![](https://github.com/RubenJTL/Computacion-Grafica/blob/master/TORTUGA/TORTUGA1.png)
![alt text](https://raw.githubusercontent.com/username/projectname/branch/path/to/img.png)
![alt text](https://raw.githubusercontent.com/username/projectname/branch/path/to/img.png)
![alt text](https://raw.githubusercontent.com/username/projectname/branch/path/to/img.png)
![alt text](https://raw.githubusercontent.com/username/projectname/branch/path/to/img.png)
