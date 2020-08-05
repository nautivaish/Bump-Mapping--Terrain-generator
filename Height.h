#include <vector>

using namespace std;

/*! class to store details of mesh */
class MeshHeight
{
public:

	MeshHeight(int x, int z);
	/*!	Constructor to set width and length of map as x and z respectively.	*/

	
	/*!	Value Retrieval	*/
	int GetWidth();
	/*!
	*@return width of Map
	*/
	int GetLength();
	/*!
	*@return Length of Map
	*/
	double GetMaxHeight();
	/*!
	*@return maximum height to calculate rgb values
	*/

	void drawTriangleMesh(bool wireframe, bool shadeflat);
	/*!	Draws the triangular 2-D mesh	*/
	void calcHeight();
	/*!	Assigns different heights randomly to each vertex 	*/

private:
	

	/*!	Private MeshHeight class variables	*/

	double **HeightArray;

	int mapWidth; 
	int mapLength; 	
	vector <double> **vertexNormals;
	vector <double> **faceNormal;
	int faceIndex;
	/*!
	*@param double **HeightArray : stores heights of vertices of triangle in the 2-D map
	*@param int mapWidth : width of x-plane of map
	*@param int mapLength : width of z-plane of map
	*@param vector <double> **vertexNormals : stores unit vector of all vertex points of the triangles
	*@param vector <double> **faceNormal : stores unit vector of the faces of the triangles
	*@param int faceIndex : Stores the no. of triangle in one row.
	*/

};

