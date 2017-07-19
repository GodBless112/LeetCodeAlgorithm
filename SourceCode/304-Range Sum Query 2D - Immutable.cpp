//	304. Range Sum Query 2D - Immutable
//------------------------------------------------------------------------------//
//	Given a 2D matrix matrix, find the sum of the elements inside the rectangle //
//	defined by its upper left corner (row1, col1) and lower right corner		//
//	(row2, col2).																//
//	Range Sum Query 2D															//
//	The above rectangle(with the red border) is defined by(row1, col1) = (2, 1) //
//	and (row2, col2) = (4, 3), which contains sum = 8.							//
//	Example:																	//
//	Given matrix = [															//
//		[3, 0, 1, 4, 2],														//
//		[5, 6, 3, 2, 1],														//
//		[1, 2, 0, 1, 5],														//
//		[4, 1, 0, 1, 7],														//
//		[1, 0, 3, 0, 5]															//
//	]																			//
//	sumRegion(2, 1, 4, 3) -> 8													//
//	sumRegion(1, 1, 2, 2) -> 11													//
//	sumRegion(1, 2, 2, 4) -> 12													//
//	Note:																		//
//		1.You may assume that the matrix does not change.						//
//		2.There are many calls to sumRegion function.							//
//		3.You may assume that row1 ≤ row2 and col1 ≤ col2.					//
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
//计算以[0,0],[i,j]为界的矩形的和缓存起来，动态规划,sums[i][j]=sums[i-1][j] + sums[i][j-1] - sums[i-1][j-1] 
//+ matrix[i - 1][j - 1]
//计算[row1,col1],[row2,col2]时，有sums[row2][col2]-sums[row2][col1-1]-sums[row1-1][col2]+sums[row1-1][col1-1]
class NumMatrix {
public:
	NumMatrix(vector<vector<int>> matrix) :matrixSum(matrix) {
		for (int i = 0; i < matrixSum.size(); ++i)
			for (int j = 0; j < matrixSum[0].size(); ++j)
				if (i == 0 && j == 0) continue;
				else if (i == 0)
					matrixSum[i][j] += matrixSum[i][j - 1];
				else if (j == 0)
					matrixSum[i][j] += matrixSum[i - 1][j];
				else
					matrixSum[i][j] += matrixSum[i - 1][j] + matrixSum[i][j - 1] - matrixSum[i - 1][j - 1];
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		if (row1 == 0 && col1 == 0)
			return  matrixSum[row2][col2];
		if (row1 == 0)
			return matrixSum[row2][col2] - matrixSum[row2][col1 - 1];
		if (col1 == 0)
			return  matrixSum[row2][col2] - matrixSum[row1 - 1][col2];
		return matrixSum[row2][col2] - matrixSum[row1 - 1][col2] - matrixSum[row2][col1 - 1] + matrixSum[row1 - 1][col1 - 1];
	}
private:
	vector<vector<int>> matrixSum;
};

//将缓存数组增加一维避免边界判断
class NumMatrix2 {
private:
	int row, col;
	vector<vector<int>> sums;
public:
	NumMatrix2(vector<vector<int>> matrix) {
		row = matrix.size();
		col = row>0 ? matrix[0].size() : 0;
		sums = vector<vector<int>>(row + 1, vector<int>(col + 1, 0));
		for (int i = 1; i <= row; i++) {
			for (int j = 1; j <= col; j++) {
				sums[i][j] = matrix[i - 1][j - 1] +
					sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1];
			}
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		return sums[row2 + 1][col2 + 1] - sums[row2 + 1][col1] - sums[row1][col2 + 1] + sums[row1][col1];
	}
};
//加一个函数判断边界
class NumMatrix3 {
public:
	NumMatrix3(vector<vector<int>> matrix) {
		accu = matrix;
		for (int i = 0; i<matrix.size(); ++i)
			for (int j = 0; j<matrix[0].size(); ++j)
				accu[i][j] += a(i - 1, j) + a(i, j - 1) - a(i - 1, j - 1);
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		return a(row2, col2) - a(row1 - 1, col2) - a(row2, col1 - 1) + a(row1 - 1, col1 - 1);
	}

private:
	vector<vector<int>> accu;
	int a(int i, int j) {
		return i >= 0 && j >= 0 ? accu[i][j] : 0;
	}
};
/**
* Your NumMatrix object will be instantiated and called as such:
* NumMatrix obj = new NumMatrix(matrix);
* int param_1 = obj.sumRegion(row1,col1,row2,col2);
*/
//int main(void)
//{
//	vector<vector<int>> matrix{ {3, 0, 1, 4, 2},
//								{5, 6, 3, 2, 1},
//								{1, 2, 0, 1, 5},
//								{4, 1, 0, 1, 7},
//								{1, 0, 3, 0, 5} };
//	NumMatrix2 test(matrix);
//	cout << test.sumRegion(0, 1, 4, 3) << endl;
//	cout << test.sumRegion(1, 1, 2, 2) << endl;
//	cout << test.sumRegion(1, 2, 2, 4) << endl;
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