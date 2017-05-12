//	89. Gray Code
//------------------------------------------------------------------------------//
//	The gray code is a binary numeral system where two successive values differ //
//	in only one bit.															//
//	Given a non - negative integer n representing the total number of bits in	//
//	the code, print the sequence of gray code.A gray code sequence must begin	//
//	with 0.																		//
//	For example, given n = 2, return[0, 1, 3, 2].Its gray code sequence is :	//
//	00 - 0																		//
//	01 - 1																		//
//	11 - 3																		//
//	10 - 2																		//
//	Note :																		//
//		For a given n, a gray code sequence is not uniquely defined.			//
//		For example, [0, 2, 3, 1] is also a valid gray code sequence according	//
//	to the above definition.													//
//		For now, the judge is able to judge based on one instance of gray code	//
//	sequence.Sorry about that.													//
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
//自然编码转换为格雷码，最高位不变，其余为Gi=Bi XOR Bi-1
class Solution 
{
public:
	vector<int> grayCode(int n) 
	{
		size_t size = 1 << n;
		vector<int> result;
		for (size_t i = 0; i < size; i++)
			result.push_back(BinarytoGray(i));
		return result;
	}
private:
	static unsigned int BinarytoGray(unsigned int n)
	{
		return n ^ (n >> 1);
	}
};
//递归算法:
//这种方法基于格雷码是反射码的事实，利用递归的如下规则来构造：
//	1.位格雷码有两个码字
//	2.(n + 1)位格雷码中的前2^n个码字等于n位格雷码的码字，按顺序书写，加前缀0
//	3.(n + 1)位格雷码中的后2^n个码字等于n位格雷码的码字，按逆序书写，加前缀1[3]
//	4.n + 1位格雷码的集合 = n位格雷码集合(顺序)加前缀0 + n位格雷码集合(逆序)加前缀1
class Solution2 
{
public:
	vector<int> grayCode(int n) 
	{
		vector<int> result;
		result.reserve(1 << n);
		result.push_back(0);
		for (int i = 0; i < n; i++) {
			const int highest_bit = 1 << i;
			for (int j = result.size() - 1; j >= 0; j--)
				result.push_back(highest_bit | result[j]);
		}
		return result;
	}
};
//迭代方法实现构造
class Solution3 
{
public:
	vector<int> grayCode(int n)
	{
		vector<int> result(1, 0);
		for (int i = 0; i < n; i++) {
			int curCount = result.size();
			// push back all element in result in reverse order
			while (curCount) {
				curCount--;
				int curNum = result[curCount];
				curNum += (1 << i);
				result.push_back(curNum);
			}
		}
		return result;
	}
};
//int main(void)
//{
//	Solution3 test;
//	auto x = test.grayCode(2);
//	for_each(x.begin(), x.end(), [](int i) {
//		cout << i << " ";
//	});
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