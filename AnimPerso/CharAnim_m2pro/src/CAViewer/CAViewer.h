#include <random>
#include <Viewer.h>
#include "BVHTools.h"
#include <chrono>
#include <BVH.h>
#include <BVHJoint.h>
#include <Vec3.h>
#include "CASkeleton.h"
#include "CAMotionGraph.h"
#include <memory>

#ifndef _CAVIEWER_H
#define _CAVIEWER_H

class CAViewer : public Viewer
{
public:
	CAViewer() : Viewer(), isPhysics(false), m_bvhFrame(0), gen(rd())
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
	std::unique_ptr<CAMotionGraph> m_motiongraph;
	//! mocap frame number (when mocap is used)
	chara::CAGrapheNode::GrapheNodeID m_idGrapheNode = 0;
	int m_bvhFrame;
	std::chrono::time_point<std::chrono::system_clock> start, end;
    //! target point for the IK
    math::Vec3f m_target;
	std::random_device rd;
	std::mt19937 gen;
	/// skeleton (build from the mocap-BVH data m_bvh)
	chara::CASkeleton	m_skel;
	int ancien = 0;
	float percent;
	int target = 0;



};

#endif
