#pragma once
#include "ofMain.h"

class ControlVoltage{
public:
    ControlVoltage();
    void readValue(double _in);
    
    double getFiltered();
    double getRaw();
    
    void setAlpha(float _alpha);
    void setExponential();
    void setUnipolar();
    
private:
    double filteredValue(double _in, double _lastOut);
    float alpha;
    double currentValue, lastValue;
    bool exponentialReturn, bipolarVolts;
    
};
