// Palindrome Number
//从最高位和最低位两头开始比较
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
// constants
// function prototype
using namespace std;
class Solution 
{
public:
	bool isPalindrome(int x) 
	{
		if (x < 0)
			return false;
		int division = 1;
		while (x / division >= 10)
			division *= 10;
		while (x > 0)
		{
			int left = x / division;
			int right = x % 10;
			if (left != right)
				return false;
			x = (x%division) / 10;
			division /= 100;
		}
		return true;
	}
};
//int main(void)
//{
//	Solution test;
//	cout << test.isPalindrome(12321) << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
