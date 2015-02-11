
#ifndef __CASkeleton_H__
#define __CASkeleton_H__

#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>
#include <Mat4.h>
#include <BVH.h>
#include <BVHJoint.h>
#include <Vec4.h>
#include <CAJoint.h>

namespace chara {

   class CASkeleton
   {
   public:
      //! Cr�er un squelette ayant la m�me structure que d�finit dans le BVH
		   CASkeleton()= default;
		   CASkeleton(const BVH& bvh);
		   void remplissageSkeleton(const BVHJoint* bvhj, int num_pere);

		   //! Positionne ce squelette dans la position n du BVH
		   void setPose(const BVH& bvh, const int framenumber);
		   void setPose(const BVH& bvh1, const int framenumber1, const BVH& bvh2, const int framenumber2, float percent);
		   void setPose(int indice, chara::BVHJoint * jbvh, const int framenumber);
		   //! Calcule la distance entre deux postures
		   //! precond: les deux squelettes doivent avoir le 
		   //! m�me nombre d'articulations (m�me structure d'arbre)
		   float distance(const CASkeleton& skel);

		   //! Affiche en OpenGL le squelette, les liens entre les articulations
		   //! sont donn�s par le champ m_fatherId de CAJoint
		   void drawGL() const;
		   const std::vector<chara::CAJoint>& getJoints() const {return m_joint;}

		private:
		   //! L'ensemble des articulations.
		   //! Remarque : la notion de hi�rarchie (arbre) n'est plus n�cessaire ici,
		   //! pour tracer les os on utilise l'information "fatherID" de la class CAJoint
		   std::vector<CAJoint> m_joint;
	};
} // namespace

#endif //
