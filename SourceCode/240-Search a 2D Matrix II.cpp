//	240. Search a 2D Matrix II
//------------------------------------------------------------------------------//
//	Write an efficient algorithm that searches for a value in an m x n matrix.	//
//	This matrix has the following properties:									//
//	Integers in each row are sorted in ascending from left to right.			//
//	Integers in each column are sorted in ascending from top to bottom.			//
//	For example,																//
//	Consider the following matrix :												//
//	[																			//
//		[1, 4, 7, 11, 15],														//
//		[2, 5, 8, 12, 19],														//
//		[3, 6, 9, 16, 22],														//
//		[10, 13, 14, 17, 24],													//
//		[18, 21, 23, 26, 30]													//
//	]																			//
//	Given target = 5, return true.												//
//	Given target = 20, return false.											//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<stack>

// constants
// function prototype
using namespace std;
//矩阵的二分搜索，找到中间点，如果是target则返回true
//否则中间点将划分得到剩余三个可能区域
//耗时较长，收敛太慢
class Solution {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		const int m = matrix.size();
		if (m == 0) return false;
		const int n = matrix[0].size();
		if (n == 0) return false;
		return DFS(matrix, target, 0, 0, m - 1, n - 1);
	}
private:
	bool DFS(vector<vector<int>>& matrix, int target, int row1, int col1, int row2, int col2) {
		pair<int, int> start = { row1,col1 }, end = { row2,col2 };
		if (start.first <= end.first&&start.second <= end.second) {
			pair<int, int> mid;
			mid.first = start.first + (end.first - start.first) / 2;
			mid.second = start.second + (end.second - start.second) / 2;
			if (target == matrix[mid.first][mid.second])
				return true;
			else if (target < matrix[mid.first][mid.second]) {
				return DFS(matrix, target, start.first, start.second, mid.first - 1, mid.second - 1)
					|| DFS(matrix, target, start.first, mid.second, mid.first - 1, end.second)
					|| DFS(matrix, target, mid.first, start.second, end.first, mid.second - 1);
			}
			else {
				return DFS(matrix, target, mid.first + 1, mid.second + 1, end.first, end.second)
					|| DFS(matrix, target, start.first, mid.second + 1, mid.first, end.second)
					|| DFS(matrix, target, mid.first + 1, start.second, end.first, mid.second);
			}
		}
		return false;
	}
};
//时间复杂度O(m+n)
class Solution2 {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int m = matrix.size();
		if (m == 0) return false;
		int n = matrix[0].size();

		int i = 0, j = n - 1;
		while (i < m && j >= 0) {
			if (matrix[i][j] == target)
				return true;
			else if (matrix[i][j] > target) {
				j--;
			}
			else
				i++;
		}
		return false;
	}
};
//二分搜索的优化，时间复杂度O(mlogn)，按照先行后列二分搜索
class Solution3 {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		return searchMatrix(matrix, target, 0, matrix.size() - 1);
	}

	bool searchMatrix(vector<vector<int>>& matrix, int target, int top, int bottom) {
		if (top > bottom)
			return false;

		int mid = top + (bottom - top) / 2;
		if (matrix[mid].front() <= target && target <= matrix[mid].back())
			if (searchVector(matrix[mid], target)) return true;

		if (searchMatrix(matrix, target, top, mid - 1)) return true;
		if (searchMatrix(matrix, target, mid + 1, bottom)) return true;

		return false;
	}

	bool searchVector(vector<int>& v, int target) {
		int left = 0, right = v.size() - 1;

		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (v[mid] == target)
				return true;
			if (v[mid] < target)
				left = mid + 1;
			else
				right = mid - 1;
		}

		return false;
	}
};
//类似方案1
class Solution4 {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.size() == 0) return false;
		int row = matrix.size(), col = matrix[0].size();
		return help(matrix, 0, row - 1, 0, col - 1, target);
	}

	bool help(vector<vector<int>>& matrix, int row_start, int row_end, int col_start, int col_end, int target) {
		if (row_start>row_end || col_start>col_end)  return false;
		int row_mid = (row_start + row_end) / 2, col_mid = (col_start + col_end) / 2;
		if (matrix[row_mid][col_mid] == target)    return true;
		else if (matrix[row_mid][col_mid]>target) {
			/*** left-up || left-down || right-up ***/
			return help(matrix, row_start, row_mid - 1, col_start, col_mid - 1, target) ||
				help(matrix, row_mid, row_end, col_start, col_mid - 1, target) ||
				help(matrix, row_start, row_mid - 1, col_mid, col_end, target);
		}
		else {
			/*** right-down || left-down || right-up ***/
			return help(matrix, row_mid + 1, row_end, col_mid + 1, col_end, target) ||
				help(matrix, row_mid + 1, row_end, col_start, col_mid, target) ||
				help(matrix, row_start, row_mid, col_mid + 1, col_end, target);
		}
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<vector<int>> matrix = { {1,   4,  7, 11, 15},
//								   {2,   5,  8, 12, 19},
//								   {3,   6,  9, 16, 22},
//								   {10, 13, 14, 17, 24},
//								   {18, 21, 23, 26, 30} };
//	vector<vector<int>> matrix2 = { { 1,   2,  3,  4,  5 },
//								    { 6,   7,  8,  9, 10 },
//								    { 11, 12, 13, 14, 15 },
//								    { 16, 17, 18, 19, 20 },
//								    { 21, 22, 23, 24, 25 } };
//	for (int i = 0; i < 30; i++)
//		cout << boolalpha << test.searchMatrix(matrix2, i) << endl;
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}