//ported from The Book of Shaders
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

#define PI 3.14159


vec2 rotate2D (vec2 _st, float _angle) {
    _st -= 0.5;
    _st =  mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle)) * _st;
    _st += 0.5;
    return _st;
}

vec2 tile (vec2 _st, float _zoom) {
    _st *= _zoom;
    return fract(_st);
}

vec2 rotateTilePattern(vec2 _st){

    //  Scale the coordinate system by 2x2
    _st *= 2.0 * CV3;

    //  Give each cell an index number
    //  according to its position
    float index = 1.0;
    index *= float(subSystem);

    float modx = mod(_st.x, 2.0);
    float mody = mod(_st.y, 2.0);

    index += step(1.0, modx);
    index += step(1.0, mody);

    //      |
    //  2   |   3
    //      |
    //--------------
    //      |
    //  0   |   1
    //      |

    // Make each cell between 0.0 - 1.0
    _st = fract(_st);

    // Rotate each cell according to the index
    if(index == 1.0){
        //  Rotate cell 1 by 90 degrees
        _st = rotate2D(_st*CV1,PI*0.5*time * .1);
    } else if(index == 2.0){
        //  Rotate cell 2 by -90 degrees
        _st = rotate2D(_st*CV2,PI*-0.5*time * .2);
    } else if(index == 3.0){
        //  Rotate cell 3 by 180 degrees
        _st = rotate2D(_st/(CV1 + CV2),PI*time * .4);
    }

    return _st;
}

void main () {
    vec2 st = gl_FragCoord.xy/resolution.xy;

    float s = 3.0 * CV0;

    st = tile(st, s);
    st = rotateTilePattern(st);

    // Make more interesting combinations
    float n = 2.0 * float(subSystem);
    st = tile(st, max(0.1, n));
    // st = rotate2D(st,-PI*time*0.25);
    // st = rotateTilePattern(st*2.);
    // st = rotate2D(st,PI*time*0.25);

    // step(st.x,st.y) just makes a b&w triangles
    // but you can use whatever design you want.
    FRAG_COLOR = vec4(vec3(step(st.x,st.y)).r, 0.0, 0.0,1.0);
}
