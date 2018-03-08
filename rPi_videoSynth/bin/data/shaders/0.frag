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

	// void main()
	// {
	// 	float r = gl_gl_FragCoord.x/resolution.x;
	// 	float g = gl_gl_FragCoord.y/resolution.y;
  //
	// 	FRAG_COLOR = vec4(r, g, CV0, 1.0);
	// }


  vec2 random2(vec2 st){
      st = vec2( dot(st,vec2(127.1,311.7)),
                dot(st,vec2(269.5,183.3)) );
      return -1.0 + 2.0*fract(sin(st)*43.54);
  }

  // Value Noise by Inigo Quilez - iq/2013
  // https://www.shadertoy.com/view/lsf3WH
  float noise(vec2 st) {
      vec2 i = floor(st);
      vec2 f = fract(st);

      vec2 u = f*f*(3.0-2.0*f);

      return mix( mix( dot( random2(i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ),
                       dot( random2(i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),
                  mix( dot( random2(i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ),
                       dot( random2(i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y);
  }

  void main() {
      vec2 st = gl_FragCoord.xy/resolution.xy;
      st.x *= resolution.x/resolution.y;
      vec3 color = vec3(0.0);

      float t = 1.0;
      // Uncomment to animate
      t = abs(1.0-sin(time*.1))*5.;
      // Comment and uncomment the following lines:
      st += noise(st*2.)*t; // Animate the coordinate space
      color = vec3(1.) * smoothstep(.18,.2,noise(st)); // Big black drops
      color += smoothstep(.15,.2,noise(st*10.)); // Black splatter
      color -= smoothstep(.35,.4,noise(st*10.)); // Holes on splatter

      FRAG_COLOR = vec4(1.-color,1.0);
  }
