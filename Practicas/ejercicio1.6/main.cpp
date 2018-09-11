#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <tuple>
#include <cmath>

using namespace std;

typedef tuple<float,float> Point;


float ndh;
float ndv;
float width=300;
float height=300;
float ndhm1=1;
float ndvm1=1;
float ndhm0=-1;
float ndvm0=-1;

float xmin=0;
float xmax=100;
float ymin=0;
float ymax=100;

int tam =50;
int midx=0;
int midy=0;


bool inp_to_ndc();
bool ndc_to_user();
bool user_to_ndc(Point user);
bool ndc_to_dc();

void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(ndhm0,ndhm1,ndvm0,ndvm1);
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


void display(void){
	//drawPolygon(50,360);
	//drawPolygon(50,20);
	drawLine(make_tuple(-1.0,-1.0),make_tuple(1,1));
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
    glutInitWindowSize(500,500);
    glutCreateWindow("Ejemplo");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
}

bool inp_to_ndc(Point a){
	if (ndhm0<=get<0>(a) and ndhm1>=get<0>(a) and ndvm0<=get<1>(a) and ndvm1>=get<1>(a) )
	{
		ndcx=dcx/ndhm1;
		ndcy=dcy/ndvm1;
		return true;
	}
	return false;
}

bool ndc_to_dc(Point a){
	if (ndhm0<=get<0>(a) and ndhm1>=get<0>(a) and ndvm0<=get<1>(a) and ndvm1>=get<1>(a) )
	{
		dcx=round(ndcx*ndhm1);
		dcy=round(ndcy*ndvm1);
		return true;
	}
	return false;
}



bool user_to_ndc(Point user){
	float ndcx,ndcy;
	if (xmin<=get<0>(user) and  xmax>=get<0>(user) and ymin<=get<1>(user) and  ymax>=get<1>(user))
	{
		ndcx=(get<0>(user)-xmin);
		ndcx=ndcx*(ndhm1-ndhm0);
		ndcx=ndcx/(xmax-xmin);
		ndcx=ndhm0+ndcx;
		
		ndcy=(get<1>(user)-ymin);
		ndcy=ndcy*(ndvm1-ndvm0);
		ndcy=ndcy/(ymax-ymin);
		ndcy=ndvm0+ndcy;
		
		return true;
	}
	return false
}

bool ndc_to_user(Point a){
	float x,y;
	if (ndhm0<=get<0>(a) and ndhm1>=get<0>(a) and ndvm0<=get<1>(a) and ndvm1>=get<1>(a))
	{
		x=get<0>(a)-ndhm0;
		x=x*(xmax-xmin);
		x=x/(ndhm1-ndhm0);
		x=x+xmin;

		y=get<1>(a)-ndvm0;
		y=y*(ymax-ymin);
		y=y/(ndvm1-ndvm0);
		y=y+ymin;

		return true;
	}
	return false;
}