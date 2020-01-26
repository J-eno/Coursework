using namespace std;
#include <iostream>
#include <cstdio>
#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include <math.h>
#include <sstream>
#include <Eigen/Dense>
#include <getopt.h>
#include "entities.h"
#include <boost/algorithm/string.hpp>

//if you give this function a string, it will give you a vector of that string, split on whitespace
vector<string> Vectorize(string myString);
Eigen::Vector3d BuildNeighbors(Boid currBoid, vector<Boid> boids);
vector<Boid> Timestep(vector<Boid> boids, double currentFrame, string outFile);
void PrintBoids(Boid currBoid, string outFile);

int main(int argc, char *argv[])
{

  //parameters
  Properties p;
  /*double size;
  double neighborRadius;
  double numNeighbors;
  double mass;
  double collision;
  double centering;
  double velocity;
  double hunger;
  double damping;
  double timeStep;
  double simLength;
  */
  int numBoids;
  int numFood;
  vector<Boid> boids;
  vector<Food> food;

  //I/O stuff
  //Default input file
  string inFile = "sample.in";
  //Default output file
  string outFile = "sample00.out";

  switch (argc)
{
case 2:
    inFile = argv[1];
    break;
case 3:
    inFile = argv[1];
    outFile = argv[2];
    break;
default:
    cout << "Using default values." << endl;
    break;
}
  
  ifstream ifs;
  ifs.open(inFile, ios::in);
  
  string currString;
  vector<string> tokens;
  string data;
  vector<string> dataVector;
  
  bool boidsGotten = false;
  //while we can get a line from our file
  while(getline(ifs, currString))
  {
    if(currString != "")
    {
        
      //First line is a bunch of parameters
      tokens = Vectorize(currString);
      if(tokens.size() == 11) //there are 11 parameters
      {
      p.size = stod(tokens[0]);
      p.neighborRadius = stod(tokens[1]);
      p.numNeighbors = stod(tokens[2]);
      p.mass = stod(tokens[3]);
      p.collision = stod(tokens[4]);
      p.centering = stod(tokens[5]);
      p.velocity = stod(tokens[6]);
      p.hunger = stod(tokens[7]);
      p.damping = stod(tokens[8]);
      p.timeStep = stod(tokens[9]);
      p.simLength = stod(tokens[10]);
      }
      else if (tokens.size() == 1 && !boidsGotten)
      {
        numBoids = stoi(tokens[0]);
        int counter = 0;
        //get boids
        while(counter < numBoids)
        {
          //get boid's position and velocity
          getline(ifs, data);
          //separate them by space
          dataVector = Vectorize(data);
          //We want to get the position and velocity without the brackets
          dataVector[0] = dataVector[0].substr(1, dataVector[0].size() - 2);
          dataVector[1] = dataVector[1].substr(1, dataVector[1].size() - 2);
          vector<string> pos;
          vector<string> vel;
          //split strings on commas and store tokens in vector
          boost::split(pos, dataVector[0], boost::is_any_of(","));
          boost::split(vel, dataVector[1], boost::is_any_of(","));
          //turn tokens into Vector3d;
          Eigen::Vector3d position(stod(pos[0]),stod(pos[1]),stod(pos[2]));
          Eigen::Vector3d velocity(stod(vel[0]),stod(vel[1]),stod(vel[2]));
          //make a new boid
          Boid *newBoid = new Boid(position, velocity, p);
          //add it to our list of boids
          boids.push_back(*newBoid);
          delete newBoid;
          counter++;
        }
        boidsGotten = true;
      }
      else if (tokens.size() == 1 && boidsGotten)
      {
        numFood = stoi(tokens[0]);
        int counter = 0;
        //get boids
        while(counter < numFood)
        {
          //get boid's position and velocity
          getline(ifs, data);
          if(data != "")
          {
          //separate them by space
          dataVector = Vectorize(data);
          //We want to get the position and velocity without the brackets
          dataVector[0] = dataVector[0].substr(1, dataVector[0].size() - 2);
          dataVector[1] = dataVector[1].substr(1, dataVector[1].size() - 2);
          vector<string> pos;
          vector<string> vel;
          //split strings on commas and store tokens in vector
          boost::split(pos, dataVector[0], boost::is_any_of(","));
          boost::split(vel, dataVector[1], boost::is_any_of(","));
          //turn tokens into Vector3d;
          Eigen::Vector3d position(stod(pos[0]),stod(pos[1]),stod(pos[2]));
          Eigen::Vector3d velocity(stod(vel[0]),stod(vel[1]),stod(vel[2]));
          //make a new boid
          Food *newFood = new Food(position, velocity, stoi(dataVector[2]), p);
          //add it to our list of boids
          food.push_back(*newFood);
          delete newFood;
          counter++;
          }
        }
        
      }
      
    }
  }
  //PARSING DONE AT THIS POINT

  //get total number of frames
  int numFrames = ceil(p.simLength/p.timeStep);
  //int numFrames = 100;
  
  //Open output stream, print the number of frames, close output stream
  ofstream ofs;
  ofs.open(outFile);
  ofs << numFrames << endl;
  ofs.close();

  //iterate over each frame
  for(double i = 0; i < numFrames; i++)
    {
      
      boids = Timestep(boids, i, outFile);
      //Unused food code
      int foodCount = 0;
      Food currFood;
      for(int f = 0; f < food.size(); f++)
	{
	  if(food[f].isActive)
	    {
	      foodCount++;
	      currFood = food[f];
	    }
	}
    //Open output stream in append mode, print the number of food, close output stream
      ofs.open(outFile, ios::app);
      ofs << 0 << endl;
      ofs.close();
      
    }
  return 0;
}

