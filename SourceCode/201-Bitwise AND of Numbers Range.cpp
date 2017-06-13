//	201. Bitwise AND of Numbers Range
//------------------------------------------------------------------------------//
//	Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise	//
//	AND of all numbers in this range, inclusive.								//
//	For example, given the range[5, 7], you should return 4.					//
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
//思想是，对于m到n，如果对应的二进制位相同则保持不变，
//不同则代表这一位上发生了改变，则这一位一定为0
class Solution {
public:
	int rangeBitwiseAnd(int m, int n) {
		int bits1 = getbits(m), bits2 = getbits(n);
		if (bits1 < bits2) return 0;
		int result = 0;
		for (int i = bits1 - 1; i >= 0; --i) {
			int shift = 1 << i;
			if ((shift&m) == (shift&n))
				result |= shift&m;
			else
				break;
		}
		return result;
	}
private:
	int getbits(int x) {
		int bits = 0;
		while (x) {
			bits++;
			x >>= 1;
		}
		return bits;
	}
};
//递归的做法
class Solution2 {
public:
	int rangeBitwiseAnd(int m, int n) {
		return (n > m) ? (rangeBitwiseAnd(m >> 1, n >> 1)) << 1 : m;
	}
};
class Solution3 {
public:
	int rangeBitwiseAnd(int m, int n) {
		while (m < n) n = n & (n - 1);
		return n;
	}
};
//迭代的做法
class Solution4 {
public:
	int rangeBitwiseAnd(int m, int n) {
		if (m == 0) {
			return 0;
		}
		int moveFactor = 1;
		while (m != n) {
			m >>= 1;
			n >>= 1;
			moveFactor <<= 1;
		}
		return m * moveFactor;
	}
};
//int main(void)
//{
//	Solution4 test;
//	cout << test.rangeBitwiseAnd(11, 12);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}