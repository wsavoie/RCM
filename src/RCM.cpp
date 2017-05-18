// RCM.cpp : Defines the entry point for the console application.
//



#include <math.h>
#include <iostream>
#include <string>
#include <random>
#include <complex>      // std::complex, std::real
#include "smarticle.h"
//#include <Ogre.h>
//#include <OgreCamera.h>
//#include <OgreEntity.h>
//#include <OgreLogManager.h>
//#include <OgreRoot.h>
//#include <OgreViewport.h>
//#include <OgreSceneManager.h>
//#include <OgreRenderWindow.h>
//#include <OgreConfigFile.h>

#include <irrlicht.h>

using namespace std;
using namespace gte;
//using namespace Ogre;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
//extern "C"
//#ifdef _IRR_WINDOWS_
//#pragma comment(lib, "D:/irrlicht-1.8.1/lib/Win64-visualStudio/Irrlicht.lib")
//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
//#endif
double scale = 1;
bool plot = true;
//using namespace smart;
//Ogre::Root* mRoot;
//Ogre::RenderWindow* mRenderWindow;
//Ogre::SceneManager* mSceneMgr;
//Ogre::Viewport* mViewport;
//Ogre::Camera* mCamera;
double ang1 = 1, ang2 = 1, box = 1, lw = 1;
vector3df center(0, 0, 0);
void openRead(std::ofstream& stream, std::string fileN, unsigned int idx = 1);
vector3df Cap2Angle(gte::Capsule3<double> cap);
void drawGlobalCoordinateFrame(IrrlichtDevice* device);
irr::core::vector3df Cap2IrrVec(Vector<3, double> cap);
IMeshSceneNode* addCapsuleNode(gte::Capsule3<double> capsule, int color, IrrlichtDevice* device, vector3df rotVec);
void drawSmarticle(Smarticle smart, IrrlichtDevice* device, int color);
void switchAxis(vector3df* vec);
vector3df posToIrrlicht(vector3df rightSystem);
vector3df rotToIrrlicht(vector3df rightSystem);
class MyEventReceiver : public IEventReceiver
{
public:
	// This is the one method that we have to implement
	//virtual bool OnEvent(const SEvent& event)
	//{
	//	// Remember whether each key is down or up
	//	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	//		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	//	return false;
	//}
		virtual bool OnEvent(const SEvent& event)
		{
			if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			{
				KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
				{
					key = true;
					return true;
				}
			}
			return false;
		}
	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}
	virtual bool keydown()
	{
		if(key)
		{
			key = false;
			return true;
		}
		return false;
	}
	MyEventReceiver()
	{
		//for (u32 i = 0; i<KEY_KEY_CODES_COUNT; ++i)
		//	KeyIsDown[i] = false;
		memset(KeyIsDown, false, sizeof(KeyIsDown));
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	bool key=false;
};



