//
// Created by Stoorx on 08.05.2019.
//

#pragma once

class FourierElement {
  public:
    FourierElement() = default;
    
    FourierElement(double amplitude, double phase) :
            Amplitude(amplitude),
            Phase(phase) {
    }
    
    
    double Amplitude = 0.0;
    double Phase     = 0.0;
};

