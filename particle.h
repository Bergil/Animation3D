#ifndef _PARTICLE_H_
#define _PARTICLE_H_

class Particle
{
	protected:
		Vec3f P; //Position
		Vec3f V; //Vitesse
		Vec3f F; //Force
		float mass; //Poids

	public:
		Particle(const float _mass, const Vec3f _p) : mass(_mass), p(_p), v(0,0,0), v(0,0,0) {}
		void addForce(const Vec3f& af);
		void computeOneStep(const float dt);        // mise à jour de la position et de la vitesse en fonction de f et de dt

		Vec3f getP();
		Vec3f getV();
		Vec3f getF();
		float getMass();
};


#endif