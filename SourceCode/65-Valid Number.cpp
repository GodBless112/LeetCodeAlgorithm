//	65. Valid Number
//------------------------------------------------------------------------------//
//	Validate if a given string is numeric.										//
//	Some examples :																//
//	"0" = > true																//
//	" 0.1 " = > true															//
//	"abc" = > false																//
//	"1 a" = > false																//
//	"2e10" = > true																//
//	Note: It is intended for the problem statement to be ambiguous.You should	//
//	gather all requirements up front before implementing one.					//
//	Update(2015 - 02 - 10) :													//
//	The signature of the C++ function had been updated.If you still see your	//
//	function signature accepts a const char * argument, please click the reload	//
//	button  to reset your code definition.										//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<stack>
#include<stdio.h>
#include<deque>
// constants
// function prototype
using namespace std;
//复杂逻辑判断，虽然快，但是易出错，不推荐
class Solution 
{
public:
	bool isNumber(string s) 
	{
		const int size = s.size();
		//清除前后空格
		int numStart, epos, start = 0, end = size - 1;
		while (s[start] == ' ')
			start++;
		while (s[end] == ' ')
			end--;
		int dotCount = 0, ecount = 0;
		int sign;
		if (s[start] == '-' || s[start] == '+')
			sign = (s[start++] == '-') ? -1 : 1;
		numStart = end + 1;
		epos = end + 1;
		for (int i = start; i <= end; i++)
		{
			if (s[i] == '.')
			{
				if (dotCount == 0 && i < epos)
				{
					dotCount++;
					continue;
				}
				else
					return false;
			}
			if (s[i] == 'e')
			{
				if (i == end || ecount > 0 || i < numStart)
					return false;
				if (s[i + 1] == '+' || s[i + 1] == '-')
				{
					if (i + 1 == end)
						return false;
					else
					{
						ecount++;
						epos = i;
						i++;
						continue;
					}
				}
				else
				{
					if (isdigit(s[i + 1]))
					{
						ecount++;
						epos = i;
						i++;
						continue;
					}
				}
			}
			if (!isdigit(s[i]))
				return false;
			else
				numStart = i;
		}
		return numStart != (end + 1);
	}
};
//有限自动机
class Solution2 
{
public:
	bool isNumber(const string& s) 
	{
		enum InputType {
			INVALID, // 0
			SPACE, // 1
			SIGN, // 2
			DIGIT, // 3
			DOT, // 4
			EXPONENT, // 5
			NUM_INPUTS // 6
		};
		const int transitionTable[][NUM_INPUTS] = {
			-1, 0, 3, 1, 2, -1, // next states for state 0
			-1, 8, -1, 1, 4, 5, // next states for state 1
			-1, -1, -1, 4, -1, -1, // next states for state 2
			-1, -1, -1, 1, 2, -1, // next states for state 3
			-1, 8, -1, 4, -1, 5, // next states for state 4
			-1, -1, 6, 7, -1, -1, // next states for state 5
			-1, -1, -1, 7, -1, -1, // next states for state 6
			-1, 8, -1, 7, -1, -1, // next states for state 7
			-1, 8, -1, -1, -1, -1, // next states for state 8
		};
		int state = 0;
		for (auto ch : s) 
		{
			InputType inputType = INVALID;
			if (isspace(ch))
				inputType = SPACE;
			else if (ch == '+' || ch == '-')
				inputType = SIGN;
			else if (isdigit(ch))
				inputType = DIGIT;
			else if (ch == '.')
				inputType = DOT;
			else if (ch == 'e' || ch == 'E')
				inputType = EXPONENT;
			// Get next state from current state and input symbol
			state = transitionTable[state][inputType];
			// Invalid input
			if (state == -1) return false;
		}
		// If the current state belongs to one of the accepting (final) states,
		// then the number is valid
		return state == 1 || state == 4 || state == 7 || state == 8;
	}
};

//利用strtod()
class Solution3
{
public:
	bool isNumber(string s) 
	{
		return isNumber(s.c_str());
	}
private:
	bool isNumber(char const* s) {
		char* endptr;
		strtod(s, &endptr);
		if (endptr == s) return false;
		for (; *endptr; ++endptr)
			if (!isspace(*endptr)) return false;
		return true;
	}
};
//https://discuss.leetcode.com/topic/2710/a-simple-solution-in-cpp
class Solution4
{
public:
	bool isNumber(string s)
	{
		int i = 0;

		// skip the whilespaces
		for (; s[i] == ' '; i++) {}

		// check the significand
		if (s[i] == '+' || s[i] == '-') i++; // skip the sign if exist

		int n_nm, n_pt;
		for (n_nm = 0, n_pt = 0; isdigit(s[i]) || s[i] == '.'; i++)
			s[i] == '.' ? n_pt++ : n_nm++;
		if (n_pt>1 || n_nm<1) // no more than one point, at least one digit
			return false;

		// check the exponent if exist
		if (s[i] == 'e') {
			i++;
			if (s[i] == '+' || s[i] == '-') i++; // skip the sign

			int n_nm = 0;
			for (; isdigit(s[i]); i++, n_nm++) {}
			if (n_nm<1)
				return false;
		}

		// skip the trailing whitespaces
		for (; s[i] == ' '; i++) {}

		return s[i] == 0;  // must reach the ending 0 of the string
	}
};

//int main(void)
//{
//	Solution4 test;
//	string s(" 1e1.1  ");
//	cout << boolalpha << test.isNumber(s);
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
