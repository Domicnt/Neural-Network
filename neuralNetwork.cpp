#include "stdafx.h"

//constructor

NeuralNetwork::NeuralNetwork(std::vector<int> size)
{
	learningRate = 0.05;
	for (auto i = 0; i < std::size(size); i++)
	{
		layers.emplace_back();
		for (auto j = 0; j < size[i]; j++)
		{
			layers[i].neurons.emplace_back();
			layers[i].error.emplace_back();
		}
	}
	for (auto i = 0; i < std::size(layers) - 1; i++)
	{
		layers[i].weights = { int(std::size(layers[i].neurons)), int(std::size(layers[i + 1].neurons)) };
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

void NeuralNetwork::calculate(std::vector<double> const& inputs)
{
	//load inputs into first layer of NN
	for (auto i = 0; i < std::size(inputs); i++)
	{
		layers[0].neurons[i] = inputs[i];
	}
	//loop through all layers of the NN, calculating all values
	for (auto i = 1; i < std::size(layers); i++)
	{
		for (auto j = 0; j < std::size(layers[i].neurons); j++)
		{
			//add up values * weights
			double sum = 0;
			for (auto k = 0; k < std::size(layers[i - 1].neurons); k++)
			{
				sum += layers[i - 1].neurons[k] * layers[i - 1].weights.elements[k][j];
			}
			layers[i].neurons[j] = sigmoid(sum) + layers[i].bias;
		}
	}
}

void NeuralNetwork::error(std::vector<double> const& outputs)
{
	//first layer
	for (auto i = 0; i < std::size(outputs); i++)
	{
		layers[std::size(layers) - 1].error[i] = .5 * pow(outputs[i] - layers[std::size(layers) - 1].neurons[i], 2);
	}
	//hidden layers
	for (auto i = std::size(layers) - 2; i > 0; i--)
	{
		for (auto j = 0; j < std::size(layers[i].neurons); j++)
		{
			layers[i].error[j] = 0;
			for (auto k = 0; k < std::size(layers[i + 1].neurons); k++)
			{
				layers[i].error[j] += (layers[i].weights.elements[j][k] * layers[i + 1].error[k]) + sigmoidDerivative(layers[i + 1].neurons[k]);
			}
		}
	}
}

void NeuralNetwork::trainstep(std::vector<double> const& inputs, std::vector<double> const& outputs)
{
	calculate(inputs);
	error(outputs);

}

void NeuralNetwork::train(std::vector<std::vector<double>> const& inputs, std::vector<std::vector<double>> const& outputs, int const& epoch)
{
	int input = 0;
	int output = 0;
	for (auto i = 0; i < epoch; i++)
	{
		trainstep(inputs[input], outputs[output]);
		double errors = 0;
		for (auto j = 0; j < std::size(layers[std::size(layers) - 1].neurons); j++)
		{
			errors += layers[std::size(layers) - 1].error[j];
		}
		std::cout << errors << "\n";
		input < std::size(inputs) - 1 ? input++ : input = 0;
		output < std::size(outputs) - 1 ? output++ : output = 0;
	}
	print();
}

void NeuralNetwork::print()
{
	for (auto const& i : layers)
	{
		for (auto const& j : i.neurons)
		{
			std::cout << j << "   ";
		}
		std::cout << "\n\n";
	}
}