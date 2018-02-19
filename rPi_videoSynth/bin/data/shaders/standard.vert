// #ifdef GL_ES
// precision mediump float;
// #endif

attribute vec4 position;
uniform mat4 modelViewProjectionMatrix;

void main(){
	gl_Position = modelViewProjectionMatrix * position;
}
