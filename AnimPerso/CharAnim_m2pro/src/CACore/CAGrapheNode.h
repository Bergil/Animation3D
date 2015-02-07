 
#ifndef __CAGrapheNode_H__
#define __CAGrapheNode_H__
#include <vector>
#include <BVH.h>

namespace chara {
	
	class CAGrapheNode
	{			
		public : 
			//! Un noeud du graphe d'animation est repéré par un entier=un identifiant
			typedef int GrapheNodeID;
			//! Une animation BVH est repérée par un identifiant=un entier 
			typedef int BVH_ID;
			
			CAGrapheNode(int BVH_ID, int num_frame, int next);
			std::vector<GrapheNodeID>& getListIdNext() {return ids_next;}
			const std::vector<GrapheNodeID>& getListIdNext() const {return ids_next;}
			const BVH_ID & getIdBVH() const {return id_bvh;}
			const BVH_ID & getNumFrame() const {return frame;}
			
		private :
		//! Un noeud du graphe contient l'identifiant de l'animation, le numéro 
		//! de la frame et les identifiants des noeuds successeurs 
			BVH_ID id_bvh;
			int frame;
			std::vector<GrapheNodeID> ids_next;     //! Liste des nœuds successeurs 
			
   };
}  
#endif
