//	344. Reverse String
//------------------------------------------------------------------------------//
//	Write a function that takes a string as input and returns the string		//
//	reversed.																	//
//	Example:																	//
//	Given s = "hello", return "olleh".											//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_set>
// constants
// function prototype
using namespace std;
class Solution {
public:
	string reverseString(string s) {
		int n = s.size();
		for (int i = 0; i < n / 2; ++i)
			swap(s[i], s[n - i - 1]);
		return s;
	}
};
//STL
class Solution2 {
public:
	string reverseString(string s) {
		reverse(s.begin(), s.end());
		return s;
	}
};
class Solution3 {
public:
	string reverseString(string s) {
		return string(s.rbegin(), s.rend());
	}
};
//两段夹逼
class Solution4 {
public:
	string reverseString(string s) {
		int i = 0, j = s.size() - 1;
		while (i < j) {
			swap(s[i++], s[j--]);
		}

		return s;
	}
};
//int main(void)
//{
//	Solution2 test;
//	cout << test.reverseString("ssa");
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