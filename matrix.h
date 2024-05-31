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
	Matrix(const Vector& v)
	{
		n = 1;
		m = v.size();
		for (int i = 0; i < m; i++)
		{
			Vector a(1, 1);
			arr.push_back(a);
		}
	}
	Matrix(const Matrix& a) :m(a.m)
	{
		arr.clear();
		for (int i = 0; i < a.m; i++)
			arr.push_back(a.arr[i]);
	}
	double& operator()(int i, int j)
	{
		return arr[i][j];
	}
	void print() const
	{
		for (int i = 0; i < this->m; i++)
		{
			std::cout << i<< ". ";
			this->arr[i].print();
		}
			
		std::cout << std::endl;
	}
	int size() const
	{
		return m;
	}
	int get_n() const
	{
		return n;
	}
	std::vector<Vector>& get_arr()
	{
		return arr;
	}
	void del_vec(int i)
	{
		arr.push_back(arr[i]);
		arr.erase(arr.begin()+i);
	}
	Vector& operator[](int i)
	{
		return arr[i];
	}
	
	Matrix operator*( Matrix& mat) 
	{
		if (this->n != mat.m) throw 0;

		Matrix c(this->m, mat.n);
		for (int i = 0; i < c.m; i++)
		{
			for (int j = 0; j < c.n; j++)
			{
				for (int k = 0; k < mat.m; k++)
					c.arr[i][j] += arr[i][k] * mat(k,j);
			}
		}
		return c;
	}
	Matrix& operator=(const Matrix& a)
	{
		if (&a == this)
		{
			return *this;
		}
		this->m = a.m;
		arr.clear();
		for (int i = 0; i < this->m; i++)
		{
			arr.push_back(a.arr[i]);
		}
		return *this;
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