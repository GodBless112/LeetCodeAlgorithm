//	202. Happy Number
//------------------------------------------------------------------------------//
//	Write an algorithm to determine if a number is "happy".						//
//	A happy number is a number defined by the following process : Starting with //
//	any positive integer, replace the number by the sum of the squares of its	//
//	digits, and repeat the process until the number equals 1 (where it will		//
//	stay), or it loops endlessly in a cycle which does not include 1. Those		//
//	numbers for which this process ends in 1 are happy numbers.					//
//	Example : 19 is a happy number												//
//		1^2 + 9^2 = 82															//
//		8^2 + 2^2 = 68															//
//		6^2 + 8^2 = 100															//
//		1^2 + 0^2 + 0^2 = 1 													//
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
//利用hash表记录元素是否出现过
class Solution {
public:
	bool isHappy(int n) {
		unordered_set<int> dict;
		while (true) {
			if (1 == n) return true;
			if (dict.find(n) != dict.end())
				return false;
			dict.insert(n);
			n = calHappyNumber(n);
		}
	}
private:
	int calHappyNumber(int n) {
		int result = 0, tmp;
		while (n) {
			tmp = n % 10;
			result += tmp*tmp;
			n /= 10;
		}
		return result;
	}
};
//不用hash表，应用Floyd环路检测算法
class Solution2 {
public:
	bool isHappy(int n) {
		int slow, fast;
		slow = fast = n;
		do {
			slow = calHappyNumber(slow);
			fast = calHappyNumber(fast);
			fast = calHappyNumber(fast);
		} while (slow != fast);
		if (slow == 1) return 1;
		else return 0;
	}
private:
	int calHappyNumber(int n) {
		int result = 0, tmp;
		while (n) {
			tmp = n % 10;
			result += tmp*tmp;
			n /= 10;
		}
		return result;
	}
};
//数学方法，利用[2,6]不是happynumber的事实，并且所有非happynumber最终会形成环，落在这个区间
class Solution3 {
public:
	bool isHappy(int n) {
		while (n>6) {
			int next = 0;
			while (n) { next += (n % 10)*(n % 10); n /= 10; }
			n = next;
		}
		return n == 1;
	}
};
//int main(void)
//{
//	Solution3 test;
//	cout << boolalpha << test.isHappy(910);
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//	
//	return 0;
//}