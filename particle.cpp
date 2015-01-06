#include particule.h

using namespace math;

Particle::addForce(const Vec3f& af)
{
	F += af;
}

void Particle::computeOneStep(const float dt)
{
	V = V + dt * (F/m);	
	P = P + dt * V;
}

Vec3f Particle::getP()
{
	return P;
}

Vec3f Particle::getV()
{
	return V;
}

Vec3f Particle::getF()
{
	return F;
}

float Particle::getMass()
{
	return mass;
}	
