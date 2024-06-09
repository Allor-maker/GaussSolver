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
		double max = 0;
		int ind = -1;
		for (int j = 0; j < m; j++)
		{
			if (abs(arr[j][i]) > max && abs(arr[j][i])>0.0000000001 && check_elem(j)==false)//!!
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
			if (abs(v[k] - v[j] * div) < 0.0000000001)
				v[k] = 0;
			else
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
		
	}
	void solution()//finding the solution quantity and writing them into the final vector
	{
		if (eror_check() == true)
		{
			ans.clear();
			std::cout << "!" << std::endl;
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
		
	}
	void root_search(Vector& x)//root search
	{
		for (int i = 0; i < indexes_str.size(); i++)
		{
			x[i] = v[indexes_str[i]] / static_cast<double>(elements[i]);//!!!
		}
	}
	
	bool eror_check()//checking for the presence of a null string equal to a non-zero number
	{
		for (int i = m-1; i >= 0; i--)
		{
			if (arr[i].nul_vect() && abs(v[i])>0.0000000001)
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

