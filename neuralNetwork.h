#pragma once
#include "stdafx.h"

class NeuralNetwork
{
public:
	//how quickly the NN learns
	double learningRate;
	
	//one layer of the net
	class Layer
	{
	public:
		//constructor
		Layer() { bias = 0; }

		//input into neurons in the net
		std::vector<double> z;
		//value of neurons in the net
		std::vector<double> activation;
		//Matrix of weights for this layer
		Matrix weights;
		//bias for this layer
		double bias;
	};
	std::vector<Layer> layers;
	//error for each neuron
	std::vector<std::vector<double>> errors;
	//summed error for each neuron
	std::vector<std::vector<double>> errorsSum;

	//constructor
	NeuralNetwork(std::vector<int> size);

	//sigmoid activation function
	double static sigmoid(double const& x);
	//sigmoid derivative
	double static sigmoidDerivative(double const& x);
	//uses inputs to return outputs
	void propagate(std::vector<double> const& inputs);
	//calculate error based on given outputs
	void error(std::vector<double> const& outputs);
	//one step of the training algorithm
	void backpropagate();
	//training algorithm
	void train(std::vector<std::vector<double>> const& inputs, std::vector<std::vector<double>> const& outputs, int const& epoch);
	//prints the network to the console - a visualization
	void print();
};