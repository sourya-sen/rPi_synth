#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  a2d.setup("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);

  analogIn.resize(8);
	ofSetBackgroundColor(0);

	gpio14.setup("14");
	gpio14.export_gpio();
	gpio14.setdir_gpio("out");

	gpio15.setup("15");
	gpio15.export_gpio();
	gpio15.setdir_gpio("out");

	gpio18.setup("18");
	gpio18.export_gpio();
	gpio18.setdir_gpio("out");

	gpio17.setup("17");
	gpio17.export_gpio();
	gpio17.setdir_gpio("in");

	mux.resize(8);

	for(auto &m : mux){
		m = "0";
	}

  o_cv.resize(4);
  sender.setup(HOST, PORT);

}

//--------------------------------------------------------------
void ofApp::update(){

  for(int i = 0; i < chip; i++){
	   if(i<4){
	      analogIn[i] = 1023 - a2d.getValueAllChannel(chip)[i]; //fix potentiometer wired the wrong way by inverting the value :P
	     } else {
	        analogIn[i] = a2d.getValueAllChannel(chip)[i];
	       }
      usleep(100);
    }

  int r0 [] = {0, 1, 0, 1, 0, 1, 0, 1};
  int r1 [] = {0, 0, 1, 1, 0, 0, 1, 1};
  int r2 [] = {0, 0, 0, 0, 1, 1, 1, 1};

  for(int i = 0; i< mux.size(); i++){

	gpio14.setval_gpio(ofToString(r0[i]));
	gpio15.setval_gpio(ofToString(r1[i]));
	gpio18.setval_gpio(ofToString(r2[i]));

	gpio17.getval_gpio(mux[i]);
	usleep(100);
	}

  o_system = ofBinaryToInt(ofToString(100 * ofToInt(mux[0]) + 10 * ofToInt(mux[1]) + ofToInt(mux[2])));
  o_subSystem = ofBinaryToInt(ofToString(10 * ofToInt(mux[3]) + ofToInt(mux[4])));

  if(mux[5] == "1"){
    o_fx0 = true;
  } else {
    o_fx0 = false;
  }

  if(mux[6] == "1"){
    o_fx1 = true;
  } else {
    o_fx1 = false;
  }

  if(mux[7] == "1"){
    o_fx2= true;
  } else {
    o_fx2 = false;
  }


  int max = 1023 * 1023;

  for(int i = 0; i< o_cv.size(); i++){
    o_cv[i] = ofMap(analogIn[i] * analogIn[i+4], 0, max, 0, 1.0f);
  }

  //Let's send everything over OSC :)
  //TODO: SEND ONLY IF THEY'RE NEW VALUES -> Add checks!

  ofxOscMessage system;
  system.setAddress("/sys");
  system.addIntArg(o_system);
  sender.sendMessage(system, false);

  ofxOscMessage subSystem;
  subSystem.setAddress("/subSys");
  subSystem.addIntArg(o_subSystem);
  sender.sendMessage(subSystem, false);

  for(int i = 0; i<o_cv.size(); i++){
    ofxOscMessage cv;
    cv.setAddress("/cv" + ofToString(i));
    cv.addFloatArg(o_cv[i]);
    sender.sendMessage(cv, false);
  }

  ofxOscMessage fx0;
  fx0.setAddress("/fx0");
  fx0.addBoolArg(o_fx0);
  sender.sendMessage(fx0, false);

  ofxOscMessage fx1;
  fx1.setAddress("/fx1");
  fx1.addBoolArg(o_fx1);
  sender.sendMessage(fx1, false);

  ofxOscMessage fx2;
  fx2.setAddress("/fx2");
  fx2.addBoolArg(o_fx2);
  sender.sendMessage(fx2, false);
/*    
    if(ofGetElapsedTimeMillis()%1000 == 0){
        cout << "system: " << system << endl;
        cout << "subsytem" << subSystem << endl;
        cout << "FX: " << fx0 << " " << fx1 << " " << fx2 << endl;
    }
*/

}

//--------------------------------------------------------------
void ofApp::draw(){
/*
  for(int i = 0; i < analogIn.size(); i++){
		float spacing = (ofGetWidth()/2)/float(analogIn.size());
		ofDrawBitmapStringHighlight(ofToString(analogIn[i]), i * spacing + 20, 10);
	}

	for(int i = 0; i< mux.size(); i++){
		float spacing = (ofGetWidth()/2)/float(mux.size());
		ofDrawBitmapStringHighlight(ofToString(mux[i]), i * spacing + 20, 30);
	}

  ofDrawBitmapStringHighlight(ofToString(o_cv[0]), 0, ofGetHeight() - 20);
*/


	stringstream buf1, buf2;

  buf1 << "CVs: " << o_cv[0] << " - " << o_cv[1] << " - " << o_cv[2] << " - " << o_cv[3] << endl;
  buf2 << "Triggers: " << mux[0] << mux[1] << mux[2] << mux[3] << mux[4] << mux[5] << mux[6] << mux[7] << endl;

ofDrawBitmapStringHighlight(buf1.str(), 20, 20);
ofDrawBitmapStringHighlight(buf2.str(), 20, 35);
}

//--------------------------------------------------------------
void ofApp::exit(){

  a2d.quit();

  gpio14.unexport_gpio();
	gpio15.unexport_gpio();
	gpio18.unexport_gpio();
	gpio17.unexport_gpio();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
