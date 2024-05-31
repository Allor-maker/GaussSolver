#include <iostream>
#include <ctime>
#include "GaussSolver.h"
#include "vector.h"

int main()
{
	//system where m<n the answer is correct
	std::vector < double > arr1{ 3,2,6,8 };
	Vector a1(arr1);
	std::vector < double > arr2{ 1,4,5,7 };
	Vector a2(arr2);
	//std::vector<Vector<int>> arr_1{ a1,a2,a3 };
	std::vector<Vector> arr_2{ a1,a2 };//1
	//std::vector<Vector<int>> arr_3{ a1,a2,a3,a4 };
	std::vector<double>v1{ 6,10 };
	GaussSolver g2;
	//GaussSolver::print(g2.solve(arr_2, v1));

	//test for the 2*2 system (the answer is correct)
	std::vector<double> t_a1{ 4,-2 };
	std::vector<double> t_a2{ 6,1 };
	Vector t_a1_1(t_a1);
	Vector t_a1_2(t_a2);
	std::vector<double> v_0{ 22,45 };
	Vector v_1(v_0);

	std::vector<Vector> test_arr{ t_a1_1,t_a1_2 };
	GaussSolver A;
	//GaussSolver::print(A.solve(test_arr, v_1));

	//m>n system, no solutions
	std::vector<double> arr3{ 3,2 };
	Vector a3(arr3);
	std::vector<double> arr4{ 1,4 };
	Vector a4(arr4);
	std::vector<double> arr5{ 10,4 };
	Vector a5(arr5);
	std::vector<double>v2{ 6,10 };
	std::vector<Vector> arr_3{ a3,a4,a5 };

	GaussSolver B;
	//GaussSolver::print(B.solve(arr_3, v2));

	// m > n system, there is a solution
	std::vector<double> arr6{ 3,2 };
	Vector a6(arr6);
	std::vector<double> arr7{ 1,4 };
	Vector a7(arr7);
	std::vector<double> arr8{ 0,0 };
	Vector a8(arr8);
	std::vector<double>v3{ 1,2,0 };
	std::vector<Vector> arr_4{ a6,a7,a8 };

	GaussSolver С;
	//GaussSolver::print(С.solve(arr_4, v3));



	//test for matrix 100x100
	srand(time(NULL));
	Matrix Mat(100, 100);
	Matrix B_1(100);
	Vector X(100, 1);
	Matrix x_1(X);
	Vector B_2(100);
	GaussSolver q;
	std::vector<Vector> ans;
	for (int k = 0; k < 100; k++)
	{
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				Mat(i, j) = rand() % 10;
			}
		}
		B_1 = Mat * x_1;
		//B_1.print();
		for (int i = 0; i < 100; i++)
		{
			B_2[i] = B_1[i][0];
		}
		
		//ans = q.solve(Mat, B_2);
		for (int i = 0; i < 100; i++)
		{
			//if (abs(ans[0][i] - 1.0) > 0.0000000001)
			//{
				//std::cout <<i<<". " <<ans[0][i] << std::endl;
			//}
			
		}
	}
	
	
	
	
	//test fo matrix 2x5
	Matrix Mat2(2,5);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Mat2(i, j) = rand() % 10;
		}
	}
	Vector J_test(2);
	for (int i = 0; i < 2; i++)
	{
		J_test[i] = rand() % 10;
	}
	//J_test.print();
	//Mat2.print();
	GaussSolver J;
	std::vector<Vector> J_ans;
	//J_ans = J.solve(Mat2, J_test);
	//GaussSolver::print(J_ans);
	

	Matrix Mat_2(10, 10);
	Vector V_2(10);
	std::vector<Vector> ans2;
	GaussSolver o;
	//ans2 = o.solve(Mat_2, V_2);
	//GaussSolver::print(ans2);
	

	//test for matrix with 0-vecr
	Matrix Mat_null_vect(2, 5);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (j == 2)
				continue;
			Mat_null_vect(i, j) = rand() % 10;
		}
	}
	Vector null_vect_test(2);
	for (int i = 0; i < 2; i++)
	{
		null_vect_test[i] = rand() % 10;
	}
	//null_vect_test.print();
	//Mat_null_vect.print();
	GaussSolver null_vect;
	std::vector<Vector> null_vect__ans;
	//null_vect__ans = J.solve(Mat_null_vect, null_vect_test);
	//GaussSolver::print(null_vect__ans);

	//test for null-matrix
	Matrix null_mat(10, 10);
	Vector null_vec(10);
	std::vector<Vector> test_null;
	GaussSolver n;
	//test_null = n.solve(null_mat, null_vec);
	//GaussSolver::print(test_null);
}