#include "CAMotionGraphe.h"

using namespace chara;

CAMotionGraph::CAMotionGraph(const std::vector<std::string>& listebvh, float distance){
	
	for (auto i : listebvh){
		m_BVH.push_back(BVH(i));
	}
	remplissageGraphe(distance);
}


void CAMotionGraph::remplissageGraphe(float distance){
	for(unsigned int i = 0; i < m_BVH.size(); i++){
		for(unsigned int j =0; j< m_BVH[i].getNumFrame(); j++){
			m_GrapheNode.push_back(CAGrapheNode(i; j; j+1%m_BVH[i].getNumFrame()));
		}
	}

	for (unsigned int k = 0; k < m_GrapheNode.size(); k++){
		CASkeleton CAS_k(m_BVH[m_GrapheNode[k].id_bvh]);
		CAS_k.setPose(m_BVH[m_GrapheNode[k].id_bvh], m_BVH[m_GrapheNode[k].frame]);
		for (unsigned int l = 0; l < m_GrapheNode.size(); l++){
			if(m_GrapheNode[k].id_bvh != m_GrapheNode[l].id_bvh){
				CASkeleton CAS_l(m_BVH[m_GrapheNode[l].id_bvh]);
				CAS_l.setPose(m_BVH[m_GrapheNode[l].id_bvh], m_BVH[m_GrapheNode[l].frame]);
				if(CAS_k.distance(CAS_l)< distance){
						m_GrapheNode[k].ids_next.push_back(l);
				}
			}
		}
	}
}
