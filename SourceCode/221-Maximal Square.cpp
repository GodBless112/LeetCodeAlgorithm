//	221. Maximal Square
//------------------------------------------------------------------------------//
//	Given a 2D binary matrix filled with 0's and 1's, find the largest square	//
//	containing only 1's and return its area.									//
//	For example, given the following matrix :									//
//	1 0 1 0 0																	//
//	1 0 1 1 1																	//
//	1 1 1 1 1																	//
//	1 0 0 1 0																	//
//	Return 4.																	//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<set>
#include<map>
#include<unordered_map>
// constants
// function prototype
using namespace std;
//动态规划，如果当前是个1，则当前的节点包含最大正方形为左上角节点
//上面节点左面节点中最小值加1
class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int n = matrix.size();
		if (n == 0) return 0;
		int m = matrix[0].size();
		int result = 0;
		vector<vector<int>> square(n, vector<int>(m));
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) {
				if (matrix[i][j] == '1') {
					if (i == 0 || j == 0)
						square[i][j] = 1;
					else
						square[i][j] = min(min(square[i - 1][j - 1], square[i][j - 1]), square[i - 1][j]) + 1;
					result = max(result, square[i][j]);
				}
			}
						
		return result*result;
	}
};
//动态规划的优化，减少空间复杂度,用一维数组来存放动态结果
class Solution2 {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int n = matrix.size();
		if (n == 0) return 0;
		int m = matrix[0].size();
		int result = 0, prev = 0;
		vector<int> square(m + 1);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				int temp = square[j];
				if (matrix[i - 1][j - 1] == '1') {
					square[j] = min(min(square[j - 1], square[j]), prev) + 1;
					result = max(result, square[j]);
				}
				else
					square[j] = 0;
				prev = temp;
			}

		return result*result;
	}
};
//暴力法
class Solution3 {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int n = matrix.size();
		if (n == 0) return 0;
		int m = matrix[0].size();
		int result = 0, prev = 0;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) {
				if (matrix[i][j] == '1') {
					int sqlen = 1;
					bool flag = true;
					while (sqlen + i < n && sqlen + j < m && flag) {
						for (int k = j; k <= sqlen + j; k++) {
							if (matrix[i + sqlen][k] == '0') {
								flag = false;
								break;
							}
						}
						for (int k = i; k <= sqlen + i; k++) {
							if (matrix[k][j + sqlen] == '0') {
								flag = false;
								break;
							}
						}
						if (flag)
							sqlen++;
					}
					if (result < sqlen) {
						result = sqlen;
					}
				}
			}

		return result*result;
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<vector<char>> matrix{ {'1', '0', '1', '0', '0'},
//								 {'1', '0', '1', '1', '1'},
//								 {'1', '1', '1', '1', '1'},
//								 {'1', '0', '0', '1', '0'} };
//	cout << test.maximalSquare(matrix);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}