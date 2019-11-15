//ported from http://www.glslsandbox.com/e#56850.0
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

void main( void ) {

	vec2 uv = (gl_FragCoord.xy * 2.0 - resolution) / min(resolution.x, resolution.y);
	vec2 f = vec2(0.0);
	vec3 c = vec3(CV0);
	float light = 0.0;
	
	for (float x = 0.0; x < 5.0; x += 1.0)
	{
		
		f = vec2(sin(sin(time + uv.x * x) - uv.y * dot(vec2(x + uv.y), vec2(sin(uv.y*x), cos(x)))));
		f*=length(uv);
		light += (CV1 / distance(uv, f)) - (CV2 * distance(vec2((sin(time + uv.y))), vec2(uv)));
		c.y = sin(time + x*x) * CV3 + subSystem/10.;
	}
	
	c *= light;
	
	FRAG_COLOR = vec4(c.x, min(.8, c.y), min(.8, c.z), 1.0);

}
