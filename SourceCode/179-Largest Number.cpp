//	179. Largest Number
//------------------------------------------------------------------------------//
//	Given a list of non negative integers, arrange them such that they form the //
//	largest number.																//
//	For example, given[3, 30, 34, 5, 9], the largest formed number is 9534330.	//
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
//组合两个数字，然后比较并排序，这里必须用64位整型，不然会溢出。
class Solution {
public:
	string largestNumber(vector<int>& nums) {
		if (accumulate(nums.begin(), nums.end(), 0) == 0) return "0";
		sort(nums.begin(), nums.end(), mycompare);
		string result;
		for (int i = nums.size() - 1; i >= 0; --i)
			result += to_string(nums[i]);
		return result;
	}
private:
	static int64_t digits(int num) {
		int64_t result = 1;
		if (num == 0) return 10;
		while (num) {
			result *= 10;
			num /= 10;
		}
		return result;
	}
	//注意此处用函数指针的话必须用static或者全局的
	//因为类方法包含有this指针，与sort函数对象的输入不匹配
	static bool mycompare(int num1, int num2) {
		int64_t d1 = digits(num1);
		int64_t d2 = digits(num2);
		int64_t a = num1*d2 + num2;
		int64_t b = num1 + num2*d1;
		return a < b;
	}
};
//利用字符串的比较
class Solution2 {
public:
	string largestNumber(vector<int>& nums) {
		vector<string> arr;
		for (auto num : nums)
			arr.push_back(to_string(num));
		sort(arr.begin(), arr.end(), [](string &s1, string &s2) {
			return s1 + s2 > s2 + s1;
		});
		string result;
		for (auto s : arr)
			result += s;
		if (result[0] == '0') return "0";
		return result;
	}
};
//int main(void)
//{
//	Solution test;
//	vector<int> nums{ INT_MAX - 1,INT_MAX };
//	cout << test.largestNumber(nums);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//	
//	return 0;
//}