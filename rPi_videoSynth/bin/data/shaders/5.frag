#pragma include "headerFrag.glsl"
// based on http://glslsandbox.com/e#47766.0

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

	void main( void ) {

		vec2 p = ( gl_FragCoord.xy / resolution.xy ) - 0.5;
		float sx = 0.2 * (p.x + 0.5) * sin( 25.0 * p.x - 10. * time);
		float dy = 1./ ( 20. * abs(p.y - sx));
		dy += 1./ (20. * length(p - vec2(p.x, 0.)));
		FRAG_COLOR = vec4( (p.x + 0.5) * dy, 0.5 * dy, dy, 1.0 );

	}
