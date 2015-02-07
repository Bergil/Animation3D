#pragma once 
#include "CASkeleton.h"
#include "BVH.h"
#include "CAGrapheNode.h"
#include <memory>

class CAMotionGraph
{
	private:
	   //! L'ensemble des BVH du graphe d'animation
	   std::vector<std::unique_ptr<chara::BVH>> m_BVH;

	   //! Tous les noeuds du graphe d'animation
	   //! Un noeud du graphe contient l'identifiant de l'animation, le numéro 
	   //! de la frame et les identifiants des noeuds successeurs 
	   std::vector<chara::CAGrapheNode> m_GrapheNode;

	public:
	   CAMotionGraph()= default;
	   CAMotionGraph(const std::vector<std::string>& listebvh, float distance);
	   void remplissageGraphe(float distance);
	   const std::vector<chara::CAGrapheNode> & getGrapheNode() const {return m_GrapheNode;}
	   const std::vector<std::unique_ptr<chara::BVH>> & getBVH() const {return m_BVH;}
	   
};

