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
		float r = gl_FragCoord.x/1024.0;
		float g = gl_FragCoord.y/768.0;

		FRAG_COLOR = vec4(r, g, CV0, 1.0);
	}
