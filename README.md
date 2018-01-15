# CaysNet
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
#include "CaysNet.h"
```

##### 2. Create instance
```cpp
CaysNet::NN sNetwork;
```

##### 3. Stack layers
```cpp
sNetwork.addLayer<CaysNet::Layer::FullLayer>(784, 50);
sNetwork.addLayer<CaysNet::Layer::BatchNormLayer>(50, .9f);
sNetwork.addLayer<CaysNet::Layer::LReLULayer>(50);

//...

sNetwork.addLayer<CaysNet::Layer::FullLayer>(50, 10);
sNetwork.addLayer<CaysNet::Layer::SoftmaxLayer>(10);
```

##### 4. Create optimizer instance.
```cpp
CaysNet::Optimizer::Supervised::Adagrad sOptimizer{sNetwork, 32, .005f};  //Reference of a NN instance, batch size, learning late.
```

##### 5. Train!
```cpp
sOptimizer::train<CaysNet::Loss::MulticlassCE>(1, 60000, sTrainInput.data(), sTrainOutput.data());  //Epoch count, training set size, pointer of input vector, pointer of desired output vector.
```
