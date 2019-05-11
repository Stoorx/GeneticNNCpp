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

//    std::vector<NeuronLayer<Neuron>> layers;
//
//    NeuronLayer<InputNeuron> inputLayer;
//    NeuronLayer<InnerNeuron> innerLayer;
//

//    inputLayer.AddNeuron(std::make_shared<InputNeuron>(0));
//    innerLayer.AddNeurons(std::vector<std::shared_ptr<InnerNeuron>>(
//            {
//                new InnerNeuron()
//            }
//            ))
    auto in1 = std::make_shared<InputNeuron>(5);
    auto in2 = std::make_shared<InputNeuron>(5);
    
    auto inner1 = std::make_shared<InnerNeuron>(2);
    auto inner2 = std::make_shared<InnerNeuron>(2);
    
    inner1->AddPrevNeuron(in1, true);
    inner1->AddPrevNeuron(in2, true);
    inner2->AddPrevNeuron(in1, true);
    inner2->AddPrevNeuron(in2, true);
    
    auto out1 = std::make_shared<OutputNeuron>();
    
    
    out1->AddPrevNeuron(inner1);
    out1->AddPrevNeuron(inner2);
    
    
    std::cout << out1->Calculate();
    return 0;
}