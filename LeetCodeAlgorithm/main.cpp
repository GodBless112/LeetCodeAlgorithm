﻿//	120. Triangle
//------------------------------------------------------------------------------//
//	Given a triangle, find the minimum path sum from top to bottom. Each step	//
//	you may move to adjacent numbers on the row below.							//
//	For example, given the following triangle									//
//	[																			//
//		    [2],																//
//		   [3, 4],																//
//		 [6, 5, 7],																//
//		[4, 1, 8, 3]															//
//	]																			//
//	The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).	//
//	Note:																		//
//	Bonus point if you are able to do this using only O(n) extra space, where n //
//	is the total number of rows in the triangle.								//
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

class Solution {
public:
	int minimumTotal(vector<vector<int>>& triangle) {

	}
};

int main(void)
{
	Solution test;
	vector<vector<int>> triangle{ {2},{3,4},{6,5,7},{4,1,8,3} };
	cout << test.minimumTotal(triangle);
	cout << endl;

	// code to keep window open for MSVC++
	cin.clear();
	while (cin.get() != '\n')
		continue;
	cin.get();

	return 0;
}