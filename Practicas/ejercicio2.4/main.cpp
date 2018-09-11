#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <tuple>
#include <cmath>

using namespace std;

typedef tuple<float,float> Point;

float widht=500;
float height=500;
int tam =50;
int midx=widht/2;
int midy=height/2;


void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,500.0,0.0,500.0);
}


void drawLine(Point a, Point b){
    float x1;
    float x2;
    float y1;
    float y2;
    tie(x1,y1) = a;
    tie(x2,y2) = b;
    glBegin(GL_LINES);
        glVertex2i(x1,y1);
        glVertex2i(x2,y2);
    glEnd();
}

void drawPolygon(int lade){
	float radio=height/3;
	float angle=360/lade;
	float theta,theta1;
	float x,y,x1,y1; 
	glBegin(GL_LINES);
		for (int i = 0; i < lade; ++i)
		{
			theta=i*angle*M_PI/180;
			theta1=(i+1)*angle*M_PI/180;
			x=cos(theta)*radio+midx;
			y=sin(theta)*radio+midy;
			x1=cos(theta1)*radio+midx;
			y1=sin(theta1)*radio+midy;
			drawLine(make_tuple(x,y),make_tuple(x1,y1));
		}
			theta1=(0)*angle*M_PI/180;
			x1=cos(theta)*radio+midx;
			y1=sin(theta)*radio+midy;
			drawLine(make_tuple(x,y),make_tuple(x1,y1));
	glEnd();
}

void drawPolygon(float distance,int lade){
	float angle=360/lade;
	float theta,theta1;
	float x,y,x1,y1; 
	glBegin(GL_LINES);
		for (int i = 0; i < lade; ++i)
		{
			theta=i*angle*M_PI/180;
			theta1=(i+1)*angle*M_PI/180;
			x=cos(theta)*distance+midx;
			y=sin(theta)*distance+midy;
			x1=cos(theta1)*distance+midx;
			y1=sin(theta1)*distance+midy;
			drawLine(make_tuple(x,y),make_tuple(x1,y1));
		}
			theta1=(0)*angle*M_PI/180;
			x1=cos(theta)*distance+midx;
			y1=sin(theta)*distance+midy;
			drawLine(make_tuple(x,y),make_tuple(x1,y1));
	glEnd();
}

void display(void){
	drawPolygon(150,360);
	//drawPolygon(50,20);
	//drawPolygon(4);
	//drawLinePM(make_tuple(0,50),make_tuple(60,50));
	glFlush();
}

void lineSegment(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2i(180,15);
        glVertex2i(10,145);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
	
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(midx,midy);
    glutInitWindowSize(widht,height);
    glutCreateWindow("Ejemplo");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
}
