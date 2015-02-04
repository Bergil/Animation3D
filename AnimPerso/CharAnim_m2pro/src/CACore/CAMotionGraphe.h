 
#ifndef __CAMotionGraph_H__
#define __CAMotionGraph_H__

#include "CASkeleton.h"
#include "BVH.h"
#include "CAGrapheNode.h"

class CAMotionGraph
{
	private:
	   //! L'ensemble des BVH du graphe d'animation
	   std::vector<chara::BVH> m_BVH;

	   //! Tous les noeuds du graphe d'animation
	   //! Un noeud du graphe contient l'identifiant de l'animation, le numéro 
	   //! de la frame et les identifiants des noeuds successeurs 
	   std::vector<chara::GrapheNode> m_GrapheNode;

	public:
	   CAMotionGraph()= default;
	   CAMotionGraph(const std::vector<std::string>& listebvh, float distance);
	   void remplissageGraphe(float distance);
	   
};

#endif
