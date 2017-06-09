//	200. Number of Islands
//------------------------------------------------------------------------------//
//	Given a 2d grid map of '1's (land) and '0's (water), count the number of	//
//	islands. An island is surrounded by water and is formed by connecting		//
//	adjacent lands horizontally or vertically. You may assume all four edges of //
//	the grid are all surrounded by water.										//
//	Example 1:																	//
//	11110																		//
//	11010																		//
//	11000																		//
//	00000																		//
//	Answer : 1																	//
//	Example 2 :																	//
//	11000																		//
//	11000																		//
//	00100																		//
//	00011																		//
//	Answer : 3																	//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<queue>
// constants
// function prototype
using namespace std;
//不相交集的方法，Union Find
class UnionFind{
public:
	explicit UnionFind(int numElements) :s(numElements, -1) {
		count = numElements;
	}
	int find(int x) const {
		if (s[x] < 0) return x;
		else return find(s[x]);
	}
	int find(int x) {
		if (s[x] < 0) return x;
		else
			return s[x] = find(s[x]);
	}
	void unionSets(int root1, int root2) {
		int i = find(root1), j = find(root2);
		if (i == j) return;
		if (s[j] < s[i])
			s[i] = j;
		else {
			if (s[i] == s[j]) 
				s[i]--;
			s[j] = i;
		}
		count--;
	}
	bool isConected(int root1, int root2) {
		return find(root1) == find(root2);
	}
	int getCount() {
		return count;
	}
private:
	vector<int> s;
	int count;
};
class Solution {
public:
	int numIslands(vector<vector<char>>& grid) {
		int m = grid.size();
		if (m == 0) return 0;
		int n = grid[0].size();
		UnionFind uf(m*n);
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (grid[i][j] != '1') continue;
				if (i > 0 && grid[i - 1][j] == '1')
					uf.unionSets(i*n + j, (i - 1)*n + j);
				if (j > 0 && grid[i][j - 1] == '1')
					uf.unionSets(i*n + j, i*n + j - 1);
			}
		}
		int result = 0;
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				if (grid[i][j] == '1' && uf.find(i*n + j) == i*n + j)
					result++;
		return result;
	}
};
//DFS的方法
class Solution2 {
public:
	int numIslands(vector<vector<char>>& grid) {
		const int m = grid.size();
		if (m == 0) return 0;
		int n = grid[0].size();
		int count = 0;
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				if (grid[i][j] == '1') {
					++count;
					DFS(grid, i, j);
				}
		return count;
	}
private:
	void DFS(vector<vector<char>> &grid, int i, int j) {
		if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == '0')
			return;
		grid[i][j] = '0';
		DFS(grid, i - 1, j);
		DFS(grid, i, j - 1);
		DFS(grid, i + 1, j);
		DFS(grid, i, j + 1);
	}
};
//BFS的方法
class Solution3 {
public:
	int numIslands(vector<vector<char>>& grid) {
		const int m = grid.size();
		if (m == 0) return 0;
		int n = grid[0].size();
		int count = 0;
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				if (grid[i][j] == '1') {
					++count;
					BFS(grid, i, j);
				}
		return count;
	}
private:
	void BFS(vector<vector<char>> &grid, int i, int j) {
		queue<pair<int, int>> q;
		q.push(make_pair(i, j));
		grid[i][j] = '0';
		while (!q.empty()) {
			i = q.front().first, j = q.front().second;
			q.pop();
			if (i > 0 && grid[i - 1][j] == '1') {
				q.push(make_pair(i - 1, j));
				grid[i - 1][j] = '0';
			}
			if (i < grid.size() - 1 && grid[i + 1][j] == '1') {
				q.push(make_pair(i + 1, j));
				grid[i + 1][j] = '0';
			}
			if (j > 0 && grid[i][j - 1] == '1') {
				q.push(make_pair(i, j - 1));
				grid[i][j - 1] = '0';
			}
			if (j < grid[0].size() - 1 && grid[i][j + 1] == '1') {
				q.push(make_pair(i, j + 1));
				grid[i][j + 1] = '0';
			}
		}
	}
};

//int main(void)
//{
//	Solution3 test;
//	vector<vector<char>> grid = { { '1','1','0','0','0' },
//								  { '1','1','0','0','0' },
//								  { '0','0','1','0','0' },
//								  { '0','0','0','1','1' } };
//	cout << test.numIslands(grid);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//	
//	return 0;
//}