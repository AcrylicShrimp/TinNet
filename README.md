# TinNet
A C++14 based deep learning library. Easy to use!

## Dependencies
There's no dependencies except for C++14 standard library.

## Usage
#### 0. Don't forget to include 'TinNet.h'.
```cpp
#include <TinNet.h>
```

#### 1. Create a graph and blueprint instance.
```cpp
Graph graph;
GraphBP bp{graph};        //GraphBP allows you to create nodes in that graph instance.
```

#### 2. Define your graph.
```cpp
auto &op = bp.constant(10.f) - 5.f;
```

#### 3. Initialize that graph.
```cpp
graph.initialize();
graph.enableBackward();   //Only if you need back-propagation.
```

#### 4. Use!
```cpp
auto result = op.forward();
```
