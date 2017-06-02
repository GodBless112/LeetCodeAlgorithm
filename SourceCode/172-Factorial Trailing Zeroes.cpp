//	172. Factorial Trailing Zeroes
//------------------------------------------------------------------------------//
//	Given an integer n, return the number of trailing zeroes in n!.				//
//	Note: Your solution should be in logarithmic time complexity. 				//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<ctime>
// constants
// function prototype
using namespace std;
//数学问题，看后面有几个0，只能是由5的倍数元素构成
//5的话会构成1个0,25会构成2个0，...，以此类推
class Solution {
public:
	int trailingZeroes(int n) {
		int result = 0;
		while (n >= 5) {
			result += n / 5;
			n /= 5;		//除是为了避免越界
		}
		return result;
	}
};
//想要乘的话，需要用longlong
class Solution2 {
public:
	int trailingZeroes(int n) {
		int result = 0;
		for (long long i = 5; n / i>0; i *= 5) {
			result += (n / i);
		}
		return result;
	}
};
//递归
class Solution3 {
public:
	int trailingZeroes(int n) {
		return n == 0 ? 0 : n / 5 + trailingZeroes(n / 5);
	}
};
//int main(void)
//{
//	Solution3 test;
//	cout << test.trailingZeroes(2015);
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