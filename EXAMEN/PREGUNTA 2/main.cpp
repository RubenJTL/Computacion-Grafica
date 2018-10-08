//#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <math.h>
#include <string>
#include <stdlib.h>
/* Global variables */
#define NUM_VERTICES 3
#define N 4


char title[] = "PREGUNTA 2";

void makePointMatrix(double (&pointMatrix)[N][NUM_VERTICES]);
void storePoints(double pointMatrix[N][NUM_VERTICES]);

void multiplyMatrix(double a[N][N], int r1, int c1 ,double b[N][NUM_VERTICES], int r2, int c2, double (&c)[N][NUM_VERTICES]);
void translate(double matrix[N][NUM_VERTICES], int dx, int dy, int dz, double (&result)[N][NUM_VERTICES]);
void scale(double matrix[N][NUM_VERTICES], double sx, double sy, double sz, double (&result)[N][NUM_VERTICES]);
void printVer();


void translatePoints(int dx,int dy, int dz);
void rotatePointsXpos(double opuesto, double costado);
void rotatePointsYpos(double opuesto, double costado);
void rotatePointsZpos(double opuesto, double costado);
void rotatePointsXneg(double opuesto, double costado);
void rotatePointsYneg(double opuesto, double costado);
void rotatePointsZneg(double opuesto, double costado);


void rotateXneg(double matrix[N][NUM_VERTICES], double opuesto,double costado, double (&result)[N][NUM_VERTICES]);
void rotateYneg(double matrix[N][NUM_VERTICES], double opuesto,double costado, double (&result)[N][NUM_VERTICES]);
void rotateZneg(double matrix[N][NUM_VERTICES], double opuesto,double costado, double (&result)[N][NUM_VERTICES]);
void rotateXpos(double matrix[N][NUM_VERTICES], double opuesto,double costado, double (&result)[N][NUM_VERTICES]);
void rotateYpos(double matrix[N][NUM_VERTICES], double opuesto,double costado, double (&result)[N][NUM_VERTICES]);
void rotateZpos(double matrix[N][NUM_VERTICES], double opuesto,double costado, double (&result)[N][NUM_VERTICES]);

typedef struct Point3D
{
    double x,y,z;
    void print()
    {
        printf("{%d, %d, %d} ", (int)x, (int)y, (int)z);
    }
};

Point3D v[NUM_VERTICES];



void ejes(void);
// La funcion encargada de dibujar o redibujar la ventana cada vez que sea necesario.
void display(void);
//void keyboard(unsigned char key, int x, int y);
 
/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
 
/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
 
   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix
  // glTranslatef(1.5f, 0.0f, -7.0f);  // Move right and into the screen
  
   // Render a pyramid consists of 4 triangles
   glLoadIdentity();                  // Reset the model-view matrix
   glTranslatef(0.0f, 0.0f, -12.0f);  // Move left and into the screen
   for (int i = 0; i < NUM_VERTICES-1; ++i)
   {
   		glBegin(GL_LINES);
		glVertex3f(v[i].x, v[i].y, v[i].z);

		glVertex3f(v[i+1].x, v[i+1].y, v[i+1].z);
		//printf("%f,%f,%f\n",v[i].x,v[i].y,v[i].z );
		//printf("%f,%f,%f\n",v[i+1].x, v[i+1].y, v[i+1].z );
		printf("\n");
		glEnd();
   }
  
   //ejes();
   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}
 
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(30.0f, aspect, 0.1f, 100.0f);
}
 
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	glVertex3f(-1.0, 2.0, 3.0);
	glVertex3f(1.0, 1.0, 1.0);
	glEnd();
   	glBegin(GL_LINES);           // Begin drawing the pyramid with 4 triangles
    glVertex3f(1.0, 1.0, 1.0);
  	glVertex3f(3.0,2.0,1.0);
	v[0].x=-1.0;
   	v[0].y=2.0;
   	v[0].z=3.0;
   	v[1].x=1.0;
   	v[1].y=1.0;
   	v[1].z=1.0;
   	v[2].x=3.0;
   	v[2].y=2.0;
   	v[2].z=1.0;
   	printf("Matriz original de puntos\n");
   	printVer();
   	
   	printf("Matriz de puntos con traslacion (-1,-1,-1)\n");
   	translatePoints(-v[1].x,-v[1].y,-v[1].z);
   	printVer();
   //	rotatePointsYpos(2,-2);
   	printf("Matriz de puntos con RotacionZ\n" );
   	rotatePointsZpos(v[0].y,-v[0].x);
   	printVer();
   //	rotatePointsZpos(1,2);
   	printf("Matriz de puntos con RotacionY\n");
   	rotatePointsYpos(v[0].z,v[0].x);
   	printVer();

   	//printf("%f\n",v[1].x);
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}

