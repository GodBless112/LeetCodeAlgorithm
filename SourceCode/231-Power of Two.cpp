//	231. Power of Two
//------------------------------------------------------------------------------//
//	Given an integer, write a function to determine if it is a power of two.	//
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
//跟每一个2的幂次比较，时间复杂度O(logn)
class Solution {
public:
	bool isPowerOfTwo(int n) {
		for (int i = 0; i < 31; ++i)
			if ((n^(1 << i)) == 0)
				return true;
		return false;
	}
};
//求二进制1的个数的方法，利用n&(n-1),时间复杂度O(1)
class Solution2 {
public:
	bool isPowerOfTwo(int n) {
		return n > 0 && !(n&(n - 1));
	}
};
//递归，时间复杂度O(logn)
class Solution3 {
public:
	bool isPowerOfTwo(int n) {
		return n > 0 && (n == 1 || (n % 2 == 0 && isPowerOfTwo(n / 2)));
	}
};
//数学的方法，对整型来说最大值为2^30
//（1）如果n=2^k，则2^30 = 2^k * 2^(30-k)，则2^30 % 2^k = 0
//（2）假设n=2^k * j,j为奇数，那么2^30 % n=2^30 % (j*2^k)=2^(30-k) % j != 0
class Solution4 {
public:
	bool isPowerOfTwo(int n) {
		return n > 0 && (1073741824 % n == 0);
	}
};
//int main(void)
//{
//	Solution4 test;
//	cout << boolalpha << test.isPowerOfTwo(1<<30);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}