//
// Created by Stoorx on 08.05.2019.
//

#pragma once

#include <cstdint>
#include <vector>
#include <FourierElement.h>
#include <Random.h>
#include <cmath>

class FourierSeries {
  public:
    explicit FourierSeries(uint64_t length) :
            mElements(length, FourierElement()) {
    }
    
    static FourierSeries CreateFromRandom(uint64_t length) {
        auto fs     = FourierSeries(length);
        auto random = Random::GetGlobalInstance();
        
        for(int i = 0; i < fs.getLength(); ++i) {
            fs[i] = FourierElement(random.NextDouble(), random.NextDouble());
        }
        
        return fs;
    }
    
    virtual double Calculate(double x) {
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
        return mElements.size();
    }
  
  
  protected:
    std::vector<FourierElement> mElements;
};

class PitchedFourierSeries : FourierSeries {
  public:
    explicit PitchedFourierSeries(uint64_t length) :
            FourierSeries(length), Pitch(0) {
    }
    
    static PitchedFourierSeries CreateFromRandom(uint64_t length) {
        auto pfs    = PitchedFourierSeries(length);
        auto random = Random::GetGlobalInstance();
        
        for(int i = 0; i < pfs.getLength(); ++i) {
            pfs[i] = FourierElement(random.NextDouble(), random.NextDouble());
        }
        
        pfs.Pitch = random.NextDouble();
        
        return pfs;
    }
    
    double Pitch = 0;
    
};