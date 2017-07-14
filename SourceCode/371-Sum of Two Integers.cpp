//	371. Sum of Two Integers
//------------------------------------------------------------------------------//
//	Calculate the sum of two integers a and b, but you are not allowed to use	//
//	the operator + and -.														//
//	Example:																	//
//	Given a = 1 and b = 2, return 3.											//
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
//先或得到所有比特，如果某些位上两者都为1，则需要进位
class Solution {
public:
	int getSum(int a, int b) {
		int Xor = a | b, And = a & b;
		while (And) {
			Xor ^= And;		//进位
			int temp = Xor;
			Xor |= (And << 1);	//进位
			And = temp & (And << 1);
		}
		return Xor;
	}
};
//改进版
class Solution2 {
public:
	int getSum(int a, int b) {
		int sum = a;

		while (b != 0)
		{
			sum = a ^ b;//calculate sum of a and b without thinking the carry 
			b = (a & b) << 1;//calculate the carry
			a = sum;//add sum(without carry) and carry
		}

		return sum;
	}
};
//法2的迭代版
class Solution3 {
public:
	int getSum(int a, int b) {
		if (b == 0) return a;
		int sum, carry;
		sum = a^b;
		carry = (a&b) << 1;
		return getSum(sum, carry);
	}
};
//int main(void)
//{
//	Solution3 test;
//	for (int i = 0; i < 16; ++i)
//		cout << i << " " << boolalpha << test.getSum(i,-8) << endl;
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