//	69. Sqrt(x)
//------------------------------------------------------------------------------//
//	Implement int sqrt(int x).													//
//	Compute and return the square root of x.									//
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
//二分搜索
class Solution 
{
public:
	int mySqrt(int x) 
	{
		if (x < 0)
			return INT_MIN;
		if (x < 2)
			return x;
		int start = 0;
		int end = x;
		int lastmid = 0;
		while (start <= end)
		{
			int mid = start + (end - start) / 2;	//不要用（start+end）/2，会溢出
			if (x / mid == mid)		//不要用mid*mid，会溢出
				return mid;
			else if (x / mid > mid)
			{
				start = mid + 1;
				lastmid = mid;
			}
				
			else
				end = mid - 1;
		}
		return lastmid;
	}
};
class Solution2
{
public:
	int mySqrt(int x)
	{
		if (x == 0)
			return 0;
		int left = 1, right = x;
		while (true) {
			int mid = left + (right - left) / 2;
			if (mid > x / mid) {
				right = mid - 1;
			}
			else {
				if (mid + 1 > x / (mid + 1))
					return mid;
				left = mid + 1;
			}
		}
	}
};
//二分搜索，采用位运算，x^.5=2^k1+2^k2+...2^kn，先找到最大的k，然后依次寻找剩余的k
class Solution3
{
public:
	int mySqrt(int x) {
		if (x == 0)
			return 0;
		int h = 0;
		while (((long long)(1 << h)*(long long)(1 << h)) <= x) // firstly, find the most significant bit
			h++;
		h--;
		int b = h - 1;
		int res = (1 << h);
		while (b >= 0) {  // find the remaining bits
			if ((long long)(res | (1 << b))*(long long)(res | (1 << b)) <= x)
				res |= (1 << b);
			b--;
		}
		return res;
	}
};
//int main(void)
//{
//	Solution3 test;
//	cout << test.mySqrt(2147395599);
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
