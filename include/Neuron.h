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
    ChainableNeuron() : mInputCache(), mPrevNeurons() {}
    
    explicit ChainableNeuron(std::vector<std::shared_ptr<Neuron>>& prevNeurons) :
            mInputCache(prevNeurons.size(), 0),
            mPrevNeurons(prevNeurons) {
    }
    
    uint64_t GetInputsCount() override {
        return mPrevNeurons.size();
    }
    
    virtual void AddPrevNeuron(std::shared_ptr<Neuron>& prevNeuron) {
        mPrevNeurons.push_back(prevNeuron);
        mInputCache.push_back(0.0);
    }
    
    virtual void AddPrevNeuron(std::shared_ptr<Neuron>&& prevNeuron) {
        mPrevNeurons.emplace_back(prevNeuron);
        mInputCache.emplace_back(0.0);
    }
    
    virtual void AddPrevNeurons(std::vector<std::shared_ptr<Neuron>>& neurons) {
        for(auto& neuronPtr: neurons) {
            AddPrevNeuron(neuronPtr);
        }
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
    InnerNeuron(uint64_t activationFunctionLength = 10) :
            ChainableNeuron(),
            mActivationFunction(0, activationFunctionLength),
            mDefaultActivationFunctionLength(activationFunctionLength) {
    }
    
    void AddPrevNeuron(std::shared_ptr<
            Neuron>& prevNeuron, uint64_t dimensionActivationLength, bool randomizeWeights = false) {
        ChainableNeuron::AddPrevNeuron(prevNeuron);
        mActivationFunction.AddDimension(dimensionActivationLength, randomizeWeights);
    }
    
    void AddPrevNeuron(std::shared_ptr<
            Neuron>&& prevNeuron, uint64_t dimensionActivationLength, bool randomizeWeights = false) {
        ChainableNeuron::AddPrevNeuron(prevNeuron);
        mActivationFunction.AddDimension(dimensionActivationLength, randomizeWeights);
    }
    
    void AddPrevNeuron(std::shared_ptr<Neuron>& prevNeuron, bool randomizeWeights = false) {
        ChainableNeuron::AddPrevNeuron(prevNeuron);
        mActivationFunction.AddDimension(randomizeWeights);
    }
    
    void AddPrevNeuron(std::shared_ptr<Neuron>&& prevNeuron, bool randomizeWeights = false) {
        ChainableNeuron::AddPrevNeuron(prevNeuron);
        mActivationFunction.AddDimension(randomizeWeights);
    }
    
    void AddPrevNeurons(std::vector<std::shared_ptr<Neuron>>& neurons, bool randomizeWeights = false) {
        for(auto& neuronPtr: neurons) {
            AddPrevNeuron(neuronPtr);
            mActivationFunction.AddDimension(randomizeWeights);
        }
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
    OutputNeuron() : ChainableNeuron() {
    
    }
    
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
    InputNeuron(double value) : mValue(value) {}
    
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
