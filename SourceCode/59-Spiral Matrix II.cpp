//	59. Spiral Matrix II
//------------------------------------------------------------------------------//
//	Given an integer n, generate a square matrix filled with elements from 1 to	//
//	n2 in spiral order.															//
//	For example,																//
//	Given n = 3,																//
//	You should return the following matrix :									//
//	[																			//
//		[1, 2, 3],																//
//		[8, 9, 4],																//
//		[7, 6, 5]																//
//	]																			//
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
//类似于Spiral Matrix，定义行和列的当前范围，从左到右，从上到下，从右到左，从下到上
class Solution 
{
public:
	vector<vector<int>> generateMatrix(int n) 
	{
		vector<vector<int>> result(n, vector<int>(n));
		int num = 1;
		int RowStart = 0, RowEnd = n - 1;
		int ColStart = 0, ColEnd = n - 1;
		while (true)
		{
			//let to right
			for (int i = ColStart; i <= ColEnd; ++i)
				result[RowStart][i] = num++;
			if (++RowStart > RowEnd) break;
			//top to bottom
			for (int i = RowStart; i <= RowEnd; ++i)
				result[i][ColEnd] = num++;
			if (--ColEnd < ColStart) break;
			//right to left
			for (int i = ColEnd; i >= ColStart; --i)
				result[RowEnd][i] = num++;
			if (--RowEnd < RowStart) break;
			//bottom to top
			for (int i = RowEnd; i >= RowStart; --i)
				result[i][ColStart] = num++;
			if (++ColStart > ColEnd) break;
		}
		return result;
	}
};
//虚拟起始点（0，-1）
class Solution2
{
public:
	vector<vector<int>> generateMatrix(int n)
	{
		vector<vector<int>> dirs = { { 0,1 }, { 1,0 }, { 0,-1 }, { -1,0 } };
		int nr = n;
		int nc = n - 1;
		int num = 1;
		vector<int> nSteps{ nr,nc };
		int ir = 0, ic = -1;
		int iDir = 0;
		vector<vector<int>> result(n, vector<int>(n));
		while (nSteps[iDir % 2])
		{
			for (int i = 0; i < nSteps[iDir % 2]; i++)
			{
				ir += dirs[iDir % 4][0];
				ic += dirs[iDir % 4][1];
				result[ir][ic] = num++;
			}
			nSteps[iDir % 2]--;
			iDir = (iDir + 1) % 4;
		}
		return result;
	}
};
//将螺旋分成一圈一圈，每一圈包含4部分，这仅适用于方阵
class Solution3
{
public:
	vector<vector<int>> generateMatrix(int n)
	{
		vector<vector<int>> result(n, vector<int>(n));
		int num = 1;
		int start = 0, end = n - 1;
		while (start < end)
		{
			for (int col = start; col < end; col++) result[start][col] = num++;
			for (int row = start; row < end; row++) result[row][end] = num++;
			for (int col = end; col > start; col--) result[end][col] = num++;
			for(int row = end; row > start; row--) result[row][start] = num++;
			start++; end--;
		}
		if (start == end)
			result[start][end] = num;
		return result;
	}
};
//int main(void)
//{
//	Solution3 test;
//	auto x = test.generateMatrix(3);
//	for (auto a : x)
//	{
//		for (auto b : a)
//			cout << b << " ";
//		cout << endl;
//	}
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
