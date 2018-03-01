#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofDisableArbTex();
    
    receiver.setup(PORT);
    
    CV.resize(4);
    fx0 = false;
    fx1 = false;
    fx2 = false;
    
    system = 0;
    subSystem = 0;
    
    //...load all the shaders here.
    shaders.resize(8);
    
    for(int i = 0; i<shaders.size(); i++){
        string path = "shaders/";
        string fileName = ofToString(i) + ".frag";
        shaders[i].load("shaders/standard.vert", path + fileName);
    }
    
    mainImage.allocate(ofGetWidth(), ofGetHeight());
    
    debugMode = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    while(receiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if(m.getAddress() == "/sys"){
            system = m.getArgAsInt(0);
        } else if (m.getAddress() == "/subSys") {
            subSystem = m.getArgAsInt(0);
        } else if (m.getAddress() == "/fx0"){
            fx0 = m.getArgAsBool(0);
        } else if (m.getAddress() == "/fx1"){
            fx1 = m.getArgAsBool(0);
        } else if (m.getAddress() == "/fx2"){
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
    
    
    //----------> MAIN FBO CALL.
    
    mainImage.begin();
    ofSetColor(0);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    runSystem(system);
    
    mainImage.end();
    
    //----------> EFFECTS INTEGRATION FBO (TO DO).

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    mainImage.draw(0, 0);
    
    if(debugMode){
        ofDrawBitmapStringHighlight("System: " + ofToString(system), 10, 15);
        ofDrawBitmapStringHighlight("Sub System: " + ofToString(subSystem), 10, 35);
        ofDrawBitmapStringHighlight("FXs:" + ofToString(fx0) + " " + ofToString(fx1) + " " + ofToString(fx2), 10, 55);
        ofDrawBitmapStringHighlight("CVs:" + ofToString(CV[0]) + " " + ofToString(CV[1]) + " " + ofToString(CV[2]) + " " + ofToString(CV[3]), 10, 75);
        
    }
    
    
}

//--------------------------------------------------------------
void ofApp::sendUniforms(int selectedShader){
    shaders[selectedShader].setUniform1f("CV0", CV[0]);
    shaders[selectedShader].setUniform1f("CV1", CV[1]);
    shaders[selectedShader].setUniform1f("CV2", CV[2]);
    shaders[selectedShader].setUniform1f("CV3", CV[3]);
    shaders[selectedShader].setUniform1f("time", ofGetElapsedTimef());
    shaders[selectedShader].setUniform1i("subSystem", subSystem);
    shaders[selectedShader].setUniform2f("resolution", ofVec2f(ofGetWidth(), ofGetHeight()));
    
}
//--------------------------------------------------------------
void ofApp::runSystem(int _sys){
    
    shaders[system].begin();
    sendUniforms(system);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    shaders[system].end();
    
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == ' '){
        debugMode = !debugMode;
    }
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
