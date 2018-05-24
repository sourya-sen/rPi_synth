#include "ofApp.h"

//--------------------------------------------------------------
static int bToD(unsigned num){
    unsigned res = 0;
    
    for(int i = 0; num > 0; ++i){
        if((num % 10) == 1) res += (1 << i);
        num /= 10;
    }
    
    return res;
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundColor(0);
    
    gui.setup();
    
    gui.add(Pots.setup("Potentiometers", "0 to 1"));
    Pots.setBackgroundColor(ofColor::darkRed);
    gui.add(pot0.setup("POT0", 0, 0.0, 1.0));
    gui.add(pot1.setup("POT1", 0, 0.0, 1.0));
    gui.add(pot2.setup("POT2", 0, 0.0, 1.0));
    gui.add(pot3.setup("POT3", 0, 0.0, 1.0));
    
    gui.add(CV.setup("CVs", "-5V to 5V"));
    CV.setBackgroundColor(ofColor::darkRed);
    gui.add(cv0.setup("CV0", 5.0, -5.0, 5.0));
    gui.add(cv1.setup("CV1", 5.0, -5.0, 5.0));
    gui.add(cv2.setup("CV2", 5.0, -5.0, 5.0));
    gui.add(cv3.setup("CV3", 5.0, -5.0, 5.0));
    
    gui.add(System.setup("System", ""));
    System.setBackgroundColor(ofColor::darkRed);
    gui.add(gate0.setup("SYS0", false));
    gui.add(gate1.setup("SYS1", false));
    gui.add(gate2.setup("SYS2", false));
    
    gui.add(SubSystem.setup("SubSystem", ""));
    SubSystem.setBackgroundColor(ofColor::darkRed);
    gui.add(gate3.setup("SUBSYSTEM0", false));
    gui.add(gate4.setup("SUBSYSTEM1", false));
    
    gui.add(FX.setup("FX", ""));
    FX.setBackgroundColor(ofColor::darkRed);
    gui.add(gate5.setup("FX0 (DISABLED)", false));
    gui.add(gate6.setup("FX1 (WHITE STROBE)", false));
    gui.add(gate7.setup("FX2 (ENABLE)", true));
    
    sender.setup(HOST, PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofxOscMessage cv;
    cv.setAddress("/cv");
    
    cv.addFloatArg(pot0);
    cv.addFloatArg(pot1);
    cv.addFloatArg(pot2);
    cv.addFloatArg(pot3);
    
    cv.addFloatArg(ofMap(cv0, -5.0, 5.0, 0.0, 1.0));
    cv.addFloatArg(ofMap(cv1, -5.0, 5.0, 0.0, 1.0));
    cv.addFloatArg(ofMap(cv2, -5.0, 5.0, 0.0, 1.0));
    cv.addFloatArg(ofMap(cv3, -5.0, 5.0, 0.0, 1.0));
    
    sender.sendMessage(cv, true);
    
    ofxOscMessage gates;
    gates.setAddress("/gates");
    
    gates.addBoolArg(gate0);
    gates.addBoolArg(gate1);
    gates.addBoolArg(gate2);
    gates.addBoolArg(gate3);
    gates.addBoolArg(gate4);
    gates.addBoolArg(gate5);
    gates.addBoolArg(gate6);
    gates.addBoolArg(gate7);
    
    sender.sendMessage(gates, true);

    auto currentSystem = bToD(100 * gate0 + 10 * gate1 + gate2);
    auto currentSubSystem = bToD(10 * gate3 + gate4);
    
    System = ofToString(currentSystem);
    SubSystem = ofToString(currentSubSystem);
    
    string FString;
    
    if(gate7 == true){
        if((gate6 == false) && (gate5 == false)){
            FString = "Enabled";
        } else if ((gate6 == true)){
            FString = "White";
        } else if ((gate5 == true)){
            FString = "Effect On";
        }
    } else {
        FString = "Disabled";
    }
    
    FX = FString;
 
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    gui.draw();

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
