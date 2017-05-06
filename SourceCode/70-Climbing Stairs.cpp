//	70. Climbing Stairs
//------------------------------------------------------------------------------//
//	You are climbing a stair case. It takes n steps to reach to the top.		//
//	Each time you can either climb 1 or 2 steps.In how many distinct ways can	//
//	you climb to the top ?														//
//	Note : Given n will be a positive integer.									//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
// constants
// function prototype
using namespace std;
//可以看成是一个斐波拉契数列，另F[i]为爬到i的方法书，对于第i阶梯，想要爬上去
//可以从i-1爬1步，i-2爬2步，则F[i]=F[i-1]+F[i-2]
//迭代
class Solution 
{
public:
	int climbStairs(int n) 
	{
		int prev = 0;
		int cur = 1;
		for (int i = 1; i <= n; i++)
		{
			int tmp = cur;
			cur += prev;
			prev = tmp;
		}
		return cur;
	}
};
//公式法：斐波拉契数列通项公式:an=1/5^(1/2){[(1+5^(1/2))/2]^n-[(1-5^(1/2))/2]^n}
class Solution2
{
public:
	int climbStairs(int n)
	{
		double C = sqrt(5);
		return floor((pow((1 + C) / 2, n + 1) + pow((1 - C) / 2, n + 1)) / C + 0.5);
	}
};
//二分法求斐波拉契数列第n项值，O(logn)
class Solution3
{
public:
	int climbStairs(int n)
	{
		if (n == 0 || n == 1)
			return 1;
		int a1[2] = { 1,1 };
		int a2[2] = { 1,0 };
		int *a[2] = { a1,a2 };
		MATRIX b(a, 2);
		MATRIX res = MatrixPow(b, n);
		return res.m[0][0];
	}
private:
	class MATRIX
	{
	public:
		explicit MATRIX(int N = 0) :m(N), MatrixSize(N)
		{
			for (int i = 0; i < N; i++)
				m[i].resize(N);
			//初始化为单位阵
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					m[i][j] = (i == j);
		}
		MATRIX(int **input_matrix, int N) :m(N), MatrixSize(N)
		{
			for (int i = 0; i < N; i++)
				m[i].resize(N);
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					m[i][j] = input_matrix[i][j];
		}
		friend MATRIX MatrixPow(MATRIX m, int k)
		{
			MATRIX T(m.MatrixSize);
			while (k)
			{
				if (k & 1) //k为奇数
					T = T*m;
				m = m*m;
				k >>= 1;
			}
			return T;
		}
#ifndef MOD
		friend MATRIX operator*(const MATRIX &m, const MATRIX &n)
		{
			MATRIX U(m.MatrixSize);
			if (m.MatrixSize != n.MatrixSize)
			{
				cerr << "Error!\n";
				return U;
			}
			for (int i = 0; i < m.MatrixSize; i++)
			{
				for (int j = 0; j < m.MatrixSize; j++)
				{
					U.m[i][j] = 0;
					for (int k = 0; k < m.MatrixSize; k++)
					{
						U.m[i][j] += m.m[i][k] * n.m[k][j];
					}
				}

			}
			return U;
		}
#else
		//取模值的情况
		friend MATRIX operator*(const MATRIX &m, const MATRIX &n)
		{
			MATRIX U(m.MatrixSize);
			if (m.MatrixSize != n.MatrixSize)
			{
				cerr << "Error!\n";
				return U;
			}
			for (int i = 0; i < m.MatrixSize; i++)
			{
				for (int j = 0; j < m.MatrixSize; j++)
				{
					U.m[i][j] = 0;
					for (int k = 0; k < m.MatrixSize; k++)
					{
						U.m[i][j] += (m.m[i][k] % MOD) * (n.m[k][j] % MOD);
						U.m[i][j] = U.m[i][j] % MOD;
					}
				}

			}
			return U;
		}
#endif // !MOD
	public:
		std::vector<std::vector<int>> m;
		int MatrixSize;
	};
};
//int main(void)
//{
//	Solution2 test;
//	cout << test.climbStairs(10);
//	cout << endl;
//	
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