//Vectorize Function
//Converts string into vector, splitting on whitespace
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

//
vector<Boid> Timestep(vector<Boid> boids, double currentFrame, string outFile)
{
  //Open output stream in append mode, print the number of boids, close output stream
  ofstream ofs;
  ofs.open(outFile, ios::app);
  ofs << boids.size() << endl;
  ofs.close();
  //for each boid
  for(int i = 0; i < boids.size(); i++)
  {
    Boid currBoid = boids[i];
    //print boids current position and velocity
    PrintBoids(currBoid, outFile);
    
    //make each boid rebuild their neighbors
    Eigen::Vector3d avgVel(0,0,0);
    double x, y, z;
    for(int j = 0; j < boids.size(); j++)
    {
        if (boids[j].pos != currBoid.pos)
        {
          if(currBoid.neighbors.size() < currBoid.props.numNeighbors)
          {
            //calculate if other boids are in this boids sphere
            //FORMULA: (x - cx)^2 + (y - cy)^2 + (z - cz)^2 <= r^2
            x = pow((boids[j].pos.x() - currBoid.pos.x()),2);
            y = pow((boids[j].pos.y() - currBoid.pos.y()),2);
            z = pow((boids[j].pos.z() - currBoid.pos.z()),2); 
            //currBoid.neighbors.push_back(boids[j]);
            if( (x + y + z) <= (currBoid.props.neighborRadius*currBoid.props.neighborRadius))
            {
                currBoid.neighbors.push_back(boids[j]);
                avgVel += boids[j].vel;
            }
            
          }
        }
    }
    if( currBoid.neighbors.size() > 0)
    { 
      avgVel /= currBoid.neighbors.size();
    }

    //Move boid
    currBoid.Move(avgVel, currentFrame);
    //empty neighbors list
    currBoid.neighbors.clear();
    //update boids list
    boids[i] = currBoid;

  }
  return boids;
}

//Function to Print Boids
void PrintBoids(Boid currBoid, string outFile)
{
  ofstream ofs;
  ofs.open(outFile, ios::app);
  ofs << "[" << currBoid.pos.x() << "," << currBoid.pos.y() << "," << currBoid.pos.z() << "] "
      << "[" << currBoid.vel.x() << "," << currBoid.vel.y() << "," << currBoid.vel.z() << "]" << endl;
  ofs.close();
}
