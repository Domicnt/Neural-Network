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
		
		//value of neurons in the net
		std::vector<double> neurons;
		//error for each neuron
		std::vector<double> error;
		//Matrix of weights for this layer
		Matrix weights;
		//bias for this layer
		double bias;
	};
	std::vector<Layer> layers;

	//constructor
	NeuralNetwork(std::vector<int> size);

	//sigmoid activation function
	double static sigmoid(double const& x);
	//sigmoid derivative
	double static sigmoidDerivative(double const& x);
	//uses inputs to return outputs
	void calculate(std::vector<double> const& inputs);
	//calculate error based on given outputs
	void error(std::vector<double> const& outputs);
	//one step of the training algorithm
	void trainstep(std::vector<double> const& inputs, std::vector<double> const& outputs);
	//training algorithm
	void train(std::vector<std::vector<double>> const& inputs, std::vector<std::vector<double>> const& outputs, int const& epoch);
	//prints the network to the console - a visualization
	void print();
};