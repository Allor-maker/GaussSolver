#pragma once
#include "vector.h"
#include <vector>

class Matrix
{
private:
	std::vector<Vector> arr;
	int n = 0; // colons
	int m = 0; // lines
public:
	Matrix() {};

	Matrix(int m,int n =0):m(m),n(n)
	{
		for (int i = 0; i < m; i++)
		{
			Vector x(n);
			arr.push_back(x);
		}
	}
	Matrix(std::vector<Vector> v) :arr(v),m(v.size()),n(v[0].size())
	{	}
	double operator()(int i, int j)
	{
		return arr[i][j];
	}
	void print() const
	{
		for (int i = 0; i < this->m; i++)
			this->arr[i].print();
	}
	int size() const
	{
		return m;
	}
	int get_n() const
	{
		return n;
	}
	void del_vec()
	{
		arr.pop_back();
	}
	Vector& operator[](int i)
	{
		return arr[i];
	}
	Matrix& transp()
	{
		Matrix b(*this);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++)
			{
				this->arr[i][j] = b.arr[j][i];
			}
		}
		return *this;	
	}
	int pows(int i) const
	{
		int res = -1;//переменная для учета степени -1
		for (int k = 0; k < i; k++)
		{
			res *= -1;
		}

		return res;

	}
};