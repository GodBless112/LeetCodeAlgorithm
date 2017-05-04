//	66. Plus One
//------------------------------------------------------------------------------//
//	Given a non-negative integer represented as a non-empty array of digits,	//
//	plus one to the integer.													//
//	You may assume the integer do not contain any leading zero, except the		//
//	number 0 itself.															//
//	The digits are stored such that the most significant digit is at the head	//
//	of the list.																//
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
	vector<int> plusOne(vector<int>& digits) 
	{
		int n = digits.size();
		vector<int> result(n + 1, 0);
		int sum = 0;
		
		for (int i = n - 1; i >= 0; --i)
		{
			if (i == n - 1)
				sum = digits[i] + 1;
			else
				sum = digits[i] + result[i + 1];
			result[i + 1] = sum % 10;
			result[i] += sum / 10;
		}
		if (result[0] == 0)
			result.erase(result.begin());
		return result;
	}
};
//STL
class Solution2 
{
public:
	vector<int> plusOne(vector<int> &digits)
	{
		add(digits, 1);
		return digits;
	}
private:
	// 0 <= digit <= 9
	void add(vector<int> &digits, int digit) 
	{
		int c = digit; //统一成进位
		for (auto it = digits.rbegin(); it != digits.rend(); ++it) 
		{
			*it += c;
			c = *it / 10;
			*it %= 10;
		}
		if (c > 0) digits.insert(digits.begin(), 1);
	}
};
//STL:lamnbda函数
class Solution3
{
public:
	vector<int> plusOne(vector<int> &digits)
	{
		add(digits, 1);
		return digits;
	}
private:
	void add(vector<int> &digits, int digit)
	{
		int carry = digit;
		for_each(digits.rbegin(), digits.rend(), [&carry](int &d)
		{
			d += carry;
			carry = d / 10;
			d %= 10;
		});
	}
};

//int main(void)
//{
//	Solution3 test;
//	vector<int> input{ 1,9,9,9,9 };
//	auto x = test.plusOne(input);
//	for (auto y : input)
//		cout << y;
//	cout << endl;
//	for (auto y : x)
//		cout << y;
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
