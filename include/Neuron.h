//
// Created by Stoorx on 10.05.2019.
//

#pragma once

#include <vector>
#include <FourierHypersurface.h>

class Neuron {
public:
    Neuron(std::vector<Neuron> &prevNeurons, uint64_t activationFunctionLength) :
            mActivationFunction(prevNeurons.size(), activationFunctionLength),
            mInputCache(prevNeurons.size(), 0),
            mPrevNeurons(std::move(prevNeurons)) {
    }

    virtual double Calculate() {
        std::vector<double> inputValues(GetInputsCount(), 0.0);
        for (int i = 0; i < GetInputsCount(); ++i) {
            inputValues[i] = mPrevNeurons[i].Calculate();
        }

        if (inputValues != mInputCache)
            mCache = mActivationFunction.Calculate(inputValues);

        return mCache;
    }

    uint64_t GetInputsCount() {
        return mPrevNeurons.size();
    }

    void AddPrevNeuron(const Neuron &prevNeuron, uint64_t dimensionActivationLength, bool randomizeWeights = false) {
        mPrevNeurons.push_back(prevNeuron);
        mInputCache.push_back(0.0);
        mActivationFunction.AddDimension(dimensionActivationLength, randomizeWeights);
    }

protected:
    std::vector<double> mInputCache;
    double mCache = 0.0;

    FourierHypersurface mActivationFunction;
    std::vector<Neuron &> mPrevNeurons;

};
