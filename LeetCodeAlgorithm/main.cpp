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

class Solution {
public:
	int divide(int dividend, int divisor) {
		// 􁒂 dividend = INT_MIN 􁬥􅖌-dividend 􀑉􂏑􀜩􅖌􁝯􀐔􂩗 long long
		long long a = dividend >= 0 ? dividend : -(long long)dividend;
		long long b = divisor >= 0 ? divisor : -(long long)divisor;
		// 􁒂 dividend = INT_MIN 􁬥􅖌divisor = -1 􁬥􅖌􃐂􁳋􀑉􂏑􀜩􅖌􁝯􀐔􂩗 long long
		long long result = 0;
		while (a >= b) {
			long long c = b;
			for (int i = 0; a >= c; ++i, c <<= 1) {
				a -= c;
				result += 1 << i;
			}
		}
		return ((dividend^divisor) >> 31) ? (-result) : (result);
	}
};

int main(void)
{
	Solution test;
	auto x=test.divide(8,3);
	cout << x;
	// code to keep window open for MSVC++
	cin.clear();
	while (cin.get() != '\n')
		continue;
	cin.get();

	return 0;
}
