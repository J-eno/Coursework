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
  void setMaterials(double kd, double ks, double e, double kt, double it);

  double m_tValue = INFINITY;
  double m_alpha;
  double m_beta;
  double m_gamma;
  Eigen::Vector3d m_normal, m_color;
  double m_kd;//Diffuse coefficient
  double m_ks;//Specular coefficient
  double m_e;//Specular exponent
  double m_kt;//Refraction coefficient
  double m_it;//Index of refraction
};

class Polygon : public Geometry
{
public:
  Polygon();

  Polygon(double r, double g, double b, double numVertices, bool phong);

  void Init( double r, double g, double b, double numVertices);
  void Clear();
  vector<Polygon> Triangularize();
  void AddVertex(Eigen::Vector3d vertex);
  void AddScreenVertex(Eigen::Vector4d vertex);
  void AddNormal(Eigen::Vector3d normal);

  void SetPhongNormal(double alpha, double beta, double gamma);
  void SetNormal();

  double cross2d(Eigen::Vector2d x, Eigen::Vector2d y);

  Eigen::Vector2d project(Eigen::Vector3d x, int projectDir);
  vector<Polygon> newTris;
  vector<Eigen::Vector3d> m_vertices, m_normals, m_colors;
  vector<Eigen::Vector4d> m_screenVertices;
  bool m_isConcave = false;
  bool m_clipped = false;
  bool m_phong = false;

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

private:
  Eigen::Vector3d m_center;
  double m_radius;
};


class Light
{
public:
  Light();
  Light(Eigen::Vector3d position, Eigen::Vector3d color);
  Eigen::Vector3d m_position;
  Eigen::Vector3d m_color;
};

#endif
