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
#include <stdlib.h>      /* rand */
#include <time.h>       /* time */
#include "geometry.h"

//if you give this function a string, it will give you a vector of that string, split on whitespace
vector<string> Vectorize(string myString);

Eigen::Vector3d shade(HitRecord hr, vector<Light> lights, vector<Polygon> polygons);
Eigen::Vector3d trace(Ray ray, double t0, double t1, vector<Light> lights, vector<Polygon> polygons, Eigen::Vector3d color);
Eigen::Vector3d refract(Ray ray, HitRecord hr, vector<Polygon> polygons, Eigen::Vector3d color);

int main(int argc, char *argv[])
{
   // Command Line Options
   int c;
   int samples = 1;
   int maxRayDepth = 5;
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
            maxRayDepth = atoi(optarg);
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
    
    //seed random
    srand(time(0));

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
	      counter++;
	    }
	  //add to vector of polygons
	  polygons.push_back(*poly);
  
	  //deallocate poly memory
	  delete poly;
	  poly = NULL;

	  break;
	case 's':
	  //make new sphere
	  sphere = new Sphere(materialData[0], materialData[1], materialData[2],
			      stod(tokens[1]),  stod(tokens[2]),  stod(tokens[3]),  stod(tokens[4]));
      sphere->setMaterials(materialData[3], materialData[4], materialData[5], materialData[6], materialData[7]);
	  //put it in spheres vector
	  spheres.push_back(*sphere);
      delete sphere;	  
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

  for(int i = 0; i < resY; i++)
    {
      for(int j = 0; j < resX; j++)
	{ 
      //set our t-Range
	  double t0 = 0;
	  double t1 = INFINITY;
      //set default color
	  Eigen::Vector3d color(0,0,0) ;
	  
      //get the pixel location
	  Eigen::Vector3d pixel = cam.m_topLeft
	    + (cam.m_u * j * cam.m_pixelWidth)
	    - (cam.m_v * i * cam.m_pixelHeight);
        double h = cam.m_pixelWidth;
	  for(int m = 0; m < samples; m++)
      {
        for(int n = 0; n < samples; n++)
        {
            if(stratified)
            {
                pixel.x() = pixel.x() - (h*0.5) + m*(h/samples) + (rand() % 2) * h/samples;
                pixel.y() = pixel.y() - (h*0.5) + n*(h/samples) + (rand() % 2) * h/samples;
            }
	        //create and initialize the ray
	        Ray ray;
	        ray.SetEye(cam.m_from);
	        Eigen::Vector3d direction = (pixel - cam.m_from).normalized();
	        ray.SetDirection(direction);
            color += trace(ray, t0, t1, lights, polygons, bgColor);
        }
      }
	 
        color /= (samples*samples);
      

	  //color = trace(ray, t0, t1, lights, polygons, bgColor);
	  
        
	  //set pixel color
	  for(int m = 0; m < 3; m++)
	    {
	      double p = color[m];
	      pixels[i][j][m]= fmax(fmin(p,1),0)*255;
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

Eigen::Vector3d trace(Ray ray, double t0, double t1, vector<Light> lights, vector<Polygon> polygons, Eigen::Vector3d color)
{
  Eigen::Vector3d bgColor = color;
  HitRecord hr;
  hr.raydepth = 0;
  //angle between view direction and normal
  double c1,c2, currIOR, nextIOR, IOR;
  //make new ray for reflections
  Ray reflectionRay;
  //reflection direction
  Eigen::Vector3d r,t;

  //Refraction Ray
  Ray refractionRay;
  Eigen::Vector3d refrNormal;
  bool inside = false;
  double bias = 1e-9;
  bool hit = false;
  //if our polygon vector has items, loop through them
	  if(!polygons.empty())
	    {
	      for(int k = 0; k < polygons.size(); k++)
		{     
		  if(polygons[k].Intersect(ray, t0, t1, hr))
		    {

                t1 = hr.t;
                hr.raydepth = ray.depth;
                color = shade(hr, lights, polygons);
                hit = true;
                c1 = hr.normal.dot(hr.viewDir);

                //Setup Reflection Ray
                reflectionRay.SetEye(hr.point);
                r = -hr.viewDir + 2*(c1)*hr.normal;
                r.normalize(); 
                reflectionRay.SetDirection(r);
                //REFRACTION CODE**********************************************
                //Setup Refraction Ray
                //Attempted but was not successful
                /*currIOR =1; nextIOR = hr.it;
                
                IOR = currIOR/nextIOR;        
                c2 = sqrt(1- (IOR*IOR) * (1 -(c1*c1)));                
                refractionRay.SetEye(hr.point);
                t = (hr.normal * c1 - hr.viewDir)*(IOR) - hr.normal*(c2);
                t.normalize();
                refractionRay.SetDirection(t);*/
		    }
		}
	    }
  if (hit) {
      //cout << "HIT" << endl;
      //cout << hr.ks <<endl;
      //cout << hr.kt <<endl << endl;
    if (hr.ks> 0 && hr.raydepth < 5)
    {
        //cout << "reflectable" << endl;
        reflectionRay.depth++;
        color += hr.ks*trace(reflectionRay, t0+bias, t1, lights, polygons, bgColor);    
    }
    //REFRACTION CODE**********************************************
    /*if(hr.kt > 0 )
        {
            color += refract(refractionRay,hr,polygons, bgColor);
        }*/
  return color;
  }
	  //if our spheres vector has items loop through them
	 /* if(!spheres.empty())
	    {
	      
	      for(int l = 0; l < spheres.size(); l++)
	     {
	       
              if(spheres[l].Intersect(ray, t0, t1, hr))
                {
                  t1 = spheres[l].GetT();
                }
            }
	    }*/
  return bgColor;

}
Eigen::Vector3d shade(HitRecord hr, vector<Light> lights, vector<Polygon> polygons)
{
    double localR = 0;
    double localG = 0;
    double localB = 0;
    double diffuse;
    double specular;
    double bias = 1e-9;
    double lightIntensity = 1/sqrt(lights.size());
    Eigen::Vector3d lightDir, halfway, localColor, totalColor;


    for(int i = 0; i < lights.size(); i++)
    {
        //sets light color
        Eigen::Vector3d col = lights[i].m_color;
        //light direction is position of the light - starting point
        lightDir = (lights[i].m_position - hr.point).normalized();
        halfway = (lightDir + hr.viewDir).normalized();
        //make a shadow ray
        Ray shadowRay;
	    shadowRay.SetEye(hr.point);
	    shadowRay.SetDirection(lightDir);
        //t0 with some bias
        double t0 = bias;
        //t1 = 1 because the t at the light is 1 or something
        double t1 = (lights[i].m_position - hr.point).norm();
        bool blocked = false;
        double dp1 = (hr.normal).dot(lightDir);
        double dp2 = (hr.normal).dot(halfway);
        diffuse = fmax(0, dp1 );
        specular = pow(fmax(0, dp2 ), hr.e);
        //for each polygon in our vector, check whether our shadow ray intersects
        if(!polygons.empty())
	    {
	      for(int k = 0; k < polygons.size(); k++)
		{   
            HitRecord dummy;  
		  if(polygons[k].Intersect(shadowRay, t0, t1, dummy))
		    {
                if(dummy.t > t0 && dummy.t < t1)
                {
                    blocked = true;
                    break;
                }
		    }
		}
	    }
            //if light is nor blocked add light contribution
            if(!blocked)
            {
                localR += (hr.kd*hr.color[0]* diffuse  + hr.ks*specular)  * lightIntensity;
                localG += (hr.kd*hr.color[1]* diffuse  + hr.ks*specular)  * lightIntensity;
                localB += (hr.kd*hr.color[2]* diffuse  + hr.ks*specular) * lightIntensity;
            }
    }
       

    localColor << localR, localG, localB;
  
 
    //cout << "Polygon Color: " << hr.color[0] << " " << hr.color[1] <<" " << hr.color[2] << endl;
    //cout << "Final Color: " << localR <<" " << localG << " " <<localB << endl << endl;
    return localColor;
}

Eigen::Vector3d refract(Ray ray, HitRecord hr, vector<Polygon> polygons, Eigen::Vector3d color)
{
    Eigen::Vector3d lightDir, halfway, localColor, totalColor;
    localColor = color;   
    double t0 = 1e-9;
    double t1 = INFINITY;
    if(!polygons.empty())
	    {
	      for(int k = 0; k < polygons.size(); k++)
		{     
		  if(polygons[k].Intersect(ray, t0, t1, hr))
		    {
                
               localColor = hr.kt * hr.color;
		    }
	    }
    }
    
    return localColor;
}
