#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "Height.h"
#include <time.h>

using namespace std;

const double X_SCALE = 1.5;
const double z_SCALE = 1.5;
const double DISPLACE_HEIGHT = 0.5;
const int MAX_RADIUS = 20;

/*! Maximum height to calculate colours */
double maxHeight = 0;

/*! Constructor	
 * To set the width and length values and create three dynamic 2D arrays - one for each heights,face normals and vertex normals. 
 */

MeshHeight::MeshHeight(int x, int z)
{
	mapWidth = x;
	mapLength = z;

	/*! Creating a 2D array dynamically to match map xz plane */
	HeightArray = new double *[mapLength];

	for (int i = 0; i < mapLength; i++)
	{
		HeightArray[i] = new double [mapWidth];
	}

	/*! Initializing the height values to 0 */
	for (int j = 0; j < mapLength; j++)
	{
		for (int k = 0; k < mapWidth; k++)
		{
			HeightArray[j][k] = 0;
		}
	}

	/*! Dynamic array creation for Face normals */
	faceIndex = (mapWidth - 1) * 2;

	faceNormal = new vector <double> *[mapLength - 1];
	for (int i = 0; i < mapLength; i++) faceNormal[i] = new vector <double> [faceIndex];

	/*! Dynamic array creation for Point normals */
	vertexNormals = new vector <double> *[mapLength];
	for (int i = 0; i < mapLength; i++) vertexNormals[i] = new vector <double> [mapWidth];
}

/*!	Get Functions	*/
/*!
 * Functions to retrieve private map parameters
 */

int MeshHeight::GetLength()
{
	return mapLength;
}

int MeshHeight::GetWidth()
{
	return mapWidth;
}

double MeshHeight::GetMaxHeight()
{
	return maxHeight;
}

/*!	Drawing Functions	*/

/*!
 * These functions are used to draw the height mesh.
 */
void MeshHeight::drawTriangleMesh(bool wireframe, bool shadeflat)
{
	for (int i = 0; i < mapLength - 1; i++)
	{
		/*! Determine if it is wireframe or filled terrain */
		if (wireframe == true) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		/*! Shade modelling */
		if (shadeflat == true) glShadeModel(GL_FLAT);
		else glShadeModel(GL_SMOOTH);

		/*! Triangle strips */
		glBegin(GL_TRIANGLE_STRIP);
			for (int j = 0; j < mapWidth; j++)
			{
				/*! Colouring the first strip */
				if (wireframe == false)
				{
					if (HeightArray[i][j] < 0) glColor3d(0, 1, 0);
					else if (HeightArray[i][j] < maxHeight * 0.1) glColor3d(0.05, 0.95, 0);
					else if (HeightArray[i][j] < maxHeight * 0.2) glColor3d(0.1, 0.9, 0);
					else if (HeightArray[i][j] < maxHeight * 0.3) glColor3d(0.15, 0.85, 0);
					else if (HeightArray[i][j] < maxHeight * 0.4) glColor3d(0.2, 0.8, 0);
					else if (HeightArray[i][j] < maxHeight * 0.5) glColor3d(0.25, 0.75, 0);
					else if (HeightArray[i][j] < maxHeight * 0.6) glColor3d(0.3, 0.7, 0);
					else if (HeightArray[i][j] < maxHeight * 0.7) glColor3d(0.35, 0.65, 0);
					else if (HeightArray[i][j] < maxHeight * 0.8) glColor3d(0.4, 0.6, 0);
					else if (HeightArray[i][j] < maxHeight * 0.9) glColor3d(0.45, 0.55, 0);
					else glColor3d(0.5, 0.5, 0.5);
				}
				else glColor3d(1, 1, 1);

				/*! Normals */
				if (shadeflat == true)
				{
					if (j > 0) glNormal3d(faceNormal[i][j - 1][0], faceNormal[i][j - 1][1], faceNormal[i][j - 1][2]);
				}
				else glNormal3d(vertexNormals[i][j][0], vertexNormals[i][j][1], vertexNormals[i][j][2]);

				/*! Draw first vertex */
				if (wireframe == false) glVertex3d(double(i - mapLength / 2), HeightArray[i][j], double(j - mapWidth / 2));
				else glVertex3d(double(i - mapLength / 2), (HeightArray[i][j] + 0.1), double(j - mapWidth / 2));

				/*! Colouring the second strip*/
				if (wireframe == false)
				{
					if (HeightArray[i + 1][j] < 0) glColor3d(0, 1, 0);
					else if (HeightArray[i + 1][j] < maxHeight * 0.1) glColor3d(0.05, 0.95, 0);
					else if (HeightArray[i + 1][j] < maxHeight * 0.2) glColor3d(0.1, 0.9, 0);
					else if (HeightArray[i + 1][j] < maxHeight * 0.3) glColor3d(0.15, 0.85, 0);
					else if (HeightArray[i + 1][j] < maxHeight * 0.4) glColor3d(0.2, 0.8, 0);
					else if (HeightArray[i + 1][j] < maxHeight * 0.5) glColor3d(0.25, 0.75, 0);
					else if (HeightArray[i + 1][j] < maxHeight * 0.6) glColor3d(0.3, 0.7, 0);
					else if (HeightArray[i + 1][j] < maxHeight * 0.7) glColor3d(0.35, 0.65, 0);
					else if (HeightArray[i + 1][j] < maxHeight * 0.8) glColor3d(0.4, 0.6, 0);
					else if (HeightArray[i + 1][j] < maxHeight * 0.9) glColor3d(0.45, 0.55, 0);
					else glColor3d(0.5, 0.5, 0.5);
				}
				else glColor3d(1, 1, 1);

				/*! Normals */
				if (shadeflat == true)
				{
					if (j > 0) glNormal3d(faceNormal[i][j][0], faceNormal[i][j][1], faceNormal[i][j][2]);
				}
				else glNormal3d(vertexNormals[i + 1][j][0], vertexNormals[i + 1][j][1], vertexNormals[i + 1][j][2]);

				/*! Draw second vertex */
				if (wireframe == false) glVertex3d(double(i + 1 - mapLength / 2), HeightArray[i + 1][j], double(j - mapWidth / 2));
				else glVertex3d(double(i + 1 - mapLength / 2), (HeightArray[i + 1][j] + 0.1), double(j - mapWidth / 2));
			}
		glEnd();
	}
	return;
}

