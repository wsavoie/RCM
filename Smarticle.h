#pragma once
//#include <Mathematics/GteDistSegmentSegment.h>
//#include <Mathematics/GteCapsule.h>
//#include <Mathematics/GteTIQuery.h>
#include <Mathematics/GteDistSegmentSegment.h>
#include <Mathematics/GteCapsule.h>
#include <Mathematics/GteTIQuery.h>
#include <math.h>
//#include "GlobalVars.h"


#define _USE_MATH_DEFINES

#ifndef SMARTICLE_H_
#define SMARTICLE_H_
namespace gte {



		class Smarticle
		{
		public:
			static double D;
			static double boxSize;
			static double w;// = 14 * D;//width including caps
			static double l;// = 1 * D;//length including caps
			static double L;// = l - D;//length excluding caps
			static double W;// = w - D;//length excluding caps
			double ang1;
			double ang2;
			Capsule3<double> cap0;
			Capsule3<double> cap1;
			Capsule3<double> cap2;


			Smarticle(double mang1, double mang2);
			~Smarticle();
			bool checkNotColliding(Smarticle other, Smarticle main);
			bool Smarticle::checkEndPts();




			//static Segment3<double> genSeg(double x1, double y1, double z1, double x2, double y2, double z2);
			//static Vector<3, double> rotateByAngle(double ang, Vector<3, double> point0, Vector<3, double> point1, Vector<3, double> b);
		};
		template <typename Real>

		class TIQuery<Real, Capsule3<Real>, Capsule3<Real>>
		{
		public:
			struct Result
			{
				bool intersect;
			};

			Result operator()(Capsule3<Real> const& capsule0,
				Capsule3<Real> const& capsule1);
		};
		template <typename Real>
		typename TIQuery<Real, Capsule3<Real>, Capsule3<Real>>::Result
			TIQuery<Real, Capsule3<Real>, Capsule3<Real>>::operator()(
			Capsule3<Real> const& capsule0, Capsule3<Real> const& capsule1)
		{
			Result result;
			DCPQuery<Real, Segment3<Real>, Segment3<Real>> ssQuery;
			auto ssResult = ssQuery(capsule0.segment, capsule1.segment);
			Real rSum = capsule0.radius + capsule1.radius;
			result.intersect = (ssResult.distance <= rSum);
			return result;
		}



		/*template <int N, typename Real>
		class Vector
		{
		public:
		template <int N, typename Real>
		Vector<3, double>& operator@(Vector<3, double> const& a, Vector<3, double> const& b);



		Vector<3, double>& operator@Vector<3, double> const& a, Vector<3, double> const& b)
		{
		Vector<3, double> result;
		result[0] = u[1] * v[2] - u[2] * v[1];
		result[1] = u[2] * v[0] - u[0] * v[2];
		result[2] = u[0] * v[1] - u[1] * v[0];
		return result;
		};
		};*/
		
	}

	gte::Segment3<double> genSeg(double x1, double y1, double z1, double x2, double y2, double z2);
	gte::Vector<3, double> genVec(double x, double y, double z);
	gte::Vector<3, double> crossProd(gte::Vector<3, double> u, gte::Vector<3, double> v);
	gte::Vector<3, double> rotateByAngle(double ang, gte::Vector<3, double> point0, gte::Vector<3, double> point1, gte::Vector<3, double> b);

#endif /* SMARTICLE_H_ */
