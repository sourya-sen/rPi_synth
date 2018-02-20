#pragma include "version.glsl"

#ifdef GLES
		precision mediump float;
		#define IN attribute
		#define OUT varying
		#define TEXTURE texture2D
		#define FRAG_COLOR gl_FragColor
#else
		// #version 330
		#define IN in
		#define OUT out
		#define TEXTURE texture
 		#define FRAG_COLOR fragColor
		out vec4 fragColor
#endif

	// uniform mat4 projectionMatrix;
	uniform mat4 modelViewMatrix;
	uniform mat4 textureMatrix;
	uniform mat4 modelViewProjectionMatrix;

	IN vec4  position;
	IN vec2  texcoord;
	IN vec4  color;
	IN vec3  normal;

	OUT vec4 v_color;
  OUT vec2 v_texCoord;
  OUT vec4 v_normal;

	void main()
	{
		v_color = color;
		v_texCoord = texcoord;
		gl_Position = modelViewProjectionMatrix * position;
	}
