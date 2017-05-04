//	54. Spiral Matrix
//------------------------------------------------------------------------------//
//	Given a matrix of m x n elements (m rows, n columns), return all elements	//
//	of the matrix in spiral order.												//
//	For example,																//
//	Given the following matrix :												//
//	[																			//
//		[1, 2, 3],																//
//		[4, 5, 6],																//
//		[7, 8, 9]																//
//	]																			//
//	You should return[1, 2, 3, 6, 9, 8, 7, 4, 5].								//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<unordered_map>
// constants
// function prototype
using namespace std;
//思路1：按照从左往右，从上往下，从右往左，从下往上的顺序一直走，遇到越界则停止
class Solution 
{
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) 
	{
		vector<int> result;
		if (matrix.empty())
			return result;
		int RowStart = 0, RowEnd = matrix.size() - 1;
		int ColStart = 0, ColEnd = matrix[0].size() - 1;
		while (true)
		{
			//let to right
			for (int i = ColStart; i <= ColEnd; ++i)
				result.push_back(matrix[RowStart][i]);
			if (++RowStart > RowEnd) break;
			//top to bottom
			for (int i = RowStart; i <= RowEnd; ++i)
				result.push_back(matrix[i][ColEnd]);
			if (--ColEnd < ColStart) break;
			//right to left
			for (int i = ColEnd; i >= ColStart; --i)
				result.push_back(matrix[RowEnd][i]);
			if (--RowEnd < RowStart) break;
			//bottom to top
			for (int i = RowEnd; i >= RowStart; --i)
				result.push_back(matrix[i][ColStart]);
			if (++ColStart > ColEnd) break;
		}
		return result;
	}
};
//对于一个m X n矩阵，假设有一个虚拟的起始点（0,-1），则顺序是先往右走n步，往下走m-1步
//然后往左n-1步，往右m-1步,直至其中一个为0
class Solution2
{
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) 
	{
		vector<vector<int> > dirs{ { 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 } };
		vector<int> res;
		int nr = matrix.size();     if (nr == 0) return res;
		int nc = matrix[0].size();  if (nc == 0) return res;

		vector<int> nSteps{ nc, nr - 1 };

		int iDir = 0;   // index of direction.
		int ir = 0, ic = -1;    // initial position
		while (nSteps[iDir % 2]) 
		{
			for (int i = 0; i < nSteps[iDir % 2]; ++i) 
			{
				ir += dirs[iDir][0]; ic += dirs[iDir][1];
				res.push_back(matrix[ir][ic]);
			}
			nSteps[iDir % 2]--;
			iDir = (iDir + 1) % 4;
		}
		return res;
	}
};
//方案1的优化，提前确定result的大小
class Solution3 
{
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) 
	{
		if (matrix.empty()) return{};
		int m = matrix.size(), n = matrix[0].size();
		vector<int> spiral(m * n);
		int u = 0, d = m - 1, l = 0, r = n - 1, k = 0;
		while (true)
		{
			// up
			for (int col = l; col <= r; col++) spiral[k++] = matrix[u][col];
			if (++u > d) break;
			// right
			for (int row = u; row <= d; row++) spiral[k++] = matrix[row][r];
			if (--r < l) break;
			// down
			for (int col = r; col >= l; col--) spiral[k++] = matrix[d][col];
			if (--d < u) break;
			// left
			for (int row = d; row >= u; row--) spiral[k++] = matrix[row][l];
			if (++l > r) break;
		}
		return spiral;
	}
};

//int main(void)
//{
//	Solution test;
//	vector<vector<int>> a = { {1,2,3},{4,5,6},{7,8,9} };
//	auto x = test.spiralOrder(a);
//	for (auto y : x)
//		cout << y << " ";
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
