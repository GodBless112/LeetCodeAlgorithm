//	29. Divide Two Integers
//------------------------------------------------------------------------------//
//	Divide two integers without using multiplication, division and mod operator.//
//	If it is overflow, return MAX_INT.											//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
#include<stack>
#include<list>
// constants
// function prototype
using namespace std;
//不断的减去除数，每次将除数加倍，减少时间
class Solution
{
public:
	int divide(int dividend, int divisor)
	{
		if (divisor == 0 || (dividend == INT_MIN) && (divisor == -1))
			return INT_MAX;
		long long a = dividend > 0 ? dividend : -(long long)dividend;
		long long b = divisor > 0 ? divisor : -(long long)divisor;
		long long result = 0;
		while (a >= b)
		{
			long long c = b;
			for (int i = 0; a >= c; i++, c <<= 1)
			{
				a -= c;
				result += 1 << i;
			}
		}
		return ((dividend^divisor) >> 31) ? (-result) : result;
	}
};
//2,3思想类似于1，只是先把divisor倍增到小于dividend的值，减去，反复
class Solution2 {
public:
	int divide(int dividend, int divisor) {
		if (!divisor || (dividend == INT_MIN && divisor == -1))
			return INT_MAX;
		int result = 0;
		const bool sign = (dividend > 0 && divisor < 0) ||
			(dividend < 0 && divisor > 0);
		unsigned int a = dividend >= 0 ? dividend : -dividend;
		unsigned int b = divisor >= 0 ? divisor : -divisor;
		while (a >= b) {
			int multi = 1;
			unsigned int bb = b;
			while (a >= bb) {
				a -= bb;
				result += multi;
				if (bb < INT_MAX >> 1) { // 􄭡􂂑􂏑􀜩
					bb += bb;
					multi += multi;
				}
			}
		}
		if (sign) return -result;
		else return result;
	}
};
class Solution3 {
public:
	int divide(int dividend, int divisor) {
		//special cases
		if (divisor == 0 || (dividend == INT_MIN && divisor == -1))
			return INT_MAX;

		// transform to unsigned int
		bool sign = (dividend > 0) ^ (divisor > 0);
		unsigned int A = (divisor < 0) ? -divisor : divisor;
		unsigned int B = (dividend < 0) ? -dividend : dividend;
		int ret = 0;

		// shift 32 times
		for (int i = 31; i >= 0; i--)
		{
			if ((B >> i) >= A)
			{
				ret = (ret << 1) | 0x01;
				B -= (A << i);   // update B
			}
			else
				ret = ret << 1;
		}

		if (sign)
			ret = -ret;

		return ret;
	}
};
//int main(void)
//{
//	Solution3 test;
//	auto x = test.divide(8, 3);
//	cout << x;
//
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
