
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
      //! Créer un squelette ayant la même structure que définit dans le BVH
		   CASkeleton()= default;
		   CASkeleton(const BVH& bvh);
		   void remplissageSkeleton(const BVHJoint* bvhj, int num_pere);

		   //! Positionne ce squelette dans la position n du BVH
		   void setPose(const BVH& bvh, const int framenumber);
		   void setPose(int indice, chara::BVHJoint * jbvh, const int framenumber);
		   //! Calcule la distance entre deux postures
		   //! precond: les deux squelettes doivent avoir le 
		   //! même nombre d'articulations (même structure d'arbre)
		   float distance(const CASkeleton& skel);

		   //! Affiche en OpenGL le squelette, les liens entre les articulations
		   //! sont donnés par le champ m_fatherId de CAJoint
		   void drawGL() const;
		   

		private:
		   //! L'ensemble des articulations.
		   //! Remarque : la notion de hiérarchie (arbre) n'est plus nécessaire ici,
		   //! pour tracer les os on utilise l'information "fatherID" de la class CAJoint
		   std::vector<CAJoint> m_joint;
	};
} // namespace

#endif //
