#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    receiver.setup(PORT);
    
    CV.resize(4);
    fx0 = false;
    fx1 = false;
    fx2 = false;
    
    system = 0;
    subSystem = 0;
    
    debugMode = true;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // check for mouse moved message
        if(m.getAddress() == "/sys"){
            system = m.getArgAsInt(0);
        } else if (m.getAddress() == "/subSys") {
                system = m.getArgAsInt(0);
        } else if (m.getAddress() == "/fx0"){
            fx0 = m.getArgAsBool(0);
        } else if (m.getAddress() == "/fx1"){
            fx1 = m.getArgAsBool(0);
        } else if (m.getAddress() == "fx2"){
            fx2 = m.getArgAsBool(0);
        } else if (m.getAddress() == "/cv0"){
            CV[0] = m.getArgAsFloat(0);
        } else if (m.getAddress() == "/cv1"){
            CV[1] = m.getArgAsFloat(0);
        } else if (m.getAddress() == "/cv2"){
            CV[2] = m.getArgAsFloat(0);
        } else if (m.getAddress() == "/cv3"){
            CV[3] = m.getArgAsFloat(0);
        }
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(debugMode){
        ofDrawBitmapStringHighlight("System: " + ofToString(system), 10, 15);
        ofDrawBitmapStringHighlight("Sub System: " + ofToString(subSystem), 10, 30);
        ofDrawBitmapStringHighlight("FXs:" + ofToString(fx0) + " " + ofToString(fx1) + " " + ofToString(fx2), 10, 45);

    }

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
