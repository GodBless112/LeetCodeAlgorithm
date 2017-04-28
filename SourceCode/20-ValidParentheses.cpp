//	20. Valid Parentheses
//------------------------------------------------------------------------------//
//	Given a string containing just the characters '(', ')', '{', '}',			//
//	'[' and ']', determine if the input string is valid. The brackets must 		//
//	 close in the correct order, "()" and "()[]{}" are all valid but "(]" and	//
//	"([)]" are not.																//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
#include<stack>
// constants
// function prototype
using namespace std;
//用一个栈存放括号，遇到左括号入栈，右括号匹配出栈，如果最后栈空则为TRUE
class Solution 
{
public:
	bool isValid(string s) 
	{
		stack<int> mystack;
		for (int i = 0; i < s.size(); i++)
		{
			int k = charKind(s[i]);
			if (k < 3)
				mystack.push(k);
			else
			{
				if (!mystack.empty() && (k - mystack.top()) == 3)
					mystack.pop();
				else
					return false;
			}
		}
		return mystack.empty();
	}
private:
	int charKind(char c)
	{
		switch (c)
		{
		case '(':
			return 0;
		case '{':
			return 1;
		case '[': 
			return 2;
		case ')':
			return 3;
		case '}':
			return 4;
		case ']':
			return 5;
		default:
			return -1;
		}
	}
};
//不用转换成int，直接char
class Solution2 
{
public:
	bool isValid(string s) {
		stack<char> paren;
		for (char& c : s) {
			switch (c) {
			case '(':
			case '{':
			case '[': paren.push(c); break;
			case ')': if (paren.empty() || paren.top() != '(') return false; else paren.pop(); break;
			case '}': if (paren.empty() || paren.top() != '{') return false; else paren.pop(); break;
			case ']': if (paren.empty() || paren.top() != '[') return false; else paren.pop(); break;
			default:; // pass
			}
		}
		return paren.empty();
	}
};
//int main(void)
//{
//	Solution test;
//	string s("({[[]]})()");
//	cout << boolalpha << test.isValid(s) << endl;
//		
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
