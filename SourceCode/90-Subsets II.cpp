//	90. Subsets II
//------------------------------------------------------------------------------//
//	Given a collection of integers that might contain duplicates, nums, return	//
//	all possible subsets.														//
//	Note: The solution set must not contain duplicate subsets.					//
//		For example,															//
//		If nums = [1, 2, 2], a solution is :									//
//		  [																		//
//			  [2],																//
//			  [1],																//
//			  [1, 2, 2],														//
//			  [2, 2],															//
//			  [1, 2],															//
//			  []																//
//		  ]																		//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<set>
#include<iterator>
// constants
// function prototype
using namespace std;
//递归，在递归的每一层略去相同的元素
class Solution
{
public:
	vector<vector<int>> subsetsWithDup(vector<int>& nums)
	{
		const int size = nums.size();
		sort(nums.begin(), nums.end());
		vector<vector<int>> result;
		vector<int> sub;
		result.push_back(sub);
		subsetsDFS(size, 0, 0, sub, nums, result);
		return result;
	}
private:
	void subsetsDFS(int n, int start, int cur, vector<int> &sub, vector<int> &nums, vector<vector<int>> &result)
	{
		if (cur == n)
			return;
		for (int i = start; i < n; i++)
		{
			if (i != start&&nums[i] == nums[i - 1])
				continue;
			sub.push_back(nums[i]);
			result.push_back(sub);
			subsetsDFS(n, i + 1, cur + 1, sub, nums, result);
			sub.pop_back();
		}
	}
};
//递归方法，利用map记录每个元素出现的次数
class Solution2
{
public:
	vector<vector<int> > subsetsWithDup(vector<int> &S) {
		vector<vector<int> > result;
		sort(S.begin(), S.end()); //必须排序
		unordered_map<int, int> count_map;
		for_each(S.begin(), S.end(), [&count_map](int e) {
			if (count_map.find(e) != count_map.end())
				count_map[e]++;
			else
				count_map[e] = 1;
		});
		//把map里的pair放到vector
		vector<pair<int, int> > elems;
		for_each(count_map.begin(), count_map.end(),
			[&elems](const pair<int, int> &e) {
			elems.push_back(e);
		});
		sort(elems.begin(), elems.end());
		vector<int> path; //中间结果
		subsets(elems, 0, path, result);
		return result;
	}
private:
	static void subsets(const vector<pair<int, int> > &elems,
		size_t step, vector<int> &path, vector<vector<int> > &result) {
		if (step == elems.size()) {
			result.push_back(path);
			return;
		}
		for (int i = 0; i <= elems[step].second; i++) {
			for (int j = 0; j < i; ++j) {
				path.push_back(elems[step].first);
			}
			subsets(elems, step + 1, path, result);
			for (int j = 0; j < i; ++j) {
				path.pop_back();
			}
		}
	}
};
//递归，位向量法
class Solution3
{
public:
	vector<vector<int> > subsetsWithDup(vector<int> &S) {
		vector<vector<int> > result; //必须排序
		sort(S.begin(), S.end());
		vector<int> count(S.back() - S.front() + 1, 0);
		//计算所有元素的个数
		for (auto i : S) {
			count[i - S[0]]++;
		}
		//每个元素选择了多少次
		vector<int> selected(S.back() - S.front() + 1, -1);
		subsets(S, count, selected, 0, result);
		return result;
	}
private:
	static void subsets(const vector<int> &S, vector<int> &count,
		vector<int> &selected, size_t step, vector<vector<int> > &result) {
		if (step == count.size()) {
			vector<int> subset;
			for (size_t i = 0; i < selected.size(); i++) {
				for (int j = 0; j < selected[i]; j++) {
					subset.push_back(i + S[0]);
				}
			}
			result.push_back(subset);
			return;
		}
		for (int i = 0; i <= count[step]; i++) {
			selected[step] = i;
			subsets(S, count, selected, step + 1, result);
		}
	}
};
//迭代的方法，每次将nums中剩余的一个元素添加到已有的各子集，形成一组新的子集，并加入结果
class Solution4
{
public:
	vector<vector<int>> subsetsWithDup(vector<int>& nums)
	{
		sort(nums.begin(), nums.end());
		vector<vector<int> > result(1);
		size_t previous_size = 0;
		for (size_t i = 0; i < nums.size(); ++i) {
			const size_t size = result.size();
			for (size_t j = 0; j < size; ++j) {
				if (i == 0 || nums[i] != nums[i - 1] || j >= previous_size) {
					result.push_back(result[j]);
					result.back().push_back(nums[i]);
				}
			}
			previous_size = size;
		}
		return result;
	}
};
//二进制法
class Solution5
{
public:
	vector<vector<int>> subsetsWithDup(vector<int>& nums)
	{
		sort(nums.begin(), nums.end());
		//用set去重，不能用unordered_set，因为输出要求有序
		set<vector<int> > result;
		const size_t n = nums.size();
		vector<int> v;
		for (size_t i = 0; i < 1U << n; ++i) {
			for (size_t j = 0; j < n; ++j) {
				if (i & 1 << j)
					v.push_back(nums[j]);
			}
			result.insert(v);
			v.clear();
		}
		vector<vector<int> > real_result;
		copy(result.begin(), result.end(), back_inserter(real_result));
		return real_result;
	}
};
//int main(void)
//{
//	Solution4 test;
//	vector<int> input = { 1,2,2 };
//	auto a = test.subsetsWithDup(input);
//	for_each(a.begin(), a.end(), [](vector<int> &x) {
//		for (auto y : x)
//			cout << y << " ";
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