#include "ofMain.h"
#include "ofApp.h"

int main( ){
#ifdef TARGET_OPENGLES
    ofGLESWindowSettings settings;
    settings.glesVersion = 2;
    settings.windowMode = OF_FULLSCREEN;
#else
    ofGLWindowSettings settings;
    settings.setGLVersion(3,3);
    settings.windowMode = OF_WINDOW;
#endif
    
    settings.width = 1024;
    settings.height = 768;
   
    ofCreateWindow(settings);
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
    
}
