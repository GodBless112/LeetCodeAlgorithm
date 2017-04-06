// String to Integer (atoi)
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
// constants
// function prototype
using namespace std;
class Solution {
public:
	int myAtoi(string str) 
	{
		int result = 0;
		int symbol = 1;
		int i = 0;
		const int n = str.size();
		while (i < n && str[i] == ' ')
			i++;
		if (i < n && str[i] == '+')
			i++;
		else if (i < n && str[i] == '-')
		{
			symbol = -1;
			i++ ;
		}
		for (; i < str.size(); i++)
		{
			if (isdigit(str[i]))
			{
				int x = str[i] - '0';
				if (result > INT_MAX / 10 || (result == INT_MAX / 10 && x > 7))
					return symbol == -1 ? INT_MIN : INT_MAX;
				result = result * 10 + x;
			}
			else
				break;
		}
		return symbol*result;
	}
};
class Solution2
{
public:
	int myAtoi(string str) {
		long result = 0;
		int indicator = 1;
		int i = str.find_first_not_of(' ');
		if (i == -1)
			return 0;
		for (; i<str.size();)
		{
			if (str[i] == '-' || str[i] == '+')
				indicator = (str[i++] == '-') ? -1 : 1;
			while ('0' <= str[i] && str[i] <= '9')
			{
				result = result * 10 + (str[i++] - '0');
				if (result*indicator >= INT_MAX) return INT_MAX;
				if (result*indicator <= INT_MIN) return INT_MIN;
			}
			return result*indicator;
		}
	}
};
class Solution3
{
public:
	int myAtoi(string str)
	{
		int ret = 0;
		int base = INT_MAX / 10;
		int i = str.find_first_not_of(' ');
		int sign = 1;
		if (i == -1)
			return 0;
		if (str[i] == '+' || str[i] == '-')
			sign = (str[i++] == '-') ? -1 : 1;
		while (isdigit(str[i]))
		{
			if (ret > base || (ret == base) && (str[i] - '0') > 7)
				return sign > 0 ? INT_MAX : INT_MIN;
			ret = ret * 10 + (str[i++] - '0');
		}
		return ret*sign;
	}
};
//int main(void)
//{
//	Solution3 test;
//	cout << test.myAtoi("  -2147483649") << endl;
//	cout << atoi("-2147483649");
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
