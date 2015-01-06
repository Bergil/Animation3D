#ifndef _SPRING_H_
#define _SPRING_H_

class Spring
{
public:
   Spring() : p1(NULL), p2(NULL), l0(0.f), k(0.f) {}
   Spring(Particle* _p1, Particle* _p2, const float _l0, const float _k) { set(_p1,_p2,_l0,_k) }
   void set(Particle* _p1, Particle* _p2, const float _l0, const float _k);
   void applyForceToParticles();
protected:
   Particle* p1;
   Particle* p2;
   float l0;
   float k; //raideur
   //float v; //viscosité
};

#endif _SPRING_H_
