#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <GL/glut.h>
#include "Height.h"

using namespace std;	

/*!  Global Variables
*/	
vector <MeshHeight> maps;

/*!  Map  Size parameters
*/
int width, height;


/*!  Rotation variables
*/
float _angleX = 0.0f;
float _angleY = 0.0f;
float _angleZ = 0.0f;

/*!  Translation variables
*/
float translateX = 0.0f;
float translateY = 0.0f;
float translateZ = -20.0f;


/*!  Wireframe variables
*/
int wireframeOption = 0;
bool wireframeToggle = false;

/*!  Shading and light 
*/
bool shader = true;
bool lights = false;
bool light0on = true;
GLfloat light0pos[] = {1 , 10 , 0 , 1};
GLfloat light1pos[] = {-1 , 10 , 0 , 1};



/*!  Draw Terrain scene
*/
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*!  Camera
	*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*!  Transforms
	*/
	glTranslatef(translateX, translateY, translateZ);
    glRotatef(_angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(_angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(_angleZ, 0.0f, 0.0f, 1.0f);

	/*!  Lighting
	*/
	if (lights == true)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);

		glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
		glEnable(GL_LIGHT0);

		glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
		glEnable(GL_LIGHT1);
	}
	else glDisable(GL_LIGHTING);

	
	maps[0].drawTriangleMesh(wireframeToggle, shader);
	if (wireframeOption == 2) maps[0].drawTriangleMesh(false, shader);
	
	/*!  Flush pipeline
	*/
	glFlush();

	/*!  Double Buffering
	*/
	glutSwapBuffers();

	/*!  Flush pipeline
	*/
	glutPostRedisplay();
}

/*! Initialize the terrain 
*/
void CreateTerrain(void)
{
	/*! Generate flat terrain
	*/
	MeshHeight terrain(width + 1, height + 1);

	/*! Create hills
	*/
	terrain.calcHeight();

	maps.push_back(terrain);

	width = maps[0].GetWidth();
	height = maps[0].GetLength();
	light0pos[1] = maps[0].GetMaxHeight() + 8;
	light1pos[1] = maps[0].GetMaxHeight() + 8;
}

void Instructions()
{
	cout << "\n";
	cout<<"This is the instructions menu: ^_^\n";
	cout << "t -> Turn wireframe on/off\n";
	cout << "<space> -> toggle the shading mode \n";
	cout << "Esc -> Exit code\n";	
	cout << "r -> Reset the position" << endl;
	cout << "Arrow keys, i,j,k,l,w,a,s,d for translation and rotation controls" << endl;
	cout << "h -> Display the Instructions menu again" << endl;
	cout << endl;
	
	return;
}

/*! Initiates the creation of the terrain - user triggered
*/
void getTerrainSize(void)
{
	double wd, ht;

	cout << "Enter the width of terrain upto 300: ";
	cin >> wd;
	width = floor(wd);
	cout << "Enter the length of the terrain upto 300: ";
	cin >> ht;
	height = floor(ht);

	CreateTerrain();
}

/*!  The GLUT keyboard function 
 *	Esc -> Quit
 *	r -> reset position
 *	t -> Toggle wireframe modes
 *	<space> -> Toggle between flat and smooth shading
 *  Arrow keys, i,j,k,l,w,a,s,d -> rotation and translation control
 *	h -> Display Instructions script
 */




/*! Called when a key is pressed
*/
void RegularKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 27: /*!  Escape key */
	        exit(0);

        /*! Input instruction keys. */
        case 'i':                   /*! Scene moves down (Y-axis) */
	        translateY -= 1.0f;
	        break;

        case 'k':                   /*! Scene moves up (Y-axis) */
	        translateY += 1.0f;
	        break;

        /*! Rotation (follows right hand thumb rule) */
        case 'w':                   /*! Scene rotates about +ve X-axis */
	        _angleX += 1.5f;
	        break;

        case 's':                   /*! Scene rotates about -ve X-axis */
	        _angleX -= 1.5f;
	        break;

        case 'a':                   /*! Scene rotates about +ve Y-axis */
	        _angleY += 1.5f;
	        break;

        case 'd':                   /*! Scene rotates about -ve Y-axis */
	        _angleY -= 1.5f;
	        break;

        case 'j':                   /*! Scene rotates about +ve Z-axis */
        	_angleZ += 1.5f;
        break;

        case 'l':                   /*! Scene rotates about -ve Z-axis */
       		_angleZ -= 1.5f;
        break;

        case 'r':                   /*! Reset Scene to initial state */
	        _angleX = 0.0f;
	        _angleY = 0.0f;
	        _angleZ = 0.0f;

	        translateX = 0.0f;
	        translateY = 0.0f;
	        translateZ = -20.0f;
			break;
		case 'h':
			Instructions();
			break;
		case 't':
			wireframeOption = (wireframeOption + 1) % 3;
			if (wireframeOption != 0) wireframeToggle = true;
			else wireframeToggle = false;
			break;
		case ' ':
			shader = !shader;
			break;


    }

    glutPostRedisplay();            /*! redraw scene */
}


/*! Called when special keys are pressed */
void specialKeys(int key, int x, int y) {
    switch(key)
    {
        case GLUT_KEY_UP:           /*! Scene zooms in (Z-axis) */
        translateZ += 1.0f;
        break;  
        case GLUT_KEY_DOWN:         /*! Scene zooms out (Z-axis) */
        translateZ -= 1.0f;
        break;
        case GLUT_KEY_LEFT:         /*! Scene goes left (X-Axis) */
        translateX -= 1.0f;
        break;
        case GLUT_KEY_RIGHT:        /*! Scene goes right (X-Axis) */
        translateX += 1.0f;
        break;
    }

    glutPostRedisplay();

}

/*! 	MAIN PROGRAM */

int main(int argc, char** argv)
{

		cout << "This is a program to generate random terrains. \n";
		cout << endl;
		Instructions();
		getTerrainSize();
		
	glutInit(&argc, argv);	
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glOrtho(0, height, width, 0, -5, 5);

		

	/*! Terrain window */
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	int Window = glutCreateWindow("#3D TERRAIN - BUMP MAPPING#");

	/*! Depth testing */
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glMatrixMode(GL_PROJECTION);
	glOrtho(-width/2, width/2 , -height/2 , height , -width * height /2, width * height / 2);

	glClearColor(0, 0, 0, 0);

	/*! GLUT Functions */
	glutKeyboardFunc(RegularKeys);
	glutSpecialFunc(specialKeys);
	glutDisplayFunc(drawScene);

	glutMainLoop();

	return 0;
}