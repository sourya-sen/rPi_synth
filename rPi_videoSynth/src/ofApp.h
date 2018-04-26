#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ControlVoltage.h"

#define PORT 12345
#define WIDTH 1024
#define HEIGHT 768

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void sendUniforms(ofShader * _shader);
    void runSystem(int _sys);
    
    void loadShaders();
    
    ofxOscReceiver receiver;
    
    vector<int> gateIn;
    vector<ControlVoltage> CV;
    int system, subSystem;
    int lastSystem;
    bool fx0, fx1, fx2;

    bool debugMode;
    bool keyboardMode;
    
    vector<ofShader> shaders;
    ofShader * selectedShader;
    
    ofFbo mainImage;
    ofFbo whiteStrobe;
    ofFbo invertedImage;
		
};
