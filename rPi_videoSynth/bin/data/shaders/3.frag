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

	float getColor(float d, float rad, float t, float offset) {

	float v = 0.0;
	for(int i = 1; i < 10; i++) {
		v += (sin(rad * float(i) + t / pow(float(i), 2.0) + float(i) + offset) * 0.5 + 0.5) * pow(0.5, float(i));
	}
	v = 1.0 - smoothstep(v, v + 0.27, d);
	return v;
}

void main( void ) {

	vec2 st = gl_FragCoord.xy / min(resolution.x, resolution.y) * 2.0 - resolution.xy / min(resolution.x, resolution.y);

	float d = length(st);
	float rad = atan(st.y, st.x);
	float t = time * max(1.0, 5.0 * CV0);

	float r = getColor(d, rad, t, -0.125);
	float g = getColor(d, rad, t,  0.27);
	float b = getColor(d, rad, t,  0.54);

	FRAG_COLOR = vec4(r, g,  b, 1.0);

}
