
#include "CASkeleton.h"

namespace chara {

	void CAJoint::remplissageJoint(const BVHJoint* , int num_pere)
	{
		m_fatherId = num_pere;
	}

	// TODO
	CASkeleton::CASkeleton(const BVH& bvh)
	{
		remplissageSkeleton(bvh.getRoot(), -1);
	}

	void CASkeleton::remplissageSkeleton(const BVHJoint* bvhj, int num_pere)
	{
		int num;
		CAJoint c;
		//c.remplissageJoint(bvhj, num_pere);
		c.m_fatherId = num_pere;
		m_joint.push_back(c);
		num = m_joint.size()-1;
		fprintf(stderr, "Je suis le noeud: %d, mon pere est: %d\n", num, num_pere);

		for(int i = 0; i < bvhj->getNumChild(); i++)
		{
			remplissageSkeleton(bvhj->getChild(i), num);
		}
	}

	void CASkeleton::setPose(const BVH& bvh, const int frameNumber)
	{

	}

	float CASkeleton::distance(const CASkeleton& skel) const
	{
		return 0.0f;
	}

	void CASkeleton::drawGL() const
	{

	}

}