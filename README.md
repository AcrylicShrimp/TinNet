# TinNet
A C++14 based deep learning library. Easy to use!

#### Limited GPU accelerations now available!

### Supported layer types (Limited GPU accelerations available)
Layer | Supports GPU
------|-------------
Fully-connected layer | Yes
Convolution layer | No
Max pooling layer | No
Batch normalization layer | No
Activation layers | Yes

### Supported optimizers (Limited GPU accelerations available)
Optimizer | Supports GPU
----------|-------------
SGD | Yes
Momentum | No
Adagrad | No
RMSProp | No
Adam | No

### Supported loss functions (GPU accelerations available)
* MSE
* CE
* Multiclass CE

### Supported initializers
* Constant
* Uniform
* Normal
* Glorot
* Xavier
* He

## Usage
#### 1. Include first
```cpp
#include "TinNet.h"
```
###### If you want to use GPU, include below additionally.
```cpp
#include "TinNet_GPU.h"
```

#### 2. Create instance
###### For CPU,
```cpp
TinNet::NN sNetwork;
```
###### For GPU,
```cpp
TinNet::NN_GPU sNetwork;
```

#### 3. Stack layers
###### For CPU,
```cpp
sNetwork.addLayer<TinNet::Layer::FullLayer>(784, 50);
sNetwork.addLayer<TinNet::Layer::BatchNormLayer>(50, .9f);
sNetwork.addLayer<TinNet::Layer::LReLULayer>(50);
sNetwork.addLayer<TinNet::Layer::FullLayer>(50, 10);
sNetwork.addLayer<TinNet::Layer::BatchNormLayer>(10, .9f);
sNetwork.addLayer<TinNet::Layer::SoftmaxLayer>(10);
```
###### For GPU,
```cpp
sNetwork.addLayer<TinNet::Layer::FullLayer_GPU>(784, 50);
sNetwork.addLayer<TinNet::Layer::LReLULayer_GPU>(50);
sNetwork.addLayer<TinNet::Layer::FullLayer_GPU>(50, 10);
sNetwork.addLayer<TinNet::Layer::SoftmaxLayer_GPU>(10);
```

#### 4. Initialize network
```cpp
sNetwork.initBias<Initializer::Constant>(.0f);
sNetwork.initWeight<Initializer::He>();
```

#### 5. Create optimizer instance.
###### For CPU,
```cpp
TinNet::Optimizer::Supervised::Adagrad sOptimizer{sNetwork, 32, .005f};  //Reference of a NN instance, batch size, learning late.
```
###### For GPU,
```cpp
TinNet::Optimizer::Supervised::SGD sOptimizer{sNetwork, 32, .001f};
sOptimizer.addTrainingSet(60000u, sTrainInput.data(), sTrainOutput.data());
```

#### 6. Train!
###### For CPU,
```cpp
sOptimizer::train<TinNet::Loss::MulticlassCE>(1, 60000, sTrainInput.data(), sTrainOutput.data());  //Epoch count, training set size, pointer of input vector, pointer of desired output vector.
```
###### For GPU,
```cpp
sOptimizer.train<Loss::MulticlassCE_GPU>(1);
```
