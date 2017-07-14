//	367. Valid Perfect Square
//------------------------------------------------------------------------------//
//	Given a positive integer num, write a function which returns True if num	//
//	is a perfect square else False.												//
//	Note: Do not use any built - in library function such as sqrt.				//
//	Example 1 :																	//
//		Input : 16																//
//		Returns : True															//
//	Example 2 :																	//
//		Input : 14																//
//		Returns : False															//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_set>
#include<unordered_map>
// constants
// function prototype
using namespace std;
//现有sqrt求解
class Solution {
public:
	bool isPerfectSquare(int num) {
		if (num < 1) return false;
		int s = round(sqrt(num));
		return s*s == num;
	}
};
//牛顿迭代法求解sqrt
class Solution2 {
public:
	bool isPerfectSquare(int num) {
		if (num < 1) return false;
		long long r = num;
		while (r*r > num)
			r = (r + num / r) / 2;
		return r*r == num;
	}
};
//Bisection法求解根，二分搜索	
class Solution3 {
public:
	bool isPerfectSquare(int num) {
		if (num < 1) return false;
		long long l = 0, r = num;
		while (l <= r) {
			long long mid = l + (r - l) / 2;
			long long sqmid = mid*mid;
			if (sqmid > num) r = mid - 1;
			else if (sqmid < num) l = mid + 1;
			else return true;
		}
		return false;
	}
};
//利用完全平方数的特性，k^2=1+3+5+...+2*k-1
class Solution4 {
public:
	bool isPerfectSquare(int num) {
		if (num < 1) return false;
		for (int i = 1; num > 0; i += 2)
			num -= i;
		return num == 0;
	}
};
//int main(void)
//{
//	Solution2 test;
//	for (int i = 0; i < 16; ++i)
//		cout << i << " " << boolalpha << test.isPerfectSquare(i) << endl;
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