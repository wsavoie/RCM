
#include "Smarticle.h"

using namespace gte;

Smarticle::Smarticle(double mang1, double mang2) : ang1(mang1), ang2(mang2)
{
}
double Smarticle::D = 1;
double Smarticle::boxSize = 35 * D;
double Smarticle::w = 14 * D;// = 14 * D;//width including caps
double Smarticle::l = 14 * D;// = 1 * D;//length including caps
double Smarticle::L = l - D;// = l - D;//length excluding caps
double Smarticle::W = w - D;// = w - D;//length excluding caps
Smarticle::~Smarticle()
{};
bool Smarticle::checkNotColliding(Smarticle other, Smarticle main)
{
	gte::TIQuery<double, Capsule3<double>, Capsule3<double>> result;

	//make this into a loop which checks 0->0:2, 1->0:2 2->0:2;
	if (result(other.cap0, main.cap0).intersect) return false;
	if (result(other.cap0, main.cap1).intersect) return false;
	if (result(other.cap0, main.cap2).intersect) return false;

	if (result(other.cap1, main.cap0).intersect) return false;
	if (result(other.cap1, main.cap1).intersect) return false;
	if (result(other.cap1, main.cap2).intersect) return false;

	if (result(other.cap2, main.cap0).intersect) return false;
	if (result(other.cap2, main.cap1).intersect) return false;
	if (result(other.cap2, main.cap2).intersect) return false;

	return true;
}
	bool Smarticle::checkEndPts()
	{
		double center = boxSize / 2.0;
		double x, y, z = 0;
		for (unsigned i = 0; i < 2; i++) //each loop examines if the end point of any capsules extend past the sphereical volume
		{
			//if length of vector pointing from endpoint to center of system is greater than the radius of system, the particle is outside
			x = cap0.segment.p.at(i)[0] - center;
			y = cap0.segment.p.at(i)[1] - center;
			z = cap0.segment.p.at(i)[2] - center;

			if (sqrt(x*x + y*y + z*z) > center)  //if position's r is greater than sphere radius
				return false;

			x = cap1.segment.p.at(i)[0] - center;
			y = cap1.segment.p.at(i)[1] - center;
			z = cap1.segment.p.at(i)[2] - center;

			if (sqrt(x*x + y*y + z*z) > center)  //if position's r is greater than sphere radius
				return false;

			x = cap2.segment.p.at(i)[0] - center;
			y = cap2.segment.p.at(i)[1] - center;
			z = cap2.segment.p.at(i)[2] - center;

			if (sqrt(x*x + y*y + z*z) > center)  //if position's r is greater than sphere radius
				return false;
		}
		return true;
	}

gte::Vector<3, double>  genVec(double x, double y, double z)
{
	Vector<3, double> result;
	result[0] = x;
	result[1] = y;
	result[2] = z;
	return result;
}
gte::Segment3<double>  genSeg(double x1, double y1, double z1, double x2, double y2, double z2)
{
	gte::Segment3<double> resultSeg;
	Vector<3, double> p0;
	Vector<3, double> p1;
	
	
	//create p0 and p1 vecs
	p0 =  genVec(x1, y1, z1);
	resultSeg.p.at(0) = p0;
	
	p1 =  genVec(x2, y2, z2);
	resultSeg.p.at(1) = p1;
	
	//get center
	Vector<3, double> center;
	center = (p0 + p1) / 2.0;
	
	//get unit direction
	Vector<3, double> dir;
	dir = p1 - p0;
	double len = gte::Length(dir);
	dir /= len;
	
	//get extent
	double extent = len / 2.0;
	resultSeg.SetCenteredForm(center, dir, extent);
	
	return resultSeg;
	
}
	
gte::Vector<3, double> crossProd(gte::Vector<3, double> u, Vector<3, double> v)
{
	gte::Vector<3, double> result;
	result[0] = u[1] * v[2] - u[2] * v[1];
	result[1] = u[2] * v[0] - u[0] * v[2];
	result[2] = u[0] * v[1] - u[1] * v[0];
	return result;
}
	
gte::Vector<3, double>  rotateByAngle(double ang, gte::Vector<3, double> point0, gte::Vector<3, double> point1, gte::Vector<3, double> b)
{//https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
	//v == a from wiki
	gte::Vector<3, double> result, v, k;
	v = (point1 - point0);
	k =  crossProd(v, b);
	k = k / gte::Length(k);
	//result = v*cos(ang) + crossProd(k, v)*sin(ang) + k*(Dot(k, v))*(1 - cos(ang)) + point0;
	
	result = v*cos(ang) +  crossProd(k, v)*sin(ang) + k*(Dot(k, v))*(1 - cos(ang)) + point0;
	return result;
}



