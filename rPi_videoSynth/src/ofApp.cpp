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
    
   // ofSetFrameRate(25);
    
    ofDisableArbTex();
    
    receiver.setup(PORT);
    
    CVin.resize(8);
    gateIn.resize(8);
    u_CV.resize(4);
    
    CVin[4].setExponential();
    CVin[6].setUnipolar();
    CVin[7].setUnipolar();
    
    system = 0;
    subSystem = 0;
    
    fx0 = false;
    fx1 = false;
    fx2 = false;
    
    //------> load all the shaders here.
    shaders.resize(8);
    loadShaders();
    
    mainImage.allocate(WIDTH, HEIGHT, GL_RGB);
    whiteStrobe.allocate(WIDTH, HEIGHT, GL_RGB);
    invertedImage.allocate(WIDTH, HEIGHT, GL_RGB);
    
    whiteStrobe.begin();
    ofSetColor(255, 255, 255);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    whiteStrobe.end();
    
    debugMode = false;
    keyboardMode = false;
    
    ofSetBackgroundColor(0);
    lastSystem = -1;
    
    ofSetFullscreen(true);
    
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
            for(int i = 0; i<CVin.size(); i++){
                CVin[i].readValue(m.getArgAsFloat(i));
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
    
    //----------> COMPUTE UNIFORM CVs
    
    for(int i = 0; i < u_CV.size(); i++){
        u_CV[i] = CVin[i].getRaw() * CVin[i+4].getFiltered();
    }
    
    
    //----------> MAIN FBO CALL.
    
    mainImage.begin();
    ofClear(0);
    
    if (fx2) runSystem(system); //Don't refresh if the 'enable' toggle isn't open.
    
    mainImage.end();
    
    //----------> EFFECTS INTEGRATION FBO (TO DO).

    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    //----------> MAKING SURE THE 1024X768 WINDOW ALWAYS DRAWS IN THE CENTRE.
    float x = 0;
    float y = 0;
    
    if(ofGetWidth() != WIDTH){
        x = (ofGetWidth() - WIDTH)/2.0;
    }
    
    if(ofGetHeight() != HEIGHT){
        y = (ofGetHeight() - HEIGHT)/2.0;
    }
    
    //------------> WHICH FBO TO DRAW?
    if((!fx0) && (!fx1)){
        mainImage.draw(x, y);
    } else {
        if(fx0){
            //Draw inverted image.
	    mainImage.draw(x, y);
        } //fix the else statement here once the multi works properly. 
	if (fx1){
            whiteStrobe.draw(x, y);
        }
    }
   
    
    //-------------> DEBUG MESSAGES, IF ENABLED.
    if(debugMode){
        ofDrawBitmapStringHighlight("System: " + ofToString(system), 10, 15);
        ofDrawBitmapStringHighlight("Sub System: " + ofToString(subSystem), 10, 35);
        ofDrawBitmapStringHighlight("FXs:" + ofToString(fx0) + " " + ofToString(fx1) + " " + ofToString(fx2), 10, 55);
        ofDrawBitmapStringHighlight("Uniform CVs:" + ofToString(u_CV[0]) + " " + ofToString(u_CV[1]) + " " + ofToString(u_CV[2]) + " " + ofToString(u_CV[3]), 10, 75);
	ofDrawBitmapStringHighlight("Incoming CVs:" + ofToString(CVin[4].getFiltered()) + " " + ofToString(CVin[5].getFiltered()) + " " + ofToString(CVin[6].getFiltered()) + " " + ofToString(CVin[7].getFiltered()), 10, 95);	
        
        ofDrawBitmapStringHighlight("Running at: " + ofToString(ofGetWidth()) + " by " + ofToString(ofGetHeight()) + " at " + ofToString(ofGetFrameRate())
                                    , 10, ofGetHeight() - 30);
        
        stringstream gateValues;
        
        gateValues << "RAW GATE VALUES: " <<  gateIn[0] << gateIn[1] << gateIn[2] << gateIn[3] << gateIn[4] << gateIn[5] << gateIn[6] << gateIn[7] << endl;
        
        ofDrawBitmapStringHighlight(gateValues.str(), 10, ofGetHeight() - 15);
        
    }
    
    
}

//--------------------------------------------------------------
void ofApp::sendUniforms(ofShader * _shader){
    _shader->setUniform1f("CV0", u_CV[0]);
    _shader->setUniform1f("CV1", u_CV[1]);
    _shader->setUniform1f("CV2", u_CV[2]);
    _shader->setUniform1f("CV3", u_CV[3]);
    _shader->setUniform1f("time", ofGetElapsedTimef());
    _shader->setUniform1i("subSystem", subSystem);
    _shader->setUniform2f("resolution", ofVec2f(WIDTH, HEIGHT));
    
}
//--------------------------------------------------------------
void ofApp::runSystem(int _sys){
    
    if(lastSystem != system){
        selectedShader = &shaders[system];
        lastSystem = system;
    }
    
    selectedShader->begin();
    sendUniforms(selectedShader);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    selectedShader->end();
    
    
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
