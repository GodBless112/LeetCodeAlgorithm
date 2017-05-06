//	50. Pow(x, n)
//------------------------------------------------------------------------------//
//	Implement pow(x, n).														//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<sstream>
// constants
// function prototype
using namespace std;

//递归版本
class Solution
{
public:
	double myPow(double x, int n) 
	{
		if (n == 0)
			return 1.0;
		if (n == INT_MIN)
			return myPow(x*x, n >> 1);
		if (n < 0)
			return 1.0/myPow(x, -n);
		if (n & 0x01)
			return x*myPow(x*x, n / 2);
		else
			return myPow(x*x, n / 2);
	}
};

//非递归版,比递归版效果稍好
class Solution2
{
public:
	double myPow(double x, int n)
	{
		double ret = 1.0;
		int sign = 0;
		if (n == INT_MIN)
		{
			x = x*x;
			n >>= 1;
		}
		if (n < 0)
		{
			n = -n;
			sign = 1;
		}
		while (n)
		{
			if (n & 0x01)
				ret *= x;
			x *= x;
			n >>= 1;
		}
		return sign ? (1.0 / ret) : ret;
	}
};
//另一种递归
class Solution3
{
public:
	double myPow(double x, int n) 
	{
		if (n == 0) return 1;
		double t = pow(x, n / 2);
		if (n % 2) 
		{
			return n < 0 ? 1 / x*t*t : x*t*t;
		}
		else {
			return t*t;
		}
	}
};
class Solution4
{
public:
	double myPow(double x, int n) {
		if (n < 0) return 1 / x * myPow(1 / x, -(n + 1));
		if (n == 0) return 1;
		if (n == 2) return x*x;
		if (n % 2 == 0) return myPow(myPow(x, n / 2), 2);
		else return x*myPow(myPow(x, n / 2), 2);
	}
};
//int main(void)
//{
//	Solution4 test;
//	cout << test.myPow(34.00515, INT_MIN) << endl << pow(34.00515, INT_MIN) << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
