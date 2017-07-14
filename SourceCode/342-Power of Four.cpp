//	342. Power of Four
//------------------------------------------------------------------------------//
//	Given an integer (signed 32 bits), write a function to check whether it is	//
//	a power of 4.																//
//	Example:																	//
//	Given num = 16, return true.Given num = 5, return false.					//
//	Follow up : Could you solve it without loops / recursion ?					//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_set>
// constants
// function prototype
using namespace std;
//逐一比较，时间复杂度O(log4n)
class Solution {
public:
	bool isPowerOfFour(int num) {
		for (int i = 0; i < 16; ++i)
			if ((num ^ (1 << (2*i))) == 0)
				return true;
		return false;
	}
};
class Solution2 {
public:
	bool isPowerOfFour(int num) {
		if (num < 1) return false;
		while (num % 4 == 0)
			num /= 4;
		return num == 1;
	}
};
//数学方法,n=3^i,判断i是否为整数,此处可能存在舍入误差，可以利用epsilon
class Solution3 {
public:
	bool isPowerOfFour(int num) {
		double index = log10(num) / log10(4);
		return fmod(index, 1) < numeric_limits<double>::epsilon();	
	}
};

//直接存成表
class Solution4 {
public:
	bool isPowerOfFour(int num) {
		return dict.find(num) != dict.end();
	}
private:
	static unordered_set<int> dict;
};
unordered_set<int> Solution4::dict{ 1, 4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 1048576, 4194304, 16777216, 67108864, 268435456, 1073741824};
//利用泰勒展开的性质，4^n=(3+1)^n=3^n...+1
class Solution5 {
public:
	bool isPowerOfFour(int num) {
		return num > 0 && (num&(num - 1)) == 0 && (num - 1) % 3 == 0;
	}
};
//排除2^n的情况
class Solution6 {
public:
	bool isPowerOfFour(int num) {
		return num > 0 && (1073741824 % num == 0) && (num & 0x55555555) != 0;
	}
};
//int main(void)
//{
//	Solution5 test;
//	cout << boolalpha << test.isPowerOfFour(16);
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