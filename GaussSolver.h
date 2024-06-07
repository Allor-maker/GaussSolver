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
	std::vector<int> indexes_str;//array of str indices with reference elements
	std::vector<int> indexes_col;
	std::vector<int> null_lines;
	std::vector<Vector> ans;
	std::vector<double> elements;//array of support elements
	std::vector<int> free_vect;
public:
	GaussSolver(){}

	std::vector<Vector> solve(const Matrix& a, const  Vector& vect)
	{
		m = a.size();
		n = a.get_n();
		arr = a;
		v = vect;
		diag();
		count_zero_str();
		//arr.print();
		solution();
		return ans;
	}
	bool check_elem(int j)
	{
		bool fl = false;
		for (int k = 0; k < indexes_str.size(); k++)
		{
			if (indexes_str[k] == j)
			{
				fl = true;
				break;
			}
		}
		return fl;
	}
	int choose_max_elem(int i)//i - number of column; choosing the optimal element
	{
		double max = -100000000000;
		int ind = -1;
		for (int j = 0; j < m; j++)
		{
			if (arr[j][i] > max && abs(arr[j][i])>0.0000000001 && check_elem(j)==false)
			{
				max = arr[j][i];
				ind = j;
			}	
		}
		return ind;
	}
	void zeroing_column(int j,int i)//i - column, j - vector
	{
		for (int k = 0; k < m; k++)
		{
			if (k == j)
				continue;
			double div = static_cast<double>(arr(k, i)) / static_cast<double>(arr(j,i));
			arr[k] -= (arr[j] * div);
			v[k] -= (v[j] * div);
		}
	}
	void count_zero_str()
	{
		for (int i = 0; i < m; ++i)
		{
			int fl = 0;
			for (int j = 0; j < n; j++)
			{
				if (abs(arr[i][j]) > 0.0000000001 || abs(v[i])>0.0000000001)
				{
					fl = 1;
				}
			}
			if (fl == 0)
			{
				null_str += 1;
				null_lines.push_back(i);
			}
		}
	}
	void diag()//reduction to a diagonal matrix
	{
		int j;
		for (int i = 0; i < n; i++)
		{
			j = -1;
			j = choose_max_elem(i);
			if (j == -1)
			{
				free_vect.push_back(i);
				continue;
			}
			if (j != -1)
			{
				indexes_str.push_back(j);
				indexes_col.push_back(i);
				elements.push_back(arr[j][i]);
				zeroing_column(j,i);
			}
		}
		/*for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (abs(arr[i][j]) > 0.0000000001)
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
		}*/
	}
	void solution()//finding the solution quantity and writing them into the final vector
	{
		if (eror_check() == true)
		{
			ans.clear();
		}
		else
		{
			if ((m - null_str) == n)
			{
				Vector x(m);
				root_search(x);
				ans.push_back(x);
			}
			if ((m - null_str) < n)
			{
				first_col();
				variety_of_solutions();
			}
		}
	}
	void first_col()
	{
		Vector a1(n);
		for (int i = 0; i < indexes_col.size(); i++)
		{
			a1[indexes_col[i]] = v[indexes_str[i]] / static_cast<double>(elements[i]);
		}
		ans.push_back(a1);
		/*for (int i = 0; i < n; i++)
		{
			for (int j = 0; j <m; j++)
			{
				for (int k = 0; k < indexes.size(); k++)
				{
					if (abs(arr(j, i)) > 0.0000000001 && i == indexes[k])
					{
						a1[i] = v[i] / static_cast<double>(arr(i, j));
						break;
					}
				}
			}
		}
		ans.push_back(a1);*/
	}
	void variety_of_solutions()
	{
		for (int i = 0; i < free_vect.size(); i++)
		{
			Vector a2(n);
			a2[free_vect[i]] = 1;
			for (int j = 0; j < indexes_str.size(); j++)
			{
				a2[indexes_col[j]] = (-1) * ((static_cast<double>(arr(indexes_str[j],free_vect[i])) / elements[j]));;
			}
			ans.push_back(a2);
		}
		/*int u = indexes.size();
		for (int i = 0; i < (n - u); i++)
		{

			Vector a2(n);
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
					for (int j = 0; j < n; j++)
					{
						a2[j] = (-1) * ((static_cast<double>(arr(j, k)) / elements[j]));
					}
					ans.push_back(a2);
					break;
				}

			}

		}*/
	}
	void root_search(Vector& x)//root search
	{
		for (int i = 0; i < indexes_str.size(); i++)
		{
			x[indexes_str[i]] = v[indexes_str[i]] / static_cast<double>(elements[i]);
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
		}
		return false;
	}
	static void print(std::vector<Vector> arr)
	{
		for (int i = 0; i < arr.size(); i++)
		{
			arr[i].print();
		}
		std::cout << std::endl;
	}
	static void print(std::vector<int> arr)
	{
		for (int i = 0; i < arr.size(); i++)
		{
			std::cout << arr[i];
		}
		std::cout << std::endl;
	}
	static void print(std::vector<double> arr)
	{
		for (int i = 0; i < arr.size(); i++)
		{
			std::cout << arr[i];
		}
		std::cout << std::endl;
	}
		
};

