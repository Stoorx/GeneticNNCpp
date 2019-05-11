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
            mSeries(arity, PitchedFourierSeries(seriesLength)),
            mDefaultSeriesLength(seriesLength) {
        
    }
    
    static FourierHypersurface CreateFromRandom(uint64_t arity,
            uint64_t seriesLength,
            Random& random = Random::GetGlobalInstance()) {
        FourierHypersurface fhs = FourierHypersurface(arity, seriesLength);
        
        for(PitchedFourierSeries& pfs : fhs.mSeries) {
            pfs = PitchedFourierSeries::CreateFromRandom(seriesLength);
        }
        return fhs;
    }
    
    FourierSeries& operator[](size_t idx) {
        return mSeries[idx];
    }
    
    size_t getArity() const {
        return mSeries.size();
    }
    
    double Calculate(const std::vector<double>& x) const {
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
    
    void AddDimension(bool randomized = false) {
        AddDimension(mDefaultSeriesLength, randomized);
    }
    
    void AddDimension(uint64_t seriesLength, bool randomized = false) {
        if(randomized) {
            mSeries.push_back(std::move(PitchedFourierSeries::CreateFromRandom(seriesLength)));
        }
        else {
            mSeries.emplace_back(seriesLength);
        }
    }
    
    class FourierHypersurfaceIterator : public std::vector<PitchedFourierSeries>::iterator {
      public:
        explicit FourierHypersurfaceIterator(std::vector<PitchedFourierSeries>::iterator& it) :
                std::vector<PitchedFourierSeries>::iterator(it) {
        }
        
    };
    
    FourierHypersurfaceIterator begin() {
        auto it = mSeries.begin();
        return FourierHypersurfaceIterator(it);
    }
    
    FourierHypersurfaceIterator end() {
        auto it = mSeries.end();
        return FourierHypersurfaceIterator(it);
    }
  
  protected:
    uint64_t                          mDefaultSeriesLength = 0;
    std::vector<PitchedFourierSeries> mSeries;
};
