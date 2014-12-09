
#include <Viewer.h>
#include "BVHTools.h"
#include <chrono>
#include <BVH.h>
#include <BVHJoint.h>
#include <Vec3.h>

#ifndef _CAVIEWER_H
#define _CAVIEWER_H

class CAViewer : public Viewer
{
public:
	CAViewer() : Viewer(), isPhysics(false), m_bvh(NULL), m_bvhFrame(0)
	{}

	virtual ~CAViewer ();
	virtual void draw();
	virtual void help();
	virtual void init();
	virtual void animate();
	virtual void keyPressed(unsigned char key, int x, int y);
	virtual void specialKeyPressed(int key, int x, int y);
	virtual void bvhDrawGLRec(const chara::BVHJoint& b, int frameNumber);
	virtual void bvhDrawGL(const chara::BVH& b, int frameNumber);
	virtual void bvhTransitionDrawGLRec(const chara::BVHJoint& bvhSRC, int frameNumberSRC, const chara::BVHJoint& bvhDST, int frameNumberDST, const float interpolationValue);

	virtual void bvhTransitionDrawGL(const chara::BVH& bvhSRC, int frameNumberSRC, const chara::BVH& bvhDST, int frameNumberDST, const float interpolationValue);


protected :

	bool isPhysics;

	//! mocap data
	chara::BVH*			m_bvh;
	//! mocap frame number (when mocap is used)
	int m_bvhFrame;
	std::chrono::time_point<std::chrono::system_clock> start, end;
    //! target point for the IK
    math::Vec3f m_target;

	/// skeleton (build from the mocap-BVH data m_bvh)
	//CASkeleton*	m_skel;



};

#endif
