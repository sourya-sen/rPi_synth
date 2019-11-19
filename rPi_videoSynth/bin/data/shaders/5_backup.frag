// based on http://www.glslsandbox.com/e#56924.0
#pragma include "headerFrag.glsl"

uniform sampler2D tex;

IN vec4 v_color;
IN vec2 v_texCoord;
IN vec4 v_normal;

uniform float CV0;
uniform float CV1;
uniform float CV2;
uniform float CV3;
uniform float time;
uniform int subSystem;
uniform vec2 resolution;

#define PI 3.14159

//5 - 100 : 1
#define grid 69.0
//0.2 - 0.6 : 0.1 
#define thickness 1.9
//0.0 - 10 : 1.0
#define red 5.0

float rand(vec2 co)
{
  return fract(sin(dot(co.xy, resolution)) * 65000.98432);
}

void main( void )
{

	vec2 v = gl_FragCoord.xy  / (subSystem * 100. + 100.);
	
	v -= time + vec2(sin(v.y) * CV0, cos(v.x) * CV1);
	
	float brightness = fract(rand(floor(v)) + time);
	float hue = fract(rand(floor(v) + 1.) + time);

	brightness *= thickness - length(fract(v) - vec2(thickness, thickness));
	FRAG_COLOR = vec4(brightness * red, hue*brightness*(10.0 - red), 0., 1.0);

}
