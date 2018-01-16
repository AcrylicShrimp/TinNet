# TinNet
A C++14 based deep learning library. Easy to use!

### Supported layer types
* Fully-connected layer
* Batch normalization layer
* Some activation layers

### Supported optimizers
* SGD
* Momentum
* Adagrad
* RMSProp

### Supported loss functions
* MSE
* CE
* Multiclass CE

## Usage
##### 1. Include first
```cpp
#include "TinNet.h"
```

##### 2. Create instance
```cpp
TinNet::NN sNetwork;
```

##### 3. Stack layers
```cpp
sNetwork.addLayer<TinNet::Layer::FullLayer>(784, 50);
sNetwork.addLayer<TinNet::Layer::BatchNormLayer>(50, .9f);
sNetwork.addLayer<TinNet::Layer::LReLULayer>(50);

//...

sNetwork.addLayer<TinNet::Layer::FullLayer>(50, 10);
sNetwork.addLayer<TinNet::Layer::SoftmaxLayer>(10);
```

##### 4. Create optimizer instance.
```cpp
TinNet::Optimizer::Supervised::Adagrad sOptimizer{sNetwork, 32, .005f};  //Reference of a NN instance, batch size, learning late.
```

##### 5. Train!
```cpp
sOptimizer::train<TinNet::Loss::MulticlassCE>(1, 60000, sTrainInput.data(), sTrainOutput.data());  //Epoch count, training set size, pointer of input vector, pointer of desired output vector.
```
