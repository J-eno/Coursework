//contains functions for the Camera class

#include "camera.h"

Camera::Camera()
{
  //nun really going on
}

Camera::Camera(Eigen::Vector3d from, Eigen::Vector3d at, Eigen::Vector3d up, double fov, double hither,
         double resX, double resY)
{
  //Calling Init in the constructor although I don't think that I'll be this
  Init(from, at, up, fov, hither, resX, resY);
}

Camera::~Camera()
{
  //It's empty
}

void Camera::Init(Eigen::Vector3d from, Eigen::Vector3d at, Eigen::Vector3d up, double fov, double hither,
         double resX, double resY)
{
 m_from = from;
  m_at = at;
  m_up = up;
  m_fov = fov;
  m_hither = hither;
  m_resX = resX;
  m_resY = resY;

  SetBasisVectors();
  Derive();
}

void Camera::SetBasisVectors()
{
  //calculate u, v, w
  m_w = (m_from - m_at).normalized();
  m_u = (m_up.cross(m_w)).normalized();
  m_v = m_w.cross(m_u);
}

void Camera::Derive()
{
  //derive other helpful info
  //converts degrees to radians
  m_aspect = m_resX/m_resY;
  m_angle = m_fov *(PI/180);
  m_width = 2 * tan(m_angle/2);
  m_height = m_width/m_aspect;
  m_center = m_from - m_w;
  m_topLeft =(m_center - m_u * m_width/2 + m_v * m_height/2);
  m_pixelWidth = m_width/m_resX;
  m_pixelHeight = m_height/m_resY;
}





Ray::Ray()
{
  //eh
}

Ray::Ray(Eigen::Vector3d from, Eigen::Vector3d direction)
{
  SetEye(from);
  SetDirection(direction);
}

void Ray::SetEye(Eigen::Vector3d from)
{
  m_from = from;
}

Eigen::Vector3d Ray::GetEye()
{
  return m_from;
}

void Ray::SetDirection(Eigen::Vector3d dir)
{
  m_direction = dir;
}


Eigen::Vector3d Ray::GetDirection()
{
  return m_direction;
}
