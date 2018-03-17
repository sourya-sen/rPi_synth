#pragma once

#include "ofMain.h"
#include "ofxGPIO.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

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

		MCP a2d;
		MCP_DESC chip = MCP3008;
		vector<int> analogIn;

		GPIO gpio14, gpio15, gpio17, gpio18;
		vector<string> mux;

		//these will be sent over OSC
		int o_system, lastSystem;
		int o_subSystem;
		bool o_fx0, o_fx1, o_fx2;
		vector<float> o_cv;

		ofxOscMessage cv;
		ofxOscMessage gates;
		ofxOscSender sender;

};
