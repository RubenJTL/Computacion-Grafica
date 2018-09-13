
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