//	120. Triangle
//------------------------------------------------------------------------------//
//	Given a triangle, find the minimum path sum from top to bottom. Each step	//
//	you may move to adjacent numbers on the row below.							//
//	For example, given the following triangle									//
//	[																			//
//		    [2],																//
//		   [3, 4],																//
//		 [6, 5, 7],																//
//		[4, 1, 8, 3]															//
//	]																			//
//	The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).	//
//	Note:																		//
//	Bonus point if you are able to do this using only O(n) extra space, where n //
//	is the total number of rows in the triangle.								//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>

// constants
// function prototype
using namespace std;
//动态规划，自顶向下
class Solution {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		if (triangle.size() == 1) return triangle[0][0];
		vector<int> Path(triangle.back().size(), 0);
		int minTotal = INT_MAX;
		Path[0] = triangle[0][0];
		for (int i = 1; i < triangle.size(); i++) {
			int n = triangle[i].size();	
			int prev = Path[0], cur;		//记录前一个未改变的数
			for (int j = 1; j < n - 1; j++) {
				cur = prev;
				prev = Path[j];
				Path[j] = min(Path[j], cur) + triangle[i][j];
			}		
			Path[n - 1] = triangle[i][n - 1] + prev;
			Path[0] += triangle[i][0];
		}
		for (int i = 0; i < Path.size(); i++)
			minTotal = min(minTotal, Path[i]);
		return minTotal;
	}
};
//自底向上的做法，动态规划
//设状态为f(i,j)，表示从(i,j)出发，路径和最小，则状态转移方程为：
//f(i,j) = min{f(i + 1; j),f(i + 1,j + 1)} + (i,j)
class Solution2 {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		vector<int> minTotal = triangle.back();
		for (int i = triangle.size() - 2; i >= 0; --i)
			for (int j = 0; j < triangle[i].size(); ++j)
				minTotal[j] = min(minTotal[j], minTotal[j + 1]) + triangle[i][j];
		return minTotal[0];
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<vector<int>> triangle{ {2},{3,4},{6,5,7},{4,1,8,3} };
//	cout << test.minimumTotal(triangle);
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