#include "stdafx.h"

//constructor

NeuralNetwork::NeuralNetwork(std::vector<int> size)
{
	learningRate = 0.05;
	for (auto i = 0; i < std::size(size); i++)
	{
		layers.emplace_back();
		errors.emplace_back();
		errorsSum.emplace_back();
		for (auto j = 0; j < size[i]; j++)
		{
			layers[i].z.emplace_back();
			layers[i].activation.emplace_back();
			errors[i].emplace_back();
			errorsSum[i].emplace_back();
		}
	}
	for (auto i = 1; i < std::size(layers); i++)
	{
		layers[i].weights = { int(std::size(layers[i].activation)), int(std::size(layers[i - 1].activation)) };
		layers[i].weights.randomize();
	}
}

//functions

double NeuralNetwork::sigmoid(double const& x)
{
	//2.71828 is e
	return 1. / (1 + pow(2.71828, -x));
}

double NeuralNetwork::sigmoidDerivative(double const& x)
{
	return x * (1 - x);
}

void NeuralNetwork::propagate(std::vector<double> const& inputs)
{
	//load inputs into first layer of NN
	for (auto i = 0; i < std::size(inputs); i++)
	{
		layers[0].activation[i] = inputs[i];
	}
	//loop through all layers of the NN, calculating all values
	for (auto i = 1; i < std::size(layers); i++)
	{
		for (auto j = 0; j < std::size(layers[i].activation); j++)
		{
			//add bias and values * weights
			layers[i].z[j] = layers[i].bias;
			for (auto k = 0; k < std::size(layers[i - 1].activation); k++)
			{
				layers[i].z[j] += layers[i - 1].activation[k] * layers[i].weights.elements[j][k];
			}
			//get the activation of the neuron
			layers[i].activation[j] = sigmoid(layers[i].z[j]);
		}
	}
}

void NeuralNetwork::error(std::vector<double> const& outputs)
{
	//find error of output layer
	for (auto i = 0; i < std::size(outputs); i++)
	{
		errors[std::size(layers) - 1][i] = (layers[std::size(layers) - 1].activation[i] - outputs[i]) * sigmoidDerivative(layers[std::size(layers) - 1].z[i]);
	}

	//loop through each layer, going backwards
	for (int i = std::size(layers) - 2; i > 0; i--)
	{
		//loop through each neuron in that layer
		for (auto j = 0; j < std::size(layers[i].activation); j++)
		{
			//loop through each neuron in the layer ahead
			for (auto k = 0; k < std::size(layers[i + 1].activation); k++)
			{
				errors[i][j] = errors[i + 1][k] * layers[i + 1].weights.elements[k][j] * sigmoidDerivative(layers[i].z[j]);
			}
		}
	}
}

void NeuralNetwork::backpropagate()
{
	//loop through each layer, going backwards
	for (int i = std::size(layers) - 1; i > 0; i--)
	{
		//loop through each neuron in the previous layer
		for (auto j = 0; j < std::size(layers[i - 1].activation); j++)
		{
			//loop through each neuron in this layer
			for (auto k = 0; k < std::size(layers[i].activation); k++)
			{
				layers[i].weights.elements[k][j] -= errorsSum[i][k] * layers[i - 1].activation[j] * learningRate;
				layers[i].bias -= errorsSum[i][k] * learningRate;
			}
		}
	}
}

void NeuralNetwork::train(std::vector<std::vector<double>> const& inputs, std::vector<std::vector<double>> const& outputs, int const& epoch)
{
	for (auto i = 0; i < epoch; i++)
	{
		//find sum of error
		for (auto j = 0; j < std::size(inputs); j++)
		{
			//calculate outputs given inputs
			propagate(inputs[j]);
			//find error
			error(outputs[j]);
			//sum error
			for (auto k = 0; k < std::size(errors); k++)
			{
				for (auto l = 0; l < std::size(errors[k]); l++)
				{
					errorsSum[k][l] += errors[k][l];
				}
			}
		}
		//find cost
		double cost = 0;
		for (auto k = 0; k < std::size(errors); k++)
		{
			for (auto l = 0; l < std::size(errors[k]); l++)
			{
				cost += errorsSum[k][l];
			}
		}
		std::cout << cost << std::endl;
		//update weights and biases based on error
		backpropagate();
		//reset sum of errors
		for (auto k = 0; k < std::size(errors); k++)
		{
			for (auto l = 0; l < std::size(errors[k]); l++)
			{
				errorsSum[k][l] = 0;
			}
		}
	}
}

void NeuralNetwork::print()
{
	for (auto const& i : layers)
	{
		for (auto const& j : i.activation)
		{
			std::cout << j << "   ";
		}
		std::cout << "\n\n";
	}
}