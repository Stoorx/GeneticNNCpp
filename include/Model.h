#include <memory>

//
// Created by Stoorx on 11.05.2019.
//

#pragma once

#include <vector>
#include <memory>
#include <NeuronLayer.h>
#include "Neuron.h"

class Model {
  public:
    Model() :
            mLayers() {
        
    }
    
    void AddLayer(NeuronLayer& neuronLayer) {
        mLayers.push_back(neuronLayer);
    }
    
    void AddLayer(NeuronLayer&& neuronLayer) {
        mLayers.emplace_back(std::move(neuronLayer));
    }
    
    NeuronLayer& GetInputLayer() {
        return mLayers[0];
    }
    
    Model Crossingover(Model& other) {
        Model newModel;
        auto  layerIterator = other.mLayers.begin();
        for(auto& layer: mLayers) {
            auto        neuronIterator = layer.begin();
            NeuronLayer neuronLayer;
            for(auto& neuron: layer) {
                auto otherInnerNeuron = dynamic_cast<InnerNeuron*>(neuronIterator->get());
                auto innerNeuron      = dynamic_cast<InnerNeuron*>(neuron.get());
                if(innerNeuron != nullptr && otherInnerNeuron != nullptr) {
                    FourierHypersurface fourierHypersurface(0, innerNeuron->GetActivationFunction().getArity());
                    auto                otherDimensionsIterator = otherInnerNeuron->GetActivationFunction().begin();
                    auto                newInnerNeuron          = std::make_shared<InnerNeuron>();
                    uint64_t            dimensionPosition       = 0;
                    for(auto& dimension: innerNeuron->GetActivationFunction()) {
                        PitchedFourierSeries pfs(dimension.getLength());
                        auto                 pfsIterator = otherDimensionsIterator->begin();
                        auto                 fElement    = FourierElement();
                        for(auto& element: dimension) {
                            fElement.Amplitude = (element.Amplitude + pfsIterator->Amplitude) / 2;
                            fElement.Phase     = (element.Phase + pfsIterator->Phase) / 2;
                            pfs[dimensionPosition] = fElement;
                            dimensionPosition++;
                            pfsIterator++;
                        }
                        fourierHypersurface.AddDimension(pfs);
                        otherDimensionsIterator++;
                    }
                    newInnerNeuron->SetActivationFunction(fourierHypersurface);
                    neuronLayer.AddNeuron(newInnerNeuron);
                }
                else {
                    auto inputNeuron = dynamic_cast<InputNeuron*>(neuron.get());
                    if(innerNeuron != nullptr) {
                        neuronLayer.AddNeuron(std::make_shared<InputNeuron>(neuron));
                    }
                    else {
                        neuronLayer.AddNeuron(std::make_shared<OutputNeuron>(neuron));
                    }
                    
                }
                neuronIterator++;
            }
            newModel.AddLayer(neuronLayer);
            layerIterator++;
        }
        for(uint64_t i = 1; i < mLayers.size(); ++i) {
            mLayers[i].AddPrevLayer(mLayers[i - 1]);
        }
        return newModel;
    }
  
  protected:
    std::vector<NeuronLayer> mLayers;
};
