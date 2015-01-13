
#version 330
uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;
uniform vec3 LightPos;
uniform sampler2D TexUnit;
uniform int NormalType;

in vec4 Position;
in vec2 TexCoord;
in vec3 Normal;
in vec3 Color;

out vec3 vertColor;
out vec3 vertLightDir;
out vec3 vertNormal;

void main(void)
{
	float y;
	vertColor = Color;
	vec2 D = vec2(TexCoord.x+1, TexCoord.y);
	vec2 G = vec2(TexCoord.x-1, TexCoord.y);
	vec2 H = vec2(TexCoord.x, TexCoord.y+1);
	vec2 B = vec2(TexCoord.x, TexCoord.y-1);
	
	gl_Position = Position;

	if (NormalType==0) vertNormal = vec3(0,0,0);
	if (NormalType==1) vertNormal = Normal;
	else
	{
		y = texture( TexUnit, TexCoord ).r;
		gl_Position.y += y;
		//vertNormal = vec3(0,1,0);	// aie aie aie il manque le calcul de la normale
		vec3 x = vec3( 2, texture( TexUnit, D ).r-texture( TexUnit, G ).r, 0);
		vec3 y = vec3( 0, texture( TexUnit, H ).r-texture( TexUnit, B ).r, 2);
		vertNormal = cross( normalize(y), normalize(x) );
	}
	
	vertLightDir = LightPos - gl_Position.xyz;
	gl_Position = ProjectionMatrix * CameraMatrix * ModelMatrix * gl_Position;
	//vertNormal = (ProjectionMatrix * CameraMatrix * ModelMatrix * (Position+vertNormal))- gl_Position;

	//gl_PointSize = 4.0 * gl_Position.w / gl_Position.z;
}
