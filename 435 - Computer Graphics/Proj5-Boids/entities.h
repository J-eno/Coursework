#ifndef ENTITIES_H
#define ENTITIES_H
#include <iostream>
#include <vector>
#include <math.h>
#include <Eigen/Dense>
using namespace std;

class Properties
{
    public:
    double size;
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
    double minX = -0.5;
    double maxX = 0.5;
    double minY = -0.25;
    double maxY = 0.25;
    double minZ = -0.125;
    double maxZ= 0.125;
};

class Boid
{
    public:
    Boid(Eigen::Vector3d position, Eigen::Vector3d velocity, Properties p);

    void Move(Eigen::Vector3d avgVel, double currFrame);

    Eigen::Vector3d pos, vel, frc, pos0, vel0, acc; //position, velocity, force, and acceleration
    Properties props;
    vector<Boid> allBoids;
    vector<Boid> neighbors;
    Eigen::Vector3d nearestDistance;
    bool xReversed, yReversed, zReversed, reversed;
};

class Food
{
public:
  Food(Eigen::Vector3d position, Eigen::Vector3d velocity, int time, Properties p);
  Food();
  void Move(double currFrame);
  Eigen::Vector3d pos, vel, frc, pos0, vel0, acc;
  Properties props;
  bool isActive = false;
  int aliveTime; 
};


#endif
