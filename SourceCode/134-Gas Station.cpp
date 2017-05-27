//	134. Gas Station
//------------------------------------------------------------------------------//
//	There are N gas stations along a circular route, where the amount of gas at //
//	station i is gas[i].														//
//	You have a car with an unlimited gas tank and it costs cost[i] of gas to	//
//	travel from station i to its next station(i + 1).You begin the journey with //
//	an empty tank at one of the gas stations.									//
//	Return the starting gas station's index if you can travel around the circuit//
//	once, otherwise return -1.													//
//	Note:																		//
//	The solution is guaranteed to be unique.									//
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

//贪心算法，时间复杂度O(N)
class Solution {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int totalremain = 0, curremain = 0;
		int i, j = -1;
		int n = gas.size();
		for (i = 0; i < n; i++) {
			totalremain += gas[i] - cost[i];
			curremain += gas[i] - cost[i];
			if (curremain < 0) {
				j = i;
				curremain = 0;
			}		
		}
		return (totalremain >= 0) ? j + 1 : -1;
	}
};
//int main(void)
//{
//	Solution test;
//	vector<int> gas{ 4,2 };
//	vector<int> cost{ 5,1 };
//	cout << test.canCompleteCircuit(gas, cost);
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