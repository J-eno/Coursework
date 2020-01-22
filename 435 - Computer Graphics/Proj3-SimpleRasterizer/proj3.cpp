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
#include <getopt.h>
#include "camera.h"
#include "geometry.h"

//if you give this function a string, it will give you a vector of that string, split on whitespace
vector<string> Vectorize(string myString);
void VertexProcess(Polygon &triangle, Camera cam, vector<Light> lights);
Eigen::Vector3d shade(vector<Light> lights, Eigen::Vector3d point, Eigen::Vector3d normal, Eigen::Vector3d eye, Eigen::Vector3d color, double kd, double ks, double e);
void Clip(Camera cam, Polygon &triangle);
bool IntersectPlane(Eigen::Vector3d normal, Eigen::Vector3d eye, Eigen::Vector3d a, Eigen::Vector3d b );
double fxx(double x, double y, Eigen::Vector4d one, Eigen::Vector4d two);

int main(int argc, char *argv[])
{
  // Command Line Options
  int c;
  int samples = 1;
  bool stratified = false;
  bool phong = false;
  while ((c = getopt(argc, argv, "jd:s:p")) != -1)
    {
      switch (c)
        {
        case 'j':
	  stratified = true;
	  cout << "stratified... ONLINE" << endl;
	  break;
        case 'd':
	  break;
        case 'p':
	  phong = true;
	  cout << "Phong Shading... ONLINE" << endl;
	  break;
        case 's':
	  samples = atoi(optarg);
	  cout << "Taking " << samples*samples << " samples..." << endl;
        default:
	  //abort();
	  break;
        }
    }
  
   
  //Relatively Global but not Global variables
  double resX, resY;//picture resolution
  Eigen::Vector3d bgColor;
  Eigen::Vector3d shapeColor;
  vector<Light> lights;
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
      
      //SWITCH STATEMENT VARIABLES - variables made solely for use in this switch
      string data;
      vector<string> dataVec;
      //camera
      Eigen::Vector3d tempFrom;
      Eigen::Vector3d tempAt;
      Eigen::Vector3d tempUp;
      double tempAngle;
      double tempHither;
      //Light
      Light* newLight;
      Eigen::Vector3d lightPos;
      Eigen::Vector3d lightCol;
      //polygons
      Polygon* poly;
      Sphere* sphere;
      double counter;
      Eigen::Vector3d newVert;
      vector<Polygon> newTris; //vector of new triangles
      Eigen::Vector3d newNorm;
      int currentObject = 0;
      //END SWITCH STATEMENT VARIABLES =========================================
      //switch statement operates on the value of our first token(which we cast to an int)
      switch(tokens[0][0])
	{
	  //if the first token in the letter "b"
	case 'b':
	  //put the rest of the vector into bgColor
	  bgColor << stod(tokens[1]), stod(tokens[2]), stod(tokens[3]);
	  break;
	  //if the first token is the letter "v"
	case 'v':
	  
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
	case 'l':
	  lightPos << stod(tokens[1]), stod(tokens[2]), stod(tokens[3]);
	  
	  if(tokens.size() > 4)
	    {
	      lightCol << stod(tokens[4]), stod(tokens[6]), stod(tokens[6]);
	    }
	  else
	    {
	      lightCol << 1, 1, 1;
	    }
	  //make new light with position and color
	  newLight = new Light(lightPos, lightCol);
	  //push it into light vector
	  lights.push_back(*newLight);
	  delete newLight;
	  break;
	case 'f':
	  //empty materials vector in case there was something in there already
	  materialData.clear();
	  //put everything in the tokens vector into the materials vector
	  //start at 1 so that we don't include the 'f'
	  for(int i = 1; i < tokens.size(); i++)
	    {
	      materialData.push_back(stod(tokens[i]));
	    }
	  break;
	case 'p':
	  //Initialize new Polygon with RGB and number of vertices
	  poly = new Polygon(materialData[0], materialData[1], materialData[2], stod(tokens[1]), phong);
	  poly->setMaterials(materialData[3], materialData[4], materialData[5], materialData[6], materialData[7]);
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
	      if(tokens[0].length() > 1) //if the token string is > 0 then there are more than one char aka. 'pp'
		{
		  newNorm << stod(dataVec[3]),stod(dataVec[4]),stod(dataVec[5]);
		  poly->AddNormal(newNorm);
		}
	      //poly->AddScreenVertex(newScreenVert);
	      counter++;
	    }
	  //If polygon has more than 3 points
	  if(stod(tokens[1]) > 3)
	    {
	      //Turn into fan of triangles
	      newTris = poly->Triangularize();
	      //add each new triangle to vector of polygons
	      for(int i = 0; i < newTris.size(); i++)
		{
		  polygons.push_back(newTris[i]);
		}
	    }
	  else
	    {
	      //add to vector of polygons
	      polygons.push_back(*poly);
	    }
	  
	  //deallocate poly memory
	  delete poly;
	  poly = NULL;
	  
	  break;
	case 's':
	  //make new sphere
	  /*sphere = new Sphere(materialData[0], materialData[1], materialData[2],
	    stod(tokens[1]),  stod(tokens[2]),  stod(tokens[3]),  stod(tokens[4]));
	    sphere->setMaterials(materialData[3], materialData[4], materialData[5], materialData[6], materialData[7]);
	    //put it in spheres vector
	    spheres.push_back(*sphere);
	    delete sphere;	 */ 
	  break;
	default:
	  cout << "hi" << endl;
	}
      tokens.clear();
    }
  ifs.close();
  ////////////////////////////////////////////////////////////////
  //END OF PARSER////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////

  //create image array
  unsigned char pixels[(int)resY][(int)resX][3];
  //vector of all our pixels
  vector<pixel> pix;
  //Fill pixel vector
  for(int i = 0; i < resY; i++)
    {
      for(int j = 0; j < resX; j++)
	{ 
	  pixel p;
	  p.x = j;
	  p.y = i;
	  //get the pixel location
	  p.location = cam.m_topLeft
	    + (cam.m_u * j * cam.m_pixelWidth)
	    - (cam.m_v * i * cam.m_pixelHeight);
	
	  pix.push_back(p);
	}
    }
  //Do Vertex Processing and clipping
  for(int i = 0; i < polygons.size(); i++)
    {
      //Vertex Processing
      VertexProcess(polygons[i], cam, lights);
      //Clipping
      //Clip(cam, polygons[i]);
    }
  //Rasterization
  //For each triangle
  for(int i = 0; i < polygons.size(); i++)
    {
      Polygon triangle = polygons[i];
      if(triangle.m_clipped == false)
        {
	  int xMin, xMax, yMin, yMax;
	  //do homogeneous divide on each vertex and find mins and maxes
	  for(int j = 0; j < triangle.m_screenVertices.size(); j++)
	    {
	      Eigen::Vector4d vertex = triangle.m_screenVertices[j];
	      
	      vertex /= vertex[3];
	      triangle.m_screenVertices[j] = vertex;
	      
	      //if we are at the first vertex, set xMin - yMax to vertex values
	      if(j == 0)
		{
		  xMin = floor(vertex[0]);
		  xMax = ceil(vertex[0]);
		  yMin = floor(vertex[1]);
		  yMax = ceil(vertex[1]);
		}
	      //Find min and max
	      if(vertex[0] < xMin)
		{
		  xMin = floor(vertex[0]);
		}
	      if(vertex[0] > xMax)
		{
		  xMax = ceil(vertex[0]);
		}
	      if(vertex[1] < yMin)
		{
		  yMin = floor(vertex[1]);
		}
	      if(vertex[1] > yMax)
		{
		  yMax = ceil(vertex[1]);
		}
	      //Stop bounding box from going out of bounds
	      xMin = fmax(0, xMin);
	      xMax = fmin(512, xMax);
	      yMin = fmax(0, yMin);
	      yMax = fmin(512, yMax);
	    }
	  
	  Eigen::Vector4d v0, v1, v2;
	  v0 = triangle.m_screenVertices[0];
	  v1 = triangle.m_screenVertices[1];
	  v2 = triangle.m_screenVertices[2];
	  
	  Eigen::Vector3d c0, c1, c2;
	  c0 = triangle.m_colors[0];
	  c1 = triangle.m_colors[1];
	  c2 = triangle.m_colors[2];
	  double z0, z1, z2;
	  z0 = v0[2];
	  z1 = v1[2];
	  z2 = v2[2];
	  //find barycentric coords
	  double alpha, beta, gamma;
	  double fA = fxx(v0[0],v0[1],v1,v2);
	  double fB = fxx(v1[0],v1[1],v2,v0);
	  double fG = fxx(v2[0],v2[1],v0,v1);
	  for(int y = yMin; y <= yMax; y++)
	    {
	      for(int x = xMin; x <= xMax; x++)
		{
		  //calculate alpha beta and gamma
		  //alpha = fxx(x,y,v1,v2)/fA;
		  beta = fxx(x,y,v2,v0)/fB;
		  gamma = fxx(x,y,v0,v1)/fG;
		  alpha = 1-beta-gamma;
		  //cout << "ALPHA: " << alpha << " BETA: " << beta << " GAMMA: " << gamma << endl;
		  
		  if(alpha >= 0 && beta >= 0 && gamma >= 0)
		    {
		      if((alpha > 0 || fA*fxx(-1, -1, v1, v2) > 0) 
			 && (beta > 0 || fB*fxx(-1,-1, v2, v0) > 0)
			 && (gamma > 0 || fG*fxx(-1,-1,v0,v1) > 0))
			{
			  Eigen::Vector3d c = alpha*c0 +beta*c1 + gamma*c2;
			  double z = alpha*z0 + beta*z1 + gamma*z2;
			  //cout << "Z for some fragment: " << z << endl;
			  fragment frag;
			  frag.z_value = z;
			  frag.color = c;
			  int ii = x + (resX * y);
              
			  //cout << ii << " is X = " << ii%(int)resX << " and Y = " << ii/(int)resX << endl;
			  pix[x + (resX * y)].frags.push_back(frag);
			}
		    }
		}
	    }
	  
        }
    }
  
  for(int p = 0; p < pix.size(); p++)
    {
      Eigen::Vector3d color = bgColor;
      //random math i tried to get it to print the right way
      int oppIndex = pix.size() -(p +1);
      int x = p % (int)resX;
      int y = oppIndex / (int)resX;
      
      //cout << p << " is now X and Y: " << x << "," << y << endl;
      int max;//index of closest frag
      double maxZ;
      //if pixel has frags
      if(!pix[p].frags.empty())
	{
          //cout << "This pixel: " << x << " " << y << " has frags" << endl;
	  //for each pixel, loop through vector of fragments
	  for(int f = 0; f < pix[p].frags.size(); f++)
	    {
	      if(f == 0)
		{
		  max = 0;
		  maxZ = pix[p].frags[f].z_value;
		}
	      if(pix[p].frags[f].z_value > maxZ)
		{
		  maxZ = pix[p].frags[f].z_value;
		  max = f;
		}
	    }
	  color = pix[p].frags[max].color;
	}
      //set pixel color
      for(int m = 0; m < 3; m++)
	{
	  double h = color[m];
	  pixels[y][x][m]= fmax(fmin(h,1),0)*255;
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

void VertexProcess(Polygon &triangle, Camera cam, vector<Light> lights)
{
  //for every vertex in our triangle
  for(int i = 0; i < triangle.m_vertices.size(); i++)
  {
    //make a new vertex with w = 1
    Eigen::Vector4d screenVertex(triangle.m_vertices[i][0], triangle.m_vertices[i][1], triangle.m_vertices[i][2], 1);
    
    //Multiply by projection matrix
    screenVertex = cam.M * screenVertex;
    triangle.m_screenVertices.push_back(screenVertex);

    //Make a new color
    Eigen::Vector3d color;
    //If our triangle doesn't have vertex normals
    if(triangle.m_normals.empty())
    { 
      color = shade(lights, triangle.m_vertices[i], triangle.m_normal, cam.m_from, triangle.m_color, triangle.m_kd, triangle.m_ks, triangle.m_e);
    }
    else
    {
      color = shade(lights, triangle.m_vertices[i], triangle.m_normals[i], cam.m_from, triangle.m_color, triangle.m_kd, triangle.m_ks, triangle.m_e);
    }
    triangle.m_colors.push_back(color);
  }
}

//COULDN'T GET CLIPPING TO WORK
//COULDN'T GET CLIPPING TO WORK
//COULDN'T GET CLIPPING TO WORK
//COULDN'T GET CLIPPING TO WORK
void Clip(Camera cam, Polygon &triangle)
{
  Eigen::Vector3d ntopLeft, ntopRight, nbottomLeft, nbottomRight, ftopLeft, ftopRight, fbottomLeft, fbottomRight;
  ntopLeft << cam.left*cam.m_u, cam.top*cam.m_v, cam.m_w;
  ntopRight << cam.right, cam.top, cam.near;
  nbottomLeft << cam.left, cam.bottom, cam.near;
  nbottomRight << cam.right, cam.bottom, cam.near;


  Eigen::Vector3d nearCenter, farCenter;
  nearCenter = cam.m_center * cam.near;
  farCenter = cam.m_center * cam.far;

  
  //Eigen::Vector3d nearNormal = cam.m_w.normalized();
  //Eigen::Vector3d farNormal = -cam.m_w.normalized();
  Eigen::Vector3d topNormal, bottomNormal, leftNormal, rightNormal;

  topNormal = (ntopLeft - cam.m_from).cross(ntopRight - cam.m_from);
  topNormal.normalize();
  bottomNormal = (nbottomLeft - cam.m_from).cross(nbottomRight - cam.m_from);
  bottomNormal.normalize();
  leftNormal = (ntopLeft - cam.m_from).cross(nbottomLeft - cam.m_from);
  leftNormal.normalize();
  rightNormal = (ntopRight - cam.m_from).cross(nbottomRight - cam.m_from);
  rightNormal.normalize();
  //nearNormal = (ntopRight - ntopLeft).cross(nbottomRight - ntopLeft);
  //nearNormal.normalize();

  vector<Eigen::Vector3d> frustumNormals;
  frustumNormals.push_back(topNormal);
  frustumNormals.push_back(bottomNormal);
  frustumNormals.push_back(leftNormal);
  frustumNormals.push_back(rightNormal);
  //frustumNormals.push_back(nearNormal);
  //frustumNormals.push_back(farNormal);

  //triangle vertices without the w
  Eigen::Vector3d x0, x1, x2;
  x0 << triangle.m_screenVertices[0][0], triangle.m_screenVertices[0][1], triangle.m_screenVertices[0][2];
  x1 << triangle.m_screenVertices[1][0], triangle.m_screenVertices[1][1], triangle.m_screenVertices[1][2];
  x2 << triangle.m_screenVertices[2][0], triangle.m_screenVertices[2][1], triangle.m_screenVertices[2][2];

  int check1, check2, check3;
  //for each normal, alpha = n.x - n.a
  for(int i = 0; i < frustumNormals.size(); i++)
  {
      //cout << "i: " << i << endl;
      
        check1 = IntersectPlane(frustumNormals[i], cam.m_from, x0, x1);
        check2 = IntersectPlane(frustumNormals[i], cam.m_from, x1, x2);
        check3 = IntersectPlane(frustumNormals[i], cam.m_from, x2, x0);
      
      //if any of our points arent in our frustum, get rid of the whole triangle
      if(check1 == false || check2 == false || check3 == false)
      {
        triangle.m_clipped = true;
      }

  }
  //if not within our near and far plane, set clipped to true
  if(cam.near - x0[2] < 0 || x0[2] - cam.far < 0)
  {
      triangle.m_clipped = true;
  }
  if(cam.near - x1[2] < 0 || x1[2] - cam.far < 0)
  {
      triangle.m_clipped = true;
  }
  if(cam.near - x2[2] < 0 || x2[2] - cam.far < 0)
  {
      triangle.m_clipped = true;
  }

}
//COULDN'T GET CLIPPING TO WORK// IGNORE THIS
//COULDN'T GET CLIPPING TO WORK// IGNORE THIS
//COULDN'T GET CLIPPING TO WORK//IGNORE THIS
bool IntersectPlane(Eigen::Vector3d normal, Eigen::Vector3d eye, Eigen::Vector3d a, Eigen::Vector3d b )
{
    //cout << "NORMAL: " << endl << normal << endl;
    double D = -(normal.dot(eye));

    //if this is > 0, then the point is inside our frustum
    double dist = normal.dot(a) + D;
    //cout << "Distance thing? " << dist << endl;
    if(dist > 0)
    {
        return true;
    }
    //STUFF NEEDED TO IMPLEMENT CLIPPING
    /*double denominator = normal.dot(b-a);
    if (denominator == 0)
    {
        return false;
    }
    double alpha = numerator/denominator;
    if(alpha <= 1 && alpha >= 0)
    {
        return true;
    }*/
    return false;
}


double fxx(double x, double y, Eigen::Vector4d one, Eigen::Vector4d two)
{
    double result = ((one[1] - two[1])* x) + ((two[0] - one[0])*y) +(one[0]*two[1]) - (two[0]*one[1]);
    return result;
}


Eigen::Vector3d shade(vector<Light> lights, Eigen::Vector3d point, Eigen::Vector3d normal, Eigen::Vector3d eye, Eigen::Vector3d color, double kd, double ks, double e)
{
    double localR = 0;
    double localG = 0;
    double localB = 0;
    double diffuse;
    double specular;
  
    double lightIntensity = 1/sqrt(lights.size());
    Eigen::Vector3d lightDir, viewDir, halfway, localColor, totalColor;

    viewDir = -(point - eye).normalized();


    for(int i = 0; i < lights.size(); i++)
    {
        //sets light color
        Eigen::Vector3d col = lights[i].m_color;
        //light direction is position of the light - starting point
        lightDir = (lights[i].m_position - point).normalized();
        halfway = (lightDir + viewDir).normalized();
    
        double dp1 = (normal).dot(lightDir);
        double dp2 = (normal).dot(halfway);
        diffuse = fmax(0, dp1 );
        specular = pow(fmax(0, dp2 ), e);
        //for each polygon in our vector, check whether our shadow ray intersects
       
        localR += (kd*color[0]* diffuse  + ks*specular)  * lightIntensity;
        localG += (kd*color[1]* diffuse  + ks*specular)  * lightIntensity;
        localB += (kd*color[2]* diffuse  + ks*specular) * lightIntensity;
            
    }
       
    //cout << "THIS COLOR IS: " << localR*255 << " " << localG*255 << " " << localB*255 << endl;
    localColor << localR, localG, localB;
  
    //cout << "COLOR OF THIS VERTEX IS" <<endl;
    //cout << "Polygon Color: " << hr.color[0] << " " << hr.color[1] <<" " << hr.color[2] << endl;
    //cout << "Final Color: " << localR <<" " << localG << " " <<localB << endl << endl;
    return localColor;
}

