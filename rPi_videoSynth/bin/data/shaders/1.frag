#pragma include "headerFrag.glsl"
//modified from http://glslsandbox.com/e#46602.0

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

	float noise(float v, float amplitude, float frequency, float time) {
	float r = sin(v * frequency);
	float t = 0.01*(-time*130.0);
	r += sin(v*frequency*2.1 + t)*4.5;
	r += sin(v*frequency*1.72 + t*1.121)*4.0;
	r += sin(v*frequency*2.221 + t*0.437)*5.0;
	r += sin(v*frequency*3.1122+ t*4.269)*2.5;
	r *= amplitude*0.06;

	return r;
	}

	float circle(in vec2 _st, in float _radius){
    vec2 dist = _st-vec2(0.0);
		return 1.-smoothstep(_radius-(_radius*0.1), _radius+(_radius*0.1), dot(dist,dist)*4.0);
	}

	void main()
	{
		vec2 position = ( gl_FragCoord.xy / resolution.xy );
		position.x -= 0.5;
		position.y -= 0.5;

		position.x *= resolution.x/resolution.y;

		vec3 color = vec3(0.0, 0.0, 0.0);

		color = vec3(circle(position, CV0));

		if(subSystem == 0){
			//color += noise(position.x, 1.0, 1.0, time);
			color.xyz *= noise(position.y, 100.0 * CV1, 100.0 * CV2, time * CV3);
		} else if (subSystem == 1){
			color.xyz += noise(position.x, 1.0 * CV1, 10.0 * CV2, time * CV3);
		} else if (subSystem == 2){
			color += noise(position.x, 1.0 * CV1, 1.0 * CV2, time * CV3);
			color *= noise(position.y, 1.0 * CV1, 1.0 * CV2, time * CV3);
		} else if (subSystem == 3){
			color.xyz *= noise(position.y, 100.0 * CV1, 100.0 * CV2, time * CV3);
		}

		FRAG_COLOR = vec4(color, 1.0);
	}
