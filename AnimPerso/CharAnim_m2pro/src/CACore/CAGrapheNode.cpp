 #include "CAGrapheNode.h"
 
 namespace chara {
	 CAGrapheNode::CAGrapheNode(int BVH_ID, int num_frame, int next): id_bvh(BVH_ID), frame(num_frame){
		 
		 ids_next.push_back(next);
	}
}
