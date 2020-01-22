//Geometry.h
//Header for the class responsible for all Geometry

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include <Eigen/Dense>
#include <math.h>
#include <vector>
#include <iostream>
#include "camera.h"

#define PI 3.14159265

using namespace std;

class Geometry
{

 public:
  
  //default Geometry constructor
  Geometry();

  //Geometry copy constructor (will I even need this)
  // Geometry(const Geometry& C);

  //Destructor
  ~Geometry();

  void SetColor(double r, double g, double b);
  Eigen::Vector3d GetColor();
  double GetT();

  virtual bool Intersect(Ray ray, double tMin, double tMax) = 0;

protected:
  double m_tValue = INFINITY;
  double m_alpha;
  double m_beta;
  double m_gamma;
  Eigen::Vector3d m_normal;
  Eigen::Vector3d m_color;
};

class Polygon : public Geometry
{
public:
  Polygon();

  Polygon(double r, double g, double b, double numVertices);

  void Init( double r, double g, double b, double numVertices);
  void Clear();

  
  
  void AddVertex(Eigen::Vector3d vertex);

  bool Intersect(Ray ray, double tMin, double tMax);

  bool IntersectConvex(Ray ray, double tMin, double tMax);

  bool IntersectConcave(Ray ray, double tMin, double tMax);

  double cross2d(Eigen::Vector2d x, Eigen::Vector2d y);

  Eigen::Vector2d project(Eigen::Vector3d x, int projectDir);

private:
  vector<Eigen::Vector3d> m_vertices;
  bool m_isConcave;
};

class Sphere : public Geometry
{
public:
  Sphere();

  Sphere(double r, double g, double b, double x, double y, double z, double radius);

  void Init(double r, double g, double b, double x, double y, double z, double radius);
  void Clear();

  void SetCenter(double x, double y, double z);
  Eigen::Vector3d GetCenter();
  void SetRadius(double radius);
  double GetRadius();

  bool Intersect(Ray ray, double tMin, double tMax);

private:
  Eigen::Vector3d m_center;
  double m_radius;
};


#endif
