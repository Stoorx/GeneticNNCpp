//
// Created by Stoorx on 10.05.2019.
//

#pragma once

#include <vector>
#include <memory>
#include <FourierHypersurface.h>

class Neuron {
  public:
    virtual double Calculate() = 0;
    
    virtual uint64_t GetInputsCount() = 0;
};

class ChainableNeuron : public Neuron {
  public:
    explicit ChainableNeuron(std::vector<std::shared_ptr<Neuron>>& prevNeurons) :
            mInputCache(prevNeurons.size(), 0),
            mPrevNeurons(prevNeurons) {
    }
    
    uint64_t GetInputsCount() override {
        return mPrevNeurons.size();
    }
    
    virtual void AddPrevNeuron(Neuron& prevNeuron) {
        mPrevNeurons.push_back(std::shared_ptr<Neuron>(&prevNeuron));
        mInputCache.push_back(0.0);
    }
    
    void InvalidateCache() {
        mInputCache = std::vector<double>(mInputCache.size(), 0.0);
        mCache      = 0.0;
    }
  
  protected:
    std::vector<double>                  mInputCache;
    double                               mCache = 0.0;
    std::vector<std::shared_ptr<Neuron>> mPrevNeurons;
};

class InnerNeuron : public ChainableNeuron {
  public:
    InnerNeuron(std::vector<std::shared_ptr<Neuron>>& prevNeurons, uint64_t activationFunctionLength) :
            ChainableNeuron(prevNeurons),
            mActivationFunction(prevNeurons.size(), activationFunctionLength),
            mDefaultActivationFunctionLength(activationFunctionLength) {
    }
    
    void AddPrevNeuron(Neuron& prevNeuron, uint64_t dimensionActivationLength, bool randomizeWeights = false) {
        ChainableNeuron::AddPrevNeuron(prevNeuron);
        mActivationFunction.AddDimension(dimensionActivationLength, randomizeWeights);
    }
    
    void AddPrevNeuron(Neuron& prevNeuron, bool randomizeWeights = false) {
        ChainableNeuron::AddPrevNeuron(prevNeuron);
        mActivationFunction.AddDimension(randomizeWeights);
    }
    
    double Calculate() override {
        std::vector<double> inputValues(GetInputsCount(), 0.0);
        
        for(int i = 0; i < GetInputsCount(); ++i) {
            inputValues[i] = mPrevNeurons[i]->Calculate();
        }
        
        if(inputValues != mInputCache) {
            mCache = mActivationFunction.Calculate(inputValues);
        }
        
        return mCache;
    }
  
  protected:
    uint64_t            mDefaultActivationFunctionLength = 0;
    FourierHypersurface mActivationFunction;
};

class OutputNeuron : public ChainableNeuron {
  public:
    double Calculate() override {
        std::vector<double> inputValues(GetInputsCount(), 0.0);
        
        for(int i = 0; i < GetInputsCount(); ++i) {
            inputValues[i] = mPrevNeurons[i]->Calculate();
        }
        
        if(inputValues != mInputCache) {
            double   result = 0;
            for(auto value : inputValues) {
                result += value;
            }
            mCache          = result;
        }
        
        return mCache;
    }
};

class InputNeuron : public Neuron {
  public:
    void setValue(double value) {
        mValue = value;
    }
    
    virtual double Calculate() override {
        return mValue;
    }
    
    virtual uint64_t GetInputsCount() override {
        return 1;
    }
  
  protected:
    double mValue = 0.0;
};
