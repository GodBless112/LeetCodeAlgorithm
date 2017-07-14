//	326. Power of Three
//------------------------------------------------------------------------------//
//	Given an integer, write a function to determine if it is a power of three.	//
//	Follow up :																	//
//	Could you do it without using any loop / recursion ?						//
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
//逐一比较，时间复杂度O(log3n)
class Solution {
public:
	bool isPowerOfThree(int n) {
		int p = 1;
		if (n == 1) return true;
		int max = INT_MAX / 3;
		while (p < max) {
			p = p * 3;
			if (p == n)
				return true;
		}
		return false;
	}
};
class Solution2 {
public:
	bool isPowerOfThree(int n) {
		if (n < 1) return false;
		while (n % 3 == 0)
			n /= 3;
		return n == 1;
	}
};
//数学方法,n=3^i,判断i是否为整数,此处可能存在舍入误差，可以利用epsilon
class Solution3 {
public:
	bool isPowerOfThree(int n) {
		double index = log10(n) / log10(3);
		return fmod(index, 1) < numeric_limits<double>::epsilon();	
	}
};
//同power of two，对这种质数的指数来说，3^19​​的因数只能是3^0​​，3^1,..., 3^19​​
class Solution4 {
public:
	bool isPowerOfThree(int n) {
		return n > 0 && 1162261467 % n == 0;
	}
};

//直接存成表
class Solution5 {
public:
	bool isPowerOfThree(int n) {
		return dict.find(n) != dict.end();
	}
private:
	static unordered_set<int> dict;
};
unordered_set<int> Solution5::dict{ 1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441, 1594323, 4782969, 14348907, 43046721, 129140163, 387420489, 1162261467 };
//int main(void)
//{
//	Solution5 test;
//	cout << boolalpha << test.isPowerOfThree(25);
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