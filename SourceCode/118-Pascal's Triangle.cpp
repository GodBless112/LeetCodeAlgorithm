//	118. Pascal's Triangle
//------------------------------------------------------------------------------//
//	Given numRows, generate the first numRows of Pascal's triangle.				//
//	For example, given numRows = 5,												//
//	Return																		//
//	[																			//
//			    [1],															//
//			  [1, 1],															//
//		    [1, 2, 1],															//
//		  [1, 3, 3, 1],															//
//		[1, 4, 6, 4, 1]															//
//	]		 																	//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<queue>
#include<stack>
// constants
// function prototype
using namespace std;
//从左到右
class Solution 
{
public:
	vector<vector<int>> generate(int numRows) 
	{
		vector<vector<int>> result;
		if (numRows == 0)
			return result;
		result.push_back(vector<int>(1, 1));
		for (int i = 2; i <= numRows; i++)
		{
			vector<int> level(i, 1);
			for (int j = 1; j < i - 1; j++)
				level[j] = result[i - 2][j] + result[i - 2][j - 1];
			result.push_back(level);
		}
		return result;
	}
};
//从右到左
class Solution2 {
public:
	vector<vector<int> > generate(int numRows) {
		vector<vector<int> > result;
		vector<int> array;
		for (int i = 1; i <= numRows; i++) {
			for (int j = i - 2; j > 0; j--) {
				array[j] = array[j - 1] + array[j];
			}
			array.push_back(1);
			result.push_back(array);
		}
		return result;
	}
};
//int main(void)
//{
//	Solution2 test;
//	auto res = test.generate(5);
//	for_each(res.begin(), res.end(), [](vector<int> &elem) {
//		for (auto x : elem)
//			cout << x << " ";
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