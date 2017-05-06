//	48. Rotate Image
//------------------------------------------------------------------------------//
//	You are given an n x n 2D matrix representing an image.						//
//	Rotate the image by 90 degrees(clockwise).									//
//	Follow up :																	//
//	Could you do this in - place ?												//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
// constants
// function prototype
using namespace std;
//要求就地算法，可以有多种思路，将矩阵想象成一张方片，想要顺时针旋转90度，可以先沿左下右上斜线翻转，再沿中线翻转
//或者上述两个顺序颠倒
class Solution
{
public:
	void rotate(vector<vector<int>>& matrix) 
	{
		const size_t n = matrix.size();
		//沿斜对角线翻转
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n - i; j++)
				swap(matrix[i][j], matrix[n - 1 - j][n - 1 - i]);
		//沿水平中线翻转
		for (int i = 0; i < n / 2; i++)
			for (int j = 0; j < n; j++)
				swap(matrix[i][j], matrix[n - 1 - i][j]);
	}
};
class Solution2
{
public:
	void rotate(vector<vector<int>>& matrix)
	{
		const size_t n = matrix.size();
		//沿水平中线翻转
		for (int i = 0; i < n / 2; i++)
			for (int j = 0; j < n; j++)
				swap(matrix[i][j], matrix[n - 1 - i][j]);
		//沿斜对角线翻转
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n - i; j++)
				swap(matrix[i][j], matrix[n - 1 - j][n - 1 - i]);		
	}
};
//int main(void)
//{
//	Solution test;
//	vector<vector<int>> a = { {1,2},{3,4} };
//	test.rotate(a);
//	for (auto x : a)
//	{
//		for (auto y : x)
//			cout << y << " ";
//		cout << endl;
//	}
//	
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
