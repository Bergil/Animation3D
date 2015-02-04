#ifndef __ShallowWater_H__
#define __ShallowWater_H__

#include "Array2D.h"
#define watersize 1.0

class ShallowWater 
{
public:
   ShallowWater();
   //ShallowWater(const int DIMX, const int DIMY);
   ShallowWater(const int DIMX, const int DIMY, const int hauteurWater, float Dtnew);
   //void init(const int DIMX, const int DIMY);
   void init(const int DIMX, const int DIMY, const int hauteurWater, float Dtnew);
   void draw() const;
   void ShallowWaterStep();
   void Advect(Array2D& src, Array2D& dst);
   void UpdateHeight();
   void UpdateVelocities(); 
   void setG(int i, int j, float hauteur) {m_g(i,j) = hauteur;}
   void setN(int i, int j, float hauteur) {m_n(i,j) = hauteur;}
    
   
protected:
   Array2D m_g;     // height of the ground (0 if flat)
   Array2D m_h;     // height of the water : the thing to compute and to draw
   Array2D m_n;     // m_n = m_h - m_g : amount of water above the ground
   Array2D m_n2;
   Array2D m_vX;    // velocity along X   
   Array2D m_vY;    // velocity along Y
   Array2D vyprim; 
   Array2D vxprim;
   float Dt;
};

#endif
