//	74. Search a 2D Matrix
//------------------------------------------------------------------------------//
//	Write an efficient algorithm that searches for a value in an m x n matrix.	//
//	This matrix has the following properties:									//
//	Integers in each row are sorted from left to right.							//
//	The first integer of each row is greater than the last integer of the		//
//	previous row.																//
//	For example,																//
//	Consider the following matrix :												//
//	[																			//
//		[1, 3, 5, 7],															//
//		[10, 11, 16, 20],														//
//		[23, 30, 34, 50]														//
//	]																			//
//	Given target = 3, return true.												//
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
//二分搜索，先按行分割，在按列分
class Solution 
{
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) 
	{
		const int m = matrix.size();
		if (m == 0)
			return false;
		const int n = matrix[0].size();
		if (n == 0)
			return false;
		if (target<matrix[0][0] || target>matrix[m - 1][n - 1])
			return false;
		//Search Row
		int start = 0, end = m - 1;
		while (start < end)
		{
			int mid = start + (end - start) / 2 + 1;
			int midVal = matrix[mid][0];
			if (midVal == target)
				return true;
			else if (midVal < target)
				start = mid;
			else
				end = mid - 1;
		}
		//search column
		int i = 0, j = n - 1;
		while (i <= j)
		{
			int mid = i + (j - i) / 2;
			if (matrix[start][mid] == target)
				return true;
			else if (matrix[start][mid] < target)
				i = mid + 1;
			else
				j = mid - 1;
		}
		return false;
	}
};
//整体二分查找
class Solution2
{
public:
	bool searchMatrix(const vector<vector<int>>& matrix, int target) 
	{
		if (matrix.empty()) return false;
		const size_t m = matrix.size();
		const size_t n = matrix.front().size();
		int first = 0;
		int last = m * n;
		while (first < last) 
		{
			int mid = first + (last - first) / 2;
			int value = matrix[mid / n][mid % n];
			if (value == target)
				return true;
			else if (value < target)
				first = mid + 1;
			else
				last = mid;
		}
		return false;
	}
};
//int main(void)
//{
//	Solution test;
//	vector<vector<int>> a = { {1,3,5,7},{10,11,16,20},{23,30,34,50} };
//	//vector<vector<int>> a = { {3,7} };
//	cout << boolalpha << test.searchMatrix(a, 30) << endl;
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
