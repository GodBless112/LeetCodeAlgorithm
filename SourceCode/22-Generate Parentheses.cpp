//	22. Generate Parentheses
//------------------------------------------------------------------------------//
//	Given n pairs of parentheses, write a function to generate all combinations //
//	of well-formed parentheses.													//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
#include<stack>
#include<list>
// constants
// function prototype
using namespace std;
//递归
class Solution 
{
public:
	vector<string> generateParenthesis(int n) 
	{
		vector<string> result;
		DFS("", n, 0, 0, 0, result);
		return result;
	}
private:
	void DFS(string s, int n, int deep, int pre, int use, vector<string> &result)
	{
		if (deep == 2 * n)
		{
			result.push_back(s);
			return;
		}
		if (pre == 0 && use != n)
		{
			s += '(';
			deep++;
			use++;
			pre++;
		}
		if (use == n)
		{
			for (int i = 0; i < pre; i++)
				s += ')';
			result.push_back(s);
			return;
		}
		else
		{
			DFS(s + '(', n, deep + 1, pre + 1, use + 1, result);
			DFS(s + ')', n, deep + 1, pre - 1, use, result);
		}
	}
};
//也是递归，只是更加简洁
class Solution2
{
public:
	vector<string> generateParenthesis(int n) {
		vector<string> result;
		string path;
		if (n > 0) generate(n, path, result, 0, 0);
		return result;
	}
	// l表示“(”的个数,r表示“）”的个数
	void generate(int n, string& path, vector<string> &result, int l, int r) {
		if (l == n) {
			string s(path);
			result.push_back(s.append(n - r, ')'));
			return;
		}
		path.push_back('(');
		generate(n, path, result, l + 1, r);
		path.pop_back();
		if (l > r) {
			path.push_back(')');
			generate(n, path, result, l, r + 1);
			path.pop_back();
		}
	}
};
//更加简洁的递归写法，但是执行效率反而不高，因为进行了许多重复的工作
class Solution3
{
public:
	vector<string> generateParenthesis(int n) 
	{
		if (n == 0) return vector<string>(1, "");
		if (n == 1) return vector<string>(1, "()");
		vector<string> result;
		for (int i = 0; i < n; ++i)
			for (auto inner : generateParenthesis(i))
				for (auto outer : generateParenthesis(n - 1 - i))
					result.push_back("(" + inner + ")" + outer);
		return result;
	}
};
//int main(void)
//{
//	Solution3 test;
//	auto x=test.generateParenthesis(3);
//	for (auto y : x)
//		cout << y << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
