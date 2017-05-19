//	121. Best Time to Buy and Sell Stock
//------------------------------------------------------------------------------//
//	Say you have an array for which the ith element is the price of a given		//
//	stock on day i.																//
//	If you were only permitted to complete at most one transaction(ie, buy one	//
//	and sell one share of the stock), design an algorithm to find the maximum	//
//	profit.																		//
//	Example 1:																	//
//		Input: [7, 1, 5, 3, 6, 4]												//
//		Output : 5																//
//		max.difference = 6 - 1 = 5 (not 7 - 1 = 6, as selling price needs to be //
//	larger than buying price)													//
//	Example 2 :																	//
//		Input : [7, 6, 4, 3, 1]													//
//		Output : 0																//
//	In this case, no transaction is done, i.e.max profit = 0.		 			//
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
//贪心算法
class Solution 
{
public:
	int maxProfit(vector<int>& prices) 
	{
		if (prices.empty()) return 0;
		int minPrice = prices[0];
		int res = 0;
		for (int i = 1; i < prices.size(); ++i)
		{
			if (prices[i] - minPrice > res)
				res = prices[i] - minPrice;
			if (prices[i] < minPrice)
				minPrice = prices[i];
		}
		return res;
	}
};
//类似于求最大子序列和问题，把原数组转换成差值序列
class Solution2
{
public:
	int maxProfit(vector<int>& prices) {
		int maxCur = 0, maxSoFar = 0;
		for (int i = 1; i < prices.size(); i++) {
			maxCur = max(0, maxCur += prices[i] - prices[i - 1]);
			maxSoFar = max(maxCur, maxSoFar);
		}
		return maxSoFar;
	}
};

//int main(void)
//{
//	Solution2 test;
//	vector<int> prices({ 7, 1, 5, 3, 6, 4 });
//	cout << test.maxProfit(prices) << endl;
//	prices = { 7, 6, 4, 3, 1 };
//	cout << test.maxProfit(prices);
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