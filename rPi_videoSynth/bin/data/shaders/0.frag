#pragma include "headerFrag.glsl"
		//original code from http://glslsandbox.com/e#45360.0

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

	void main()
	{
	    vec2 r = resolution,
	    o = gl_FragCoord.xy - r/2.;
	    o = vec2(length(o) / r.y - (.1 + .3 * CV3), atan(o.y,o.x));
	    vec4 s = 0.07*cos(1.5*vec4(subSystem, subSystem + 1, subSystem +2, subSystem + 3) + time + o.y + cos(o.y) * cos(time)),
	    e = s.yzwx,
	    f = max(o.x-s,e-o.x);
	    FRAG_COLOR = dot(clamp(f*r.y,0.,(1. + 2.0 * CV2)), (50.0 + 50.0 * CV1)*(s-e)) * (s-(.1 * CV0));
	}