/*!	Terrain Algorithm	*/
/*!
 * Function to intialiaize the terrain.
 */
/*! compute unit normal vector of a triangle strip */
vector <double> CalcNormalVector(vector <double> p1, vector <double> p2, vector <double> p3)
{
	double x, y, z;
	double length;
	vector <double> u, v;
	vector <double> normal;
	
	/*! u vector */
	x = p1[0] - p2[0]; u.push_back(x);
	y = p1[1] - p2[1]; u.push_back(y);
	z = p1[2] - p2[2]; u.push_back(z);

	/*! v vector */
	x = p3[0] - p2[0]; v.push_back(x);
	y = p3[1] - p2[1]; v.push_back(y);
	z = p3[2] - p2[2]; v.push_back(z);

	/*! Normal */
	x = u[1] * v[2] - u[2] * v[1];
	y = u[2] * v[0] - u[0] * v[2];
	z = u[0] * v[1] - u[1] * v[0];

	length = sqrt(x*x + y*y + z*z);

	normal.push_back(-1 * x / length);
	normal.push_back(-1 * y / length);
	normal.push_back(-1 * z / length);

	return normal;
}

void MeshHeight::calcHeight()
{
	double dz, dx;
	double distance;
	double bound;
	int x, z;
	double radius;
	double inclineAngle;

	/*! Determine no. hills in terrain */
	int area = mapWidth * mapLength;
	int num = area/1000;
	srand(time(0));	
	int numbCircles = rand() % area + num * (mapWidth);

	/*! Calc height */
	for (int a = 0; a < numbCircles; a++)
	{
		/*! Circle parameters */
		x = rand() % mapWidth;
		z = rand() % mapLength;
		radius = rand() % MAX_RADIUS + 1;

		/*! Check progress For each terrain point */
		cout << "LOADING MAP: " << a << "/" << numbCircles - 1 << endl;

		for (int i = 0; i < mapLength; i++)
		{
			for (int j = 0; j < mapWidth; j++)
			{
				dz = z - i;
				dx = x - j;

				/*! Calculate distance between point and circle centre */
				distance = sqrt((dz*dz) + (dx*dx));

				bound = distance * 2  / radius;

				if (fabs(bound) <= 1.0)
				{
					inclineAngle = bound * 3.14 / 180;
					HeightArray[i][j] += (DISPLACE_HEIGHT / 2.0)  + (cos(inclineAngle) * DISPLACE_HEIGHT / 2.0);

					if (HeightArray[i][j] > maxHeight) maxHeight = HeightArray[i][j];
				}
			}
		}
	}

	cout << "Calculating normals..." << endl;
	cout << "Calculating face normals..." << endl;
	vector <double> point;
	point.push_back(0); point.push_back(0); point.push_back(0);
	
	vector <double> p1, p2, p3;
	p1 = point; p2 = point; p3 = point;

	vector <double> face;

	for (int i = 0; i < mapLength - 1; i++)
	{
		for (int j = 0; j < faceIndex - 1; j++)
		{
			p1[0] = i + 1; p1[1] = HeightArray[i + 1][j]; p1[2] = j;
			p2[0] = i; p2[1] = HeightArray[i][j]; p2[2] = j;
			p3[0] = i; p3[1] = HeightArray[i][j + 1]; p3[2] = j + 1;
			face = CalcNormalVector(p1, p2, p3);
			faceNormal[i][j] = face;

			p1[0] = i; p1[1] = HeightArray[i][j + 1]; p1[2] = j + 1;
			p2[0] = i + 1; p2[1] = HeightArray[i + 1][j]; p2[2] = j;
			p3[0] = i + 1; p3[1] = HeightArray[i + 1][j + 1]; p3[2] = j + 1;
			face = CalcNormalVector(p1, p2, p3);
			faceNormal[i][j + 1] = face;
		}
	}

	cout << "Face normals computed. Now getting point normals" << endl;
	int index;

	/*! First point in row 1 */
	vertexNormals[0][0] = faceNormal[0][0];

	/*! Middle points in row 1 */
	for (int i = 1; i < mapWidth - 1; i++)
	{
		index = i * 2;
		point[0] = (faceNormal[0][index - 2][0] + faceNormal[0][index - 1][0] + faceNormal[0][index][0]) / 3;
		point[1] = (faceNormal[0][index - 2][1] + faceNormal[0][index - 1][1] + faceNormal[0][index][1]) / 3;
		point[2] = (faceNormal[0][index - 2][2] + faceNormal[0][index - 1][2] + faceNormal[0][index][2]) / 3;

		vertexNormals[0][i] = point;
	}

	/*! Last point in row 1 */
	point[0] = (faceNormal[0][(mapWidth * 2) - 4][0] + faceNormal[0][(mapWidth * 2) - 3][0]) / 2;
	point[1] = (faceNormal[0][(mapWidth * 2) - 4][1] + faceNormal[0][(mapWidth * 2) - 3][1]) / 2;
	point[2] = (faceNormal[0][(mapWidth * 2) - 4][2] + faceNormal[0][(mapWidth * 2) - 3][2]) / 2;

	vertexNormals[0][mapWidth - 1] = point;

	/*! Middle rows */

	for (int i = 1; i < mapLength - 1; i++)
	{
		/*! First point  */
		point[0] = (faceNormal[i - 1][0][0] + faceNormal[i - 1][1][0] + faceNormal[i][0][0]) / 3;
		point[1] = (faceNormal[i - 1][0][1] + faceNormal[i - 1][1][1] + faceNormal[i][0][1]) / 3;
		point[2] = (faceNormal[i - 1][0][2] + faceNormal[i - 1][1][2] + faceNormal[i][0][2]) / 3;

		vertexNormals[i][0] = point;

		/*! Middle points */
		for (int j = 1; j < mapWidth - 1; j++)
		{
			index = j * 2;

			point[0] = (faceNormal[i - 1][index - 1][0] + faceNormal[i - 1][index][0] + faceNormal[i - 1][index + 1][0] + faceNormal[i][index - 2][0] + faceNormal[i][index - 1][0] + faceNormal[i][index][0]) / 6;
			point[1] = (faceNormal[i - 1][index - 1][1] + faceNormal[i - 1][index][1] + faceNormal[i - 1][index + 1][1] + faceNormal[i][index - 2][1] + faceNormal[i][index - 1][1] + faceNormal[i][index][1]) / 6;
			point[2] = (faceNormal[i - 1][index - 1][2] + faceNormal[i - 1][index][2] + faceNormal[i - 1][index + 1][2] + faceNormal[i][index - 2][2] + faceNormal[i][index - 1][2] + faceNormal[i][index][2]) / 6;
			
			vertexNormals[i][j] = point;
		}

		/*! Last point */
		point[0] = (faceNormal[i - 1][(mapWidth * 2) - 3][0] + faceNormal[i][(mapWidth * 2) - 4][0] + faceNormal[i][(mapWidth * 2) - 3][0]) / 3;
		point[1] = (faceNormal[i - 1][(mapWidth * 2) - 3][1] + faceNormal[i][(mapWidth * 2) - 4][1] + faceNormal[i][(mapWidth * 2) - 3][1]) / 3;
		point[2] = (faceNormal[i - 1][(mapWidth * 2) - 3][2] + faceNormal[i][(mapWidth * 2) - 4][2] + faceNormal[i][(mapWidth * 2) - 3][2]) / 3;
	
		vertexNormals[i][mapWidth - 1] = point;
	}

	/*! Last row - First point */
	point[0] = (faceNormal[mapLength - 2][0][0] + faceNormal[mapLength - 2][1][0]) / 2;
	point[1] = (faceNormal[mapLength - 2][0][1] + faceNormal[mapLength - 2][1][1]) / 2;
	point[2] = (faceNormal[mapLength - 2][0][2] + faceNormal[mapLength - 2][1][2]) / 2;

	vertexNormals[mapLength - 1][0] = point;

	/*! Last row- middle points */
	for (int i = 1; i < mapWidth - 1; i++)
	{
		index= i*2;

		point[0] = (faceNormal[mapLength - 2][index - 1][0] + faceNormal[mapLength - 2][index][0] + faceNormal[mapLength - 2][index + 1][0]) / 3;
		point[1] = (faceNormal[mapLength - 2][index - 1][1] + faceNormal[mapLength - 2][index][1] + faceNormal[mapLength - 2][index + 1][1]) / 3;
		point[2] = (faceNormal[mapLength - 2][index - 1][2] + faceNormal[mapLength - 2][index][2] + faceNormal[mapLength - 2][index + 1][2]) / 3;
	
		vertexNormals[mapLength - 1][i] = point;
	}

	/*! Last row- last point */
	vertexNormals[mapLength - 1][mapWidth - 1] = faceNormal[mapLength - 2][(mapWidth * 2) - 3];

	cout << "Finally Done(yayy! ^_^) drawing terrain..." << endl;

	return;
}