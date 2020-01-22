//Implementation for Geometry Classes

#include "geometry.h"

Geometry::Geometry()
{
  //Empty because abstract
}

Geometry::~Geometry()
{
  //also empty because we won't manually delete these
}

void Geometry::SetColor(double r, double g, double b)
{
  m_color << r,g,b;
}

Eigen::Vector3d Geometry::GetColor()
{
  return m_color;
}

double Geometry::GetT()
{
  return m_tValue;
}

void Geometry::setMaterials(double kd, double ks, double e, double kt, double it)
{
    m_kd = kd;
    m_ks = ks;
    m_e = e;
    m_kt = kt;
    m_it = it;
}


//============================================
//Polygon Class
//============================================

Polygon::Polygon()
{
  //it's here
}
Polygon::Polygon(double r, double g, double b, double numVertices, bool Phong)
{
  m_phong = Phong;
  Init(r,g,b,numVertices);
}

void Polygon::Init(double r, double g, double b, double numVertices)
{
  SetColor(r,g,b);
  if(numVertices > 3)
    {
      m_isConcave = true;
    }
}

//reset polygon data
void Polygon::Clear()
{
  m_vertices.clear();
  m_isConcave = false;
}

//Turn polygon with more than 3 points into triangles
vector<Polygon> Polygon::Triangularize()
{
  int i = 1; 
 while(i <= m_vertices.size() - 2)
  {
   Polygon *newTri = new Polygon(m_color[0], m_color[1], m_color[2], 3, m_phong);
   newTri->setMaterials(m_kd, m_ks, m_e, m_kt, m_it);
   newTri->AddVertex(m_vertices[0]);
   newTri->AddVertex(m_vertices[i]);
   newTri->AddVertex(m_vertices[i+1]);
   if(!m_normals.empty())
    {
     newTri->AddNormal(m_normals[0]);
     newTri->AddNormal(m_normals[i]);
     newTri->AddNormal(m_normals[i+1]);
    }
   newTri->SetNormal();
   for(int i = 0; i < 3; i++)
     {
       newTri->m_normals.push_back(newTri->m_normal);
     }
   newTris.push_back(*newTri);
   i++;
  }
  return newTris;
}

void Polygon::AddVertex(Eigen::Vector3d vertex)
{
  m_vertices.push_back(vertex);
}
 void Polygon::AddScreenVertex(Eigen::Vector4d vertex)
 {
   m_screenVertices.push_back(vertex);
 }
void Polygon::AddNormal(Eigen::Vector3d normal)
{
  m_normals.push_back(normal);
}

  void Polygon::SetNormal()
  {
    Eigen::Vector3d v0 = m_vertices[0];
    Eigen::Vector3d v1 = m_vertices[1];
    Eigen::Vector3d v2 = m_vertices[2];

    //normal  = cross product of two edges
    m_normal = (v1 - v0).cross(v2 - v0);
    m_normal.normalize();
    //cout << "Normal " << m_normal << endl;
  }
  void Polygon::SetPhongNormal(double alpha, double beta, double gamma)
  {
    Eigen::Vector3d n0 = m_normals[0];
    Eigen::Vector3d n1 = m_normals[1];
    Eigen::Vector3d n2 = m_normals[2];

    m_normal = alpha*n0 + beta*n1 + gamma*n2;
    m_normal.normalize();
  }

  
double Polygon::cross2d(Eigen::Vector2d x, Eigen::Vector2d y)
{
 return x[0]*y[1]-x[1]*y[0];
}

Eigen::Vector2d Polygon::project(Eigen::Vector3d x, int projectDir) {
  switch (projectDir) {
  case 0:
    return Eigen::Vector2d(x[1],x[2]);
  case 1:
    return Eigen::Vector2d(x[0],x[2]);
  case 2:
    return Eigen::Vector2d(x[0],x[1]);
  }
  return Eigen::Vector2d(1.0, 1.0);
}

//===============================================================
// LIGHT CLASS
//===============================================================
Light::Light()
{

}
Light::Light(Eigen::Vector3d position, Eigen::Vector3d color)
{
    m_position = position;
    m_color = color;
}

//===============================================================
// SPHERE CLASS
//===============================================================
/*
Sphere:: Sphere()
{

}

Sphere::Sphere(double r, double g, double b, double x, double y, double z, double radius)
{
  Init(r,g,b,x,y,z,radius);
}

void Sphere::Init(double r, double g, double b, double x, double y, double z, double radius)
{
  SetColor(r,g,b);
  SetCenter(x,y,z);
  SetRadius(radius);
}
void Sphere::Clear()
{
}

void Sphere::SetCenter(double x, double y, double z)
{
  m_center << x, y, z;
}

Eigen::Vector3d Sphere::GetCenter()
{
  return m_center;
}
void Sphere::SetRadius(double radius)
{
  m_radius = radius;
}
double Sphere::GetRadius()
{
  return m_radius;
}


bool Sphere::Intersect(Ray ray, double tMin, double tMax, HitRecord &hr)
{
  //a(t)^2 + b(t) + c = 0
  //a = ray.directionDOTray.direction
  //b = 2ray.directionDOTray.origin - center
  //c = (origin-centerDOTorigin-center) - radius squared

  double a = 1;
  double b = (2*ray.GetDirection()).dot(ray.GetEye() - m_center);
  double c = (ray.GetEye() - m_center).dot(ray.GetEye() - m_center) - (m_radius*m_radius);

  double discriminant = b*b - 4*a*c;

  if(discriminant < 0)
    {
      return false;
    }
  double t0;
  double t1;
  
  if(discriminant == 0)
    {
      t0 = -(b/2*a);
      t1 = -(b/2*a);
    }
  else
    {
      t0 = (-b-sqrt(discriminant))/(2*a);
      t1 = (-b+sqrt(discriminant))/(2*a);
    }

  //If neither t is in our t-range (behind camera) return false
  if((t0 < tMin || t0 > tMax) && (t1 < tMin || t1 > tMax))
    {
      return false;
    }
  //If t0 is in range but t1 is out of range, use t0
  if((t0 >= tMin && t0 <= tMax) && (t1 < tMin || t1 > tMax))
    {
      m_tValue = t0;
    }
  //If t1 is in range but t0 is out of range, use t1
  if((t1 >= tMin && t1 <= tMax) && (t0 < tMin || t0 > tMax))
    {
      m_tValue = t1;
    }
  //If both, use smallest
  if((t0 >= tMin && t0 <= tMax) && (t1 >= tMin || t1 <= tMax))
    {
      m_tValue = fmin(t0,t1);
    }


  return true;
}
*/
