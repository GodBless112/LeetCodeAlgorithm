//2017滴滴在线笔试B卷
#include<iostream>
#include<string>
#include<cmath>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<functional>
#include<numeric>
#include<unordered_set>

// constants
using namespace std;
// function prototype
//海岛问题，
int getGroup(vector<vector<int>> &group, int pos)
{
	int i = pos / group[0].size();
	int j = pos%group[0].size();
	if (group[i][j] == -1)
		return i*group[0].size() + j;
	else
		return getGroup(group, group[i][j]);
}
int CountIsland(int n, int m, vector<vector<int>> &theMap)
{
	int result = 0;
	int left, right, up, down;
	vector<vector<int>> group(n, vector<int>(m, -2));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			left = max(0, j - 1);
			right = min(m - 1, j + 1);
			up = max(0, i - 1);
			down = min(n - 1, i + 1);
			if (theMap[i][j] == 1)
			{
				if (group[i][left] > -2)
					group[i][j] = getGroup(group, i*m + left);
				else if (group[up][j] > -2)
					group[i][j] = getGroup(group, up*m + j);
				else
					group[i][j] = -1;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (theMap[i][j] == 1 && group[i][j] == -1)
				result++;
		}
	}
	return result;
}

//T9 拼音实现
string DigToLetterMap[10] = { " ","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };
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
vector<string> letterCombinations(string digits)
{
	vector<string> result;
	if (digits.empty())
		return result;
	dfs(digits, 0, "", result);
	return result;
}

std::vector<std::string> split(std::string str, std::string pattern)
{
	std::vector<std::string> ret;
	if (pattern.empty())
		return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
	while (index != str.npos)
	{
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())
		ret.push_back(str.substr(start));
	return ret;
}

int lcs(string str1, string str2, vector<vector<int>>& vec) {
	int len1 = str1.size();
	int len2 = str2.size();
	vector<vector<int>> c(len1 + 1, vector<int>(len2 + 1, 0));
	for (int i = 0; i <= len1; i++) {
		for (int j = 0; j <= len2; j++) {
			if (i == 0 || j == 0) {
				c[i][j] = 0;
			}
			else if (str1[i - 1] == str2[j - 1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				vec[i][j] = 0;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				vec[i][j] = 1;
			}
			else {
				c[i][j] = c[i][j - 1];
				vec[i][j] = 2;
			}
		}
	}

	return c[len1][len2];
}

string findMostlikeWord(vector<string> &dic, string input)
{
	string result;
	int maxLen = 0;
	vector<string> source = letterCombinations(input);
	unordered_set<string> setDic;
	vector<string> uniqueDic;
	for (int i = 0; i < dic.size(); i++)
	{
		if (setDic.find(dic[i]) == setDic.end())
		{
			setDic.insert(dic[i]);
			transform(dic[i].begin(), dic[i].end(), dic[i].begin(), ::tolower);
			uniqueDic.push_back(dic[i]);
		}
	}
	for (int i = 0; i < uniqueDic.size(); i++)
	{
		for (int j = 0; j < source.size(); j++)
		{
			vector<vector<int>> lenrecord(uniqueDic[i].size() + 1, vector<int>(source[j].size() + 1, -1));
			int len = lcs(uniqueDic[i], source[j], lenrecord);
			if (len > maxLen)
			{
				maxLen = len;
				result = uniqueDic[i];
			}
		}
		
	}
	
	return result;
}
int main()
{
	/*int n, m;
	string s;
	getline(cin, s);
	n = s[0] - '0';
	m = s[1] - '0';
	vector<vector<int>> theMap(n, vector<int>(m));

	for (int i = 0; i < n; i++)
	{
		getline(cin, s);
		for (int j = 0; j < m; j++)
			theMap[i][j] = s[j] - '0';
	}
	cout << CountIsland(n, m, theMap) << endl;*/
	string input = "Produces a printable string representation of a dictionary";
	//getline(cin, input);
	vector<string> dictionary = split(input, " ");
	getline(cin, input);
	cout << findMostlikeWord(dictionary, input);
	
	// code to keep window open for MSVC++
	std::cin.clear();
	while (std::cin.get() != '\n')
		continue;
	std::cin.get();
	return 0;
}
