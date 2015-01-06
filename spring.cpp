#include "spring.h"

using namespace math;

void Spring::set(Particle* _p1, Particle* _p2, const float _l0, const float _k){
	p1 = _p1;
	p2 = _p2
	l0 = _l0;
	k = _k;
}

void Spring::applyForceToParticles(){
	Vec3f f1 = k*(((p1.getP()-p2.getP()) - l0) /l0);
	Vec3f f2 = k*(((p2.getP()-p1.getP()) - l0) /l0);
	p1.addForce(f1);
	p2.addForce(f2);
}
