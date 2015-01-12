
#ifndef __CAJoint_H__
#define __CAJoint_H__

#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>
#include <Mat4.h>
#include <BVH.h>
#include <BVHJoint.h>
#include <Vec4.h>
#include <math.h>
#include <Quaternion.h>

namespace chara {
	class CAJoint
	{
			private :
			   
			   int m_fatherId;        // Le numéro du père dans le tableau de CAJoint de CASkeleton
			   math::TQuaternion<float> q_local2world;   // La matrice passant du repère de l'articulation vers le monde. On peut aussi stocker un quaternion + une translation
			   math::Vec3<float> t_local2world;
			   //Mat4f m_world2local;   // Si besoin : La matrice passant du repère du monde vers l'articulation
			
			public :   
			
			   CAJoint();
			   CAJoint(int num_pere) {m_fatherId = num_pere;}
			   int getM_fatherId() {return m_fatherId;}
			   void setM_fatherId(int num_pere) {m_fatherId = num_pere;}
			  // void remplissageJoint(const BVHJoint* , int num_pere);
			   math::TQuaternion<float>  getQ_local2world() const {return q_local2world;}
			   void setQ_local2world(math::TQuaternion<float>  quat) {q_local2world = quat;}
			   math::Vec3<float>  getT_local2world() const {return t_local2world;}
			   void setT_local2world(math::Vec3<float>  vec) {t_local2world = vec;}
			   
	}; 
}

#endif
