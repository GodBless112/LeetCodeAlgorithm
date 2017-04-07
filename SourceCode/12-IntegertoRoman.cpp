//	12-Integer to Roman
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
// constants
// function prototype
using namespace std;
//查表法
class Solution 
{
public:
	string intToRoman(int num) 
	{
		char* RomanTable[4][10]=
		{
			{"","I","II","III","IV","V","VI","VII","VIII","IX"},
			{"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"},
			{"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"},
			{"","M","MM","MMM"}
		};
		string ret;
		ret += RomanTable[3][num / 1000];
		ret += RomanTable[2][num / 100 % 10];
		ret += RomanTable[1][num / 10 % 10];
		ret += RomanTable[0][num % 10];
		return ret;
	}
};
//查表法，静态声明
class Solution2
{
public:
	static char* RomanTable[4][10];
public:
	string intToRoman(int num)
	{
		
		string ret;
		ret += RomanTable[3][num / 1000];
		ret += RomanTable[2][num / 100 % 10];
		ret += RomanTable[1][num / 10 % 10];
		ret += RomanTable[0][num % 10];
		return ret;
	}
};
char* Solution2::RomanTable[4][10] =
{
	{ "","I","II","III","IV","V","VI","VII","VIII","IX" },
	{ "","X","XX","XXX","XL","L","LX","LXX","LXXX","XC" },
	{ "","C","CC","CCC","CD","D","DC","DCC","DCCC","CM" },
	{ "","M","MM","MMM" }
};
class Solution3 {
public:
	string intToRoman(int num) {
		const int radix[] = { 1000, 900, 500, 400, 100, 90,
			50, 40, 10, 9, 5, 4, 1 };
		const string symbol[] = { "M", "CM", "D", "CD", "C", "XC",
			"L", "XL", "X", "IX", "V", "IV", "I" };
		string roman;
		for (size_t i = 0; num > 0; ++i) {
			int count = num / radix[i];
			num %= radix[i];
			for (; count > 0; --count) roman += symbol[i];
		}
		return roman;
	}
};
//int main(void)
//{
//	Solution3 test;
//	cout << test.intToRoman(123) << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
