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
			zero(i,i);
			for (int j = i + 1; j < m; j++)
			{
				if (zero(j, i) == 1) break;

				double div = static_cast<double>(arr(i, i))/static_cast<double>(arr(j, i));
				arr[j] *= div;
				arr[j] -= arr[i];
				v[j] *= div;
				v[j] -= (v[i]);
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
				ans.clear();
		}
		if (m < n)
		{
			Vector a1(m);
			for (int i = m - 1; i >= 0; i--)
			{
				a1[i] = v[i] / static_cast<double>(arr(i,i));
				for (int k = i + 1; k < m; k++)
				{
					a1[i] -= (arr(i,k) * static_cast<double>((a1[k]))/(arr(i,i)));
				}
			}

			ans.push_back(a1);

			for (int i = 0; i < n - m; i++)
			{
				Vector a2(m);
				for (int j = m - 1; j >= 0; j--)
				{
					a2[j] = (-1) * (static_cast<double>(arr(j,m+i)) / arr(j,j));
					for (int k = j+1; k < m; k++)
					{
						a2[j] -= (arr(j,k)*(a2[k]) / static_cast<double>(arr(j,j)));
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
			x[i] /= static_cast<double>(arr(i,i));
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

	bool zero(int i,int j)//rearrangement of lines in places for more convenient reduction to a triangular form
	{
		
		for (int k = i; k < m; k++)
		{
			if (arr[k][j] != 0)
			{
				std::swap(arr[i], arr[k]);
				std::swap(v[i], v[k]);
				return 0;
			}
			if (k == m - 1 && arr[k][i] == 0)
				return 1;
		}
		return 1;


	}
};

