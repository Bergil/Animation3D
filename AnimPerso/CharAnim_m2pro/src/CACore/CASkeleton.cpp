
#include "CASkeleton.h"
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Tools.h"


using namespace chara;

CASkeleton::CASkeleton(const BVH& bvh)
{
	remplissageSkeleton(bvh.getRoot(), -1);
}

void CASkeleton::remplissageSkeleton(const BVHJoint* bvhj, int num_pere)
{
	int num;
	CAJoint c(num_pere);
	m_joint.push_back(c);
	num = m_joint.size()-1;
	for(int i = 0; i < bvhj->getNumChild(); i++)
	{
		remplissageSkeleton(bvhj->getChild(i), num);
	}
} 
//! Positionne ce squelette dans la position n du BVH
void CASkeleton::setPose(const BVH& bvh, const int framenumber){
	
	for(int i = 0; i< bvh.getNumJoint(); i++){
		chara::BVHJoint * jbvh = bvh.getJoint(i);
		setPose(i, jbvh, framenumber);		
	}
}

void CASkeleton::setPose(const BVH& bvh1, const int framenumber1, const BVH& bvh2, const int framenumber2, float percent){
	CASkeleton tmp1(bvh1); 
	CASkeleton tmp2(bvh2);
	tmp1.setPose(bvh1, framenumber1);
	tmp2.setPose(bvh2, framenumber2);
	for(unsigned int i = 0; i < m_joint.size(); i++){
		m_joint[i].setT_local2world(tmp1.getJoints()[i].getT_local2world() * (1-percent) + tmp2.getJoints()[i].getT_local2world() * percent);
		m_joint[i].setQ_local2world(math::TQuaternion<float>::slerp(tmp1.getJoints()[i].getQ_local2world(), tmp2.getJoints()[i].getQ_local2world(), percent));
	}
}

void CASkeleton::setPose(int indice, chara::BVHJoint * jbvh, const int framenumber){
	
	math::TQuaternion<float> Q;
	math::TQuaternion<float> Qtemp;
	math::Vec3<float> T;
	
	math::Vec3<float> vecAxisX(1.0,0.0,0.0);
	math::Vec3<float> vecAxisY(0.0,1.0,0.0);
	math::Vec3<float> vecAxisZ(0.0,0.0,1.0);
	
	BVHJoint* bvhparent = jbvh->getParent();
	if (bvhparent != nullptr){
		int indicePere;
		indicePere = m_joint[indice].getM_fatherId();
		Q = m_joint[indicePere].getQ_local2world();
		T = m_joint[indicePere].getT_local2world();
	}

	float v[3];
	jbvh->getOffset(v[0], v[1], v[2]);
	for(int i = 0; i < jbvh->getNumChannel(); i++){
		chara::BVHChannel* chan = jbvh->getChannel(i);
		if(chan->isRotation()){
			switch(chan->getAxis()){
				case AXIS_X : 
							Qtemp *= math::TQuaternion<float>(vecAxisX, convertDegreeToRadian(chan->getData(framenumber)));
							break;
				case AXIS_Y : 
							Qtemp *= math::TQuaternion<float>(vecAxisY, convertDegreeToRadian(chan->getData(framenumber)));
							break;
				case AXIS_Z : 
							Qtemp *= math::TQuaternion<float>(vecAxisZ, convertDegreeToRadian(chan->getData(framenumber)));
							break;
			}
					
		}else if(chan->isTranslation()){
			switch(chan->getAxis()){
				case AXIS_X : 
							v[0] += chan->getData(framenumber);
							break;
				case AXIS_Y : 
							v[1] += chan->getData(framenumber);
							break;
				case AXIS_Z : 
							v[2] += chan->getData(framenumber);
							break;
			}		
		}
	}
	
	T += Q*math::Vec3<float>(v[0], v[1], v[2]);
	Q *= Qtemp;
	m_joint[indice].setQ_local2world(Q);
	m_joint[indice].setT_local2world(T);
	
}

//! Calcule la distance entre deux postures
//! precond: les deux squelettes doivent avoir le 
//! même nombre d'articulations (même structure d'arbre)
float CASkeleton::distance(const CASkeleton& skel){
	float dist = 0.0;
	assert(skel.m_joint.size() == m_joint.size());
	for(unsigned int i = 0; i < m_joint.size(); i++){
		math::Vec3<float> temp(m_joint[i].getT_local2world() - skel.m_joint[i].getT_local2world());
		dist += temp.norm();
	}
	return dist;
}

//! Affiche en OpenGL le squelette, les liens entre les articulations
//! sont donnés par le champ m_fatherId de CAJoint
void CASkeleton::drawGL() const{
	
	glPointSize(8.0);
	glBegin(GL_POINTS);
	
	for (unsigned int i = 0; i< m_joint.size(); i++){	
		glVertex3f(m_joint[i].getT_local2world().x, m_joint[i].getT_local2world().y, m_joint[i].getT_local2world().z);
	}
	glEnd();
	
}
