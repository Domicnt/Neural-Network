#include "stdafx.h"

//constructor

Matrix::Matrix(int const& x, int const& y)
{
	//add x rows and y columns
	for (auto i = 0; i < x; i++)
	{
		elements.emplace_back();
		for (auto j = 0; j < y; j++)
		{
			elements[i].emplace_back();
		}
	}
}

//operators

Matrix Matrix::operator * (double const& scalar)
{
	//multiply elements by scalar
	for (auto& i : elements)
	{
		for (auto& j : i)
		{
			j *= scalar;
		}
	}

	return *this;
}

Matrix Matrix::operator * (Matrix const& obj) {
	//make sure amount of rows in matrix 1 = amount of columns in matrix 2
	if (std::size(elements[0]) != std::size(obj.elements)) return {1,1};

	Matrix result(std::size(elements), std::size(obj.elements[0]));

	for (auto i = 0; i < std::size(elements); i++)
	{
		for (auto j = 0; j < std::size(obj.elements[0]); j++)
		{
			double total = 0;
			for (auto k = 0; k < std::size(elements[0]); k++)
			{
				total += elements[i][k] * obj.elements[k][j];
			}
			result.elements[i][j] = total;
		}
	}
	
	return result;
}

//functions

void Matrix::print()
{
	//set cout to print doubles/floats to 2 decimal places
	std::cout << std::fixed;
	std::cout << std::setprecision(2);
	//print all elements
	for (auto const& i : elements)
	{
		for (auto const& j : i)
		{
			std::cout << j << "   ";
		}
		std::cout << "\n\n";
	}
}

void Matrix::randomize()
{
	for (auto& i : elements)
	{
		for (auto& j : i)
		{
			j = double(rand()) / RAND_MAX;
		}
	}
}