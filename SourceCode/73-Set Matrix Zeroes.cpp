//	73. Set Matrix Zeroes
//------------------------------------------------------------------------------//
//	Given a m x n matrix, if an element is 0, set its entire row and column to	//
//	0. Do it in place.															//
//	Follow up:																	//
//	Did you use extra space ?													//
//	A straight forward solution using O(mn) space is probably a bad idea.		//
//	A simple improvement uses O(m + n) space, but still not the best solution.	//
//	Could you devise a constant space solution ?								//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
#include<functional>
// constants
// function prototype
using namespace std;
//O(m+n)空间复杂度，时间复杂度O(m*n)
class Solution 
{
public:
	void setZeroes(vector<vector<int>>& matrix)
	{
		int m = matrix.size();
		int n = matrix[0].size();
		vector<bool> Row_Has_Zero(m, false);
		vector<bool> Col_Has_Zero(n, false);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (matrix[i][j] == 0)
					Row_Has_Zero[i] = Col_Has_Zero[j] = true;
		for (int i = 0; i < m; i++)
			if (Row_Has_Zero[i])
				fill(matrix[i].begin(), matrix[i].end(), 0);
		for (int j = 0; j < n; j++)
			if (Col_Has_Zero[j])
				for (int i = 0; i < m; i++)
					matrix[i][j] = 0;
	}
};
//不用额外的数组记录行列是否存在0，直接用矩阵的第一行第一列来记录
class Solution2
{
public:
	void setZeroes(vector<vector<int>>& matrix)
	{
		int m = matrix.size();
		int n = matrix[0].size();
		bool Row_Has_Zero = false;
		bool Col_Has_Zero = false;
		for (int i = 0; i < n; i++)
			if (matrix[0][i] == 0) {
				Row_Has_Zero = true;
				break;
			}
		for (int i = 0; i < m; i++)
			if (matrix[i][0] == 0) {
				Col_Has_Zero = true;
				break;
			}
		for (int i = 1; i < m; i++)
			for (int j = 1; j < n; j++)
				if (matrix[i][j] == 0) {
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}
		for (int i = 1; i < m; i++)
			for (int j = 1; j < n; j++)
				if (matrix[i][0] == 0 || matrix[0][j] == 0)
					matrix[i][j] = 0;
		if (Row_Has_Zero)
			for (int i = 0; i < n; i++)
				matrix[0][i] = 0;
		if (Col_Has_Zero)
			for (int i = 0; i < m; i++)
				matrix[i][0] = 0;
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<vector<int>> a = { {1,2,3},{0,1,0},{3,3,3} };
//	for_each(a.begin(), a.end(), [](vector<int> & x)
//	{
//		for (int i = 0; i < x.size(); i++)
//			cout << x[i] << " ";
//		cout << endl;
//	});
//	cout << endl;
//	test.setZeroes(a);
//	for_each(a.begin(), a.end(), [](vector<int> & x)
//	{
//		for (int i = 0; i < x.size(); i++)
//			cout << x[i] << " ";
//		cout << endl;
//	});
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
