#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

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
    
    ofxPanel gui;
    ofxLabel Pots, CV, System, SubSystem, FX;
   
    ofxFloatSlider pot0, pot1, pot2, pot3;
    ofxFloatSlider cv0, cv1, cv2, cv3;
    
    ofxToggle gate0, gate1, gate2, gate3, gate4, gate5, gate6, gate7;
    
    ofxOscSender sender;
		
};
