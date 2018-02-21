This folder contains the shaders to run the program.
To make it cross platform and run tests from the Mac, there are unique header files needed for all platforms.
These files are not tracked by git and you have to make sure they exist here.

Make two files, one called `headerFrag.glsl` and another called `headerVert.glsl`.

If you're on a desktop, the `headerVert` will look like this:

````
#version 330
#define IN in
#define OUT out
#define TEXTURE texture
#define FRAG_COLOR fragColor
out vec4 fragColor;
````

And the `headerFrag` will look like this:

````
#version 330
#define IN in
#define OUT out
#define TEXTURE texture
#define FRAG_COLOR fragColor
out vec4 fragColor;
````

If you're on the Pi, then the `headerVert` will look like this:
````
precision highp float
#define IN attribute
#define OUT varying
#define TEXTURE texture2D
#define FRAG_COLOR gl_FragColor
````

And `headerFrag` should be"
````
precision highp float
#define IN attribute
#define OUT varying
#define TEXTURE texture2D
#define FRAG_COLOR gl_FragColor
````

To write cross platform shaders, please follow the definitions in the header files, ie, no attributes or ins but use IN, no varying or out but OUT and so on and so forth.
