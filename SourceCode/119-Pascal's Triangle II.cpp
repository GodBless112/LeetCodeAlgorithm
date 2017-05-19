//	119. Pascal's Triangle II
//------------------------------------------------------------------------------//
//	Given an index k, return the kth row of the Pascal's triangle.				//
//	For example, given k = 3,													//
//	Return[1, 3, 3, 1].															//
//	Note:																		//
//	Could you optimize your algorithm to use only O(k) extra space ?		 	//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<queue>
#include<stack>
// constants
// function prototype
using namespace std;
//从左到右
class Solution {
public:
	vector<int> getRow(int rowIndex) {
		vector<int> cur;
		for (int i = 0; i <= rowIndex; ++i)
		{
			vector<int> next(i + 1, 1);
			for (int j = 1; j < i; ++j)
				next[j] = cur[j] + cur[j - 1];
			cur = next;
		}
		return cur;
	}
};
class Solution2
{
public:
	vector<int> getRow(int rowIndex)
	{
		vector<vector<int>> result;
		result.push_back(vector<int>(1, 1));
		for (int i = 1; i <= rowIndex; i++)
		{
			vector<int> level(i + 1, 1);
			for (int j = 1; j < i; j++)
				level[j] = result[i - 1][j] + result[i - 1][j - 1];
			result.push_back(level);
		}
		return result.back();
	}
};
//从右到左,空间O(k)
class Solution3 {
public:
	vector<int> getRow(int rowIndex){
		vector<int> level;
		for (int i = 0; i <= rowIndex; ++i) {
			for (int j = i - 1; j > 0; --j)
				level[j] = level[j] + level[j - 1];
			level.push_back(1);
		}
		return level;
	}
};
//int main(void)
//{
//	Solution2 test;
//	auto res = test.getRow(3);
//	for_each(res.begin(), res.end(), [](int elem) {
//		cout << elem << " ";
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