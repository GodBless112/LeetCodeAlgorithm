//	49. Group Anagrams
//------------------------------------------------------------------------------//
//	Given an array of strings, group anagrams together.							//
//	For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],				//
//	Return :																	//
//	[																			//
//		["ate", "eat", "tea"],													//
//		["nat", "tan"],															//
//		["bat"]																	//
//	]																			//
//	Note: All inputs will be in lower - case.									//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<unordered_map>
// constants
// function prototype
using namespace std;
//先将每个字符串排序，放进一个哈希表中
class Solution 
{
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) 
	{
		vector<vector<string>> result;
		unordered_map<string, vector<string>> groupMap;
		for (auto &s : strs)
		{
			string key = s;
			sort(key.begin(), key.end());
			groupMap[key].push_back(s);
		}
		for (auto itr = groupMap.begin(); itr != groupMap.end(); itr++)
			result.push_back(itr->second);
		return result;
	}
};
//由于字母只有小写字母，可以自己实现排序加快速度
class Solution2
{
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs)
	{
		vector<vector<string>> result;
		unordered_map<string, vector<string>> groupMap;
		for (auto &s : strs)
		{
			string key = strSort(s);
			groupMap[key].push_back(s);
		}
		for (auto itr = groupMap.begin(); itr != groupMap.end(); itr++)
			result.push_back(itr->second);
		return result;
	}
private:
	string strSort(string& s) {
		int count[26] = { 0 }, n = s.length();
		for (int i = 0; i < n; i++)
			count[s[i] - 'a']++;
		int p = 0;
		string t(n, 'a');
		for (int j = 0; j < 26; j++)
			for (int i = 0; i < count[j]; i++)
				t[p++] += j;
		return t;
	}
};

//int main(void)
//{
//	Solution2 test;
//	vector<string> input = { "eat", "tea", "tan", "ate", "nat", "bat" };
//	auto a = test.groupAnagrams(input);
//	for (auto x : a)
//	{
//		for (auto y : x)
//			cout << y << " ";
//		cout << endl;
//	}
//	
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