void openRead(std::ofstream& stream, std::string fileN, unsigned int idx)
{
	if (idx == 0) {
		stream.open(fileN);
	}
	else {
		stream.open(fileN, std::ios::app);
	}

}
void drawSmarticle(Smarticle smart,IrrlichtDevice* device, int color)
{

	//IMeshSceneNode* mid = addCapsuleNode(smart.cap1, color, device, Cap2Angle(smart.cap1) * 180 / PI);

	
	//vector3df a = Cap2Angle(smart.cap0);
	//switchAxis(&a);
	//vector3df b = Cap2Angle(smart.cap1);
	//switchAxis(&b);
	//vector3df c = Cap2Angle(smart.cap2);
	//switchAxis(&c);
	
	IMeshSceneNode* left = addCapsuleNode(smart.cap0, color, device, Cap2Angle(smart.cap0));
	IMeshSceneNode* mid = addCapsuleNode(smart.cap1, color, device, Cap2Angle(smart.cap1));
	IMeshSceneNode* right = addCapsuleNode(smart.cap2, color, device, Cap2Angle(smart.cap2));
	cout << "\n\n\n" << left->getRotation().X;
	//addCapsuleNode(smart.cap2, color, device, c * 180 / PI);
}
vector3df Cap2Angle(gte::Capsule3<double> cap)
{
	////capsule to vector
	//vector3df capv = Cap2IrrVec(cap.segment.p[1] - cap.segment.p[0]);
	////normalize since acos only works between [-1,1]
	//capv = capv.normalize();
	////acos(v1.v2)= angle between vectors, but v1 = [1,1,1] so just acos of vec
	//cout << "\nacos:(" << acos(capv.X) * 180 / PI << "," << acos(capv.Y) * 180 / PI << "," << acos(capv.Z) * 180 / PI << ")\nasin:(" << asin(capv.X) * 180 / PI << "," << asin(capv.Y) * 180 / PI << "," << asin(capv.Z) * 180 / PI << ")\n";
	//capv = vector3df(acos(capv.X), acos(capv.Y), acos(capv.Z));

	vector3df capv = Cap2IrrVec(cap.segment.p[0] - cap.segment.p[1]);

	//capv=capv.normalize();
	vector3df temp(acos(capv.X / capv.getLength()), acos(capv.Y / capv.getLength()), acos(capv.Z / capv.getLength()));
	//temp = temp*180.0 / PI;
	temp = capv.getHorizontalAngle();
	//temp.X = temp.X + 180 * (cos(temp.X*PI / 180) + sin(temp.X*PI / 180));
	//temp.Y = temp.Y + 90 * (cos(temp.Y*PI / 180) + sin(temp.Y*PI / 180));

	//temp.Z = temp.Z+(cos(temp.Y*PI/180)*+sin(temp.Y*PI/180));
	
	cout << "\nCap2Angle:(" << temp.X << ", " << temp.Y << ", " << temp.Z << ")\n";
	return 	temp;
}

 void add_typical_Lights(IrrlichtDevice* device,
	irr::core::vector3df pos1 = irr::core::vector3df(30.f, 100.f, 30.f),
	irr::core::vector3df pos2 = irr::core::vector3df(30.f, 80.f, -30.f),
	double rad1 = 290,
	double rad2 = 190,
	irr::video::SColorf col1 = irr::video::SColorf(0.7f, 0.7f, 0.7f, 1.0f),
	irr::video::SColorf col2 = irr::video::SColorf(0.7f, 0.8f, 0.8f, 1.0f)) {
	// create lights
	scene::ILightSceneNode* mlight1 = device->getSceneManager()->addLightSceneNode(0, pos1, col1, (f32)rad1);

	scene::ILightSceneNode* mlight2 = device->getSceneManager()->addLightSceneNode(0, pos2, col2, (f32)rad2);

	mlight2->enableCastShadow(false);
}

 irr::core::vector3df Cap2IrrVec(Vector<3, double> cap)
 {
	 return vector3df(cap[0], cap[1], cap[2]);
 }
 irr::core::vector3df Cap2IrrVec2(Vector<3, double> cap)
 {
	 return vector3df(cap[2], cap[0], -cap[1]);
 }

 //void drawGlobalCoordinateFrame(IrrlichtDevice* device)
 //{
	// double len = Smarticle::l;
	// double rad = Smarticle::D/2;
	// vector3df pos(0, Smarticle::boxSize, 0);
	// pos = pos + center;
	// io::path blue = "D:/RCMcode/RCM/textures/blue.png";
	// io::path green = "D:/RCMcode/RCM/textures/green.png";
	// io::path red = "D:/RCMcode/RCM/textures/red.png";
	// 
	// ISceneNode* xaxis = device->getSceneManager()->addSphereSceneNode(rad*2, 30, 0, -1, pos+vector3df(len, 0, 0), vector3df(0, 0, 0)); // adds our sphere scene node
	// ISceneNode* yaxis = device->getSceneManager()->addSphereSceneNode(rad*2, 30, 0, -1, pos+vector3df(0, len, 0), vector3df(0, 0, 0)); // adds our sphere scene node
	// ISceneNode* zaxis = device->getSceneManager()->addSphereSceneNode(rad*2, 30, 0, -1, pos+vector3df(0, 0, len), vector3df(0, 0, 0)); // adds our sphere scene node


	// IMesh* cyl = device->getSceneManager()->getMesh("D:/RCMcode/RCM/textures/cylinder.obj");
	// IMeshSceneNode* cylX = device->getSceneManager()->addMeshSceneNode(cyl);
	// IMeshSceneNode* cylY = device->getSceneManager()->addMeshSceneNode(cyl); 
	// IMeshSceneNode* cylZ = device->getSceneManager()->addMeshSceneNode(cyl); 
	// cylX->setScale(vector3df(1, len / 2, 1)); 
	// cylY->setScale(vector3df(1, len / 2, 1));
	// cylZ->setScale(vector3df(1, len / 2, 1));

	// cylX->setPosition(pos + vector3df((len - rad) / 2, 0, 0));
	// cylY->setPosition(pos + vector3df(0, (len - rad) / 2, 0));
	// cylZ->setPosition(pos + vector3df(0, 0, (len - rad) / 2));
	// 
	// cylX->setRotation(vector3df(0, 0, 90.0));
	// cylY->setRotation(vector3df(0, 0, 0));
	// cylZ->setRotation(vector3df(90.0, 0, 0));

	// cylX->setMaterialTexture(0, device->getVideoDriver()->getTexture(red));
	// xaxis->setMaterialTexture(0, device->getVideoDriver()->getTexture(red));

	// cylY->setMaterialTexture(0, device->getVideoDriver()->getTexture(green));
	// yaxis->setMaterialTexture(0, device->getVideoDriver()->getTexture(green));

	// cylZ->setMaterialTexture(0, device->getVideoDriver()->getTexture(blue));
	// zaxis->setMaterialTexture(0, device->getVideoDriver()->getTexture(blue));

 //}

 void drawGlobalCoordinateFrame(IrrlichtDevice* device)
 {
	 double len = Smarticle::l;
	 double rad = Smarticle::D / 2;
	 vector3df pos(0, Smarticle::boxSize, 0);
	 pos = pos + center;
	 io::path blue = "D:/RCMcode/RCM/textures/blue.png";
	 io::path green = "D:/RCMcode/RCM/textures/green.png";
	 io::path red = "D:/RCMcode/RCM/textures/red.png";

	 ISceneNode* xaxis = device->getSceneManager()->addSphereSceneNode(rad * 2, 30, 0, -1, pos + vector3df(len, 0, 0), vector3df(0, 0, 0)); // adds our sphere scene node
	 ISceneNode* yaxis = device->getSceneManager()->addSphereSceneNode(rad * 2, 30, 0, -1, pos + vector3df(0, len, 0), vector3df(0, 0, 0)); // adds our sphere scene node
	 ISceneNode* zaxis = device->getSceneManager()->addSphereSceneNode(rad * 2, 30, 0, -1, pos + vector3df(0, 0, len), vector3df(0, 0, 0)); // adds our sphere scene node


	 IMesh* cyl = device->getSceneManager()->getMesh("D:/RCMcode/RCM/textures/cylinder.obj");
	 IMeshSceneNode* cylX = device->getSceneManager()->addMeshSceneNode(cyl);
	 IMeshSceneNode* cylY = device->getSceneManager()->addMeshSceneNode(cyl);
	 IMeshSceneNode* cylZ = device->getSceneManager()->addMeshSceneNode(cyl);
	 cylX->setScale(vector3df(1, len / 2, 1));
	 cylY->setScale(vector3df(1, len / 2, 1));
	 cylZ->setScale(vector3df(1, len / 2, 1));

	 cylX->setPosition(pos + vector3df((len - rad) / 2, 0, 0));
	 cylY->setPosition(pos + vector3df(0, (len - rad) / 2, 0));
	 cylZ->setPosition(pos + vector3df(0, 0, (len - rad) / 2));

	 cylX->setRotation(vector3df(0, 0, 90.0));
	 cylY->setRotation(vector3df(0, 0, 0));
	 cylZ->setRotation(vector3df(90.0, 0, 0));

	 cylX->setMaterialTexture(0, device->getVideoDriver()->getTexture(red));
	 xaxis->setMaterialTexture(0, device->getVideoDriver()->getTexture(red));

	 cylY->setMaterialTexture(0, device->getVideoDriver()->getTexture(green));
	 yaxis->setMaterialTexture(0, device->getVideoDriver()->getTexture(green));

	 cylZ->setMaterialTexture(0, device->getVideoDriver()->getTexture(blue));
	 zaxis->setMaterialTexture(0, device->getVideoDriver()->getTexture(blue));



 }


 void switchAxis(vector3df* vec)
 {
	 vector3df temp = *vec;
	 vec->Z = temp.Y;
	 vec->Y = temp.Z;

 }
 vector3df irrlichtGyrate()
 {
	 return vector3df(0, 0, 0);
 }
 IMeshSceneNode* addCapsuleNode(gte::Capsule3<double> capsule, int color, IrrlichtDevice* device, vector3df rotVec)
 {

	 //vector3df rotVec = Cap2IrrVec(rot);
	 double rad = capsule.radius;
	 ISceneManager* smgr = device->getSceneManager();
	 IVideoDriver* driver = device->getVideoDriver();

	 //std::string blue = "D:/RCMcode/RCM/textures/blue.png";
	 io::path blue = "D:/RCMcode/RCM/textures/blue.png";
	 io::path green = "D:/RCMcode/RCM/textures/green.png";
	 io::path red = "D:/RCMcode/RCM/textures/red.png";
	 io::path capColor = "";
	 //Ogre::Entity* ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");

	 IMesh* cyl = smgr->getMesh("D:/RCMcode/RCM/textures/cylinder.obj");
	 //auto mRenderer = C::OgreRenderer::bootstrapSystem();
	 switch (color)
	 {
		case 0: //unsuccessful other smarticle
			capColor = red;
			break;
		case 1: //successful other smarticle
			capColor = green;
			break;
		case 2: //main smarticle
			capColor = blue;
			break;
	 }
	 
	
	 //

	 vector3df p0r = Cap2IrrVec(capsule.segment.p[0]);
	 vector3df p1r = Cap2IrrVec(capsule.segment.p[1]);
	 vector3df p0 = Cap2IrrVec(capsule.segment.p[0]);
	 vector3df p1 = Cap2IrrVec(capsule.segment.p[1]);
	 vector3df dir(0,0,0);
	 vector3df dir2(0, 0, 0);
	 dir = p0-p1;
	 
	 double len = dir.getLength();
	 

	 double height = (p1 - p0).getLength();
	 vector3df cen = (p0 + p1) / 2;
	 vector3df z (0,0, 1);
	 vector3df p =(p1 - p0);
	 vector3df t = z.crossProduct(p);
	 double angle = acos(z.dotProduct(p) / p.getLength());
	 
	 //double rotx = atan(2 * (angle*t.X + t.Y*t.Z) / (1 - 2 * (t.X*t.X + t.Y*t.Y))) * 180 / PI;
	 double rotx = atan2(2.0 * (angle*t.X + t.Y*t.Z), (1 - 2 * (t.X*t.X + t.Y*t.Y))) * 180.0 / PI;
	 double roty = asin(2.0 * (angle*t.Y - t.Z*t.X)) * 180.0 / PI;
	 //double rotz = atan(2*(angle*t.Z+t.X*t.Y) /
		// (1 - 2 * (t.Y*t.Y + t.Z*t.Z)))*180 / PI;
	 double rotz = atan2(2.0 * (angle*t.Z + t.X*t.Y), (1 - 2 * (t.Y*t.Y + t.Z*t.Z))) * 180.0 / PI;
	 
	 vector3df rot(rotx, roty, rotz);
	 //IMesh* cyl = smgr->getGeometryCreator()->createCylinderMesh(rad,len,20,irr::video::SColor (0,255,255,255),true,0);
	
	 dir2 = dir;
	/* dir.X = -dir2.X;
	 dir.Y = -dir2.Y;
	 dir.Z = -dir2.Z;*/

	 vector3df centerPos = (p0 + p1) / 2;
	 centerPos = posToIrrlicht(centerPos);
	 IMeshSceneNode* cylinder = smgr->addMeshSceneNode(cyl, 0, -1, centerPos, rotVec); // adds our sphere scene node
	 //switchAxis(&centerPos);
	 //cylinder->setPosition(centerPos);
	 //cylinder->setPosition(vector3df(0, 0, 0));
	 cylinder->setScale(vector3df(rad, len / 2, rad));
	
	 dir = dir / len;
	 vector3df output = rot;

	 vector3df irrRotVec = rotToIrrlicht(rot);
	// cylinder->setRotation(rot);
	 //cylinder->setRotation(vector3df(acos(dir.X) * 180 / PI, acos(-dir.Z) * 180 / PI, -acos(dir.Y) * 180 / PI));
	 //cylinder->setRotation(rotVec);

	 //IGUIEnvironment* guienv = device->getGUIEnvironment();
	// cout << "Rot (" << output.X << ", " << output.Y << ", " << output.Z << ")\n";
	 output = irrRotVec;
	 //cout << "irrRot (" << output.X << ", " << output.Y << ", " << output.Z << ")\n";
	 p0 = posToIrrlicht(p0);
	 p1 = posToIrrlicht(p1);
	 ISceneNode* sphere0 = smgr->addSphereSceneNode(rad, 30, 0, -1, p0, vector3df(0, 0, 0)); // adds our sphere scene node
	 ISceneNode* sphere1 = smgr->addSphereSceneNode(rad, 30, 0, -1, p1, vector3df(0, 0, 0)); // adds our sphere scene node
	 sphere0->setMaterialTexture(0, driver->getTexture(capColor));
	 sphere1->setMaterialTexture(0, driver->getTexture(capColor));
	 cylinder->setMaterialTexture(0, driver->getTexture(capColor));
	 return cylinder;
 }

