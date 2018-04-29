#include "ControlVoltage.h"

//--------------------------------------------------------------
ControlVoltage::ControlVoltage(){
    alpha = 0.2;
    currentValue = 0.0;
    lastValue = 0.0;
    exponentialReturn = false;
    bipolarVolts = true;
}
//--------------------------------------------------------------
void ControlVoltage::readValue(double _in){
    currentValue = _in;
}
//--------------------------------------------------------------
double ControlVoltage::getFiltered(){
    double answer = filteredValue(currentValue, lastValue);
    
    lastValue = answer;
    
    if(bipolarVolts == false){
        answer = ofMap(answer, 0.5, 1.0, 0.0, 1.0, true);
    }
    
    if (exponentialReturn){
        answer = pow(answer, 2);
    }
    
    return answer;
}
//--------------------------------------------------------------
double ControlVoltage::filteredValue(double _in, double _lastOut){
    double answer;
    answer = _lastOut + alpha * (_in - _lastOut);
    return answer;
}
//--------------------------------------------------------------
double ControlVoltage::getRaw(){
    return currentValue;
}
//--------------------------------------------------------------
void ControlVoltage::setAlpha(float _alpha){
    alpha = _alpha;
}
//--------------------------------------------------------------
void ControlVoltage::setExponential(){
    exponentialReturn = true;
}

//--------------------------------------------------------------
void ControlVoltage::setUnipolar(){
    bipolarVolts = false;
}
