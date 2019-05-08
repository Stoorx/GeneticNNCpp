//
// Created by Stoorx on 08.05.2019.
//

#pragma once

#include <cstdint>
#include <FourierSeries.h>
#include <Random.h>
#include <vector>
#include <IncorrectArgsException.h>

class FourierHypersurface {
  public:
    explicit FourierHypersurface(uint64_t arity, uint64_t seriesLength) :
            mSeries(arity, PitchedFourierSeries(seriesLength)) {
        
    }
    
    static FourierHypersurface CreateFromRandom(uint64_t arity,
            uint64_t seriesLength,
            Random& random = Random::GetGlobalInstance()) {
        FourierHypersurface fhs = FourierHypersurface(arity, seriesLength);
        
        // TODO: Rewrite to foreach
        for(int i = 0; i < arity; ++i) {
            fhs.mSeries[i] = PitchedFourierSeries::CreateFromRandom(seriesLength);
        }
        return fhs;
    }
    
    FourierSeries& operator[](size_t idx) {
        return mSeries[idx];
    }
    
    size_t getArity() const {
        return mSeries.size();
    }
    
    double Calculate(std::vector<double>& x) const {
        if(x.size() != mSeries.size()) {
            throw IncorrectArgsException();
        }
        
        double   result = 0;
        uint64_t i      = 0;
        for(const PitchedFourierSeries& fs : mSeries) {
            result += fs.Calculate(x[i]);
            ++i;
        }
        
        return result;
    }
  
  protected:
    std::vector<PitchedFourierSeries> mSeries;
};