//void createSphere(const std::string& strName, const float r, const int nRings = 16, const int nSegments = 16)
//{
//	ManualObject * manual = mSceneMgr->createManualObject(strName);
//	manual->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_LIST);
//
//	float fDeltaRingAngle = (Math::PI / nRings);
//	float fDeltaSegAngle = (2 * Math::PI / nSegments);
//	unsigned short wVerticeIndex = 0;
//
//	// Generate the group of rings for the sphere
//	for (int ring = 0; ring <= nRings; ring++) {
//		float r0 = r * sinf(ring * fDeltaRingAngle);
//		float y0 = r * cosf(ring * fDeltaRingAngle);
//
//		// Generate the group of segments for the current ring
//		for (int seg = 0; seg <= nSegments; seg++) {
//			float x0 = r0 * sinf(seg * fDeltaSegAngle);
//			float z0 = r0 * cosf(seg * fDeltaSegAngle);
//
//			// Add one vertex to the strip which makes up the sphere
//			manual->position(x0, y0, z0);
//			manual->normal(Vector3(x0, y0, z0).normalisedCopy());
//			manual->textureCoord((float)seg / (float)nSegments, (float)ring / (float)nRings);
//
//			if (ring != nRings) {
//				// each vertex (except the last) has six indicies pointing to it
//				manual->index(wVerticeIndex + nSegments + 1);
//				manual->index(wVerticeIndex);
//				manual->index(wVerticeIndex + nSegments);
//				manual->index(wVerticeIndex + nSegments + 1);
//				manual->index(wVerticeIndex + 1);
//				manual->index(wVerticeIndex);
//				wVerticeIndex++;
//			}
//		}; // end for seg
//	} // end for ring
//	manual->end();
//	MeshPtr mesh = manual->convertToMesh(strName);
//	mesh->_setBounds(AxisAlignedBox(Vector3(-r, -r, -r), Vector3(r, r, r)), false);
//
//	mesh->_setBoundingSphereRadius(r);
//	unsigned short src, dest;
//	if (!mesh->suggestTangentVectorBuildParams(VES_TANGENT, src, dest))
//	{
//		mesh->buildTangentVectors(VES_TANGENT, src, dest);
//	}
//}
 vector3df posToIrrlicht(vector3df rightSystem)
 {
	 vector3df irrPos(0, 0, 0);
	 irrPos.X = rightSystem.X;
	 irrPos.Y = rightSystem.Z;
	 irrPos.Z = rightSystem.Y;
	 return irrPos;

 }
 vector3df rotToIrrlicht(vector3df rightSystem)
 {
	 vector3df irrRot(0, 0, 0);
	 irrRot.X = -rightSystem.X;
	 irrRot.Y = -rightSystem.Z;
	 irrRot.Z = -rightSystem.Y;
	 return irrRot;
 }
