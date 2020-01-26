#include "entities.h"
#include <Eigen/Dense>

Boid::Boid(Eigen::Vector3d position, Eigen::Vector3d velocity, Properties p)
{
    pos0 = position;
    pos = pos0;
    vel0 = velocity;
    vel = vel0;
    frc << 0,0,0;
    acc << 0,0,0;
    nearestDistance << 9999, 9999,9999;
    xReversed = false;
    yReversed = false;
    zReversed = false;
    reversed = false;
    props = p;
}

void Boid::Move(Eigen::Vector3d avgVel, double currFrame)
{
    //cout << "My neighbors: " << neighbors.size() << endl;
     pos0 = pos;
     vel0 = vel;
    
    //if xReversed is true, and we are now in our x bound, set xReversed to false
    if((pos.x() < props.maxX && pos.x() > props.minX) && xReversed)
    {
        xReversed = false;
    }
    //if yReversed is true, and we are now back in our y bound, set yReversed to false
    if((pos.y() < props.maxY && pos.y() > props.minY) && yReversed)
    {
        yReversed = false;
    }
    //if zReversed is true, and we are now back in our z bound, set zReversed to false
    if((pos.z() < props.maxZ && pos.z() > props.minZ) && zReversed)
    {
     
        zReversed = false;
    }

    //--FORCES NEEDED--  
    //COLLISION FORCE
    Eigen::Vector3d cForce(0,0,0);
    Eigen::Vector3d avgPos(0,0,0);
    //Eigen::Vector3d absDist = nearestDistance.cwiseAbs();
    

    for( int i = 0; i < neighbors.size(); i++)
    {
        
            avgPos += neighbors[i].pos;

            Eigen::Vector3d dist = neighbors[i].pos - pos;
            Eigen::Vector3d absDist = dist.cwiseAbs();
            //if a neighbor is under .15 units away from us on every axis
            if(absDist.x() < 0.15 && absDist.y() < 0.15 && absDist.z() < 0.15)
            {
                //increase collision force using their distance
                cForce += -(dist/dist.dot(dist));
            }
    }
        //scale collision force to manageable levels
        cForce *= props.collision;

    //VELOCITY MATCHING
    //velocity matching force
    Eigen::Vector3d vForce = (avgVel - vel);
    vForce *= props.velocity;
   
   
    //FLOCK CENTERING? 
    if(neighbors.size() > 0)
    {
        avgPos /= neighbors.size();
    }

    Eigen::Vector3d centForce = (avgPos - pos);
    centForce*=props.centering;
   
    //force = sum of all other forces
    frc = vForce + centForce + cForce;
    

    //a = F/m
    acc = frc/props.mass;

    //find velocity
    vel = (vel0 + acc)*props.damping;

    //handle bounds checking
    if((pos.x() >= props.maxX || pos.x() <= props.minX) && !xReversed)
    {
        vel.x() *= -1;
        xReversed = true;
    }
    if((pos.y() >= props.maxY || pos.y() <= props.minY) && !yReversed)
    {
        vel.y() *= -1;
        yReversed = true;
    }
    if((pos.z() >= props.maxZ || pos.z() <= props.minZ) && !zReversed)
    {
        vel.z() *= -1;
        zReversed = true;
    }

    //find position
    pos = pos0 + vel0*0.08;
   
    
}

Food::Food(Eigen::Vector3d position, Eigen::Vector3d velocity, int time, Properties p)
{
    pos0 = pos = position;
    vel0 = vel = velocity;
    aliveTime = time;
    props = p;
}
Food::Food()
{
    //do nothing
}

void Food::Move(double currFrame)
{
  if(ceil(aliveTime/props.timeStep) >= currFrame && !isActive)
    {
      isActive = true;
    }

  //Force Needed
  //Weak gravitational force
  Eigen::Vector3d g(0, -9.81, 0);
  if(isActive)
    {
      vel = vel + g;
      pos = pos + vel*0.1;
    }
}


