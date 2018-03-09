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

	void main()
	{
		vec2 r = resolution,
		o = (gl_FragCoord.xy - .5*r) / r.y * min(0.3, CV3);
		float p = (.5+floor(5.*o.x)) * CV0;
		o.x = mod(o.x, .2) - .1;
		o.y+=p * CV2;
		vec4 s = .1*cos(1.6*vec4(0,1,2,3)+p*.3*time+sin(o.y*4.+p*3.+cos(time))),
		e = s.yzwx,
		f = min(o.x-s,e-o.x);
		FRAG_COLOR = dot(clamp(-1.+f*r.y,0.,1.),40.*(s-e))*(s-.21)+f*5.0*CV1;
	}
