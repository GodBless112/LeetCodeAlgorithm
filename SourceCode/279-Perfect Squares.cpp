//	279. Perfect Squares
//------------------------------------------------------------------------------//
//	Given a positive integer n, find the least number of perfect square numbers //
//	(for example, 1, 4, 9, 16, ...) which sum to n.								//
//	For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13,	//
//	return 2 because 13 = 4 + 9.												//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<queue>

// constants
// function prototype
using namespace std;
//令n=a^2+b^2+c^2，由Legendre's three-square theorem可知，不能由三个表达的情况只能是
//n=4^a*(8*b+7)，此时由4个组成
class Solution {
public:
	int numSquares(int n) {
		while (n % 4 == 0)
			n /= 4;
		int ub = sqrt(n);
		for (int a = 0; a <= ub; ++a) {
			for (int b = a; b <= ub; ++b) {
				int c = sqrt(n - a*a - b*b);
				if (a*a + b*b + c*c == n)
					return !!a + !!b + !!c;
			}
		}
		return 4;
	}
};
//动态规划，采用static的数组而不是本地的
class Solution2 {
public:
	int numSquares(int n) {
		static vector<int> dp { 0 };
		while (dp.size() <= n) {
			int m = dp.size(), squares = INT_MAX;
			for (int i = 1; i*i <= m; ++i)
				squares = min(squares, dp[m - i*i] + 1);
			dp.push_back(squares);
		}
		return dp[n];
	}
};
//在2的基础上调整了循环结构，使其更快
class Solution3 {
public:
	int numSquares(int n) {
		static vector<int> dp{ 0 };
		int m = dp.size();
		dp.resize(max(m, n + 1), INT_MAX);
		for (int i = 1, i2; (i2 = i*i) <= n; ++i)
			for (int j = max(m, i2); j <= n; ++j)
				if (dp[j] > dp[j - i2] + 1)
					dp[j] = dp[j - i2] + 1;
		return dp[n];
	}
};
//广度优先搜索，类似于图的思想
class Solution4
{
public:
	int numSquares(int n)
	{
		if (n <= 0)
		{
			return 0;
		}

		// perfectSquares contain all perfect square numbers which 
		// are smaller than or equal to n.
		vector<int> perfectSquares;
		// cntPerfectSquares[i - 1] = the least number of perfect 
		// square numbers which sum to i.
		vector<int> cntPerfectSquares(n);

		// Get all the perfect square numbers which are smaller than 
		// or equal to n.
		for (int i = 1; i*i <= n; i++)
		{
			perfectSquares.push_back(i*i);
			cntPerfectSquares[i*i - 1] = 1;
		}

		// If n is a perfect square number, return 1 immediately.
		if (perfectSquares.back() == n)
		{
			return 1;
		}

		// Consider a graph which consists of number 0, 1,...,n as
		// its nodes. Node j is connected to node i via an edge if  
		// and only if either j = i + (a perfect square number) or 
		// i = j + (a perfect square number). Starting from node 0, 
		// do the breadth-first search. If we reach node n at step 
		// m, then the least number of perfect square numbers which 
		// sum to n is m. Here since we have already obtained the 
		// perfect square numbers, we have actually finished the 
		// search at step 1.
		queue<int> searchQ;
		for (auto& i : perfectSquares)
		{
			searchQ.push(i);
		}

		int currCntPerfectSquares = 1;
		while (!searchQ.empty())
		{
			currCntPerfectSquares++;

			int searchQSize = searchQ.size();
			for (int i = 0; i < searchQSize; i++)
			{
				int tmp = searchQ.front();
				// Check the neighbors of node tmp which are the sum 
				// of tmp and a perfect square number.
				for (auto& j : perfectSquares)
				{
					if (tmp + j == n)
					{
						// We have reached node n.
						return currCntPerfectSquares;
					}
					else if ((tmp + j < n) && (cntPerfectSquares[tmp + j - 1] == 0))
					{
						// If cntPerfectSquares[tmp + j - 1] > 0, this is not 
						// the first time that we visit this node and we should 
						// skip the node (tmp + j).
						cntPerfectSquares[tmp + j - 1] = currCntPerfectSquares;
						searchQ.push(tmp + j);
					}
					else if (tmp + j > n)
					{
						// We don't need to consider the nodes which are greater ]
						// than n.
						break;
					}
				}

				searchQ.pop();
			}
		}

		return 0;
	}
};
//数学方法，基本思路同1
class Solution5
{
private:
	int is_square(int n)
	{
		int sqrt_n = (int)(sqrt(n));
		return (sqrt_n*sqrt_n == n);
	}

public:
	// Based on Lagrange's Four Square theorem, there 
	// are only 4 possible results: 1, 2, 3, 4.
	int numSquares(int n)
	{
		// If n is a perfect square, return 1.
		if (is_square(n))
		{
			return 1;
		}

		// The result is 4 if and only if n can be written in the 
		// form of 4^k*(8*m + 7). Please refer to 
		// Legendre's three-square theorem.
		while ((n & 3) == 0) // n%4 == 0  
		{
			n >>= 2;
		}
		if ((n & 7) == 7) // n%8 == 7
		{
			return 4;
		}

		// Check whether 2 is the result.
		int sqrt_n = (int)(sqrt(n));
		for (int i = 1; i <= sqrt_n; i++)
		{
			if (is_square(n - i*i))
			{
				return 2;
			}
		}

		return 3;
	}
};
//数学方法：5的简化
class Solution6
{
public:
	int numSquares(int n) {
		while (n % 4 == 0)
			n /= 4;
		if (n % 8 == 7)
			return 4;
		for (int a = 0; a*a <= n; ++a) {
			int b = sqrt(n - a*a);
			if (a*a + b*b == n)
				return 1 + !!a;
		}
		return 3;
	}
};
//数学方法，利用双指针
class Solution7 {
public:
	int numSquares(int n) {
		while (n % 4 == 0)
			n /= 4;
		if (n % 8 == 7)
			return 4;
		int a = -1, b = sqrt(n);
		n -= b * b;
		b += b + 1;
		while (a <= b) {
			if (n < 0)
				n += b -= 2;
			else if (n > 0)
				n -= a += 2;
			else
				return a < 0 ? 1 : 2;
		}
		return 3;
	}
};
//int main(void)
//{
//	Solution5 test;
//	cout << test.numSquares(48);
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