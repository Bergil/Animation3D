#include "Tools.h"
#include <math.h>

float convertDegreeToRadian(float degree){
	return (degree/180)*M_PI;
}

float convertRadianToDegree(float radian){
	return (radian*180)/M_PI;
} 
