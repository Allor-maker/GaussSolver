#pragma once
#include <iostream>
#include "vector.h"
#include <vector>
#include "matrix.h"


class GaussSolver
{
	int m = 0;//number of vectors
	int n = 0;//number of elements in vector
	int null_str = 0;//number of zero lines
	Matrix arr;
	Vector v;
	std::vector<int> indexes;//array of column indices with reference elements
	std::vector<Vector> ans;
	std::vector<double> elements;//array of support elements
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
	void triang()//reduction to a diagonal matrix
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (abs(arr[i][j]) > 0.000000001)
				{
					indexes.push_back(j);
					elements.push_back(arr[i][j]);
					for (int k = 0; k < m; k++)
					{
						if (k == i)
							continue;
						double div = static_cast<double>(arr(k, j)) / static_cast<double>(arr(i, j));
						arr[k] -= (arr[i] * div);
						v[k] -= (v[i] * div);
					}
					break;
				}
				if (j == n - 1 && abs(arr[i][j]) <0.0000000001 && v[i]==0)
				{
					elements.push_back(1);
					null_str += 1;
				}	
				if (j == n - 1 && arr[i][j] < 0.0000000001 && v[i] != 0)
				{
					std::swap(arr[i], arr[m]);
					std::swap(v[i], v[m]);
				}					
			}
		}
	}
	void solution()//finding the solution quantity and writing them into the final vector
	{
		if ((m - null_str) >= n)
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
		if ((m - null_str) < n)
		{
			first_col();
			variety_of_solutions();
		}
	}
	void first_col()
	{
		Vector a1(m);
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < indexes.size(); k++)
				{
					if (abs(arr(i, j)) > 0.0000000001 && j == indexes[k])
					{
						a1[i] = v[i] / static_cast<double>(arr(i, j));
						break;
					}
				}
			}
		}
		ans.push_back(a1);
	}
	void variety_of_solutions()
	{
		int u = indexes.size();
		for (int i = 0; i < (n - u); i++)
		{

			Vector a2(m);
			for (int k = 0; k < n; k++)
			{
				bool fl = 0;
				for (int o = 0; o < indexes.size(); o++)
				{
					if (k == indexes[o])
					{
						fl = 1;
						break;
					}
				}

				if (fl == 0)
				{
					indexes.push_back(k);
					for (int j = 0; j < m; j++)
					{
						a2[j] = (-1) * ((static_cast<double>(arr(j, k)) / elements[j]));
					}
					ans.push_back(a2);
					break;
				}

			}

		}
	}
	void root_search(Vector& x)//root search
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (abs(arr[i][j]) > 0.0000000001)
				{
					x[i] = v[i] / static_cast<double>(arr[i][j]);
					break;
				}
					
			}
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

		
};

