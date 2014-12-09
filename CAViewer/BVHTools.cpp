#include "BVHTools.h"

using namespace chara;
using namespace std;

float calculDistanceEntrePoses(const BVH& bvhA, const int frameNbA, const BVH& bvhB, const int frameNbB){
// Pour toutes les articulations, pour tous les channels, faire D = D+(angleA-angleB)^2
	float D = 0.0;	
	for(int j = 0; j < bvhA.getNumJoint(); j++){
		for(int i = 0; i < bvhA.getJoint(j)->getNumChannel(); i++){
			chara::BVHChannel* chanA = bvhA.getJoint(j)->getChannel(i);
			chara::BVHChannel* chanB = bvhB.getJoint(j)->getChannel(i);
			if(chanA->isRotation() && chanB->isRotation()){
				D = D + (chanA->getData(frameNbA)-chanB->getData(frameNbB)) * (chanA->getData(frameNbA)-chanB->getData(frameNbB));
			}
		}
	}
	
	return D;
}
