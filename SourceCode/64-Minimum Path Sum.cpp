//	64. Minimum Path Sum
//------------------------------------------------------------------------------//
//	Given a m x n grid filled with non-negative numbers, find a path from top	//
//	left to bottom right which minimizes the sum of all numbers along its path.	//
//	Note: You can only move either down or right at any point in time.			//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<stack>
#include<stdio.h>
#include<deque>
// constants
// function prototype
using namespace std;
//动态规划
class Solution 
{
public:
	int minPathSum(vector<vector<int>>& grid) 
	{
		int m = grid.size();
		int n = grid[0].size();
		vector<int> value(n, INT_MAX);
		value[0] = 0;
		for (int i = 0; i < m; i++)
		{
			value[0] += grid[i][0];
			for (int j = 1; j < n; j++)
				value[j] = min(value[j], value[j - 1]) + grid[i][j];
		}
		return value[n - 1];
	}
};
//备忘录法
class Solution2
{
public:
	int minPathSum(vector<vector<int>>& grid)
	{
		const int m = grid.size();
		const int n = grid[0].size(); 
		f = vector<vector<int>>(m, vector<int>(n, -1));
		return DFS(grid, m - 1, n - 1);
	}
private:
	vector<vector<int>> f;
	int DFS(const vector<vector<int>>& grid, int x, int y)
	{
		if (x < 0 || y < 0) return INT_MAX;
		if (x == 0 && y == 0)
			return grid[0][0];
		/*if (f[x][y] >= 0) return f[x][y];
		else return f[x][y] = min(DFS(grid, x - 1, y), DFS(grid, x, y - 1)) + grid[x][y];*/
		return min(getOrUpdate(grid, x - 1, y),
			getOrUpdate(grid, x, y - 1)) + grid[x][y];
	}
	int getOrUpdate(const vector<vector<int> > &grid, int x, int y) {
		if (x < 0 || y < 0) return INT_MAX; 
		if (f[x][y] >= 0) return f[x][y];
		else return f[x][y] = DFS(grid, x, y);
	}
};
//传统的动态规划
class Solution3
{
public:
	int minPathSum(vector<vector<int> > &grid) 
	{
		if (grid.size() == 0) return 0;
		const int m = grid.size();
		const int n = grid[0].size();
		vector<vector<int>> f(m, vector<int>(n, -1));
		f[0][0] = grid[0][0];
		for (int i = 1; i < m; i++) {
			f[i][0] = f[i - 1][0] + grid[i][0];
		}
		for (int i = 1; i < n; i++) {
			f[0][i] = f[0][i - 1] + grid[0][i];
		}
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				f[i][j] = min(f[i - 1][j], f[i][j - 1]) + grid[i][j];
			}
		}
		return f[m - 1][n - 1];
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<vector<int>> a = { {1,3,1},{1,5,1},{4,2,1} };
//	cout << test.minPathSum(a);
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
