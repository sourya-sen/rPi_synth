#pragma include "headerFrag.glsl"
uniform sampler2D tex;

	IN vec4 v_color;
  	IN vec2 v_texCoord;
  	IN vec4 v_normal;

	uniform float time;
	uniform int subSystem;
	uniform vec2 resolution;

    void main(){
        vec4 image = TEXTURE(tex, v_texCoord.xy);
        FRAG_COLOR = vec4(1. - image.r, 1. - image.g, 1. - image.b, 1.0);
    }