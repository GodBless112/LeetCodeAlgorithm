//	63. Unique Paths II
//------------------------------------------------------------------------------//
//	Follow up for "Unique Paths":												//
//	Now consider if some obstacles are added to the grids.How many unique paths //
//	would there be ?															//
//	An obstacle and empty space is marked as 1 and 0 respectively in the grid.	//
//	For example,																//
//	There is one obstacle in the middle of a 3x3 grid as illustrated below.		//
//	[																			//
//		[0, 0, 0],																//
//		[0, 1, 0],																//
//		[0, 0, 0]																//
//	]																			//
//	The total number of unique paths is 2.										//
//	Note: m and n will be at most 100.											//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<stack>
#include<stdio.h>
// constants
// function prototype
using namespace std;
//dynamic programming，

//动态规划的优化，不需要一个二维数组来存结果，甚至可以不用vector,时间复杂度O(n^2)
//加入障碍的判断
class Solution
{
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
	{
		int m = obstacleGrid.size();
		int n = obstacleGrid[0].size();
		if (obstacleGrid[0][0] || obstacleGrid[m - 1][n - 1])
			return 0;
		int grid[101] = {0};	//m,n<=100
		grid[0] = obstacleGrid[0][0] == 1 ? 0 : 1;
		for (int i = 0; i < m; i++)
		{
			grid[0] = grid[0] == 0 ? 0 : (obstacleGrid[i][0] ? 0 : 1);
			for (int j = 1; j < n; j++)
			{
				grid[j] = obstacleGrid[i][j] == 1 ? 0 : (grid[j] + grid[j - 1]);
			}
		}
			
				
		return grid[n - 1];
	}
};
//深度优先搜索，时间复杂度O(n^4)，会超时
class Solution3
{
public:
	int uniquePaths(int m, int n) 
	{
		if (m < 1 || n < 1) return 0;
		if (m == 1 && n == 1) return 1; 
		return uniquePaths(m - 1, n) + uniquePaths(m, n - 1);
	}
};
//备忘录法，深度优先搜索加缓存,时间复杂度O(n^2),空间复杂度O(n^2)
class Solution4
{
public:
	int uniquePaths(int m, int n) 
	{
		f = vector<vector<int> >(m, vector<int>(n, 0));
		f[0][0] = 1;
		return dfs(m - 1, n - 1);
	}
private:
	vector<vector<int> > f; 
	int dfs(int x, int y) 
	{
		if (x < 0 || y < 0) return 0; 
		if (x == 0 && y == 0) return f[0][0]; 
		if (f[x][y] > 0) 
		{
			return f[x][y];
		}
		else 
		{
			return f[x][y] = dfs(x - 1, y) + dfs(x, y - 1);
		}
	}
};
//数学公式，Cm+n-2 m-1，即从起点到终点总共要走m+n-2步，从中选择m-1步向下
class Solution5
{
public:
	int uniquePaths(int m, int n) 
	{
		if (m <= 0 || n <= 0) return 0;
		long long res = 1;
		for (int i = n; i < m + n - 1; i++) 
		{
			res = res * i / (i - n + 1);
		}
		return (int)res;
	}
};
int main(void)
{
	Solution test;
	vector<vector<int>> a = { {0},{1},{0} };
	cout << test.uniquePathsWithObstacles(a);
	cout << endl;
	double x;
	char s[11];
	gets_s(s);
	putchar()
	// code to keep window open for MSVC++
	cin.clear();
	while (cin.get() != '\n')
		continue;
	cin.get();

	return 0;
}
