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

float ball(vec2 p, float fx, float fy, float ax, float ay) {
	vec2 r = vec2(p.x + sin(time * fx) * ax * CV0, p.y + cos(time * fy) * ay * CV1);
	return abs(0.2 * min(0.4, 2. * CV3) / length(r));
}

void main(void) {
	vec2 q = gl_FragCoord.xy / resolution.xy;
	vec2 p = -1.0 + 2.0 * q;
	p.x	*= resolution.x / resolution.y;

	float col = 0.0;
	//col += ball(p, 2.0, 3.0, 4.1, 5.2);
	col += ball(p, 1.5 * float(subSystem + 1.0), 2.5, 0.2, 0.3);
	col += ball(p, 1.0, 4.0, 0.5 * float(subSystem + 2.0), 0.4);
	col += ball(p, 2.5, 3.5, 0.4, 0.5);
	col += ball(p, 3.0, 4.0, 0.5, 0.6);
	col += ball(p, 1.5, 0.5, 0.6, 0.7 * float(subSystem));
	col += ball(p, 0.1 * float(subSystem + 3.0), .5, 0.6, 0.7);

	col = max(mod(col, 0.4), min(col, 0.9));

	FRAG_COLOR = vec4(1.0, max(col * CV2, 0.3), max(col * CV2, 0.3), 1.0);
}
