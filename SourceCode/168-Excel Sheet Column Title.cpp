//	168. Excel Sheet Column Title
//------------------------------------------------------------------------------//
//	Given a positive integer, return its corresponding column title as appear	//
//	in an Excel sheet.															//
//	For example :																//
//	1->A																		//
//	2->B																		//
//	3->C																		//
//	...																			//
//	26->Z																		//
//	27->AA																		//
//	28->AB 																		//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_map>
// constants
// function prototype
using namespace std;

//其实就是转换为26进制的数，迭代的方法
class Solution {
public:
	string convertToTitle(int n) {
		string result;
		while (n)
		{
			n = n - 1;
			result = char('A' + n % 26) + result;
			n /= 26;
		}
		return result;
	}
};
//递归的做法
class Solution2 {
public:
	string convertToTitle(int n) {
		return n == 0 ? "" : convertToTitle((n - 1) / 26) + (char)((n - 1) % 26 + 'A');
	}
};
//int main(void)
//{
//	Solution test;
//	cout << test.convertToTitle(52);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//	
//	return 0;
//}