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

	// void main()
	// {
	// 	float r = gl_gl_FragCoord.x/resolution.x;
	// 	float g = gl_gl_FragCoord.y/resolution.y;
  //
	// 	FRAG_COLOR = vec4(r, g, CV0, 1.0);
	// }


vec3 fade(vec3 x) { return x * x * x * (x * (x * 6. - 15.) + 10.); }

vec3 phash(vec3 p)
{
	p = fract(mat3(1.2989833, 7.8233198, 2.3562332,
	            	6.7598192, 3.4857334, 8.2837193,
	                2.9175399, 2.9884245, 5.4987265) * p);
	p = ((2384.2345 * p - 1324.3438) * p + 3884.2243) * p - 4921.2354;
	return normalize(fract(p) * 2. - 1.);
}

float noise(vec3 p)
{
	vec3 ip = floor(p);
	vec3 fp = fract(p);
	float d000 = dot(phash(ip), fp) * CV0;
	float d001 = dot(phash(ip + vec3(0., 0., 1.)), fp - vec3(0., 0., 1.));
	float d010 = dot(phash(ip + vec3(0., 1., 0.)), fp - vec3(0., 1., 0.));
	float d011 = dot(phash(ip + vec3(0., 1., 1.)), fp - vec3(0., 1., 1.));
	float d100 = dot(phash(ip + vec3(1., 0., 0.)), fp - vec3(1., 0., 0.));
	float d101 = dot(phash(ip + vec3(1., 0., 1.)), fp - vec3(1., 0., 1.));
	float d110 = dot(phash(ip + vec3(1., 1., 0.)), fp - vec3(1., 1., 0.));
	float d111 = dot(phash(ip + vec3(1., 1., 1.)), fp - vec3(1., 1., 1.));
	fp = fade(fp);
	return mix(mix(mix(d000, d001, fp.z), mix(d010, d011, fp.z), fp.y),
	               mix(mix(d100, d101, fp.z), mix(d110, d111, fp.z), fp.y), fp.x);
}

void main(void)
{
	vec3 p = vec3(gl_FragCoord.xy * (10. * CV0 + .3) / resolution.y, time * CV1);
	FRAG_COLOR = vec4(noise(p) / 2. + 0.1 + CV2 + CV3/2.);
}
