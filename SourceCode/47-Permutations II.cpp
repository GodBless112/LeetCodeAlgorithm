//	47. Permutations II
//------------------------------------------------------------------------------//
//	Given a collection of numbers that might contain duplicates, return all		//
//	possible unique permutations.												//
//	For example,																//
//	[1, 1, 2] have the following unique permutations :							//
//	[																			//
//		[1, 1, 2],																//
//		[1, 2, 1],																//
//		[2, 1, 1]																//
//]																				//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<iterator>
#include<iomanip>
#include<unordered_map>
// constants
// function prototype
using namespace std;
//递归版本1，注意传递中间值nums时是按值传递，递归返回后不交换
class Solution 
{
public:
	vector<vector<int>> permuteUnique(vector<int>& nums)
	{
		sort(nums.begin(), nums.end());
		vector<vector<int>> result;
		permuteDFS(nums, result, 0);
		return result;
	}
private:
	void permuteDFS(vector<int> nums, vector<vector<int>> &result, int k)
	{
		if (k == nums.size() - 1)
		{
			result.push_back(nums);
			return;
		}
		for (int i = k; i < nums.size(); i++)
		{
			if (i != k && nums[i] == nums[k]) continue;
			swap(nums[i], nums[k]);
			permuteDFS(nums, result, k + 1);
		}
	}
};
//递归版本2，利用哈希表
class Solution2
{
public:
	vector<vector<int> > permuteUnique(vector<int>& num) {
		sort(num.begin(), num.end());
		unordered_map<int, int> count_map; // 􄃟􁒄􂃾􀍙􀙲􃉏􂮳􀜩􂣟􂁐􁪟
		for_each(num.begin(), num.end(), [&count_map](int e) {
			if (count_map.find(e) != count_map.end())
				count_map[e]++;
			else
				count_map[e] = 1;
		});
		
		vector<pair<int, int> > elems;
		for_each(count_map.begin(), count_map.end(),
			[&elems](const pair<int, int> &e) {
			elems.push_back(e);
		});
		vector<vector<int>> result; 
		vector<int> p; 
		n = num.size();
		permute(elems.begin(), elems.end(), p, result);
		return result;
	}
private:
	size_t n;
	typedef vector<pair<int, int> >::const_iterator Iter;
	void permute(Iter first, Iter last, vector<int> &p,
		vector<vector<int> > &result) {
		if (n == p.size()) { //收敛条件
			result.push_back(p);
		}
		//扩展状态
		for (auto i = first; i != last; i++) {
			int count = 0; //统计*i在p中出现过多少次
			for (auto j = p.begin(); j != p.end(); j++) {
				if (i->first == *j) {
					count++;
				}
			}
			if (count < i->second) {
				p.push_back(i->first);
				permute(first, last, p, result);
				p.pop_back(); //撤销动作，返回上一层
			}
		}
	}
};
//利用STL的next_permutation
class Solution3
{
public:
	vector<vector<int>> permuteUnique(vector<int>& nums)
	{
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());
		do
			result.push_back(nums);
		 while (next_permutation(nums.begin(), nums.end()));
		 return result;
	}
};
//利用自己实现的next_permutation
class Solution4
{
public:
	vector<vector<int>> permuteUnique(vector<int>& nums)
	{
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());
		do
			result.push_back(nums);
		while (next_permutation(nums));
		return result;
	}
private:
	bool next_permutation(vector<int>& nums)
	{
		int size = nums.size();
		if (size < 2)
			return false;
		auto i = nums.rbegin();
		for (; i != (nums.rend() - 1); i++)
			if (*i > *(i + 1))
				break;
		if (i == nums.rend() - 1)
		{
			reverse(nums.begin(), nums.end());
			return false;
		}
		auto j = nums.rbegin();
		while (j != (i + 1) && *j <= *(i + 1))
			j++;
		swap(*(i + 1), *j);
		reverse(nums.rbegin(), i + 1);
		return true;
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<int> a({ 2,2,1,1 });
//	auto x = test.permuteUnique(a);
//	for (auto y1 : x)
//	{
//		for (auto y2 : y1)
//			cout << y2 << " ";
//		cout << endl;
//	}
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
