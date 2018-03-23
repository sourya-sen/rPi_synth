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
  	//usleep(100);

	}

  //......................................
  int max = 1023 * 1023;

  ofxOscMessage cv;
  cv.setAddress("/cv");

  for(int i = 0; i < o_cv.size(); i++){
    o_cv[i] = ofMap(analogIn[i] * analogIn[i+4], 0, max, 0, 1.0f);
    cv.addFloatArg(o_cv[i]);
  }

  sender.sendMessage(cv, true);


  //sending gate/triggers in one OSC message.
  //.........................................
  ofxOscMessage gates;
  gates.setAddress("/gates");

  for(int i = 0; i < mux.size(); i++){
    int value = ofToInt(mux[i]);
    gates.addIntArg(value);
  }

  sender.sendMessage(gates, true);

}

//--------------------------------------------------------------
void ofApp::draw(){
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
