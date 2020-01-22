//What the hell is going on?
/*
Lovely istringstream code via Sergey Zubkov 
@ https://www.quora.com/How-do-I-split-a-string-by-space-into-an-array-in-c++
*/

using namespace std;
#include <iostream>
#include <cstdio>
#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>
#include <Eigen/Dense>
#include "camera.h"
#include "geometry.h"

//if you give this function a string, it will give you a vector of that string, split on whitespace
vector<string> Vectorize(string myString);


int main()
{
  //Relatively Global but not Global variables
  double resX, resY;//picture resolution
  Eigen::Vector3d bgColor;
  Eigen::Vector3d shapeColor;
  vector<Eigen::Vector3d> lights;
  vector<double> materialData;
  Camera cam;
  vector<Sphere> spheres;
  vector<Polygon> polygons;

  //I/O stuff
  string theFile;
  cout << "Please enter the name of the file you want to read: ";
  cin >> theFile;

  ifstream ifs;
  ifs.open(theFile, ios::in);

  string theString;
  vector<string> tokens;

  //while we can get a line from our file
  while(getline(ifs, theString))
    {
      //tokenize the line and store it in tokens
      tokens = Vectorize(theString);
      
      //change first token into a char
      char two = tokens[0][0];
      //get decimal value of that char
      int check = int(two);

      //SWITCH STATEMENT VARIABLES - variables made solely for use in this switch
      string data;
      vector<string> dataVec;
      //camera
      Eigen::Vector3d tempFrom;
      Eigen::Vector3d tempAt;
      Eigen::Vector3d tempUp;
      double tempAngle;
      double tempHither;
      //lights
      Eigen::Vector3d newLight;
      //polygons
      Polygon* poly;
      Sphere* sphere;
      double counter;
      Eigen::Vector3d newVert;
      int currentObject = 0;
      //END SWITCH STATEMENT VARIABLES =========================================
      //switch statement operates on the value of our first token(which we cast to an int)
      switch(check)
	{
	  //if the first token in the letter "b"
	case 98:
	  //put the rest of the vector into bgColor
	  bgColor << stod(tokens[1]), stod(tokens[2]), stod(tokens[3]);
	  break;
	  //if the first token is the letter "v"
	case 118:
	  
	  //from
	  getline(ifs, data);
	  dataVec = Vectorize(data);
	  tempFrom << stod(dataVec[1]), stod(dataVec[2]), stod(dataVec[3]);
	  dataVec.clear();
	  //at
	  getline(ifs, data);
	  dataVec = Vectorize(data);
	  tempAt << stod(dataVec[1]), stod(dataVec[2]), stod(dataVec[3]);
	  dataVec.clear();
	  //up
	  getline(ifs, data);
	  dataVec = Vectorize(data);
	  tempUp << stod(dataVec[1]), stod(dataVec[2]), stod(dataVec[3]);
	  dataVec.clear();
	  //angle
	   getline(ifs, data);
          dataVec = Vectorize(data);
          tempAngle = stod(dataVec[1]);
	  dataVec.clear();
	  //hither
	   getline(ifs, data);
          dataVec = Vectorize(data);
          tempHither = stod(dataVec[1]);
          dataVec.clear();
	  //resolution
	   getline(ifs, data);
          dataVec = Vectorize(data);
          resX = stod(dataVec[1]);
	  resY = stod(dataVec[2]);
          dataVec.clear();
	  //Initialize Camera
	  cam.Init(tempFrom, tempAt, tempUp, tempAngle, tempHither, resX, resY);
	  break;
	case 108:
	  //make new light
	  newLight << stod(tokens[1]), stod(tokens[2]), stod(tokens[3]);
	  //push it into light vector
	  lights.push_back(newLight);
	  
	  break;
	case 102:
	  //empty materials vector in case there was something in there already
	  materialData.clear();
	  //put everything in the tokens vector into the materials vector
	  //start at 1 so that we don't include the 'f'
	  for(int i = 1; i < tokens.size(); i++)
	    {
	      materialData.push_back(stod(tokens[i]));
	    }
	  
	  
	  break;
	case 112:
	  //Initialize new Polygon with RGB and number of vertices
	  poly = new Polygon(materialData[0], materialData[1], materialData[2], stod(tokens[1]));
	  
	  counter = 0;
	  //foreach vertex
	  while(counter < stod(tokens[1]))
	    {
	      getline(ifs, data);
	      dataVec = Vectorize(data);
	      //Turn into vector3d
	      newVert << stod(dataVec[0]),stod(dataVec[1]),stod(dataVec[2]);
	      //add vertex to polygon
	      poly->AddVertex(newVert);

	      counter++;
	    }
	  //add to vector of polygons
	  polygons.push_back(*poly);
  
	  //deallocate poly memory
	  delete poly;
	  poly = NULL;

	  break;
	case 115:
	  //make new sphere
	  sphere = new Sphere(materialData[0], materialData[1], materialData[2],
			      stod(tokens[1]),  stod(tokens[2]),  stod(tokens[3]),  stod(tokens[4]));
	  //put it in spheres vector
	  spheres.push_back(*sphere);
	  
	  break;
	default:
	  cout << "hi" << endl;
	}
      tokens.clear();
    }
  ifs.close();

  unsigned char pixels[(int)resY][(int)resX][3];

  for(int i = 0; i < resY; i++)
    {
      for(int j = 0; j < resX; j++)
	{
	  //get the pixel location
	  Eigen::Vector3d pixel = cam.m_topLeft
	    + (cam.m_u * j * cam.m_pixelWidth)
	    - (cam.m_v * i * cam.m_pixelHeight);
	  
	  //create and initialize the ray
	  Ray ray;
	  ray.SetEye(cam.m_from);
	  Eigen::Vector3d direction = (pixel - cam.m_from).normalized();
	  ray.SetDirection(direction);
	  
	  //set our t-Range
	  double t0 = 0;
	  double t1 = INFINITY;
	  Eigen::Vector3d color = bgColor;

	  
	  //if our polygon vector has items, loop through them
	  if(!polygons.empty())
	    {
	  
	      for(int k = 0; k < polygons.size(); k++)
		{	     
		  if(polygons[k].Intersect(ray, t0, t1))
		    {
		      color = polygons[k].GetColor();
		      t1 = polygons[k].GetT();
		    }
		}
	    }
	  //if our spheres vector has items loop through them
	  if(!spheres.empty())
	    {
	      
	      for(int l = 0; l < spheres.size(); l++)
	     {
	       
              if(spheres[l].Intersect(ray, t0, t1))
                {
                  color = spheres[l].GetColor();
                  t1 = spheres[l].GetT();
                }
            }
	    }
	  //set pixel color
	  for(int m = 0; m < 3; m++)
	    {
	      pixels[i][j][m]= color[m]*255;
	    }
	}
    }


  FILE *f = fopen("hide.ppm","wb");
  fprintf(f, "P6\n%d %d\n%d\n", (int)resX, (int)resY, 255);
  fwrite(pixels, 1, (int)resY*(int)resX*3, f);
  fclose(f);
  
  return 0;
}


vector<string> Vectorize(string myString)
{
  vector<string> stringVector;
  istringstream iss(myString);
  for(string s; iss >> s;)
    {
      stringVector.push_back(s);
    }
  return stringVector;
}
