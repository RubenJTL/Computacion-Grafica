# Examen Computacion Grafica
Para poder compilar cada proyecto es necesario ejecutar los .sh 

## 1 Usando las propiedades de vectores ortogonales transformar los siguientes puntos, C esta en el plano XY y A esta el eje C.
	Puntos Iniciales
	A[-1 , 2 , 3 ]
	B[ 1 , 1 , 1 ]
	C [3 , 2 , 1 ]
![](https://github.com/RubenJTL/Computacion-Grafica/blob/master/EXAMEN/PREGUNTA%202/p2_1.png)
![](https://github.com/RubenJTL/Computacion-Grafica/blob/master/EXAMEN/PREGUNTA%202/p2_2.png)
![](https://github.com/RubenJTL/Computacion-Grafica/blob/master/EXAMEN/PREGUNTA%202/p2_3.png)
![](https://github.com/RubenJTL/Computacion-Grafica/blob/master/EXAMEN/PREGUNTA%202/Matrices_puntos.png)
## 2 Algoritmo de trazado de linea 3D
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
![](https://github.com/RubenJTL/Computacion-Grafica/blob/master/EXAMEN/PREGUNTA%203/Linea3D.png)



## 3 Algoritmo de trazado de Parabola
  Algoritmo para dibujar la parabola con simetria
    
    void parabolaPlotPoints(Point center, Point actual, Matrix &resMatrix){
	    setPixel(center.y + actual.y, center.x + actual.x, resMatrix);
      setPixel(center.y - actual.y, center.x + actual.x, resMatrix);
    }
    
  Algoritmo de Parabola con Punto medio 
    
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
  ![](https://github.com/RubenJTL/Computacion-Grafica/blob/master/EXAMEN/PREGUNTA%204/parabola.png)
