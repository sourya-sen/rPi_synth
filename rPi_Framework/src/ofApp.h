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
		int o_system;
		int o_subSystem;
		bool o_draw;
		bool o_fx0, o_fx1;
		float o_cv0, o_cv1, o_cv2, o_cv3;

		ofxOscSender sender;

};
