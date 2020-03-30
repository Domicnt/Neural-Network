#pragma once
#include "stdafx.h"

class Matrix
{
public:
	//elements of the matrix
	std::vector<std::vector<double>> elements;

	//constructor
	Matrix() = default;
	Matrix(int const& x, int const& y);

	//multiply a matrix by a scalar
	Matrix operator * (double const& scalar);
	//multiply two matrices
	Matrix operator * (Matrix const& obj);
	
	//print the contents of the matrix to the console
	void print();
	//set all elements to a random value between 0 and 1
	void randomize();
};