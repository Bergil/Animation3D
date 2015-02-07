#include "CAMotionGraph.h"

using namespace chara;

CAMotionGraph::CAMotionGraph(const std::vector<std::string>& listebvh, float distance){
	
	for (auto i : listebvh){
		m_BVH.push_back(std::unique_ptr<BVH>(new BVH(i)));
	}
	remplissageGraphe(distance);
}


void CAMotionGraph::remplissageGraphe(float distance){
	for(unsigned int i = 0; i < m_BVH.size(); i++){
		unsigned int size = m_GrapheNode.size();
		for(int j =0; j< m_BVH[i].get()->getNumFrame(); j++){
			m_GrapheNode.push_back(CAGrapheNode(i, j, (size+j+1)%m_BVH[i].get()->getNumFrame()));
		}
	}

	for (unsigned int k = 0; k < m_GrapheNode.size(); k++){
		CASkeleton CAS_k(*m_BVH[m_GrapheNode[k].getIdBVH()].get());
		CAS_k.setPose(*m_BVH[m_GrapheNode[k].getIdBVH()].get(), m_GrapheNode[k].getNumFrame());
		for (unsigned int l = 0; l < m_GrapheNode.size(); l++){
			if(m_GrapheNode[k].getIdBVH() != m_GrapheNode[l].getIdBVH()){
				CASkeleton CAS_l(*m_BVH[m_GrapheNode[l].getIdBVH()].get());
				CAS_l.setPose(*m_BVH[m_GrapheNode[l].getIdBVH()].get(), m_GrapheNode[l].getNumFrame());
				if(CAS_k.distance(CAS_l)< distance){
						m_GrapheNode[k].getListIdNext().push_back(l);
				}
			}
		}
	}
}
