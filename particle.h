#ifndef _PARTICULE_H_
#define _PARTICULE_H_

class Particle
{
public:
   Particle(const float _mass, const Vec3f _p) : mass(_mass), p(_p), v(0,0,0), v(0,0,0) {}
   void addForce(const Vec3f& af);
   void computeOneStep(const float dt);        // mise à jour de la position et de la vitesse en fonction de f et de dt
   
protected:
   float mass;
   Vec3f p; //position
   Vec3f v; //vitesse
   Vec3f f; //force
};


#endif
