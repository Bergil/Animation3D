
#include "CASkeleton.h"

using namespace chara;

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

//! Positionne ce squelette dans la position n du BVH
void setPose(const BVH& bvh, const int frameNumber){
	
	
	
}


//! Calcule la distance entre deux postures
//! precond: les deux squelettes doivent avoir le 
//! même nombre d'articulations (même structure d'arbre)
float CASkeleton::distance(const CASkeleton& skel){
	float dist = 0.0;
	assert(skel.m_joint.size() == m_joint.size());
	for(int i = 0; i < m_joint.size(); i++){
		math::Vec4<float> temp(m_joint[i].m_local2world * math::Vec4<float>(0.0, 0.0, 0.0, 1.0)
						 -skel.m_joint[i].m_local2world * math::Vec4<float>(0.0, 0.0, 0.0, 1.0));
		temp /= temp.w;
		//vec4 0001 parce chaque articulation est centré dans son repère local, et en Vec4 pour la multi de matrice
		dist += math::Vec3<float>(temp.x, temp.y, temp.z).norm();
	}
	return dist;
}

//! Affiche en OpenGL le squelette, les liens entre les articulations
//! sont donnés par le champ m_fatherId de CAJoint
void CASkeleton::drawGL() const{
	
}
