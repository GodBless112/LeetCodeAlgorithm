//	17. Letter Combinations of a Phone Number
//------------------------------------------------------------------------------//
//	Given a digit string, return all possible letter combinations that the		//
//	number could represent. A mapping of digit to letters(just like on the		//
//	telephone buttons) is given below.											//	 
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
#include<set>
#include<unordered_map>
// constants
// function prototype
using namespace std;
//深度优先递归
class Solution 
{
public:
	static string DigToLetterMap[10];
	vector<string> letterCombinations(string digits) 
	{
		vector<string> result;
		if (digits.empty())
			return result;
		dfs(digits, 0, "", result);
		return result;
	}
	void dfs(string digits, size_t cur, string Path, vector<string> &result)
	{
		if (cur == digits.size())
		{
			result.push_back(Path);
			return;
		}
		for (auto c : DigToLetterMap[digits[cur] - '0'])
			dfs(digits, cur + 1, Path + c, result);
	}
};
string Solution::DigToLetterMap[10] = { " ","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };
//迭代
class Solution2
{
public:
	static string DigToLetterMap[10];
	vector<string> letterCombinations(string digits)
	{
		if (digits.empty())
			return vector<string>();
		vector<string> ret(1, "");
		for (auto c : digits)
		{
			const size_t n = ret.size();
			const size_t m = DigToLetterMap[c - '0'].size();
			ret.resize(n*m);
			for (int i = 1; i < m; i++)
				copy(ret.begin(), ret.begin() + n, ret.begin() + i*n);
			for (int i = 0; i < m; i++)
			{
				auto begin = ret.begin();
				for_each(begin + i*n, begin + (i + 1)*n, [&](string &s) {
					s += DigToLetterMap[c - '0'][i]; });
			}
		}
		return ret;
	}
};
string Solution2::DigToLetterMap[10] = { " ","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };
//int main(void)
//{
//	Solution2 test;
//	string a = "23";
//	auto x = test.letterCombinations(a);
//	
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
