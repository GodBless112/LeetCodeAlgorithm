//	131. Palindrome Partitioning
//------------------------------------------------------------------------------//
//	Given a string s, partition s such that every substring of the partition is //
//	a palindrome.																//
//	Return all possible palindrome partitioning of s.							//
//	For example, given s = "aab",												//
//	Return																		//
//	[																			//
//		["aa", "b"],															//
//		["a", "a", "b"]															//
//	]																			//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<deque>
// constants
// function prototype
using namespace std;
//回溯法，每一步都可以判断中间结果是否合法
//时间复杂度O(2^n)
class Solution {
public:
	vector<vector<string>> partition(string s) {
		vector<string> Parition;
		vector<vector<string>> result;
		DFS(0, s, Parition, result);
		return result;
	}
private:
	void DFS(int depth, string &s, vector<string> &partion, vector<vector<string>> &result) {
		if (depth == s.size()) {
			result.push_back(partion);
			return;
		}
		for (int i = depth + 1; i <= s.size(); ++i) {
			string Palindrome = s.substr(depth, i - depth);
			if (!isPalindrome(Palindrome, 0, Palindrome.size() - 1))
				continue;
			partion.push_back(Palindrome);
			DFS(i, s, partion, result);
			partion.pop_back();
		}
	}
	bool isPalindrome(const string& s, int start, int end) {
		while (start <= end) {
			if (s[start++] != s[end--])
				return false;
		}
		return true;
	}
};
class Solution2 {
public:
	vector<vector<string>> partition(string s) {
		vector<vector<string> > ret;
		vector<string> path;
		dfs(0, s, path, ret);

		return ret;
	}

	void dfs(int index, string& s, vector<string>& path, vector<vector<string> >& ret) {
		if (index == s.size()) {
			ret.push_back(path);
			return;
		}
		for (int i = index; i < s.size(); ++i) {
			if (isPalindrome(s, index, i)) {
				path.push_back(s.substr(index, i - index + 1));
				dfs(i + 1, s, path, ret);
				path.pop_back();
			}
		}
	}

	bool isPalindrome(const string& s, int start, int end) {
		while (start <= end) {
			if (s[start++] != s[end--])
				return false;
		}
		return true;
	}
};
//动态规划
class Solution3 {
public:
	vector<vector<string> > partition(string s) {
		const int n = s.size();
		vector<vector<bool>> p(n, vector<bool>(n)); // whether s[i,j] is palindrome
		fill_n(&p[0][0], n * n, false);
		for (int i = n - 1; i >= 0; --i)
			for (int j = i; j < n; ++j)
				p[i][j] = s[i] == s[j] && ((j - i < 2) || p[i + 1][j - 1]);
		vector<vector<vector<string>>> sub_palins(n); // sub palindromes of s[0,i]
		for (int i = n - 1; i >= 0; --i) {
			for (int j = i; j < n; ++j)
				if (p[i][j]) {
					const string palindrome = s.substr(i, j - i + 1);
					if (j + 1 < n) {
						for (auto v : sub_palins[j + 1]) {
							v.insert(v.begin(), palindrome);
							sub_palins[i].push_back(v);
						}
					}
					else {
						sub_palins[i].push_back(vector<string> { palindrome });
					}
				}
		}
		return sub_palins[0];
	}
};
//动态规划加DFS
class Solution4 {
	void partition(string s, int b, int n, vector<int>& ret, vector<vector<bool> >& m, vector<vector<string> >& res) {
		if (b == n)
		{
			vector<string> vs;
			int k = 0;
			for (int i = 0; i<ret.size(); i++)
			{
				vs.push_back(s.substr(k, ret[i] - k + 1));
				k = ret[i] + 1;
			}
			res.push_back(vs);
		}
		for (int i = b; i<n; i++)
		{
			if (m[i - b + 1][b])
			{
				ret.push_back(i);
				partition(s, i + 1, n, ret, m, res);
				ret.pop_back();
			}
		}
	}
public:
	vector<vector<string>> partition(string s) {
		int n = s.length();
		vector<vector<bool> > m(n + 1, vector<bool>(n, false));

		for (int len = 1; len <= n; len++)
		{
			for (int i = 0; i <= n - len; i++)
			{
				if (len == 1)m[len][i] = true;
				else if (len == 2)m[len][i] = s[i] == s[i + 1];
				else
				{

					m[len][i] = m[len - 2][i + 1] && s[i] == s[i + len - 1];
				}
			}
		}
		vector<vector<string>> res;
		vector<int> ret;
		partition(s, 0, n, ret, m, res);
		return res;
	}
};
//int main(void)
//{
//	Solution4 test;
//	auto res = test.partition("aab");
//	for_each(res.begin(), res.end(), [](vector<string> &partion) {
//		for (auto s : partion)
//			cout << s << " ";
//		cout << endl;
//	});
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