void printVer(){
	for (int i = 0; i < NUM_VERTICES; ++i)
   	{
   		v[i].print();
   		printf("\n");
   	}
   	printf("\n");
}
void translatePoints(int dx,int dy, int dz)
{
	double pointMatrix[N][NUM_VERTICES];
    makePointMatrix(pointMatrix);
    double result[N][NUM_VERTICES];
    translate(pointMatrix, dx, dy, dz, result);
	storePoints(result);
}
void rotatePointsXpos(double opuesto, double costado)
{
	double pointMatrix[N][NUM_VERTICES];
    makePointMatrix(pointMatrix);
    double result[N][NUM_VERTICES];
    rotateXpos(pointMatrix, opuesto, costado, result);
	storePoints(result);
}
void rotatePointsYpos(double opuesto, double costado)
{
	double pointMatrix[N][NUM_VERTICES];
    makePointMatrix(pointMatrix);
    double result[N][NUM_VERTICES];
    rotateYpos(pointMatrix, opuesto, costado, result);
	storePoints(result);
}
void rotatePointsZpos(double opuesto, double costado)
{
	double pointMatrix[N][NUM_VERTICES];
    makePointMatrix(pointMatrix);
    double result[N][NUM_VERTICES];
    rotateZpos(pointMatrix, opuesto, costado, result);
	storePoints(result);
}
void rotatePointsXneg(double opuesto, double costado)
{
	double pointMatrix[N][NUM_VERTICES];
    makePointMatrix(pointMatrix);
    double result[N][NUM_VERTICES];
    rotateXneg(pointMatrix, opuesto, costado, result);
	storePoints(result);
}
void rotatePointsYneg(double opuesto, double costado)
{
	double pointMatrix[N][NUM_VERTICES];
    makePointMatrix(pointMatrix);
    double result[N][NUM_VERTICES];
    rotateYneg(pointMatrix, opuesto, costado, result);
	storePoints(result);
}
void rotatePointsZneg(double opuesto, double costado)
{
	double pointMatrix[N][NUM_VERTICES];
    makePointMatrix(pointMatrix);
    double result[N][NUM_VERTICES];
    rotateZneg(pointMatrix, opuesto, costado, result);
	storePoints(result);
}

void storePoints(double pointMatrix[N][NUM_VERTICES])
    {
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            v[i].x = pointMatrix[0][i];
        }
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            v[i].y = pointMatrix[1][i];
        }
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            v[i].z = pointMatrix[2][i];
        }
}

void makePointMatrix(double (&pointMatrix)[N][NUM_VERTICES]
	)
    {
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            pointMatrix[0][i] = v[i].x;
        }
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            pointMatrix[1][i] = v[i].y;
        }
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            pointMatrix[2][i] = v[i].z;
        }
        for(int i = 0; i<NUM_VERTICES; i++)
        {
            pointMatrix[3][i] = 1;
        }
}
void ejes(void){
  // Eje X.
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex3f(5.0, 0.0, 0.0);
  glVertex3f(-5.0, 0.0, 0.0);
  glEnd();
  // Eje Y.
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);
  glVertex3f(0.0, 5.0, 0.0);
  glVertex3f(0.0, -5.0, 0.0);
  glEnd();
  // Eje Z.
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_LINES);
  glVertex3f(0.0, 0.0, 5.0);
  glVertex3f(0.0, 0.0, -5.0);
  glEnd();
}

