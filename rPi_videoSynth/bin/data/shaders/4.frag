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

	float random (in vec2 st) {
	    return fract(sin(dot(st.xy,
	                         vec2(12.9898,78.233)))
	                * 43758.5453123);
	}

	// Value noise by Inigo Quilez - iq/2013
	// https://www.shadertoy.com/view/lsf3WH
	float noise(vec2 st) {
	    vec2 i = floor(st);
	    vec2 f = fract(st);
	    vec2 u = f*f*(3.0-2.0*f);
	    return mix( mix( random( i + vec2(0.0,0.0) ),
	                     random( i + vec2(1.0,0.0) ), u.x),
	                mix( random( i + vec2(0.0,1.0) ),
	                     random( i + vec2(1.0,1.0) ), u.x), u.y);
	}

	mat2 rotate2d(float angle){
	    return mat2(cos(angle),-sin(angle),
	                sin(angle),cos(angle));
	}

	float lines(in vec2 pos, float b){
	    float scale = 15.0;
	    pos *= scale;
	    return smoothstep(0.0,
	                    .5+b*.5,
	                    abs((sin(pos.x*3.1415)+b*2.0))*.5);
	}

	void main() {
	    vec2 st = gl_FragCoord.xy/resolution.xy;
	    st.y *= resolution.y/resolution.x;

	    vec2 pos = st.yx*vec2(sin(time) * .1 , 3.);

	    float pattern = pos.x;

	    // Add noise
	    pos = rotate2d(noise(pos + sin(time/10.))) * pos * noise(vec2(time/100.) * 10. * CV0);

	    // Draw lines
	    pattern = lines(pos, abs(sin(time/10.0)));

	    FRAG_COLOR = vec4(vec3(pattern, pattern * CV1, pattern * CV2), CV3);
	}