int main(int argc, char* argv[])
{
	MyEventReceiver receiver;
	
	if (argc < 5)
	{
		ang1 = 90;
		ang2 = 90;
		lw = .3;
		
		Smarticle::w = 14 * Smarticle::D;
		Smarticle::W = Smarticle::w - Smarticle::D;
		Smarticle::L = Smarticle::W*lw;
		Smarticle::l = Smarticle::L + Smarticle::D;
		box = Smarticle::w;
		Smarticle::boxSize = box*Smarticle::D;

	}
	else
	{
		ang1 = atof(argv[1]);
		ang2 = atof(argv[2]);
		lw = atof(argv[3]);
		box = atof(argv[4]);
		Smarticle::w = 14 * Smarticle::D;
		Smarticle::W = Smarticle::w - Smarticle::D;
		Smarticle::L = Smarticle::W*lw;
		Smarticle::l = Smarticle::L + Smarticle::D;
		Smarticle::boxSize = box*Smarticle::D;
	}
	double systemRad = Smarticle::boxSize/2;
	center= vector3df(systemRad,systemRad, systemRad);
	if (argc > 5)
	{
		plot = atoi(argv[5]);

	}
	
	///////////////////////////////////////////////////IRRLICHT STUFF////////////////////////////////////
	IrrlichtDevice *device = createDevice(video::EDT_SOFTWARE, dimension2d<u32>(1024, 768), 16,false, false, false, 0);
	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		rect<s32>(10, 10, 260, 22), true);

	if(plot)
	{
		
	
		device->setEventReceiver(&receiver);
	}
	///////////////////////////////////////////////////IRRLICHT STUFF////////////////////////////////////

	///////////////////////////////////////////////////OGRE STUFF////////////////////////////////////
