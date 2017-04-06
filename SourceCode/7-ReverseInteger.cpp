// Reverse Integer
#include <iostream>
#include<vector>
#include<string>
// constants
// function prototype
using namespace std;
class Solution {
public:
	int reverse(int x) 
	{
		long long result = 0;
		long long temp = x;
		int symbol = 1;
		if (x == 0)
			return x;
		if (temp < 0)
		{
			temp = -temp;
			symbol = -1;
		}
		while (temp)
		{
			result = result * 10 + temp % 10;
			temp /= 10;
		}
		if ((result > 2147483647) || (symbol == -1 && result > 2147483648))
			return 0;
		else
			return symbol*result;
	}
};
//int main(void)
//{
//	Solution test;
//	int a = -2147483647-1;
//	cout << test.reverse(a);
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
