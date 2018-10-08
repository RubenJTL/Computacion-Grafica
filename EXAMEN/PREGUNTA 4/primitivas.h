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


/////////////////////////////////////////////////////////////////

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

void parabolaPlotPoints(Point center, Point actual, Matrix &resMatrix){
	setPixel(center.y + actual.y, center.x + actual.x, resMatrix);
    setPixel(center.y - actual.y, center.x + actual.x, resMatrix);
}
Matrix parabolaMidPoint(Point center,int a,int XMAX, Window window){
	Matrix resMatrix(window);
	resMatrix.yMax = center.y + 2*a+1;
    resMatrix.yMin = center.y ;
    resMatrix.xMax = center.x + XMAX;
    resMatrix.xMin = center.x ;
	Point p;
	p.x=0;
	p.y=0;
    double d = 1 - (2*a);
    double delNE = 3 + 2*p.y - 4*a;
    double delN = 3 + 2*p.y;
    while( p.y<= (2*a) )
    {
    	parabolaPlotPoints(center,p,resMatrix);
        if(d>0) //NE
        {
            d+= delNE;
            p.x++;
        }
        else //N
        {
            d+= delN;
        }
        p.y++;
        delN += 2;
        delNE += 2;
    }
    d = ((p.y+0.5)*(p.y+0.5) - 4*a*(p.x+1));
    double delE = -4*a;
    delNE = 2 + 2*p.y - 4*a;
    while( p.x < XMAX )
    {
    	if(d>0)
        {
        	d+= delE;
        }
        else
        {
        	d+= delNE;
            p.y++;
            delNE += 2;
        }
        p.x++;
        parabolaPlotPoints(center,p,resMatrix);
	}
	return resMatrix;
}



#endif

