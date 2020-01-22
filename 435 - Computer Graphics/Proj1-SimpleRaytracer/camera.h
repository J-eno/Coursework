//Camera.h
//Header for the class responsible for the Camera

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <Eigen/Dense>
#include <math.h>

#define PI 3.14159265

class Camera
{

 public:
  
  //default camera constructor
  Camera();

  //Camera constructor - don't think I'm going to use this now that I'm using a Switch statement in my parser
  Camera(Eigen::Vector3d from, Eigen::Vector3d at, Eigen::Vector3d up, double fov, double hither,
	 double resX, double resY);

  //Camera copy constructor (will I even need this)
  Camera(const Camera& C);

  //Destructor
  ~Camera();

  void Init(Eigen::Vector3d from, Eigen::Vector3d at, Eigen::Vector3d up, double fov, double hither,
         double resX, double resY);
  
  void SetBasisVectors();

  //derives the remaining uninitialized variables from the initialized ones
  void Derive();

  //Putting this here so that I don't have to make getters
  Eigen::Vector3d m_from;
  Eigen::Vector3d m_u;
  Eigen::Vector3d m_v;
  Eigen::Vector3d m_w;
  Eigen::Vector3d m_topLeft;
  double m_pixelWidth;
  double m_pixelHeight;

  
 private:
  Eigen::Vector3d m_at;
  Eigen::Vector3d m_up;
  double m_fov;
  double m_angle;
  double m_hither;
  double m_resX;
  double m_resY;
  double m_aspect;
  double m_width; //width of viewing plane;
  double m_height;//height of viewing plane;
  Eigen::Vector3d m_center;//center of our image plane

};


class Ray
{
 public:
  Ray();
  Ray(Eigen::Vector3d from, Eigen::Vector3d direction);

  Eigen::Vector3d GetEye();
  void SetEye(Eigen::Vector3d from);
  Eigen::Vector3d GetDirection();
  void SetDirection(Eigen::Vector3d dir);
 private:
  Eigen::Vector3d m_from;
  Eigen::Vector3d m_direction;
};

#endif
