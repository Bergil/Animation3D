#ifndef _PARTICULE_H_
#define _PARTICULE_H_

class Particle
{
	protected:
		Vec3f P;
		Vec3f V;
		Vec3f F;

	public:
		Particle();
		void addForce(const Vec3f& f);
		void computeOneStep(const float dt);
};


#endif