#ifdef GLES
		precision mediump float;
		#define IN attribute
		#define OUT varying
		#define TEXTURE texture2D
		#define FRAG_COLOR gl_FragColor
#else
		#version 330
		#define IN in
		#define OUT out
		#define TEXTURE texture
 		#define FRAG_COLOR fragColor
		out vec4 fragColor
#endif
	uniform sampler2D tex;
	IN vec4 v_color;
  IN vec2 v_texCoord;
  IN vec4 v_normal;

	void main()
	{
		FRAG_COLOR = vec4(1.0, 0.0, 0.0, 1.0);
	}
