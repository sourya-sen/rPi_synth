#pragma include "headerFrag.glsl"

	uniform sampler2D tex;
	IN vec4 v_color;
  IN vec2 v_texCoord;
  IN vec4 v_normal;

	void main()
	{
		FRAG_COLOR = vec4(1.0, 0.0, 0.0, 1.0);
	}
