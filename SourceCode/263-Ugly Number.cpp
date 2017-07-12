//	263. Ugly Number
//------------------------------------------------------------------------------//
//	Write a program to check whether a given number is an ugly number.			//
//	Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. //
//	For example, 6, 8 are ugly while 14 is not ugly since it includes another	//
//	prime factor 7.																//
//	Note that 1 is typically treated as an ugly number.							//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<set>
// constants
// function prototype
using namespace std;
class Solution {
public:
	bool isUgly(int num) {
		if (num <= 0) return false;
		if (num == 1) return true;
		while (true) {
			if (num % 5 == 0)
				num /= 5;
			else if (num % 3 == 0)
				num /= 3;
			else if (num % 2 == 0)
				num /= 2;
			else
				break;
		}
		return num == 1;
	}
};
//变形
class Solution2 {
public:
	bool isUgly(int num) {
		for (int i = 2; i<6 && num; i++)
			while (num % i == 0)
				num /= i;
		return num == 1;
	}
};
class Solution3 {
public:
	bool isUgly(int num) {
		if (num == 0) return false;

		while (num % 2 == 0) num /= 2;
		while (num % 3 == 0) num /= 3;
		while (num % 5 == 0) num /= 5;

		return num == 1;
	}
};
//int main(void)
//{
//	Solution3 test;
//	for (int i = 0; i < 20; i++)
//		cout << i << " " << boolalpha << test.isUgly(i) << endl;
//	cout << INT_MAX << " " << boolalpha << test.isUgly(INT_MAX) << endl;
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