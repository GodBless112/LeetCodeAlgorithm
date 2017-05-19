//	122. Best Time to Buy and Sell Stock II
//------------------------------------------------------------------------------//
//	Say you have an array for which the ith element is the price of a given		//
//	stock on day i.																//
//	Design an algorithm to find the maximum profit.You may complete as many		//
//	transactions as you like(ie, buy one and sell one share of the stock		//
//	multiple times).However, you may not engage in multiple transactions at the //
//	same time(ie, you must sell the stock before you buy again).		 		//
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
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int result = 0;
		for (int i = 1; i < prices.size(); ++i) {
			if (prices[i] > prices[i - 1])
				result += prices[i] - prices[i - 1];
		}
		return result;
	}
};


//int main(void)
//{
//	Solution test;
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