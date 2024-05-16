#pragma once
#include <iostream>
#include <vector>
class Vector {
private:

	double* data = nullptr;
	int n = 0;
public:
	Vector() {};
	Vector(std::vector<double> arr):n(arr.size())
	{
		data = new double[n];
		for (int i = 0; i < n; i++)
		{
			data[i] = arr[i];
		}
	}
	Vector(int n) :n(n)
	{
		if (n <= 0)
		{
			return;
		}

		data = new double[n];
		for (int i = 0; i < n; i++)
		{
			this->data[i] = 0;
		}
	}
	Vector(const Vector& v) :n(v.n)
	{
		data = new double[v.n];
		for (int i = 0; i < v.n; i++)
		{
			this->data[i] = v.data[i];
		}
	}

	Vector(double* arr, int n) :n(n)
	{
		data = new double[n];
		for (int i = 0; i < this->n; i++)
		{
			this->data[i] = *(arr + i);
		}
	}

	double& operator[](int i)
	{
		return (this->data[i]);
	}
	
	Vector operator-(const Vector& v) const {

		if (v.n != this->n) throw 0;

		Vector c(this->n);
		for (int i = 0; i < n; i++)
		{
			c.data[i] = this->data[i] - v.data[i];
		}
		return c;
	}
	int size() const
	{
		return this->n;
	}
	double scalar_mul(const Vector& v) const
	{

		double s_mul = 0;
		for (int i = 0; i < this->n; i++)
		{
			s_mul += v.data[i] * this->data[i];
		}
		return s_mul;
	}
	bool nul_vect()
	{
		for (int i = 0; i < n; i++)
		{
			if (data[i] != 0)
			{
				return false;
			}
		}
		return true;
	}
	double distant(const Vector& v) const
	{
		Vector c(this->n);
		
		c = *this - v;
		double dist = c.norma();
		return dist;
	}
	double norma()const
	{
		double scalar_q = scalar_mul(*this);
		return scalar_q;
	}
	void print() const {
		for (int i = 0; i < n; i++)
		{
			std::cout << this->data[i] << " ";
		}
		std::cout << std::endl;
	}
	
	Vector operator+(const Vector& v) const {

		if (v.n != this->n)
			throw 0;
		Vector c(v.n);
		for (int i = 0; i < n; i++)
		{
			c.data[i] = v.data[i] + this->data[i];
		}
		return c;
	}

	Vector operator*(const double& x) const {

		Vector c(this->n);
		for (int i = 0; i < n; i++)
		{
			c.data[i] = this->data[i] * x;
		}
		return c;
	}
	Vector operator/(const double& x)const
	{
		Vector c(this->n);
		for (int i = 0; i < n; i++)
		{
			c.data[i] = this->data[i] / x;
		}
		return c;
	}
	Vector reverse_v() const
	{
		Vector c(this->n);
		for (int i = 0; i < n; i++)
		{
			c.data[i] = (-1) * this->data[i];
		}
		return c;
	}

	Vector& operator=(const Vector& v)
	{
		if (&v == this)
		{
			return *this;
		}
		this->n = v.n;
		delete[] data;
		data = new double[n];
		for (int i = 0; i < this->n; i++)
		{
			this->data[i] = v.data[i];
		}
		return *this;

	}
	Vector& operator+=(const Vector& v)
	{
		if (this->n != v.n) throw 0;
		for (int i = 0; i < this->n; i++)
		{
			this->data[i] += v.data[i];
		}
		return *this;
	}
	Vector& operator-=(const Vector& v)
	{
		if (this->n != v.n) throw 0;
		for (int i = 0; i < this->n; i++)
		{
			this->data[i] -= v.data[i];
		}
		return *this;
	}
	Vector& operator*=(const double& x)
	{
		for (int i = 0; i < this->n; i++)
		{
			this->data[i] *= x;
		}
		return *this;
	}
	Vector& operator/=(const double& x)
	{
		if (x == 0) throw "Division error (incorrect value)";

		for (int i = 0; i < this->n; i++)
		{
			this->data[i] /= x;
		}
		return *this;
	}
	~Vector()
	{
		delete[] data;
	}
}; 
