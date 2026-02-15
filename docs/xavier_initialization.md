# Xavier/Glorot initialization

a strategy used to set the starting weights of a neural network with the aim of keeping the variance of the activations and the gradients roughly the same across all layers.

## vanishing gradient problem

inappropriate weight initialization can result in high variance for nodes within the hidden layers of a neural network. when these high variance values are passed to the activation function, the output can become skewed in the same direction of its inputs. if the desired output is on the other side from where it's saturated, only small changes will be made to the weights in each subsequent training phase, hindering the network's ability to learn.

## solution

initialize weights *W* such that:
1. the mean of the weights is 0
2. the variance of the weights is maintained so that the signal doesn't grow or shrink uncontrollably as it moves through the network

## formula

for a layer with *i* input units and *o* output units, the weights are drawn from a distribution with specific variance:

Var(*W*) = 2/(i+o)

our implementation uses a uniform distribution where weights are picked from [-x, x], where:

x = sqrt(6/(i+o))


