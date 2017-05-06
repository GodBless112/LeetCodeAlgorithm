//	43. Multiply Strings
//------------------------------------------------------------------------------//
//	Given two non-negative integers num1 and num2 represented as strings,		//
//	return the product of num1 and num2.										//
//	Note:																		//
//		The length of both num1 and num2 is < 110.								//
//		Both num1 and num2 contains only digits 0 - 9.							//
//		Both num1 and num2 does not contain any leading zero.					//
//		You must not use any built - in BigInteger library or convert the		//
//		inputs to integer directly.												//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<iterator>
#include<iomanip>
#include<sstream>
// constants
// function prototype
using namespace std;
//my own method, 逐位相乘，然后累加
class Solution 
{
public:
	string multiply(string num1, string num2)
	{
		string result;
		if (num1.empty() || num2.empty())
			return result;
		if (num1 == "0" || num2 == "0")
			return "0";
		if (num1.size() < num2.size())
			return multiply(num2, num1);
		vector<string> strlist;
		int carry = 0, res = 0;
		for (int i = num2.size() - 1; i >= 0 ; i--)
		{
			string temp;
			carry = 0;
			for (int j = num1.size() - 1; j >=0 ; j--)
			{
				int a = num2[i] - '0';
				int b = num1[j] - '0';		
				int ans = a*b + carry;
				res = ans % 10;
				carry = ans / 10;
				temp = to_string(res) + temp;
			}
			temp.append(num2.size() - 1 - i, '0');
			strlist.push_back(temp);
			if (carry!=0)
				strlist.back() = to_string(carry) + strlist.back();
		}
		carry = 0;
		for (int i = 0; i < strlist.back().size(); i++)
		{
			int ans = 0;
			for (int j = 0; j < strlist.size(); j++)
			{
				if (i > (strlist[j].size() - 1))
					continue;
				int pos = strlist[j].size() - 1 - i;
				ans += strlist[j][pos] - '0';
			}
			ans += carry;
			res = ans % 10;
			carry = ans / 10;
			result = to_string(res) + result;
		}
		if (carry != 0)
			result = to_string(carry) + result;
		return result;
	}
};
//利用一个数组来转存，时间复杂度O(n*m)，空间复杂度O(n+m)
//构建了一个int数组来表示大整数，数组每个元素代表整数的一位，从低位开始
typedef vector<int> bigint;
bigint make_bigint(const string &str)
{
	bigint n;
	transform(str.rbegin(), str.rend(), back_inserter(n), [](char c) {return c - '0'; });
	return n;
}
string to_string(const bigint &n)
{
	string res;
	transform(find_if(n.rbegin(), prev(n.rend()),
		[](char c) {return c > '\0'; }), n.rend(), back_inserter(res),
		[](char c) {return c + '0'; });
	return res;
}
bigint operator*(const bigint &x, const bigint &y)
{
	bigint z(x.size() + y.size());
	for (size_t i = 0; i < x.size(); ++i)
		for (size_t j = 0; j < y.size(); ++j) {
			z[i + j] += x[i] * y[j];
			z[i + j + 1] += z[i + j] / 10;
			z[i + j] %= 10;
		}
	return z;
}
class Solution2
{
public:
	string multiply(string num1, string num2)
	{
		return to_string(make_bigint(num1) * make_bigint(num2));
	}
};
//仍然是一个数组存放大整数，但是采用Int_64表示9个字符
//大整数类
class BigInt
{
public:
	BigInt(const string &s)
	{
		vector<int64_t> result;
		result.reserve(s.size() / RADIX_LEN + 1);
		for (int i = s.size(); i > 0; i -= RADIX_LEN) { // [i-RADIX_LEN, i)
			int temp = 0;
			const int low = max(i - RADIX_LEN, 0);
			for (int j = low; j < i; j++) {
				temp = temp * 10 + s[j] - '0';
			}
			result.push_back(temp);
		}
		elems = result;
	}
	string toString()
	{
		stringstream result;
		bool started = false; //用于跳过前导0
		for (auto i = elems.rbegin(); i != elems.rend(); i++) {
			if (started) { //如果多余的0都已经跳过，则输出
				result << setw(RADIX_LEN) << setfill('0') << *i;
			}
			else {
				result << *i;
				started = true; //碰到第一个非零值，则说明多余的0已经跳过
			}
		}
		if (!started) return "0"; //当x全为0时
		else return result.str();
	}
	//大整数乘法
	static BigInt multiply(const BigInt &x, const BigInt &y)
	{
		vector<int64_t> z(x.elems.size() + y.elems.size(), 0);
		for (size_t i = 0; i < y.elems.size(); i++) {
			for (size_t j = 0; j < x.elems.size(); j++) { //用y[i]去乘x的各位
				//两个数的i，j位相乘，结果累加到i+j位
				z[i + j] += y.elems[i] * x.elems[j];
				if (z[i + j] >= BIGINT_RADIX) { //看是否需要进位
					z[i + j + 1] += z[i + j] / BIGINT_RADIX; //进位
					z[i + j] %= BIGINT_RADIX;
				}
			}
		}
		while (!z.empty()&&z.back() == 0) z.pop_back(); //没有进位，去掉最高位的0
		return BigInt(z);
	}
private:
	typedef long long int64_t;
	/**一个数组元素对应9个字符
	*因为1000000000 * 1000000000没有超过2^63-1
	*/
	const static int BIGINT_RADIX = 1000000000;
	const static int RADIX_LEN = 9;
	/**万进制整数*/
	vector<int64_t> elems;
	BigInt(const vector<int64_t> num) : elems(num) {}
};
class Solution3
{
public:
	string multiply(string num1, string num2)
	{
		BigInt x(num1);
		BigInt y(num2);
		return BigInt::multiply(x, y).toString();
	}
};
//算法的思想是直接利用一个string来存放结果，而不是用数组，比上述方法好
class Solution4
{
public:
	string multiply(string num1, string num2)
	{
		string result(num1.size() + num2.size(), '0');
		for (int i = num1.size() - 1; i >= 0; --i)
		{
			int carry = 0;
			for (int j = num2.size() - 1; j >= 0; --j)
			{
				int ans = (result[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0') + carry;
				result[i + j + 1] = ans % 10 + '0';
				carry = ans / 10;
			}
			result[i] += carry;
		}
		size_t startpos = result.find_first_not_of("0");
		if (string::npos != startpos)
			return result.substr(startpos);
		return "0";
	}
};

//int main(void)
//{
//	Solution4 test;
//	cout << test.multiply("1234", "234") << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
