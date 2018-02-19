#ifdef GL_ES
precision mediump float;
#endif

uniform float CVO, CV1, CV2, CV3;
uniform int subSystem;
uniform float time;
uniform vec2 resolution;

void main()
{
    // gl_FragCoord contains the window relative coordinate for the fragment.
    // we use gl_FragCoord.x position to control the red color value.
    // we use gl_FragCoord.y position to control the green color value.
    // please note that all r, g, b, a values are between 0 and 1.

  // float windowWidth = resolution.x;
  // float windowHeight = resolution.y;
  //
	// float r = gl_FragCoord.x / windowWidth;
	// float g = gl_FragCoord.y / windowHeight;
	// float b = 1.0;
	// float a = 1.0;

	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
