//	60. Permutation Sequence
//------------------------------------------------------------------------------//
//	The set [1,2,3,…,n] contains a total of n! unique permutations.			//
//	By listing and labeling all of the permutations in order,					//
//	We get the following sequence(ie, for n = 3) :								//
//		1."123"																	//
//		2."132"																	//
//		3."213"																	//
//		4."231"																	//
//		5."312"																	//
//		6."321"																	//
//	Given n and k, return the kth permutation sequence.							//
//	Note: Given n will be between 1 and 9 inclusive								//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<stack>
// constants
// function prototype
using namespace std;
//利用next_permutation，方案不好，时间复杂度太高
class Solution 
{
public:
	string getPermutation(int n, int k) 
	{
		string result(n, '0');
		for (int i = 1; i <= n; i++) result[i - 1] += i;
		while (--k > 0)
			next_permutation(result);
		return result;
	}
private:
	bool next_permutation(string & str)
	{
		if (str.size() < 2)
			return false;
		auto i = str.rbegin();
		for (; i != (str.rend() - 1); i++)
			if (*i > *(i + 1))
				break;
		if (i == str.rend())
		{
			reverse(str.rbegin(), str.rend());
			return false;
		}
		for (auto j = str.rbegin(); j != i + 1; j++)
		{
			if (*j > *(i + 1))
			{
				swap(*j, *(i + 1));
				reverse(str.rbegin(), i + 1);
				return true;
			}
		}
	}
};
//利用康托斯编码，对于一个n!的排列，可以先分成n组，每一组以k（k=1....n)为第一个元素，
//紧接排除第一个元素的排列(n-1)!，同样的，剩余的排列也可以跟前面一样的考虑。对于第k个
//排列，可以计算k/(n-1)!看它处于n!的第几组，再看k%n!在(n-1)!排列的第几组，依次进行可以
//得到第k组的排列. 时间复杂度O(n)
class Solution2
{
public:
	string getPermutation(int n, int k)
	{
		string s(n, '0');
		string result;
		for (int i = 0; i < n; ++i)
			s[i] += i + 1;
		return kth_permutation(s, k);
	}
private:
	int factorial(int n) 
	{
		int result = 1;
		for (int i = 1; i <= n; ++i)
			result *= i;
		return result;
	}
	template<typename Sequence>
	Sequence kth_permutation(const Sequence &seq, int k)
	{
		const int n = seq.size();
		Sequence S(seq);
		Sequence result;
		int base = factorial(n - 1);
		--k;	//start from 0
		for (int i = n - 1; i > 0; k %= base, base /= i, i--)
		{
			auto a = next(S.begin(), k / base);
			result.push_back(*a);
			S.erase(a);
		}
		result.push_back(S[0]);
		return result;
	}
};
class Solution3
{
public:
	string getPermutation(int n, int k)
	{
		int i, j, fac = 1;
		string result(n, '0');
		for (i = 1; i <= n; ++i)
		{
			fac *= i;	//阶乘值
			result[i - 1] += i;
		}
		for (i = 0, k--; i < n; i++)
		{
			fac /= n - i;
			j = i + k / fac;
			char c = result[j];
			//将j之前的元素右移
			for (; j > i; --j)
				result[j] = result[j - 1];
			k %= fac;
			result[i] = c;
		}
		return result;
	}
};
//int main(void)
//{
//	Solution3 test;
//	cout << test.getPermutation(3, 6);
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
