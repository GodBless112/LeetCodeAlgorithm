//	258. Add Digits
//------------------------------------------------------------------------------//
//	Given a non-negative integer num, repeatedly add all its digits until the	//
//	result has only one digit.													//
//	For example :																//
//	Given num = 38, the process is like : 3 + 8 = 11, 1 + 1 = 2. Since 2 has	//
//	only one digit, return it.													//
//	Follow up :																	//
//	Could you do it without any loop / recursion in O(1) runtime ?				//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>

// constants
// function prototype
using namespace std;
//迭代循环
class Solution {
public:
	int addDigits(int num) {
		while (num > 9) {
			int newNum = 0;
			while (num) {
				newNum += num % 10;
				num /= 10;
			}
			num = newNum;
		}
		return num;
	}
};
//对b进制的各位上数字求和来说
//dr(n)=0,n=0
//dr(n)=b-1, if n!=0 && n%(n-1)=0
//dr(n)=n mod (b-1),if n!=0 && n%(n-1)!=0
//可简化为dr(n) = 1 + (n - 1) % 9
class Solution2 {
public:
	int addDigits(int num) {
		return num == 0 ? 0 : num % 9 ? num % 9 : 9;
	}
};
class Solution3 {
public:
	int addDigits(int num) {
		return 1 + (num - 1) % 9;
	}
};
//int main(void)
//{
//	Solution2 test;
//	cout << test.addDigits(27);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}