#include "particle.h"

using namespace math;

void Particle::addForce(const Vec3f& af)
{
	F += af;
}

void Particle::computeOneStep(const float dt)
{
	V = V + dt * (F/mass);	
	P = P + dt * V;
	F = Vec3f(0.0, 0.0, 0.0);
}

Vec3f Particle::getP() const
{
	return P;
}

Vec3f Particle::getV() const
{
	return V;
}

Vec3f Particle::getF() const
{
	return F;
}

float Particle::getMass() const
{
	return mass;
}	
