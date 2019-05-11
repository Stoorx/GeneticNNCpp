//
// Created by Stoorx on 11.05.2019.
//

#pragma once

#include <stdint.h>
#include <vector>
#include <memory>
#include <Neuron.h>

template<class T>
class NeuronLayer {
  public:
    NeuronLayer() = default;
    
    void AddNeuron(std::shared_ptr<Neuron>& neuron) {
        mNeurons.push_back(neuron);
    }
    
    void AddNeuron(std::shared_ptr<Neuron>&& neuron) {
        mNeurons.emplace_back(neuron);
    }
    
    void AddNeurons(std::vector<std::shared_ptr<Neuron>>& neurons) {
        mNeurons.push_back(neurons);
    }
    
    void AddNeurons(std::vector<std::shared_ptr<Neuron>>&& neurons) {
        mNeurons.emplace_back(neurons);
    }
    
    std::vector<double> CalculateLayer() {
        std::vector<double> result;
        
        for(auto& neuronPtr: mNeurons) {
            result.push_back(neuronPtr->Calculate());
        }
        
        return result;
    }
    
    void AddPrevLayer(NeuronLayer<Neuron>& prevLayer) {
        mPrevLayer       = &prevLayer;
        auto prevNeurons = mPrevLayer->GetNeurons();
        for(auto& neuronPtr : mNeurons) {
            neuronPtr->AddPrevNeurons(prevNeurons);
        }
    }
    
    const std::vector<std::shared_ptr<Neuron>>& GetNeurons() {
        return mNeurons;
    }
    
    uint64_t GetNeuronsCount() {
        return mNeurons.size();
    }
  
  protected:
    std::vector<std::shared_ptr<T>> mNeurons;
    NeuronLayer* mPrevLayer = nullptr;
};
