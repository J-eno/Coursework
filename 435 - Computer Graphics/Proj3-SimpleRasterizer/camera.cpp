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
  BuildFrustum();
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
  m_aspect = m_resX/m_resY;
  m_angle = m_fov *(PI/180);//converts degrees to radians which is useful for trig
  m_width = 2 * tan(m_angle/2);
  m_height = m_width/m_aspect;
  m_center = m_from - m_w;
  m_topLeft =(m_center - m_u * m_width/2 + m_v * m_height/2);
  m_pixelWidth = m_width/m_resX;
  m_pixelHeight = m_height/m_resY;
}

void Camera::BuildFrustum()
{
  near = -m_hither;
  far = 1000*near;
  left = -m_width/2;
  right = -left;
  top = m_height/2;
  bottom = -top;
  //matrices
  M_vp << m_resX*0.5, 0, 0, m_resX*0.5,
          0, m_resY*0.5, 0, m_resY*0.5,
          0, 0, 1, 0,
          0, 0, 0, 1;
  
  M_per << (2*near)/(right-left), 0, (left+right)/(left-right), 0,
            0, (2*near)/(top-bottom), (bottom+top)/(bottom-top), 0,
            0, 0, (near+far)/(near-far), (2*far*near)/(far-near),
            0, 0, 1, 0;
  
  Eigen::Matrix4d cam1, cam2;

  cam1 << m_u[0], m_u[1], m_u[2], 0,
          m_v[0], m_v[1], m_v[2], 0,
          m_w[0], m_w[1], m_w[2], 0,
          0, 0, 0, 1;

  cam2 << 1, 0, 0, -m_from[0],
          0, 1, 0, -m_from[1],
          0, 0, 1, -m_from[2],
          0, 0, 0, 1;

  M_cam = cam1*cam2;
  
  M = M_vp*M_per*M_cam;
 
}
