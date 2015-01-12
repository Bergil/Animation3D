
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <time.h>
#include <BVH.h>
#include <Mat4.h>

#include <chrono>
#include <BVHJoint.h>
#include <Vec3.h>


float calculDistanceEntrePoses(const chara::BVH& bvhA, const int frameNbA, const chara::BVH& bvhB, const int frameNbB);
// Pour toutes les articulations, pour tous les channels, faire D = D+(angleA-angleB)^2
