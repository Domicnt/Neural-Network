#include "stdafx.h"

int main()
{
	srand(time(NULL));
	NeuralNetwork nn({ 2, 2, 2 });
	std::vector<std::vector<double>> const inputs = { {0,0}, {0,1}, {1,0}, {1,1} };
	std::vector<std::vector<double>> const outputs = { {0,1}, {1,0}, {1,0}, {0,1} };
	nn.train(inputs, outputs, 1000);
	while (true)
	{
		std::vector<double> input = { 0, 0 };
		std::cin >> input[0];
		std::cin >> input[1];
		nn.propagate(input);
		//nn.print();
		std::cout << nn.layers[std::size(nn.layers) - 1].activation[0] << "\n";
		std::cout << nn.layers[std::size(nn.layers) - 1].activation[1] << "\n";
	}
}