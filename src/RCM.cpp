// RCM.cpp : Defines the entry point for the console application.
//



#include <math.h>
#include <iostream>
#include <string>
#include <random>
#include "Smarticle.h"
#include <fstream>

using namespace std;
using namespace gte;

//using namespace smart;
void openRead(std::ofstream& stream, std::string fileN, unsigned int idx = 1);

void openRead(std::ofstream& stream, std::string fileN, unsigned int idx)
{
	if (idx == 0) {
		stream.open(fileN);
	}
	else {
		stream.open(fileN, std::ios::app);
	}

}


int main(int argc, char* argv[])
{
	double ang1 = 1, ang2 = 1, box = 1, lw = 1;
	bool writeOut = true;
	unsigned int its = 1e6;
	if (argc < 5)
	{
		ang1 = 90;
		ang2 = 90;
		lw = 1;
		Smarticle::L = Smarticle::W*lw;
		Smarticle::l = Smarticle::L + Smarticle::D;
	}
	else
	{
		ang1 = atof(argv[1]);
		ang2 = atof(argv[2]);
		lw = atof(argv[3]);
		box = atof(argv[4]);
		its= atoi(argv[5]);
		writeOut = (atoi(argv[6]) != 0);

		Smarticle::w = 14 * Smarticle::D;
		Smarticle::W = Smarticle::w - Smarticle::D;
		Smarticle::L = Smarticle::W*lw;
		Smarticle::l = Smarticle::L + Smarticle::D;
		Smarticle::boxSize = box*Smarticle::D;
	}

	//to properly map to system i've already begun using
	ang1 = ang1*GTE_C_PI / 180.0 - GTE_C_PI / 2;
	ang2 = -1 * ang2*GTE_C_PI / 180.0 + GTE_C_PI / 2;

	ofstream firstFile;
	ofstream secondFile;
	ofstream intersects;
	ofstream simResults;
	if (writeOut)
	{
		firstFile.open("mainStaple.txt");
		secondFile.open("secondStaple.txt");
		intersects.open("intersects.txt");
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);
	std::uniform_real_distribution<> dis2(-1, 1);
	std::uniform_real_distribution<> dis3(-0.5,0.5);
	std::uniform_real_distribution<> rLoc(Smarticle::D/2, Smarticle::boxSize - Smarticle::D / 2); //D/2 is closeset staple can be, parallel with side of box

	/////////////////////////////////////////
	//Generate Central Staple
	gte::Capsule3<double> cap0, cap1, cap2;
	cap0.radius = Smarticle::D / 2.0;
	cap1.radius = Smarticle::D / 2.0;
	cap2.radius = Smarticle::D / 2.0;
	Vector<3, double> pmain0;
	Vector<3, double> pmain1;
	Vector<3, double> temp;
	Vector<3, double> cap1vec, cap0Rot, cap2Rot;
	double x2, y2, z2 = 0;
	double x1, y1, z1, u, fx, fy, fz;
	double rx, ry, rz;
	//pmain0 first end point of cylinder pmain1 second end point of cyl
						/////////////////////////Capsule 1, central piece
						////////////pmain0[0] = -Smarticle::W / 2 + Smarticle::boxSize / 2.0;
						////////////pmain0[1] = -Smarticle::L / 2 + Smarticle::boxSize / 2.0;
						////////////pmain0[2] = 0 + Smarticle::boxSize / 2.0;

						////////////pmain1[0] = Smarticle::W / 2 + Smarticle::boxSize / 2.0;
						////////////pmain1[1] = -Smarticle::L / 2 + Smarticle::boxSize / 2.0;
						////////////pmain1[2] = 0 + Smarticle::boxSize / 2.0;
						////////////temp = pmain1;
						////////////gte::Segment3<double> cap1seg =  genSeg(pmain0[0], pmain0[1], pmain0[2], pmain1[0], pmain1[1], pmain1[2]);
						////////////cap1vec = (pmain1 - pmain0);


						/////////////////////////Capsule 0, p0 = p0 from seg 1
						////////////pmain1[0] = -Smarticle::W / 2 + Smarticle::boxSize / 2.0;
						////////////pmain1[1] = Smarticle::L / 2 + Smarticle::boxSize / 2.0;
						////////////pmain1[2] = 0 + Smarticle::boxSize / 2.0;
						////////////cap0Rot =  rotateByAngle(ang1, pmain0, pmain1, cap1vec);
						////////////gte::Segment3<double> cap0seg =  genSeg(pmain0[0], pmain0[1], pmain0[2], cap0Rot[0], cap0Rot[1], cap0Rot[2]);


						/////////////////////////Capsule 2, p0 = p1 from seg 1
						////////////pmain0 = temp;
						////////////pmain1[0] = Smarticle::W / 2 + Smarticle::boxSize / 2.0;
						////////////pmain1[1] = Smarticle::L / 2 + Smarticle::boxSize / 2.0;
						////////////pmain1[2] = 0 + Smarticle::boxSize / 2.0;
						////////////cap2Rot =  rotateByAngle(ang2, pmain0, pmain1, cap1vec);
						////////////gte::Segment3<double> cap2seg =  genSeg(pmain0[0], pmain0[1], pmain0[2], cap2Rot[0], cap2Rot[1], cap2Rot[2]);

						//////////////construct smarticle
						////////////cap0.segment = cap0seg;
						////////////cap1.segment = cap1seg;
						////////////cap2.segment = cap2seg;
						////////////Smarticle mainSmart(ang1, ang2);
						////////////mainSmart.cap0 = cap0;
						////////////mainSmart.cap1 = cap1;
						////////////mainSmart.cap2 = cap2;

	///////////////////////////////////////// 

	//if (firstFile.is_open())
	//{

	//	firstFile.close();
	//}


	/////////////////////////////////////////

	int completed = 0;
	int NN = 0;
	//	int N = 0;
	//unsigned int	its = 0.5e6;
	bool mainNotInside = false; //this will be a flag denoting if center particle was generated inside the sphere
	int count = 0;
	int exitNum = 1e3;
 	/////////////
	/*openRead(intersects, "intersects.txt", 1);
	openRead(secondFile, "secondStaple.txt", 1);*/
	//////////////

	for (size_t i = 0; i < its; i++)
	{
		mainNotInside = true;
		count = 0;
		Smarticle mainSmart(ang1, ang2);
		while (mainNotInside)
		{

			//generate other smarticle
			gte::Capsule3<double> cap0;
			gte::Capsule3<double> cap1;
			gte::Capsule3<double> cap2;
			cap0.radius = Smarticle::D / 2.0;
			cap1.radius = Smarticle::D / 2.0;
			cap2.radius = Smarticle::D / 2.0;

			double x1, y1, z1, u, fx, fy, fz;
			double rx, ry, rz;

			//x1 = rLoc(gen);
			//y1 = rLoc(gen);
			//z1 = rLoc(gen);
			//double sqrtV1 = sqrt(x1*x1 + y1*y1 + z1*z1);
			//x1 = (Smarticle::boxSize - Smarticle::D / 2)*x1 / sqrtV1;
			//y1 = (Smarticle::boxSize - Smarticle::D / 2)*y1 / sqrtV1;
			//z1 = (Smarticle::boxSize - Smarticle::D / 2)*z1 / sqrtV1;

			//////////////////////////////////////////////////////////////
			//http://math.stackexchange.com/questions/87230/picking-random-points-in-the-volume-of-sphere-with-uniform-probability
			//define initial point of center segment
			x1 = dis2(gen);
			y1 = dis2(gen);
			z1 = dis2(gen);

			double sqrtV1 = sqrt(x1*x1 + y1*y1 + z1*z1);
			u = std::pow(dis(gen), 1.0 / 3.0);
			fx = (Smarticle::boxSize / 2.0 - Smarticle::D / 2.0)*u*x1 / sqrtV1;
			fy = (Smarticle::boxSize / 2.0 - Smarticle::D / 2.0)*u*y1 / sqrtV1;
			fz = (Smarticle::boxSize / 2.0 - Smarticle::D / 2.0)*u*z1 / sqrtV1;




			////now make a position W/2 away to determine outer points //http://mathworld.wolfram.com/SpherePointPicking.html
			rx = (dis2(gen));
			ry = (dis2(gen));
			rz = (dis2(gen));
			double sqrtVal = sqrt(rx*rx + ry*ry + rz*rz);
			pmain0[0] = (rx*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0 + fx;
			pmain0[1] = (ry*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0 + fy;
			pmain0[2] = (rz*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0 + fz;

			pmain1[0] = -(rx*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0 + fx;
			pmain1[1] = -(ry*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0 + fy;
			pmain1[2] = -(rz*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0 + fz;



			gte::Segment3<double> ocap1seg = genSeg(pmain0[0], pmain0[1], pmain0[2], pmain1[0], pmain1[1], pmain1[2]);
			cap1.segment = ocap1seg;
			Vector<3, double> cmain1, pmain01, pmain21, k, vfinal;
			//vector for segment 1 (middle)
			cmain1 = pmain1 - pmain0;
			//now generate cap0. center vec = p0top1 = p1-p0
			temp = GetOrthogonal(pmain1 - pmain0, true);
			//p0 = p0, p1 = L*temp
			x2 = (Smarticle::L*temp[0] + pmain1[0]);
			y2 = (Smarticle::L*temp[1] + pmain1[1]);
			z2 = (Smarticle::L*temp[2] + pmain1[2]);


			pmain01[0] = Smarticle::L*temp[0] + pmain0[0];
			pmain01[1] = Smarticle::L*temp[1] + pmain0[1];
			pmain01[2] = Smarticle::L*temp[2] + pmain0[2];

			cap0Rot = rotateByAngle(ang1, pmain0, pmain01, cmain1);

			gte::Segment3<double> cap0seg = genSeg(pmain0[0], pmain0[1], pmain0[2],
				cap0Rot[0],
				cap0Rot[1],
				cap0Rot[2]);


			pmain21[0] = x2;
			pmain21[1] = y2;
			pmain21[2] = z2;
			cap2Rot = rotateByAngle(ang2, pmain1, pmain21, cmain1);
			gte::Segment3<double> cap2seg = genSeg(pmain1[0], pmain1[1], pmain1[2],
				cap2Rot[0],
				cap2Rot[1],
				cap2Rot[2]);

			cap0.segment = cap0seg;
			cap2.segment = cap2seg;
			
			mainSmart.cap0 = cap0;
			mainSmart.cap1 = cap1;
			mainSmart.cap2 = cap2;
			mainSmart.cap0.radius = Smarticle::D / 2;

			if (mainSmart.checkEndPts())
			{
				mainNotInside = false;
			}


			count++;
			if (count >= exitNum)
			{		

				cout << "No location found for main particle inside sphere after " << exitNum << " steps \n";
				cout << "\nExiting program now.";
				exit(EXIT_FAILURE);
			}

		}

		//generate other smarticle
		gte::Capsule3<double> ocap0;
		gte::Capsule3<double> ocap1;
		gte::Capsule3<double> ocap2;
		ocap0.radius = Smarticle::D / 2.0;
		ocap1.radius = Smarticle::D / 2.0;
		ocap2.radius = Smarticle::D / 2.0;

		double x1, y1, z1, u,fx,fy,fz;
		double rx, ry, rz;

		//x1 = rLoc(gen);
		//y1 = rLoc(gen);
		//z1 = rLoc(gen);
		//double sqrtV1 = sqrt(x1*x1 + y1*y1 + z1*z1);
		//x1 = (Smarticle::boxSize - Smarticle::D / 2)*x1 / sqrtV1;
		//y1 = (Smarticle::boxSize - Smarticle::D / 2)*y1 / sqrtV1;
		//z1 = (Smarticle::boxSize - Smarticle::D / 2)*z1 / sqrtV1;

		//////////////////////////////////////////////////////////////
		//http://math.stackexchange.com/questions/87230/picking-random-points-in-the-volume-of-sphere-with-uniform-probability
		//define initial point of center segment
		x1 = dis2(gen);
		y1 = dis2(gen);
		z1 = dis2(gen);
	
		double sqrtV1 = sqrt(x1*x1 + y1*y1 + z1*z1);
		u = std::pow(dis(gen), 1.0 / 3.0);
		fx = (Smarticle::boxSize / 2.0 - Smarticle::D / 2.0)*u*x1 / sqrtV1;
		fy = (Smarticle::boxSize / 2.0 - Smarticle::D / 2.0)*u*y1 / sqrtV1;
		fz = (Smarticle::boxSize / 2.0 - Smarticle::D / 2.0)*u*z1 / sqrtV1;
		



		////now make a position W/2 away to determine outer points //http://mathworld.wolfram.com/SpherePointPicking.html
		rx = (dis2(gen));
		ry = (dis2(gen));
		rz = (dis2(gen));

		Vector<3, double> p0, p1, temp;
		double sqrtVal = sqrt(rx*rx + ry*ry + rz*rz);
		p0[0] = (rx*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0+fx;
		p0[1] = (ry*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0+fy;
		p0[2] = (rz*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0+fz;

		p1[0] = -(rx*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0+fx;
		p1[1] = -(ry*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0+fy;
		p1[2] = -(rz*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0+fz;



		gte::Segment3<double> ocap1seg =  genSeg(p0[0], p0[1], p0[2], p1[0], p1[1], p1[2]);
		ocap1.segment = ocap1seg;
		Vector<3, double> c1, p01, p21, k, vfinal;
		//vector for segment 1 (middle)
		c1 = p1 - p0;
		//now generate cap0. center vec = p0top1 = p1-p0
		temp = GetOrthogonal(p1 - p0, true);
		//p0 = p0, p1 = L*temp
		x2 = (Smarticle::L*temp[0] + p1[0]);
		y2 = (Smarticle::L*temp[1] + p1[1]);
		z2 = (Smarticle::L*temp[2] + p1[2]);


		p01[0] = Smarticle::L*temp[0] + p0[0];
		p01[1] = Smarticle::L*temp[1] + p0[1];
		p01[2] = Smarticle::L*temp[2] + p0[2];

		cap0Rot = rotateByAngle(ang1, p0, p01, c1);

		gte::Segment3<double> ocap0seg =  genSeg(p0[0], p0[1], p0[2],
			cap0Rot[0],
			cap0Rot[1],
			cap0Rot[2]);


		p21[0] = x2;
		p21[1] = y2;
		p21[2] = z2;
		cap2Rot =  rotateByAngle(ang2, p1, p21, c1);
		gte::Segment3<double> ocap2seg =  genSeg(p1[0], p1[1], p1[2],
			cap2Rot[0],
			cap2Rot[1],
			cap2Rot[2]);

		ocap0.segment = ocap0seg;
		ocap2.segment = ocap2seg;
		//Smarticle smartOther(90.0, 90.0);
		Smarticle smartOther(ang1, ang2);
		smartOther.cap0 = ocap0;
		smartOther.cap1 = ocap1;
		smartOther.cap2 = ocap2;
		smartOther.cap0.radius = Smarticle::D / 2;

		/*	if (smartOther.checkEndPts())
		{
		completed++;
		}
		else{
		continue;
		}

		if (mainSmart.checkNotColliding(smartOther,mainSmart))
		{
		NN++;
		}*/

		//open intersects file
		//openRead(intersects, "intersects.txt", 1);
		//openRead(secondFile, "secondStaple.txt", 1);
		if (smartOther.checkEndPts())
		{
			//if endpoints are inside system boundaries, consider it a completed test
			completed++;

			//if smarticle does not collide with other smarticle increment successful test counter NN
			if (mainSmart.checkNotColliding(smartOther, mainSmart))
			{
				NN++;
			}
		}
		else{
			continue;
		}
		if (writeOut)
		{
			firstFile << mainSmart.cap0.segment.p[1][0] << " " << mainSmart.cap0.segment.p[1][1] << " " << mainSmart.cap0.segment.p[1][2] << "\n";
			firstFile << mainSmart.cap0.segment.p[0][0] << " " << mainSmart.cap0.segment.p[0][1] << " " << mainSmart.cap0.segment.p[0][2] << "\n";

			firstFile << mainSmart.cap1.segment.p[0][0] << " " << mainSmart.cap1.segment.p[0][1] << " " << mainSmart.cap1.segment.p[0][2] << "\n";
			firstFile << mainSmart.cap1.segment.p[1][0] << " " << mainSmart.cap1.segment.p[1][1] << " " << mainSmart.cap1.segment.p[1][2] << "\n";

			firstFile << mainSmart.cap2.segment.p[0][0] << " " << mainSmart.cap2.segment.p[0][1] << " " << mainSmart.cap2.segment.p[0][2] << "\n";
			firstFile << mainSmart.cap2.segment.p[1][0] << " " << mainSmart.cap2.segment.p[1][1] << " " << mainSmart.cap2.segment.p[1][2] << "\n";

			intersects << mainSmart.checkNotColliding(smartOther, mainSmart) << "\n";


			secondFile << smartOther.cap0.segment.p[1][0] << " " << smartOther.cap0.segment.p[1][1] << " " << smartOther.cap0.segment.p[1][2] << "\n";
			secondFile << smartOther.cap0.segment.p[0][0] << " " << smartOther.cap0.segment.p[0][1] << " " << smartOther.cap0.segment.p[0][2] << "\n";

			secondFile << smartOther.cap1.segment.p[0][0] << " " << smartOther.cap1.segment.p[0][1] << " " << smartOther.cap1.segment.p[0][2] << "\n";
			secondFile << smartOther.cap1.segment.p[1][0] << " " << smartOther.cap1.segment.p[1][1] << " " << smartOther.cap1.segment.p[1][2] << "\n";

			secondFile << smartOther.cap2.segment.p[0][0] << " " << smartOther.cap2.segment.p[0][1] << " " << smartOther.cap2.segment.p[0][2] << "\n";
			secondFile << smartOther.cap2.segment.p[1][0] << " " << smartOther.cap2.segment.p[1][1] << " " << smartOther.cap2.segment.p[1][2] << "\n";
		}
	}



	cout << "Total Iterations: " << its << "\nCompleted Iterations: " << completed << "\nNon-Collisions: " << NN;
	/*ofstream simResults("results.txt");*/
	//simResults.open("results.txt");
	openRead(simResults, "results.txt", 1);
	simResults << its << "\n";
	simResults << completed << "\n";
	simResults << NN << "\n";
	simResults << Smarticle::D << "\n";
	simResults << Smarticle::L << "\n";
	simResults << Smarticle::W << "\n";
	simResults << Smarticle::boxSize << "\n";


	//remap angles back!
	ang1= 180*(ang1+ GTE_C_PI / 2)/(GTE_C_PI);
	ang2 = -1 * 180 * (ang2 - GTE_C_PI / 2) / (GTE_C_PI);
	simResults << ang1 << "\n";
	simResults << ang2 << "\n";
	simResults.close();
	intersects.close();
	secondFile.close();
	firstFile.close();
	return 0;

}

