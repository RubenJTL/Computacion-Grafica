
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <stdio.h>

using namespace std;


typedef struct Point3D
{
    double x,y,z;
    void print()
    {
        printf("{%d, %d, %d} ", (int)x, (int)y, (int)z);
    }
};


GLdouble mModel[16];
float rotaX=0.0;
float rotaY=0.0;
float rotaZ=0.0;

void putPixel(int x,int y,int z)
{	
	glPointSize(3);
    glBegin(GL_POINTS);
    	glVertex3i(x,y,z);
	glEnd();
}


int mayorNum(int x, int y, int z) {
	int max = x; 
	if (y > max) 
		max = y;
	if (z > max)
		max = z;
	return max; 
} 

void drawLine(Point3D P1, Point3D P2)
{
    int dx,dy ,dz, x,y,z;
    int err_1,err_2,err_3;
    int incX,incY,incZ;

	x=P1.x;
	y=P1.y;
	z=P1.z;

    dx=P2.x-P1.x;    
    dy=P2.y-P1.y;
    dz=P2.z-P1.z;
    
    incX = 1;    
    incY = 1;
    incZ = 1;
   
    while(x<P2.x){
    	err_1 = 2*dy - dx;
		err_2 = 2*dz - dx;
    	for (int i = 0; i < dx; i++) {

		    if (err_1 > 0) {
		        y += incY;
		        err_1 -= 2*dx;
		    }
		    if (err_2 > 0) {
		        z += incZ;
		        err_2 -= 2*dx;
		    }
		    err_1 += 2*dy;
		    err_2 += 2*dz;
		    x+= incX;
		    putPixel(x,y,z);
		}
    }
    while(y<P2.y){
    	err_1 = 2*dx - dy;
		err_2 = 2*dz - dy;
		for (int i = 0; i < dy; i++) {

		    if (err_1 > 0) {
		        x += incX;
		        err_1 -= 2*dy;
		    }
		    if (err_2 > 0) {
		        z += incZ;
		        err_2 -= 2*dy;
		    }
		    err_1 += 2*dx;
		    err_2 += 2*dz;
		    y += incY;
		    putPixel(x,y,z);
		}
    }
	while(z<P2.z) 
	{
		err_1 = 2*dy - dz;
		err_2 = 2*dx - dz;
		for (int i = 0; i < dz; i++) {

		    if (err_1 > 0) {
		        y += incY;
		        err_1 -= 2*dz;
		    }
		    if (err_2 > 0) {
		        x += incX;
		        err_2 -= 2*dz;
		    }
		    err_1 += 2*dy;
		    err_2 += 2*dx;
		    z += incZ;
		    		    putPixel(x,y,z);
		}
	}
		
    
	glBegin (GL_LINES);
		glVertex3f(0,0,P2.z);
		glVertex3f(P2.x,0,P2.z ); 
	
		glVertex3f(P2.x,0,0);
		glVertex3f(P2.x,0,P2.z);
		
		glVertex3f(P2.x,0,P2.z);
		glVertex3f(P2.x,P2.y,P2.z);
	glEnd();
	glLineWidth(1);
}


void ejes(void)
{
	glLineWidth(1);
	glBegin (GL_LINES);
		glColor3f (1,0,0);
		glVertex3f(-300,0,0);
		glVertex3f(300,0,0 ); 
	
		glColor3f (0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,300,0);
	
		glColor3f (0,0,1);
		glVertex3f(0,0,-300);
		glVertex3f(0,0,300 ); 
	glEnd();
	glColor3f (1,1,1); 
	glLineWidth(1);
}

void display(void)
{
	glPushMatrix();
	glRotatef( rotaX, 1.0, 0.0, 0.0 );
	glRotatef( rotaY, 0.0, 1.0, 0.0 );
	glRotatef( rotaZ, 0.0, 0.0, 1.0 );

	glClear(GL_COLOR_BUFFER_BIT);
	Point3D p1;
	Point3D p2;
	p1.x=0;
	p1.y=0;
	p1.z=0;

	p2.x=10;
	p2.y=10;
	p2.z=10;
	drawLine(p1,p2); 
	ejes();
    glPopMatrix();
    
    glFlush();
}


void reshape(int width, int height) 
{
    
	glGetDoublev (GL_MODELVIEW_MATRIX, mModel);
    glLoadIdentity();
    gluPerspective(20.0, (GLfloat)height / (GLfloat)width, 1.6, 128.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(25.0, 50.0, 100.0, 10, 10.0, 10.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("Linea 3D");
	glMatrixMode(GL_PROJECTION);


 //   glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

    return 0;
}
