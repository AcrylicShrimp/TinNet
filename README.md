# TinNet
A C++14 based deep learning library. Easy to use!

##### This project is under construction, a huge changes will be committed. For detail, see [here](https://github.com/AcrylicShrimp/TinNet/issues/5).

## Dependencies
There's no dependencies except for C++14 standard library.

## Usage(old, will be deprecated soon)
```cpp
//Include everything at once.
#include <TinNet.h>

//...

//TinNet::NN contains list of layers. You can define your network by stacking layer into this.
TinNet::NN network;

//Stack layers as you wish.
network.addLayer<TinNet::Layer::FullLayer>(784, 100);
network.addLayer<TinNet::Layer::ReLULayer>(100);
network.addLayer<TinNet::Layer::FullLayer>(100, 10);
network.addLayer<TinNet::Layer::SoftmaxLayer>(10);

//Initialize the network. There's some choices.
network.initWeight<TinNet::Initializer::He>();
network.initBias<TinNet::Initializer::Contant>(.0f);

//Prepare MNIST dataset.
std::vector<std::vector<float>> trainX(60000);
std::vector<std::vector<float>> trainY(60000);

std::vector<std::vector<float>> testX(10000);
std::vector<std::vector<float>> testY(10000);

//Load dataset here.
//...

//Compute classification loss.
float nLoss{network.classificationLoss(10000, testX.data(), testY.data())};

//Define optimizers.
TinNet::Optimizer::Adam optimizer(network, 32, .001f, .9f, .999f);

//Train the network once.
optimizer.train<TinNet::Loss::MulticlassCE>(1, 60000, trainX.data(), trainY.data());
```

Please refer examples for whole code.

## Graph system
TinNet now support graph system! See [here](https://github.com/AcrylicShrimp/TinNet/tree/master/Example_Graph_Basic).
