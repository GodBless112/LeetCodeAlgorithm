//	374. Guess Number Higher or Lower
//------------------------------------------------------------------------------//
//	We are playing the Guess Game. The game is as follows:						//
//	I pick a number from 1 to n.You have to guess which number I picked.		//
//	Every time you guess wrong, I'll tell you whether the number is higher or	//
//	lower.																		//
//	You call a pre - defined API guess(int num) which returns 3 possible		//
//	results(-1, 1, or 0) :														//
//		-1 : My number is lower													//
//		1 : My number is higher													//
//		0 : Congrats!You got it!												//
//	Example :																	//
//		n = 10, I pick 6.														//
//		Return 6.																//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_set>
#include<unordered_map>
// constants
// function prototype
using namespace std;
// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
const int truenum = 6;
int guess(int num) {
	if (num < truenum)
		return 1;
	else if (num > truenum)
		return -1;
	else return 0;
}
//二分搜索
class Solution {
public:
	int guessNumber(int n) {
		int left = 1, right = n;
		int mid;
		while (left <= right) {
			mid = left + (right - left) / 2;
			int res = guess(mid);
			if (res == 0)
				return mid;
			else if (res == 1)
				left = mid + 1;
			else right = mid - 1;
		}
		return -1;
	}
};
//三分搜索
class Solution2 {
public:
	int guessNumber(int n) {
		int left = 1, right = n;
		while (left <= right) {
			int mid1 = left + (right - left) / 3;
			int mid2 = right - (right - left) / 3;
			int res1 = guess(mid1);
			int res2 = guess(mid2);
			if (res1 == 0) return mid1;
			if (res2 == 0) return mid2;
			else if (res1 < 0) right = mid1 - 1;
			else if (res2 > 0) left = mid2 + 1;
			else {
				left = mid1 + 1;
				right = mid2 - 1;
			}
		}
		return -1;
	}
};
//二分搜索，结合guess结果
class Solution3 {
public:
	int guessNumber(int n) {
		int cur = (1 + n) >> 1;
		int t;
		int step = cur;
		do {
			t = guess(cur);
			step = step >> 1 ? step >> 1 : 1;
			cur += t*step;
		} while (t != 0);

		return cur;
	}
};
//int main(void)
//{
//	Solution3 test;
//	for (int i = 8; i < 16; ++i)
//		cout << i << " " << boolalpha << test.guessNumber(i) << endl;
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