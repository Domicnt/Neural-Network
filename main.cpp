#include "stdafx.h"

int main()
{
	srand(42);
	NeuralNetwork nn({ 2,2,1 });
	std::vector<std::vector<double>> const inputs = { {0,0}, {0,1}, {1,0}, {1,1} };
	std::vector<std::vector<double>> const outputs = { {0}, {1}, {1}, {0} };
	nn.train(inputs, outputs, 1000);
	while (true)
	{
		std::vector<double> input = { 0, 0 };
		std::cin >> input[0];
		std::cin >> input[1];
		nn.calculate(input);
		std::cout << nn.layers[std::size(nn.layers) - 1].neurons[0] << "\n";
	}
}