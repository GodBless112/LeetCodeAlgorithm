//	241. Different Ways to Add Parentheses
//------------------------------------------------------------------------------//
//	Given a string of numbers and operators, return all possible results from	//
//	computing all the different possible ways to group numbers and operators.	//
//	The valid operators are +, - and *.											//
//	Example 1																	//
//	Input: "2-1-1".																//
//	((2 - 1) - 1) = 0															//
//	(2 - (1 - 1)) = 2															//
//	Output : [0, 2]																//
//	Example 2																	//
//	Input : "2*3-4*5"															//
//	(2 * (3 - (4 * 5))) = -34													//
//	((2 * 3) - (4 * 5)) = -14													//
//	((2 * (3 - 4)) * 5) = -10													//
//	(2 * ((3 - 4) * 5)) = -10													//
//	(((2 * 3) - 4) * 5) = 10													//
//	Output: [-34, -14, -10, -10, 10]											//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<sstream>
#include<unordered_map>
// constants
// function prototype
using namespace std;
//分而治之，用操作符将其分成两部分，两部分分别可以计算得到一组值，
//两组值对应运算得到总的值
class Solution {
public:
	vector<int> diffWaysToCompute(string input) {
		stringstream ss(input);
		vector<char> ops;
		vector<int> nums;
		int num;
		char op;
		while (ss >> num) {
			nums.push_back(num);
			if (ss.eof())
				break;
			ss >> op;
			ops.push_back(op);
		}
		return DFS(ops, nums, 0, ops.size());
	}
private:
	vector<int> DFS(vector<char> &ops, vector<int> nums, int start, int end) {
		vector<int> result;
		if (start == end)
			result.push_back(nums[start]);
		for (int i = start; i < end; ++i) {
			vector<int> left = DFS(ops, nums, start, i);
			vector<int> right = DFS(ops, nums, i + 1, end);
			for (int j = 0; j < left.size(); ++j)
				for (int k = 0; k < right.size(); ++k) {
					int ans = ops[i] == '+' ? left[j] + right[k] :
						ops[i] == '-' ? left[j] - right[k] : left[j] * right[k];
					result.push_back(ans);
				}			
		}
		return result;
	}
};
//方案2的简化
class Soltion2 {
public:
	vector<int> diffWaysToCompute(string input) {
		vector<int> output;
		for (int i = 0; i < input.size(); i++) {
			char c = input[i];
			if (ispunct(c))
				for (int a : diffWaysToCompute(input.substr(0, i)))
					for (int b : diffWaysToCompute(input.substr(i + 1)))
						output.push_back(c == '+' ? a + b : c == '-' ? a - b : a*b);
		}
		return output.size() ? output : vector<int>{ stoi(input) };
	}
};
//动态规划，加入一个哈希表记录已经计算出来的结果，避免重复计算
class Solution2 {
public:
	vector<int> diffWaysToCompute(string input) {
		unordered_map<string, vector<int>> dpMap;
		return computeWithDP(input, dpMap);
	}

	vector<int> computeWithDP(string input, unordered_map<string, vector<int>> &dpMap) {
		vector<int> result;
		int size = input.size();
		for (int i = 0; i < size; i++) {
			char cur = input[i];
			if (cur == '+' || cur == '-' || cur == '*') {
				// Split input string into two parts and solve them recursively
				vector<int> result1, result2;
				string substr = input.substr(0, i);
				// check if dpMap has the result for substr
				if (dpMap.find(substr) != dpMap.end())
					result1 = dpMap[substr];
				else
					result1 = computeWithDP(substr, dpMap);

				substr = input.substr(i + 1);
				if (dpMap.find(substr) != dpMap.end())
					result2 = dpMap[substr];
				else
					result2 = computeWithDP(substr, dpMap);

				for (auto n1 : result1) {
					for (auto n2 : result2) {
						if (cur == '+')
							result.push_back(n1 + n2);
						else if (cur == '-')
							result.push_back(n1 - n2);
						else
							result.push_back(n1 * n2);
					}
				}
			}
		}
		// if the input string contains only number
		if (result.empty())
			result.push_back(atoi(input.c_str()));
		// save to dpMap
		dpMap[input] = result;
		return result;
	}
};
//int main(void)
//{
//	Solution test;
//	string input = "2*3-4*5";
//	vector<int> output = test.diffWaysToCompute(input);
//	for (auto x : output)
//		cout << x << " ";
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}