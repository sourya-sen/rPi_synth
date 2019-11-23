//ported from http://www.glslsandbox.com/e#57084.0
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
		vec3 redColor = vec3(1.0,0.0,0.0);
    vec3 greenColor = vec3(0.9, 0.0, 0.0);
		float s = 1.0;
		s *= float(subSystem);
    vec3 blueColor = vec3((mod(s, 2.0)))/10.0;
    vec3 yellowColor = vec3(s/4.0, s/4.0, s/4.0);


    vec2 p = (gl_FragCoord.xy*2.0-resolution);
    p /= min(resolution.x,resolution.y);

    float a = cos(p.y*1.5 - time*0.5)/1.0 * CV0;
    float b = cos(p.y*1.5 - time*0.2)/1.0 * CV1;
    float c = sin(p.y*1.5 - time*0.3 + 3.14)/1.0 * CV2;
    float d = cos(p.y*1.5 - time*0.5 + 3.14)/1.0 * CV3;

    float e = 0.2 / abs(p.x + a);
    float f = 0.1 / abs(p.x + b);
    float g = 0.1 / abs(p.x + c);
    float h = 0.1 / abs(p.x + d);

    vec3 destColor = redColor * e + greenColor * f + blueColor * g + yellowColor * h;
    FRAG_COLOR = vec4(destColor,1.0);
}
