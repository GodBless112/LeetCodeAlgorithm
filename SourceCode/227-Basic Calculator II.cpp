//	227. Basic Calculator II
//------------------------------------------------------------------------------//
//	Implement a basic calculator to evaluate a simple expression string.		//
//	The expression string contains only non - negative integers, +, -, *, /		//
//	operators and empty spaces.The integer division should truncate toward zero.//
//	You may assume that the given expression is always valid.					//
//	Some examples :																//
//	"3+2*2" = 7																	//
//	" 3/2 " = 1																	//
//	" 3+5 / 2 " = 5																//
//	Note : Do not use the eval built - in library function.						//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<sstream>
#include<stack>
#include<unordered_set>
// constants
// function prototype
using namespace std;
//先转化为逆波兰记法，然后利用栈计算
class Solution {
public:
	int calculate(string s) {
		stack<char> stack;
		string polish;
		vector<string> tokens;
		for (int i = 0; i <= s.size(); ++i) {
			if (s[i] >= '0' &&s[i] <= '9')
				polish += s[i];
			else {
				if(!polish.empty())
					tokens.push_back(polish);
				polish = "";
				if (s[i] == '+' || s[i] == '-') {
					while (!stack.empty()) {
						if (stack.top() == '(')
							break;
						tokens.push_back(string(1, stack.top()));
						stack.pop();
					}
					stack.push(s[i]);
				}
				else if (s[i] == '*' || s[i] == '/') {
					while (!stack.empty()) {
						if (stack.top() == '(' || stack.top() == '+' || stack.top() == '-')
							break;
						tokens.push_back(string(1, stack.top()));
						stack.pop();
					}
					stack.push(s[i]);
				}
				else if (s[i] == '(')
					stack.push(s[i]);
				else if (s[i] == ')') {
					while (!stack.empty()) {
						if (stack.top() == '(') {
							stack.pop();
							break;
						}
						tokens.push_back(string(1, stack.top()));
						stack.pop();
					}
				}
			}
		}
		while (!stack.empty()) {
			tokens.push_back(string(1, stack.top()));
			stack.pop();
		}
		return evalRPN(tokens);
	}
private:
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
//直接运算，在前后插入一个'+'以适应边界情况
class Solution2 {
public:
	int calculate(string s) {
		long long total = 0, terms = 0, n;
		char op;
		istringstream in('+' + s + '+');
		while (in >> op) {
			if (op == '+' || op == '-') {
				total += terms;
				in >> terms;
				terms *= 44 - op;
			}
			else {
				in >> n;
				if (op == '*')
					terms *= n;
				else
					terms /= n;
			}
		}
		return total;
	}
};
//利用栈直接运算
class Solution3 {
public:
	int calculate(string s) {
		stack<int> myStack;
		char sign = '+';
		int res = 0, tmp = 0;
		for (unsigned i = 0; i < s.size(); ++i) {
			if (isdigit(s[i]))
				tmp = 10 * tmp + s[i] - '0';
			if (!isdigit(s[i]) && !isspace(s[i]) || i == s.size() - 1) {
				if (sign == '-')
					myStack.push(-tmp);
				else if (sign == '+')
					myStack.push(tmp);
				else {
					int num;
					if (sign == '*')
						num = myStack.top() * tmp;
					else if (sign == '/')
						num = myStack.top() / tmp;
					myStack.pop();
					myStack.push(num);
				}
				sign = s[i];
				tmp = 0;
			}
		}
		while (!myStack.empty()) {
			res += myStack.top();
			myStack.pop();
		}
		return res;
	}
};
//类似于2
class Solution4 {
public:
	int calculate(string s) {
		int result = 0, cur_res = 0;
		char op = '+';
		for (int pos = s.find_first_not_of(' '); pos < s.size(); pos = s.find_first_not_of(' ', pos)) {
			if (isdigit(s[pos])) {
				int tmp = s[pos] - '0';
				while (++pos < s.size() && isdigit(s[pos]))
					tmp = tmp * 10 + (s[pos] - '0');
				switch (op) {
				case '+': cur_res += tmp; break;
				case '-': cur_res -= tmp; break;
				case '*': cur_res *= tmp; break;
				case '/': cur_res /= tmp; break;
				}
			}
			else {
				if (s[pos] == '+' || s[pos] == '-') {
					result += cur_res;
					cur_res = 0;
				}
				op = s[pos++];
			}
		}
		return result + cur_res;
	}
};
//int main(void)
//{
//	Solution4 test;
//	string input;
//	cout << "请输入计算式:\n";
//	while (getline(cin, input)) {
//		cout << test.calculate(input) << endl;
//		cout << "请输入计算式:\n";
//	}
//
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}