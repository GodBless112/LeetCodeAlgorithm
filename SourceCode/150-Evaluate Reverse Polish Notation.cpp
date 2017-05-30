//	150. Evaluate Reverse Polish Notation
//------------------------------------------------------------------------------//
//	Evaluate the value of an arithmetic expression in Reverse Polish Notation.	//
//	Valid operators are + , -, *, / .Each operand may be an integer or another	//
//	expression.																	//
//	Some examples :																//
//	["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9								//
//	["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6							//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<stack>
#include<unordered_set>
// constants
// function prototype
using namespace std;
//利用栈，遇到操作数则弹出栈顶两个元素，进行计算，压入计算结果，若是数则压入
class Solution {
public:
	int evalRPN(vector<string>& tokens) {
		stack<int> s;
		for (int i = 0; i < tokens.size(); ++i) {
			if (dict.find(tokens[i]) != dict.end()) {
				int val1 = s.top();
				s.pop();
				int val2 = s.top();
				s.pop();
				int val = calulate(val2, val1, tokens[i]);
				s.push(val);
			}
			else
				s.push(stoi(tokens[i]));
		}
		return s.top();
	}
private:
	unordered_set<string> dict{ "+","-","/","*" };
	int calulate(int val1, int val2, string &s) {
		switch (s[0])
		{
		case '+': return val1 + val2;
		case '-': return val1 - val2;
		case '/': return val1 / val2;
		case '*': return val1 * val2;
		}
	}
};
//另一种形式
class Solution2 {
public:
	int evalRPN(vector<string> &tokens) {
		stack<string> s;
		for (auto token : tokens) {
			if (!is_operator(token)) {
				s.push(token);
			}
			else {
				int y = stoi(s.top());
				s.pop();
				int x = stoi(s.top());
				s.pop();
				if (token[0] == '+') x += y;
				else if (token[0] == '-') x -= y;
				else if (token[0] == '*') x *= y;
				else x /= y;
				s.push(to_string(x));
			}
		}
		return stoi(s.top());
	}
private:
	bool is_operator(const string &op) {
		return op.size() == 1 && string("+-*/").find(op) != string::npos;
	}
};
//递归版本
class Solution3 {
public:
	int evalRPN(vector<string> &tokens) {
		int x, y;
		auto token = tokens.back(); tokens.pop_back();
		if (is_operator(token)) {
			y = evalRPN(tokens);
			x = evalRPN(tokens);
			if (token[0] == '+') x += y;
			else if (token[0] == '-') x -= y;
			else if (token[0] == '*') x *= y;
			else x /= y;
		}
		else {
			size_t i;
			x = stoi(token, &i);
		}
		return x;
	}
private:
	bool is_operator(const string &op) {
		return op.size() == 1 && string("+-*/").find(op) != string::npos;
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<string> tokens1{ "2", "1", "+", "3", "*" };
//	vector<string> tokens2{ "4", "13", "5", "/", "+" };
//	cout << test.evalRPN(tokens1) << endl;
//	cout << test.evalRPN(tokens2);
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