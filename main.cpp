#include <memory>

#include <memory>

#include <memory>

#include <memory>

#include <Random.h>
#include <iostream>
#include <FourierHypersurface.h>
#include <Neuron.h>
#include <NeuronLayer.h>

int main() {
    
    auto in1 = std::make_shared<InputNeuron>(6);
    auto in2 = std::make_shared<InputNeuron>(8);
    
    auto inner1 = std::make_shared<InnerNeuron>(200);
    auto inner2 = std::make_shared<InnerNeuron>(200);
    
    auto out1 = std::make_shared<OutputNeuron>();
    auto out2 = std::make_shared<OutputNeuron>();
    
    NeuronLayer in;
    in.AddNeuron(in1);
    in.AddNeuron(in2);
    
    NeuronLayer i;
    i.AddNeuron(inner1);
    i.AddNeuron(inner2);
    i.AddPrevLayer(in, true);
    
    NeuronLayer o;
    o.AddNeuron(out1);
    o.AddNeuron(out2);
    o.AddPrevLayer(i);
    
    auto     res = o.CalculateLayer();
    for(auto r : res) {
        std::cout << r << " ";
    }
    
    
    return 0;
}