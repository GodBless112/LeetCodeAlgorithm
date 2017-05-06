//	67. Add Binary
//------------------------------------------------------------------------------//
//	Given two binary strings, return their sum (also a binary string).			//
//	For example,																//
//	a = "11"																	//
//	b = "1"																		//
//	Return "100".																//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
// constants
// function prototype
using namespace std;
class Solution 
{
public:
	string addBinary(string a, string b) 
	{
		if (a.empty() || b.empty())
			return a.empty() ? b : a;
		int size_a = a.size(), size_b = b.size();
		int size = max(size_a, size_b);
		string result(size, '0');
		int sum = 0, carry = 0;
		for (int i = 0; i < size; ++i)
		{
			int aVal = i < size_a ? a[size_a - i - 1] - '0' : 0;
			int bVal = i < size_b ? b[size_b - i - 1] - '0' : 0;
			sum = aVal + bVal + carry;
			result[size - 1 - i] = sum % 2 + '0';
			carry = sum / 2;
		}
		if (carry != 0)
			result.insert(result.begin(), carry + '0');
		return result;
	}
};
//先将a，b逆序然后相加
class Solution2
{
public:
	string addBinary(string a, string b)
	{
		string result;
		size_t n = max(a.size(), b.size());
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		int carry = 0;
		for (size_t i = 0; i < n; i++)
		{
			int a_val = i < a.size() ? a[i] - '0' : 0;
			int b_val = i < b.size() ? b[i] - '0' : 0;
			int val = a_val + b_val + carry;
			result.insert(result.begin(), val % 2 + '0');
			carry = val / 2;
		}
		if (carry == 1)
			result.insert(result.begin(), '1');
		return result;
	}
};
//int main(void)
//{
//	Solution2 test;
//	string a = "111111";
//	string b = "01";
//	cout << test.addBinary(a, b);
//	
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
