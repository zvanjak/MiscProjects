// LU_Matrix_Solver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <iostream>

void PerformLUDecomposition(float **a, int n, int *indx, int *rowperm);
void PerformLUBacksubstitution(float **a, int n, int *indx, float b[]);

int main()
{
	//int n = 3;
	//float **a = new float*[3];
	//for (int i = 0; i < 3; i++)
	//	a[i] = new float[3];
	//float b[3];

	//a[0][0] = 1;
	//a[0][1] = 4;
	//a[0][2] = 3;
	//a[1][0] = 2;
	//a[1][1] = 7;
	//a[1][2] = 9;
	//a[2][0] = 5;
	//a[2][1] = 8;
	//a[2][2] = -2;

	//b[0] = -4;
	//b[1] = -10;
	//b[2] = 9;

	//int indx[3], rowperm[3];

	int n;
	float **a, *b;
	int *indx, *rowperm;

	std::cout << "Enter N: ";
	std::cin >> n;

	// initialization
	a = new float*[n];
	for (int i = 0; i < n; i++)
		a[i] = new float[n];
	
	b = new float[n];
	indx = new int[n];
	rowperm = new int[n];

	std::cout << "Enter values for A:\n";
	for(int i=0; i<n; i++ )
		for(int j=0; j<n; j++ )
		{
			std::cout << "A[" << i << "][" << j << "] = ";
			std::cin >> a[i][j];
		}

	std::cout<< "Enter values for b:\n";
	for(int i=0; i<n; i++ )
	{
		std::cout << "b[" << i << "] = ";
		std::cin >> b[i];
	}

	PerformLUDecomposition(a, n, indx, rowperm);

	std::cout << "Matrix A after LU decomposition\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			std::cout << " " << a[i][j] << " ";

		std::cout << std::endl;
	}

	std::cout << "Matrix L\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			if (i > j)
				std::cout << " " << a[i][j] << " ";
			else if (i == j)
				std::cout << " 1.0 ";
			else
				std::cout << " 0.0 ";

		std::cout << std::endl;
	}

	std::cout << "Matrix U\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			if (i <= j)
				std::cout << " " << a[i][j] << " ";
			else
				std::cout << " 0.0 ";

		std::cout << std::endl;
	}

	std::cout << "Permutation matrix:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			if (j == rowperm[i])
				std::cout << " 1 ";
			else
				std::cout << " 0 ";

		std::cout << std::endl;
	}

	PerformLUBacksubstitution(a, n, indx, b);

	for (int i = 0; i < n; i++)
		std::cout << "b[" << i << "] = " << b[i] << std::endl;

	return 0;
}

//Given a matrix a, this function replaces it by the LU decomposition of a rowwise permutation of itself.
//indx[1..n] is an output vector that records the row permutation effected by the partial pivoting
// d is output as ±1 depending on whether the number of row interchanges was even or odd, respectively.
void PerformLUDecomposition(float **a, int n, int *indx, int *rowperm)
{
	int		i, imax, j, k;
	float	big, dum, sum, temp;
	float	*vv = new float[n];

	for (i = 0; i < n; i++) rowperm[i] = i;		// initializing permutation to 1, 2, .. n

	for (i = 0; i < n;i++) {
		big = 0.0;
		for (j = 0; j < n;j++)
			if ((temp = fabs(a[i][j])) > big) 
				big = temp;
		
		if (big == 0.0)
		{
			printf("Singular matrix in routine ludcmp");
			return;
		}
		vv[i] = 1.0 / big; 
	}
	for (j =0; j < n;j++) 
	{
		for (i = 0; i < j; i++) 
		{
			sum = a[i][j];
			for (k = 0; k < i; k++) 
				sum -= a[i][k] * a[k][j];
	
			a[i][j] = sum;
		}
		big = 0.0;		// starting search for largest pivot element
		for (i = j; i < n; i++) 
		{
			sum = a[i][j]; 
			for (k = 0; k < j; k++)
				sum -= a[i][k] * a[k][j];
			
			a[i][j] = sum;
			if ((dum = vv[i] * fabs(sum)) >= big) {
				big = dum;
				imax = i;
			}
		}
		if (j != imax) 
		{
			// we are doing row permutation
			for (k = 0; k < n;k++) 
			{
				dum = a[imax][k];
				a[imax][k] = a[j][k];
				a[j][k] = dum;
			}
			// recording row permutation
			int dum2 = rowperm[imax];
			rowperm[imax] = rowperm[j];
			rowperm[j] = dum2;

			vv[imax] = vv[j]; 
		}

		indx[j] = imax;
		
		if (a[j][j] == 0.0) 
			a[j][j] = 1e-15;
		
		if (j != n-1) 
		{
			// now we are going to divide by pivot element
			dum = 1.0 / (a[j][j]);
			for (i = j + 1; i < n; i++) 
				a[i][j] *= dum;
		}
	} 

	delete[]vv;
}


// Solves the set of n linear equations A·X = B where A is matrix produced by LU decomposition routine
// b is input vector of right-side values
// indx[1..n] is input as the permutation vector returned by Lu decomposition routine
void PerformLUBacksubstitution(float **a, int n, int *indx, float b[])
{
	int i, ii = 0, ip, j;
	float sum;
	for (i = 0;i < n;i++) 
	{
		ip = indx[i];
		sum = b[ip];
		b[ip] = b[i];
		
		if (ii != -1)
			for (j = ii; j <= i - 1; j++) 
				sum -= a[i][j] * b[j];
		else if (sum) 
			ii = i; 
		
		b[i] = sum; 
	}
	for (i = n-1; i >= 0;i--) 
	{
		sum = b[i];
		
		for (j = i + 1;j < n;j++) 
			sum -= a[i][j] * b[j];
		
		b[i] = sum / a[i][i]; 
	} 

	
}
