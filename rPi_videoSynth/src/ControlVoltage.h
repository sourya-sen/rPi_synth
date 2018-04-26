#pragma once
#include "ofMain.h"

class ControlVoltage{
public:
    ControlVoltage();
    void readValue(double _in);
    double getFiltered();
    
private:
    double filteredValue(double _in, double _lastOut);
    float alpha;
    double currentValue, lastValue;
    bool exponentialReturn, bipolarVolts;
    
};
