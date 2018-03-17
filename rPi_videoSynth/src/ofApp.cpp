#include "ofApp.h"

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
    
    ofSetFrameRate(25);
    
    ofDisableArbTex();
    
    receiver.setup(PORT);
    
    CV.resize(4);
    gateIn.resize(8);
    
    system = 0;
    subSystem = 0;
    
    fx0 = false;
    fx1 = false;
    fx2 = false;
    
    //...load all the shaders here.
    shaders.resize(8);
    loadShaders();
    
    mainImage.allocate(1024, 768, GL_RGB);
    
    debugMode = true;
    keyboardMode = false;
    
    ofSetBackgroundColor(0);
    
    //    ofSetFullscreen(true);
    
#ifdef TARGET_OPENGLES
    ofHideCursor();
#endif
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    while(receiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if(m.getAddress() == "/cv"){
            for(int i = 0; i<CV.size(); i++){
                CV[i] = m.getArgAsFloat(i);
            }
        }
        
        else if (m.getAddress() == "/gates"){
            for(int i = 0; i<gateIn.size(); i++){
                gateIn[i] = m.getArgAsInt(i);
            }
        }
        
    }
    
    system = bToD(100 * gateIn[0] + 10 * gateIn[1] + gateIn[2]);
    subSystem = bToD(10 * gateIn[3] + gateIn[4]);
    
    fx0 = gateIn[5];
    fx1 = gateIn[6];
    fx2 = gateIn[7];
    
    
    //----------> MAIN FBO CALL.
    
    mainImage.begin();
    ofClear(0);
    runSystem(system);
    
    mainImage.end();
    
    //----------> EFFECTS INTEGRATION FBO (TO DO).
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    float x = 0;
    float y = 0;
    
    if(ofGetWidth() != 1024){
        x = (ofGetWidth() - 1024)/2.0;
    }
    
    if(ofGetHeight() != 768){
        y = (ofGetHeight() - 768)/2.0;
    }
    
    mainImage.draw(x, y);
    
    
    if(debugMode){
        ofDrawBitmapStringHighlight("System: " + ofToString(system), 10, 15);
        ofDrawBitmapStringHighlight("Sub System: " + ofToString(subSystem), 10, 35);
        ofDrawBitmapStringHighlight("FXs:" + ofToString(fx0) + " " + ofToString(fx1) + " " + ofToString(fx2), 10, 55);
        ofDrawBitmapStringHighlight("CVs:" + ofToString(CV[0]) + " " + ofToString(CV[1]) + " " + ofToString(CV[2]) + " " + ofToString(CV[3]), 10, 75);
        
        ofDrawBitmapStringHighlight("Running at: " + ofToString(ofGetWidth()) + " by " + ofToString(ofGetHeight()) + " at " + ofToString(ofGetFrameRate())
                                    , 10, ofGetHeight() - 30);
        
        stringstream gateValues;
        
        gateValues << "RAW GATE VALUES: " <<  gateIn[0] << gateIn[1] << gateIn[2] << gateIn[3] << gateIn[4] << gateIn[5] << gateIn[6] << gateIn[7] << endl;
        
        ofDrawBitmapStringHighlight(gateValues.str(), 10, ofGetHeight() - 15);
        
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
    shaders[selectedShader].setUniform2f("resolution", ofVec2f(1024, 768));
    
}
//--------------------------------------------------------------
void ofApp::runSystem(int _sys){
    
    shaders[_sys].begin();
    sendUniforms(_sys);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    shaders[_sys].end();
    
    
}
//--------------------------------------------------------------
void ofApp::loadShaders(){
    for(int i = 0; i<shaders.size(); i++){
        string path = "shaders/";
        string fileName = ofToString(i) + ".frag";
        shaders[i].load("shaders/standard.vert", path + fileName);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == ' '){
        debugMode = !debugMode;
    }
    
    if(keyboardMode){
        switch(key){
            case '0':
                system = 0;
                break;
            case '1':
                system = 1;
                break;
            case '2':
                system = 2;
                break;
            case '3':
                system = 3;
                break;
            case '4':
                system = 4;
                break;
            case '5':
                system = 5;
                break;
                
        }
    }
    
    if((key == 'r') || (key == 'R')){
        loadShaders();
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
    
    //    mainImage.allocate(ofGetWidth(), ofGetHeight());
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