void multiplyMatrix(double a[N][N], int r1, int c1 ,double b[N][NUM_VERTICES], int r2, int c2, double (&c)[N][NUM_VERTICES])
{
    if(c1 != r2)
    {
        printf("Error in multiply matrix");
        return;
    }
    /*
    printf("Transformation matrix\n");
    for(int i = 0; i<N; i++)
    {
        for(int j = 0; j<N; j++)
        {
            printf("%d  ",(int) a[i][j]);
        }
        printf("\n");
    }
    printf("\n\nPoint Matrix\n");
    for(int i = 0; i<N; i++)
    {
        for(int j = 0; j<NUM_VERTICES; j++)
        {
            printf("%d  ", (int)b[i][j]);
        }
        printf("\n");
    }
    */
    for(int i = 0; i<r1; i++)
    {
        for(int j = 0; j<c2; j++)
        {
            c[i][j] = 0;
            for(int k = 0; k<r2; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    /*
    printf("\n\nResultant matrix\n");
    for(int i = 0; i<N; i++)
    {
        for(int j = 0; j<NUM_VERTICES; j++)
        {
            printf("%d  ",(int) c[i][j]);
        }
        printf("\n");
    }
    */
}
void translate(double matrix[N][NUM_VERTICES], int dx, int dy, int dz, double (&result)[N][NUM_VERTICES])
{
    //number of columns = number of points
    double transform[N][N] =
    {
        {1,0,0,dx},
        {0,1,0,dy},
        {0,0,1,dz},
        {0,0,0,1}
    };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}
void scale(double matrix[N][NUM_VERTICES], double sx, double sy, double sz, double (&result)[N][NUM_VERTICES])
{
     double transform[N][N] = {
                         {sx,0,0,0},
                         {0,sy,0,0},
                         {0,0,sz,0},
                         {0,0,0,1}
                        };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}

void rotateXneg(double matrix[N][NUM_VERTICES], double opuesto,double costado, double (&result)[N][NUM_VERTICES])
{
	double H=sqrt(pow(costado,2)+pow(opuesto,2));
    double Cos = costado/H;
    double Sin = opuesto/H;
    double transform[N][N] = {
                         {1,0,0,0},
                         {0,Cos,Sin,0},
                         {0,-Sin,Cos,0},
                         {0,0,0,1}
                        };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}
void rotateYneg(double matrix[N][NUM_VERTICES], double opuesto,double costado, double (&result)[N][NUM_VERTICES])
{
    double H=sqrt(pow(costado,2)+pow(opuesto,2));
    double Cos = costado/H;
    double Sin = opuesto/H;
    double transform[N][N] = {
                         {Cos,0,-Sin,0},
                         {0,1,0,0},
                         {Sin,0,Cos,0},
                         {0,0,0,1}
                        };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}
void rotateZneg(double matrix[N][NUM_VERTICES], double opuesto,double costado, double (&result)[N][NUM_VERTICES])
{
    double H=sqrt(pow(costado,2)+pow(opuesto,2));
    double Cos = costado/H;
    double Sin = opuesto/H;
    double transform[N][N] = {
                         {Cos,Sin,0,0},
                         {-Sin,Cos,0,0},
                         {0,0,1,0},
                         {0,0,0,1}
                        };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}

void rotateXpos(double matrix[N][NUM_VERTICES], double opuesto,double costado, double (&result)[N][NUM_VERTICES])
{
	double H=sqrt(pow(costado,2)+pow(opuesto,2));
    double Cos = costado/H;
    double Sin = opuesto/H;
    double transform[N][N] = {
                         {1,0,0,0},
                         {0,Cos,-Sin,0},
                         {0,Sin,Cos,0},
                         {0,0,0,1}
                        };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}
void rotateYpos(double matrix[N][NUM_VERTICES], double opuesto,double costado, double (&result)[N][NUM_VERTICES])
{
    double H=sqrt(pow(costado,2)+pow(opuesto,2));
    double Cos = costado/H;
    double Sin = opuesto/H;
    double transform[N][N] = {
                         {Cos,0,Sin,0},
                         {0,1,0,0},
                         {-Sin,0,Cos,0},
                         {0,0,0,1}
                        };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}
void rotateZpos(double matrix[N][NUM_VERTICES], double opuesto,double costado, double (&result)[N][NUM_VERTICES])
{
    double H=sqrt(pow(costado,2)+pow(opuesto,2));
    double Cos = costado/H;
    double Sin = opuesto/H;
    double transform[N][N] = {
                         {Cos,-Sin,0,0},
                         {Sin,Cos,0,0},
                         {0,0,1,0},
                         {0,0,0,1}
                        };
    multiplyMatrix(transform, N, N, matrix, N, NUM_VERTICES,result);
}