//	mRoot = new Ogre::Root("", "", "ChOgre.log");
//	Ogre::RenderWindow* mWindow;
//	mRoot->loadPlugin("RenderSystem_GL");
//	mRoot->loadPlugin("Plugin_ParticleFX");
//	mRoot->loadPlugin("Plugin_CgProgramManager");
//	mRoot->loadPlugin("Plugin_OctreeSceneManager");
//
//
//	Ogre::RenderSystemList::const_iterator renderers = mRoot->getAvailableRenderers().begin();
//	while (renderers != mRoot->getAvailableRenderers().end())
//	{
//		Ogre::String rName = (*renderers)->getName();
//
//		if (rName == "OpenGL Rendering Subsystem")
//			break;
//
//		renderers++;
//	}
//	Ogre::RenderSystem *renderSystem = *renderers;
//	renderSystem->setConfigOption("Full Screen", "No");
//	renderSystem->setConfigOption("Video Mode", "1024 x 768 @ 32-bit colour");
//	renderSystem->setConfigOption("Display Frequency", "50 Hz");
//	renderSystem->setConfigOption("FSAA", "16");
//	renderSystem->setConfigOption("Fixed Pipeline Enabled", "Yes");
//	renderSystem->setConfigOption("RTT Preferred Mode", "FBO");
//	renderSystem->setConfigOption("VSync", "No");
//	renderSystem->setConfigOption("sRGB Gamma Conversion", "No");
//	mRoot->setRenderSystem(renderSystem);
//	mWindow = mRoot->initialise(true, "RCM");
//
//	//mmRoot->createRenderWindow("asf", 123, 123, false);
//	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "MainSceneManager");
//
//
//	SceneNode* mSceneNode = mSceneMgr->getRootSceneNode();
//	
//	mCamera = mSceneMgr->createCamera("PlayerCam");
//	SceneNode* mCameraNode = mSceneNode->createChildSceneNode("FirstCameraNode");
//	mCameraNode->attachObject(mCamera);
//
//	float lViewportWidth = 0.88f;
//	float lViewportHeight = 0.88f;
//	float lViewportLeft = (1.0f - lViewportWidth) * 0.5f;
//	float lViewportTop = (1.0f - lViewportHeight) * 0.5f;
//	unsigned short lMainViewportZOrder = 100;
//	Ogre::Viewport * vp = mWindow->addViewport(mCamera, lMainViewportZOrder, lViewportLeft, lViewportTop, lViewportWidth, lViewportHeight);
//	vp->setAutoUpdated(true);
//	vp->setBackgroundColour(Ogre::ColourValue(1, 0, 0)); 
//	float ratio = float(vp->getActualWidth()) / float(vp->getActualHeight());
//	mCamera->setAspectRatio(ratio);
//	mCamera->setNearClipDistance(1.5f);
//	mCamera->setFarClipDistance(3000.0f);
//	mWindow->setActive(true);
//	mWindow->setAutoUpdated(false);
//	{
//	Ogre::ManualObject* lManualObject = NULL;
//	{
//		// The manualObject creation requires a name.
//		Ogre::String lManualObjectName = "CubeWithAxes";
//		lManualObject = mSceneMgr->createManualObject(lManualObjectName);
//
//		// Always tell if you want to update the 3D (vertex/index) later or not.
//		bool lDoIWantToUpdateItLater = false;
//		lManualObject->setDynamic(lDoIWantToUpdateItLater);
//
//		// Here I create a cube in a first part with triangles, and then axes (in red/green/blue).
//
//		// BaseWhiteNoLighting is the name of a material that already exist inside Ogre.
//		// Ogre::RenderOperation::OT_TRIANGLE_LIST is a kind of primitive.
//		float lSize = 0.7f;
//		lManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);
//		{
//			float cp = 1.0f * lSize;
//			float cm = -1.0f * lSize;
//
//			lManualObject->position(cm, cp, cm);// a vertex
//			lManualObject->colour(Ogre::ColourValue(0.0f, 1.0f, 0.0f, 1.0f));
//			lManualObject->position(cp, cp, cm);// a vertex
//			lManualObject->colour(Ogre::ColourValue(1.0f, 1.0f, 0.0f, 1.0f));
//			lManualObject->position(cp, cm, cm);// a vertex
//			lManualObject->colour(Ogre::ColourValue(1.0f, 0.0f, 0.0f, 1.0f));
//			lManualObject->position(cm, cm, cm);// a vertex
//			lManualObject->colour(Ogre::ColourValue(0.0f, 0.0f, 0.0f, 1.0f));
//
//			lManualObject->position(cm, cp, cp);// a vertex
//			lManualObject->colour(Ogre::ColourValue(0.0f, 1.0f, 1.0f, 1.0f));
//			lManualObject->position(cp, cp, cp);// a vertex
//			lManualObject->colour(Ogre::ColourValue(1.0f, 1.0f, 1.0f, 1.0f));
//			lManualObject->position(cp, cm, cp);// a vertex
//			lManualObject->colour(Ogre::ColourValue(1.0f, 0.0f, 1.0f, 1.0f));
//			lManualObject->position(cm, cm, cp);// a vertex
//			lManualObject->colour(Ogre::ColourValue(0.0f, 0.0f, 1.0f, 1.0f));
//
//			// face behind / front
//			lManualObject->triangle(0, 1, 2);
//			lManualObject->triangle(2, 3, 0);
//			lManualObject->triangle(4, 6, 5);
//			lManualObject->triangle(6, 4, 7);
//
//			// face top / down
//			lManualObject->triangle(0, 4, 5);
//			lManualObject->triangle(5, 1, 0);
//			lManualObject->triangle(2, 6, 7);
//			lManualObject->triangle(7, 3, 2);
//
//			// face left / right
//			lManualObject->triangle(0, 7, 4);
//			lManualObject->triangle(7, 0, 3);
//			lManualObject->triangle(1, 5, 6);
//			lManualObject->triangle(6, 2, 1);
//		}
//		lManualObject->end();
//		// Here I have finished my ManualObject construction.
//		// It is possible to add more begin()-end() thing, in order to use 
//		// different rendering operation types, or different materials in 1 ManualObject.
//		lManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
//		{
//			float lAxeSize = 2.0f * lSize;
//			lManualObject->position(0.0f, 0.0f, 0.0f);
//			lManualObject->colour(Ogre::ColourValue::Red);
//			lManualObject->position(lAxeSize, 0.0f, 0.0f);
//			lManualObject->colour(Ogre::ColourValue::Red);
//			lManualObject->position(0.0f, 0.0f, 0.0f);
//			lManualObject->colour(Ogre::ColourValue::Green);
//			lManualObject->position(0.0, lAxeSize, 0.0);
//			lManualObject->colour(Ogre::ColourValue::Green);
//			lManualObject->position(0.0f, 0.0f, 0.0f);
//			lManualObject->colour(Ogre::ColourValue::Blue);
//			lManualObject->position(0.0, 0.0, lAxeSize);
//			lManualObject->colour(Ogre::ColourValue::Blue);
//
//			lManualObject->index(0);
//			lManualObject->index(1);
//			lManualObject->index(2);
//			lManualObject->index(3);
//			lManualObject->index(4);
//			lManualObject->index(5);
//		}
//		lManualObject->end();
//	}
//	Ogre::String lNameOfTheMesh = "MeshCubeAndAxe";
//	Ogre::String lResourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
//	lManualObject->convertToMesh(lNameOfTheMesh);
//
//	// Now I can create several entities using that mesh
//	int lNumberOfEntities = 5;
//	for (int iter = 0; iter < lNumberOfEntities; ++iter)
//	{
//		Ogre::Entity* lEntity = mSceneMgr->createEntity(lNameOfTheMesh);
//		// Now I attach it to a scenenode, so that it becomes present in the scene.
//		Ogre::SceneNode* lNode = mSceneNode->createChildSceneNode();
//		lNode->attachObject(lEntity);
//		// I move the SceneNode so that it is visible to the camera.
//		float lPositionOffset = float(1 + iter * 2) - (float(lNumberOfEntities));
//		lNode->translate(lPositionOffset, lPositionOffset, -10.0f);
//	}
//}
//	createSphere("derp", 100, 16, 16);
//	Entity* sphereEntity = mSceneMgr->createEntity("derp");
//	SceneNode* sphereNode = mSceneNode->createChildSceneNode();
//	//sphereEntity->setMaterialName("material_name_goes_here");
//	sphereNode->attachObject(sphereEntity);
//	mRoot->clearEventTimes();
//	//mViewport = mWindow->addViewport(mCamera);
//	//Ogre::TexturePtr rtt_texture = Ogre::TextureManager::getSingleton().createManual("RttTex", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D, mWindow->getWidth(), mWindow->getHeight(), 0, Ogre::PF_R8G8B8, Ogre::TU_RENDERTARGET);
//	//Ogre::RenderTexture* renderTexture = rtt_texture->getBuffer()->getRenderTarget();
//	//renderTexture->addViewport(mViewport->getCamera());
//	//renderTexture->getViewport(0)->setClearEveryFrame(true);
//	//renderTexture->getViewport(0)->setBackgroundColour(Ogre::ColourValue::Blue);
//	//renderTexture->getViewport(0)->setOverlaysEnabled(true);
//	//Entity* mEntity = mSceneMgr->createEntity("mySphere", Ogre::SceneManager::PT_SPHERE);
//	////mEntity->setMaterialName("YourMaterial");
//	//mSceneNode->attachObject(mEntity);
//	//mSceneNode->setPosition(Ogre::Vector3(10, 5, 3));
//	//mSceneNode->setScale(Ogre::Vector3(1.5, 1.5, 1.5)); // Radius, in theory.;
//	//mRenderWindow->update(true);
//	//mRenderWindow->swapBuffers();
//	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
//	Ogre::Light* light = mSceneMgr->createLight("MainLight");
//	light->setPosition(20, 80, 50);
//	//mRoot->renderOneFrame();
//	Entity* mEntity = mSceneMgr->createEntity("mySphere", Ogre::SceneManager::PT_SPHERE);
//	//mEntity->setMaterialName("YourMaterial");
//	mSceneNode->attachObject(mEntity);
//	mSceneNode->setPosition(Ogre::Vector3(0, 0, 0));
//	mSceneNode->setScale(Ogre::Vector3(1.5, 1.5, 1.5)); // Radius, in theory.;
//	while (!mWindow->isClosed())
//	{
//		mWindow->update(false);
//		Ogre::WindowEventUtilities::messagePump();
//		bool mVerticalSynchro = true;
//		mWindow->swapBuffers();
//		mRoot->renderOneFrame();
//	}
//
//
//	Ogre::LogManager::getSingleton().logMessage("end of the program");
	///////////////////////////////////////////////////OGRE STUFF////////////////////////////////////
	//to properly map to system i've already begun using
	ang1 = ang1*GTE_C_PI / 180.0 - GTE_C_PI / 2;
	ang2 = -1 * ang2*GTE_C_PI / 180.0 + GTE_C_PI / 2;
	ofstream firstFile("mainStaple.txt");
	ofstream secondFile("secondStaple.txt");
	ofstream intersects("intersects.txt");

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
	//pmain0 first end point of cylinder pmain1 second end point of cyl
	/////////////Capsule 1, central piece
	pmain0[0] = -Smarticle::W / 2 + Smarticle::boxSize / 2.0;
	pmain0[1] = -Smarticle::L / 2 + Smarticle::boxSize / 2.0;
	pmain0[2] = 0 + Smarticle::boxSize / 2.0;

	pmain1[0] = Smarticle::W / 2 + Smarticle::boxSize / 2.0;
	pmain1[1] = -Smarticle::L / 2 + Smarticle::boxSize / 2.0;
	pmain1[2] = 0 + Smarticle::boxSize / 2.0;

	//pmain0[0] = 0 + Smarticle::boxSize / 2.0;
	//pmain0[1] = Smarticle::W / 2 + Smarticle::boxSize / 2.0;
	//pmain0[2] = 0 + Smarticle::boxSize / 2.0;

	//pmain1[0] = 0+ Smarticle::boxSize / 2.0;
	//pmain1[1] = -Smarticle::W / 2 + Smarticle::boxSize / 2.0;
	//pmain1[2] = 0 + Smarticle::boxSize / 2.0;
	temp = pmain1;
	gte::Segment3<double> cap1seg =  genSeg(pmain0[0], pmain0[1], pmain0[2], pmain1[0], pmain1[1], pmain1[2]);
	cap1vec = (pmain1 - pmain0);
	

	/////////////Capsule 0, p0 = p0 from seg 1
	pmain1[0] = -Smarticle::W / 2 + Smarticle::boxSize / 2.0;
	pmain1[1] = Smarticle::L / 2 + Smarticle::boxSize / 2.0;
	pmain1[2] = 0 + Smarticle::boxSize / 2.0;
	cap0Rot =  rotateByAngle(ang1, pmain0, pmain1, cap1vec);
	gte::Segment3<double> cap0seg =  genSeg(pmain0[0], pmain0[1], pmain0[2], cap0Rot[0], cap0Rot[1], cap0Rot[2]);


	/////////////Capsule 2, p0 = p1 from seg 1
	pmain0 = temp;
	pmain1[0] = Smarticle::W / 2 + Smarticle::boxSize / 2.0;
	pmain1[1] = Smarticle::L / 2 + Smarticle::boxSize / 2.0;
	pmain1[2] = 0 + Smarticle::boxSize / 2.0;
	cap2Rot =  rotateByAngle(ang2, pmain0, pmain1, cap1vec);
	gte::Segment3<double> cap2seg =  genSeg(pmain0[0], pmain0[1], pmain0[2], cap2Rot[0], cap2Rot[1], cap2Rot[2]);

	//construct smarticle
	cap0.segment = cap0seg;
	cap1.segment = cap1seg;
	cap2.segment = cap2seg;
	Smarticle mainSmart(ang1, ang2);
	mainSmart.cap0 = cap0;
	mainSmart.cap1 = cap1;
	mainSmart.cap2 = cap2;
	
	if (plot)
	{
		drawSmarticle(mainSmart, device, 2);
	}
	///////////////////////////////////////// 

	if (firstFile.is_open())
	{
		firstFile << mainSmart.cap0.segment.p[1][0] << " " << mainSmart.cap0.segment.p[1][1] << " " << mainSmart.cap0.segment.p[1][2] << "\n";
		firstFile << mainSmart.cap0.segment.p[0][0] << " " << mainSmart.cap0.segment.p[0][1] << " " << mainSmart.cap0.segment.p[0][2] << "\n";

		firstFile << mainSmart.cap1.segment.p[0][0] << " " << mainSmart.cap1.segment.p[0][1] << " " << mainSmart.cap1.segment.p[0][2] << "\n";
		firstFile << mainSmart.cap1.segment.p[1][0] << " " << mainSmart.cap1.segment.p[1][1] << " " << mainSmart.cap1.segment.p[1][2] << "\n";

		firstFile << mainSmart.cap2.segment.p[0][0] << " " << mainSmart.cap2.segment.p[0][1] << " " << mainSmart.cap2.segment.p[0][2] << "\n";
		firstFile << mainSmart.cap2.segment.p[1][0] << " " << mainSmart.cap2.segment.p[1][1] << " " << mainSmart.cap2.segment.p[1][2] << "\n";
		firstFile.close();
	}


	/////////////////////////////////////////

	int completed = 0;
	int NN = 0;
	//	int N = 0;

	driver->beginScene(true, true, SColor(255, 100, 101, 140));
	add_typical_Lights(device,
		core::vector3df(Smarticle::boxSize, Smarticle::boxSize, Smarticle::boxSize),
		core::vector3df(0, -2.3*Smarticle::boxSize + Smarticle::boxSize, Smarticle::boxSize / 2.0));
	
	drawGlobalCoordinateFrame(device);
	ISceneNode* sphere = smgr->addSphereSceneNode(systemRad, 30, 0, -1, center, vector3df(0, 0, 0)); // adds our sphere scene node
	sphere->setMaterialTexture(0, driver->getTexture("D:/RCMcode/RCM/textures/green.png"));
	sphere->getMaterial(0).setFlag(irr::video::EMF_WIREFRAME, true);



	//ISceneNode* cube = smgr->addCubeSceneNode(5, 0, -1, center + vector3df(0, 0, 0), vector3df(0, 0, 0)); // adds our sphere scene node
	//cube->setMaterialTexture(0, driver->getTexture("D:/RCMcode/RCM/textures/green.png"));
	////cube->getMaterial(0).setFlag(irr::video::EMF_WIREFRAME, true);
	////vector3df testRot = rotToIrrlicht(vector3df(25,0, 0));
	////vector3df testRot = rotToIrrlicht(vector3df(0,-10,-10));
	//vector3df testRot = vector3df(0, 10, 10);
	////vector3df testPos = posToIrrlicht(vector3df(5, 0, 0))

	//vector3df testPos = vector3df(1, 1, 0);
	//ISceneNode* cube2 = smgr->addCubeSceneNode(5, 0, -1, center + testPos, testRot); // adds our sphere scene node
	//cube2->setMaterialTexture(0, driver->getTexture("D:/RCMcode/RCM/textures/blue.png"));
	////cube->getMaterial(0).setFlag(irr::video::EMF_WIREFRAME, true);


	//sphere->getMaterial(0).MaterialType = irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL;
	//sphere->getMaterial(0).MaterialType = irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL;
	

	//if (node)
	//{
	//	node->setMaterialFlag(EMF_LIGHTING, false);
	//	node->setMD2Animation(scene::EMAT_STAND);
	//	node->setMaterialTexture(0, driver->getTexture("D:/irrlicht-1.8.1/media/sydney.bmp"));
	//}

	scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeMaya(0, -1500, 200, 1500, -1, 120, true);
	smgr->setAmbientLight(video::SColorf(0.3, 0.3, 0.3, 1));


	//RTSCamera* camera = new RTSCamera(application.GetDevice(), application.GetDevice()->getSceneManager()->getRootSceneNode(),
	//	application.GetDevice()->getSceneManager(), -1, -50.0f, 0.5f, 0.0005f);
	camera->setUpVector(core::vector3df(0, 0, 1));
	//camera->setPosition(core::vector3df(0, -.17, .07));
	camera->setPosition(core::vector3df(0, -Smarticle::boxSize, Smarticle::boxSize/2));
	camera->setTarget(core::vector3df(0, 0, Smarticle::boxSize / 2)); //	camera->setTarget(core::vector3df(0, 0, .01));
	camera->setNearValue(0.0005f);

	unsigned int	its = 1000;
	for (unsigned int i = 0; i < its; i++)
	{
		//generate other smarticle
		gte::Capsule3<double> ocap0;
		gte::Capsule3<double> ocap1;
		gte::Capsule3<double> ocap2;
		ocap0.radius = Smarticle::D / 2.0;
		ocap1.radius = Smarticle::D / 2.0;
		ocap2.radius = Smarticle::D / 2.0;

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

		Vector<3, double> p0, p1, temp;
		double sqrtVal = sqrt(rx*rx + ry*ry + rz*rz);
		p0[0] = (rx*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0 + fx;
		p0[1] = (ry*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0 + fy;
		p0[2] = (rz*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0 + fz;

		p1[0] = -(rx*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0 + fx;
		p1[1] = -(ry*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0 + fy;
		p1[2] = -(rz*Smarticle::W / 2.0) / sqrtVal + Smarticle::boxSize / 2.0 + fz;



		gte::Segment3<double> ocap1seg = genSeg(p0[0], p0[1], p0[2], p1[0], p1[1], p1[2]);
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

		gte::Segment3<double> ocap0seg = genSeg(p0[0], p0[1], p0[2],
			cap0Rot[0],
			cap0Rot[1],
			cap0Rot[2]);


		p21[0] = x2;
		p21[1] = y2;
		p21[2] = z2;
		cap2Rot = rotateByAngle(ang2, p1, p21, c1);
		gte::Segment3<double> ocap2seg = genSeg(p1[0], p1[1], p1[2],
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
		openRead(intersects, "intersects.txt", 1);
		openRead(secondFile, "secondStaple.txt", 1);
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
			intersects.close();
			secondFile.close();
			continue;
		}
		bool collide = mainSmart.checkNotColliding(smartOther, mainSmart);
		intersects << collide << "\n";
		intersects.close();
		drawSmarticle(smartOther, device, collide);
		secondFile << smartOther.cap0.segment.p[1][0] << " " << smartOther.cap0.segment.p[1][1] << " " << smartOther.cap0.segment.p[1][2] << "\n";
		secondFile << smartOther.cap0.segment.p[0][0] << " " << smartOther.cap0.segment.p[0][1] << " " << smartOther.cap0.segment.p[0][2] << "\n";

		secondFile << smartOther.cap1.segment.p[0][0] << " " << smartOther.cap1.segment.p[0][1] << " " << smartOther.cap1.segment.p[0][2] << "\n";
		secondFile << smartOther.cap1.segment.p[1][0] << " " << smartOther.cap1.segment.p[1][1] << " " << smartOther.cap1.segment.p[1][2] << "\n";

		secondFile << smartOther.cap2.segment.p[0][0] << " " << smartOther.cap2.segment.p[0][1] << " " << smartOther.cap2.segment.p[0][2] << "\n";
		secondFile << smartOther.cap2.segment.p[1][0] << " " << smartOther.cap2.segment.p[1][1] << " " << smartOther.cap2.segment.p[1][2] << "\n";
		secondFile.close();


		if (plot)
		{
			driver->beginScene(true, true,
				video::SColor(255, 140, 161, 192));

			smgr->drawAll();
			guienv->drawAll();
			
			driver->endScene();

		}
	}
	if (plot)
	{
		while (device->run())
		{
			driver->beginScene(true, true,
				video::SColor(255, 140, 161, 192));

			smgr->drawAll();
			guienv->drawAll();

			driver->endScene();

		}
	}
	cout << "Total Iterations: " << its << "\nCompleted Iterations: " << completed << "\nNon-Collisions: " << NN;
	ofstream simResults("results.txt");
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
	secondFile.close();
	firstFile.close();

	return 0;
}

