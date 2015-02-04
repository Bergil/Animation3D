 
#ifndef __CAGrapheNode_H__
#define __CAGrapheNode_H__


namespace chara {
	
	class CAGrapheNode
	{
		private :
		//! Un noeud du graphe contient l'identifiant de l'animation, le numéro 
		//! de la frame et les identifiants des noeuds successeurs 
			BVH_ID id_bvh;
			int frame;
			std::vector<GrapheNodeID> ids_next;     //! Liste des nœuds successeurs 
			
		public : 
			//! Un noeud du graphe d'animation est repéré par un entier=un identifiant
			typedef int GrapheNodeID;

			//! Une animation BVH est repérée par un identifiant=un entier 
			typedef int BVH_ID;
			
			CAGrapheNode();	
			
   };
   
#endif
