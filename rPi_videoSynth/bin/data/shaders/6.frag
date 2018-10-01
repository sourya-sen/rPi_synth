#pragma include "headerFrag.glsl"
//Modified from http://glslsandbox.com/e#48925.0

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

	mat2 rotate(float a) {
	float c = cos(a), s = sin(a);
	return mat2(c, -s, s, c);
	}

void main() {
	vec2 uv = (2. * gl_FragCoord.xy - resolution) / resolution.y;
	vec3 color = vec3(0.9);
	uv *= rotate(time) * rotate(CV3 * time);
	uv = abs(uv);
	vec2 ar = vec2(sin(atan(uv.x, uv.y)) * CV1, length(uv));
	color = mix(color, vec3(.4, 0., .7) * CV2, sin(8. * (ar.y * 1. - time * CV0) + time * CV0) + (8. * ar.x - 8. * ar.y));
	color = mix(color, vec3(.7, .2, 0.), cos(8. ) * (5. * ar.y - 8. * ar.x));
	FRAG_COLOR = vec4(1.0 - color, 1.);
}
