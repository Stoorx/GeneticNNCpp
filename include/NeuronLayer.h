//
// Created by Stoorx on 11.05.2019.
//

#pragma once

#include <stdint.h>
#include <vector>
#include <memory>
#include <Neuron.h>

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
        mNeurons.insert(mNeurons.end(), neurons.begin(), neurons.end());
    }
    
    void AddNeurons(std::vector<std::shared_ptr<Neuron>>&& neurons) {
        mNeurons.insert(mNeurons.end(), neurons.begin(), neurons.end());
    }
    
    std::vector<double> CalculateLayer() {
        std::vector<double> result;
        
        for(auto& neuronPtr: mNeurons) {
            result.push_back(neuronPtr->Calculate());
        }
        
        return result;
    }
    
    void AddPrevLayer(NeuronLayer& prevLayer, bool randomize = false) {
        mPrevLayer       = &prevLayer;
        auto prevNeurons = mPrevLayer->GetNeurons(); // Potential null-fail
        for(auto& neuronPtr : mNeurons) {
            auto cn = dynamic_cast<ChainableNeuron*>(neuronPtr.get());
            if(cn != nullptr) {
                auto n = dynamic_cast<InnerNeuron*>(neuronPtr.get());
                if(n != nullptr) {
                    n->AddPrevNeurons(prevNeurons, randomize);
                }
                else {
                    cn->AddPrevNeurons(prevNeurons);
                }
            }
        }
    }
    
    const std::vector<std::shared_ptr<Neuron>>& GetNeurons() {
        return mNeurons;
    }
    
    uint64_t GetNeuronsCount() {
        return mNeurons.size();
    }
  
  protected:
    std::vector<std::shared_ptr<Neuron>> mNeurons;
    NeuronLayer* mPrevLayer = nullptr;
};
