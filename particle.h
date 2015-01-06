#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <Vec3.h>
#include <math.h>


class Particle
{
	protected:
		math::Vec3f P; //Position
		math::Vec3f V; //Vitesse
		math::Vec3f F; //Force
		float mass; //Poids

	public:
		Particle(const float _mass, const math::Vec3f _p) : P(_p), V(0,0,0), F(0,0,0), mass(_mass) {}
		void addForce(const math::Vec3f& af);
		void computeOneStep(const float dt);        // mise à jour de la position et de la vitesse en fonction de f et de dt

		math::Vec3f getP();
		math::Vec3f getV();
		math::Vec3f getF();
		float getMass();
};


#endif
