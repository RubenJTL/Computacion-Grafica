# Examen Computacion Grafica
## 1 Usando las propiedades de vectores ortogonales transformar los siguientes puntos, C esta en el plano XY y A esta el eje C.
## 2 Algoritmo de trazado de linea 3D
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
  ![](https://github.com/RubenJTL/Computacion-Grafica/blob/master/TORTUGA/TORTUGA1.png)