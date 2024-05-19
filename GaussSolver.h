#pragma once
#include <iostream>
#include "vector.h"
#include <vector>
#include "matrix.h"


class GaussSolver
{
	int m = 0;//number of vectors
	int n = 0;//number of elements in vector

	Matrix arr;
	Vector v;

	std::vector<Vector> ans;
public:
	GaussSolver(){}

	std::vector<Vector> solve(const Matrix& a, const  Vector& vect)
	{
		m = a.size();
		n = a.get_n();
		arr = a;
		v = vect;
		triang();
		solution();
		return ans;
	}
	void triang()//reduction to a triangular matrix
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < m; j++)
			{
				zero(i);
				double div = arr(j,i) / double(arr(i,i));
				arr[j] -= arr[i] * div;
				v[j] -= (v[i] * div);
			}
		}
		
	}
	void solution()//finding the solution quantity and writing them into the final vector
	{
		if (m >= n)
		{
			Vector x(m);
			if (eror_check() == 0)
			{
				root_search(x);
				ans.push_back(x);
			}
			else
				ans.push_back(x);
		}
		if (m < n)
		{
			Vector a1(m);
			for (int i = m - 1; i >= 0; i--)
			{
				a1[i] = v[i] / arr(i,i);
				for (int k = i + 1; k < m; k++)
				{
					a1[i] -= (arr(i,k) * abs(a1[k])/arr(i,i));
				}
			}

			ans.push_back(a1);

			for (int i = 0; i < n - m; i++)
			{
				Vector a2(m);
				for (int j = m - 1; j >= 0; j--)
				{
					a2[j] = (-1) * (arr(j,m+i) / arr(j,j));
					for (int k = j+1; k < m; k++)
					{
						a2[j] -= (arr(j,k)*(a2[k]) /arr(j,j));
					}
				}
				ans.push_back(a2);
			}
		}
			 
	}
	void nulvect_del()//removing null lines
	{
		for (int i = m-1; i >=0; i--)
		{
			if (arr[i].nul_vect() && v[i] == 0)
			{
				arr.del_vec();
				m--;
			}

		}
	}
	void root_search(Vector& x)//root search
	{
		for (int i = n - 1; i > -1; i--)
		{
			for (int j = i + 1; j < n; j++)
			{
				x[i] -= (arr(i,j)*x[j]);
			}
			x[i] += v[i];
			x[i] /= arr(i,i);
		}
	}
	bool eror_check()//checking for the presence of a null string equal to a non-zero number
	{
		for (int i = m-1; i >=0; i--)
		{
			if (arr[i].nul_vect() && v[i] != 0)
			{
				return true;
			}
			return false;
		}
	}
	static void print(std::vector<Vector> arr)
	{
		for (int i = 0; i < arr.size(); i++)
		{
			arr[i].print();
		}
		std::cout << std::endl;
	}

	void zero(int i)//rearrangement of lines in places for more convenient reduction to a triangular form
	{
		
		for (int k = i; k < n; k++)
		{
			if (arr[k][i] != 0)
			{
				std::swap(arr[i], arr[k]);
				break;
			}
		}

	}
};

