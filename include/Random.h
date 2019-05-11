//
// Created by Stoorx on 08.05.2019.
//

#pragma once

#include <cstdint>
#include <ctime>

class Random;

class Random {
  public:
    explicit Random(uint64_t seed = (uint64_t)time(nullptr)) :
            S(seed) {
        LFSR_Galois(); // warm up
    }
    
    uint64_t NextLong() {
        uint64_t result = 0;
        for(int  i      = 0; i < 64; ++i) {
            result = (result << 1U) | LFSR_Galois();
        }
        return result;
    }
    
    uint64_t NextLong(uint64_t max) {
        return NextLong() % max;
    }
    
    double NextDouble() {
        double res = (double)NextLong() / UINT64_MAX;
        if(NextLong() % 2 == 0) {
            return res;
        }
        else {
            return -res;
        }
    }
  
  
  protected:
    bool LFSR_Galois() {
        if(S & 0x0000'0000'0000'0001U) {
            S = ((S ^ 0xEA00'8002'8000'4141U) >> 1U) | 0x8000'0000'0000'0000U;
            return true;
        }
        else {
            S >>= 1U;
            return false;
        }
    }
    
    uint64_t S = 0x0000'0000'0000'0001;
    
    static Random mGlobalRandom;
  public:
    static Random& GetGlobalInstance() {
        return mGlobalRandom;
    }
};
