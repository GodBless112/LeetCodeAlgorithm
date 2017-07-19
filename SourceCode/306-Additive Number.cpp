//	306. Additive Number
//------------------------------------------------------------------------------//
//	Additive number is a string whose digits can form additive sequence.		//
//	A valid additive sequence should contain at least three numbers.Except for	//
//	the first two numbers, each subsequent number in the sequence must be the	//
//	sum of the preceding two.													//
//	For example :																//
//	"112358" is an additive number because the digits can form an additive		//
//	sequence : 1, 1, 2, 3, 5, 8.												//
//	1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8									//
//	"199100199" is also an additive number, the additive sequence is : 1, 99,	//
//	100, 199.																	//
//	1 + 99 = 100, 99 + 100 = 199												//
//	Note : Numbers in the additive sequence cannot have leading zeros, so		//
//	sequence 1, 2, 03 or 1, 02, 3 is invalid.									//
//	Given a string containing only digits '0' - '9', write a function to		//
//	determine if it's an additive number.										//
//	Follow up :																	//
//		How would you handle overflow for very large input integers ?			//
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
//递归，回溯法，用一个pos记录起点，l1表示第一个的长度，l2表示第二个长度
class Solution {
public:
	bool isAdditiveNumber(string num) {
		int size = num.size();
		if (size < 3) return false;
		for (int l1 = 1; l1 <= size / 2; ++l1)
			for (int l2 = 1; l2 <= (size - l1) / 2; ++l2)
				if (check(num, 0, l1, l2))
					return true;
		return false;
	}
private:
	bool check(const string &num, int pos, int len1, int len2) {
		int start = pos + len1 + len2;
		if (start == num.length()) { 
			if (pos == 0) return false; 
			return true; 
		}
		int minLen = max(len1, len2);
		if ((num[pos] == '0'&&len1>1) || (num[pos + len1] == '0'&&len2>1)) return false;
		long num1 = atol(num.substr(pos, len1).c_str()), num2 = atol(num.substr(pos + len1, len2).c_str());
		if (num1>INT_MAX || num2>INT_MAX) return false;
		for (int l = minLen; l <= (int)num.length() - start; ++l)
		{
			if (l>1 && num[start] == '0') return false;
			long num3 = atol(num.substr(start, l).c_str());
			if (num3 > num1 + num2) return false;
			if (num3 == num1 + num2 && check(num, pos + len1, len2, l)) return true;
		}
		return false;
	}
};
//另一种递归，传递值和字符串
class Solution2 {
public:
	bool isAdditiveNumber(string num) {
		for (int i = 1; i <= num.size() / 2; i++) {
			for (int j = 1; j <= (num.size() - i) / 2; j++) {
				if (i >= 2 && num[0] == '0' || j >= 2 && num[i] == '0')
					continue;
				if (addNum(stol(num.substr(0, i)), stol(num.substr(i, j)), num.substr(i + j)))
					return true;
			}
		}
		return false;
	}
private:
	bool addNum(long num1, long num2, string num) {
		if (num.size() > 1 && num[0] == '0') return false;
		long sum = num1 + num2, numI = stol(num);
		long len = static_cast<long>(log10(sum)) + 1;
		if (numI == sum) return true;
		if (numI < sum || sum != stol(num.substr(0, len))) return false;
		else return addNum(num2, sum, num.substr(len));
	}
};
//迭代法，确定第一个和第二个数后不断衍生，看是否和输入的字符串一致
//第一个字符以i结尾，第二个以j结尾
class Solution3 {
public:
	bool isAdditiveNumber(string num) {
		int n = num.size();
		if (n < 3) return false;
		for (int i = 1; i <= n / 2; ++i) {
			if (i > 1 && num[0] == '0') break;
			int t = min((n - i), i + (n - i) / 2);
			for (int j = i + 1; j <= t; ++j) {
				if (num[i] == '0' && j > (i + 1)) break;
				string s1 = num.substr(0, i);
				string s2 = num.substr(i, j - i);
				long long d1 = atoll(s1.c_str()), d2 = atoll(s2.c_str());
				long long next = d1 + d2;
				string nexts = to_string(next);
				string now = s1 + s2 + nexts;
				while (now.size() < num.size()) {
					d1 = d2;
					d2 = next;
					next = d1 + d2;
					nexts = to_string(next);
					now += nexts;
				}
				if (now == num) return true;
			}
		}
		return false;
	}
};

//int main(void)
//{
//	Solution2 test;
//	cout << boolalpha << test.isAdditiveNumber("000");
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