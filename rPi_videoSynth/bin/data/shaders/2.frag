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

		vec2 position = ( gl_FragCoord.xy / resolution.xy );

		float color = 0.0;
		color  = sin( position.x * (8.0 * CV0) + sin( position.y * 4.0 + time * 3.0 + 3.14 ) );
		color *= sin( position.y * (7.0 * CV0) + sin( position.x * 9.0 + time * 2.0 ) );

		FRAG_COLOR = vec4(color + CV1, color + CV2, color + CV3,1.0);

	}
