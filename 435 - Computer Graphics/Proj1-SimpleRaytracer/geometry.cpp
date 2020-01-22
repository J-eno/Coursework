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


//============================================
//Polygon Class
//============================================

Polygon::Polygon()
{
  //it's here
}
Polygon::Polygon(double r, double g, double b, double numVertices)
{
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

/*Eigen::Vector3d Polygon::GetColor()
{
  return m_color;
}

double Polygon::GetT()
{
  return m_tValue;
  }*/



void Polygon::AddVertex(Eigen::Vector3d vertex)
{
  m_vertices.push_back(vertex);
}

bool Polygon::Intersect(Ray ray, double tMin, double tMax)
{

  if(m_isConcave)
    {
      return IntersectConcave(ray, tMin, tMax);
    }
  else
    {
      return IntersectConvex(ray, tMin, tMax);
    }
}

bool Polygon::IntersectConvex(Ray ray, double tMin, double tMax)
{
 
  //Vertices and edges
  Eigen::Vector3d v0 = m_vertices[0];
  Eigen::Vector3d v1 = m_vertices[1];
  Eigen::Vector3d v2 = m_vertices[2];
  
  Eigen::Vector3d e0 = v1 - v0;
  Eigen::Vector3d e1 = v2 - v1;
  Eigen::Vector3d e2 = v0 - v2;
  
  //Compute triangle normal
  //normal  = cross product of two edges
  m_normal = (v1 - v0).cross(v2 - v0);
  m_normal.normalize();
  
  //Compute distance from Eye to triangle
  //tDistance = dot product of normal and a vertex (don't really understand this part)
  //(from what I can understand, it will return the amount of the vertex that lies in the z axis?
  //Which equates to the distance from the eye to the point?
  double tDistance = m_normal.dot(v0);
  
  //check if our viewing ray is perpendicular to the triangle normal
  if(m_normal.dot(ray.GetDirection()) == 0)
    {
      return false;
    }
  
  //Find Barycentric coordinates
  //Using matrix equation Ax = b
  Eigen::Matrix3d A;
  Eigen::Vector3d b;
  A << ray.GetDirection(), v0-v1, v0-v2;
  b << v0-ray.GetEye();
  //solve for x
  Eigen::Vector3d x = A.colPivHouseholderQr().solve(b);

  //t = x[0] , beta = x[1] , gamma = x[2]
  m_tValue = x[0];
  m_beta = x[1];
  m_gamma = x[2];
  m_alpha = 1 - m_beta - m_gamma;

  //check if t is not between tMin and tMax
  if(m_tValue < tMin || m_tValue > tMax)
    {
      return false;
    }
  if(m_beta < 0 || m_beta > 1)
    {
      return false;
    }
  if(m_gamma < 0 || m_gamma > 1-m_beta)
    {
      return false;
    }
  return true;
    
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


bool Polygon::IntersectConcave(Ray ray, double tMin, double tMax)
{
  Eigen::Vector3d v0 = m_vertices[0];
  Eigen::Vector3d v1 = m_vertices[1];
  Eigen::Vector3d v2 = m_vertices[2];
  
  //compute normal
  //normal  = cross product of two edges
  m_normal = (v1-v0).cross(v2-v0);
  m_normal.normalize();
  //Compute distance from Eye to polygon
  //tDistance = dot product of normal and a vertex (don't really understand this part)
  double tDistance = m_normal.dot(v0);

  //check if our viewing ray is perpendicular to the triangle normal
  if(m_normal.dot(ray.GetDirection()) == 0)
    {
      return false;
    }

  //Compute t for P(t) = eye + t(d)
  //t = - dot product of the normal and the eye + the distance from the Eye/ normal dot direction
  m_tValue = (tDistance - m_normal.dot(ray.GetEye()))/(m_normal.dot(ray.GetDirection()));

  //check if t is not between tMin and tMax
  if(m_tValue <= tMin || m_tValue >= tMax)
    {
      return false;
    }


    //Compute intersection point e.g. P(t) = eye + t(d) with our t
  Eigen::Vector3d point = ray.GetEye() + m_tValue*(ray.GetDirection());
  
  //convert to 2d
  int projectDir;
  if (fabs(m_normal[0]) > fabs(m_normal[1])
      && fabs(m_normal[0]) > fabs(m_normal[2]))
    {
      projectDir = 0;
    }
  else if (fabs(m_normal[1]) > fabs(m_normal[2]))
    {
      projectDir = 1;
    }
  else
    {
      projectDir = 2;
    }

  Eigen::Vector2d point2d = project(point, projectDir);
  double alpha2d, t2d;
  Eigen::Vector2d direction2d(1,0);

  //idk what this part does I'm assuming it's an optimization of some sort
  Eigen::Vector2d bbMin = project(m_vertices[0], projectDir);
  Eigen::Vector2d bbMax = bbMin;
  for (unsigned int i=1; i<m_vertices.size(); i++) {
      Eigen::Vector2d v = project(m_vertices[i], projectDir);
      if (v[0] < bbMin[0]) bbMin[0] = v[0];
      if (v[0] > bbMax[0]) bbMax[0] = v[0];
      if (v[1] < bbMin[1]) bbMin[1] = v[1];
      if (v[1] > bbMax[1]) bbMax[1] = v[1];
  }
  
  if (point2d[0] < bbMin[0]) return false;
  if (point2d[1] < bbMin[1]) return false;
  if (point2d[0] > bbMax[0]) return false;
  if (point2d[1] > bbMax[1]) return false;
  

  //linear equations -> Ax = b
  Eigen::Matrix2d A;
  Eigen::Vector2d x,b;

  
  Eigen::Vector2d p1;//first point on line segment
  Eigen::Vector2d p2;//second point on line segment
  
  int intersections=0;

  for(int i = 0; i < m_vertices.size(); i++)
    {
      p1 = project(m_vertices[i], projectDir);
      p2 = project(m_vertices[(i+1) % m_vertices.size()], projectDir);
      Eigen::Vector2d edge = p2 - p1;
      // A << direction2d, p2 - p1;
      //b << p1-point2d;
      //x = A.colPivHouseholderQr().solve(b);
      alpha2d = cross2d(p1 - point2d, direction2d/cross2d(direction2d, edge));
      t2d =  cross2d(p1 - point2d, edge/cross2d(direction2d, edge));

      if((alpha2d > 0 && alpha2d < 1) && t2d > 0)
	{
	  intersections++;
	}
    }
  if(intersections % 2 == 0)
    {return false;}
  
  return true;
}


//===============================================================
// SPHERE CLASS
//===============================================================
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



bool Sphere::Intersect(Ray ray, double tMin, double tMax)
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

