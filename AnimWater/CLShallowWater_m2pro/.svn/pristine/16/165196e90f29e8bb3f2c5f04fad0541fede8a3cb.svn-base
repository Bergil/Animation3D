#version 330
in vec3 vertColor;
in vec3 vertLightDir;
in vec3 vertNormal;
//in vec3 vertTexCoord;

out vec4 fragColor;


void main(void)
{
/*
	float l = length(vertNormal);
	float d = l > 0? dot( normalize(vertNormal), normalize(vertLightDir) ) / l : 0.0;
	float i = 0.1 + 1.2*max(d, 0.0) + 4.2*pow(d, 2.0);
    fragColor = i * vec4( vertColor.xyz, 1.f);
*/

	float l = length(vertNormal);
	float d = l > 0? dot( normalize(vertNormal), normalize(vertLightDir) ) : 0.0;
	float i = 0.1 + 0.9*d;
    fragColor = i * vec4( vertColor.xyz, 1.f);

}
