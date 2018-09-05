#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <tuple>
#include <cmath>

using namespace std;

typedef tuple<float,float> Point;


int tam =50;
int midx=50;
int midy=50;
void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,150.0);
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

void drawLinePM(Point a, Point b){
	float x,y;

	float x1=get<0> (a);
	float y1=get<1> (a);
	float x2=get<0> (b);
	float y2=get<1> (b);
	if (x1==x2 and y1>y2)
	{
		swap(y1,y2);
	}
	else if (y1==y2 and x1>x2)
	{
		swap(x1,x2);
	}
	//Point d=make_tuple((x2-x1)/2,(y2-y1)/2);
	float dx=x2-x1;
	float dy=y2-y1;
	float d=dy-dx;
	float incE=dy;
	float incNE=(dy-dx);
	x=x1;
	y=y1;
	cout<<incE<<endl;
	cout<<incNE<<endl;
	float cambio=0.01;
	glBegin(GL_POINTS);
		glVertex2i(x,y);
		cout<<x<<" "<<y<<endl;
		if(x==x2){
			while(y<y2){
				//cout<<x<<" "<<y<<endl;
				d=d+incE;
				y=y+cambio;
				glVertex2i(x,y);
			}	
		}else{
			while(x<x2){
				//cout<<x<<" "<<y<<endl;
				if(d<=0){
					d=d+incE;
					x=x+cambio;
					if(y>y2){
						y=y-cambio;
					}
				}else{
					d=d+incNE;
					x=x+cambio;
					if(y>y2){
						y=y-cambio;
					}else{
						y=y+cambio;
					}

				}
				
				glVertex2i(x,y);
			}
		}
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
	//drawPolygon(40,360);
	//drawPolygon(40,4);
	drawLinePM(make_tuple(0,0),make_tuple(400,300));
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
    glutInitWindowSize(400,300);
    glutCreateWindow("Ejemplo");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
}