//
// Created by Stoorx on 08.05.2019.
//

#pragma once

#include <stdint.h>
#include <vector>
#include <FourierElement.h>
#include <math.h>

class FourierSeries {
  public:
    FourierSeries(uint32_t length) :
            mElements(length, FourierElement()) {
    }
    
    
    
    double Calculate(double x) {
        double result = 0;
        
        int k = 0;
        int t = 1;
        
        for(FourierElement fe : mElements) {
            result += fe.Amplitude * cos((2 * k * M_PI * x)
                                         / t + fe.Phase);
            k++;
        }
        
        return result;
    }
    
    FourierElement& operator[](size_t idx) {
        return mElements[idx];
    }
    size_t getLength() const {
        return  mElements.size();
    }
    
    
  protected:
    std::vector<FourierElement> mElements;
};
