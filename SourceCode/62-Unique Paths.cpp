//	62. Unique Paths
//------------------------------------------------------------------------------//
//	A robot is located at the top-left corner of a m x n grid (marked 'Start'	//
//	in the diagram below).														//
//	The robot can only move either down or right at any point in time.The robot //
//	is trying to reach the bottom - right corner of the grid(marked 'Finish' in //
//	the diagram below).															//
//	How many possible unique paths are there ?									//
//	Above is a 3 x 7 grid.How many possible unique paths are there ?			//
//	Note : m and n will be at most 100.											//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<stack>
// constants
// function prototype
using namespace std;
//dynamic programming，时间复杂度O(n^2)
class Solution 
{
public:
	int uniquePaths(int m, int n) 
	{
		vector<vector<int>> grid(m, vector<int>(n));
		//initial
		int i, j;
		for (i = 0; i < m; ++i)
			grid[i][0] = 1;
		for (j = 0; j < n; ++j)
			grid[0][j] = 1;
		for (i = 1; i < m; i++)
			for (j = 1; j < n; j++)
				grid[i][j] = grid[i - 1][j] + grid[i][j - 1];
		return grid[m - 1][n - 1];
	}
};
//动态规划的优化，不需要一个二维数组来存结果，甚至可以不用vector
class Solution2
{
public:
	int uniquePaths(int m, int n)
	{
		int grid[101] = {0};	//m,n<=100
		grid[0] = 1;
		for (int i = 0; i < m; i++)
			for (int j = 1; j < n; j++)
				grid[j] += grid[j - 1];
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
//int main(void)
//{
//	Solution4 test;
//	cout << test.uniquePaths(3, 7);
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
