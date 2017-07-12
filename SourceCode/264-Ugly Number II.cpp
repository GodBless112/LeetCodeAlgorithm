//	264. Ugly Number II
//------------------------------------------------------------------------------//
//	Write a program to find the n-th ugly number.								//
//	Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. //
//	For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 //
//	ugly numbers.																//
//	Note that 1 is typically treated as an ugly number, and n does not exceed	//
//	1690.																		//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<queue>
// constants
// function prototype
using namespace std;
//动态规划
class Solution {
public:
	int nthUglyNumber(int n) {
		if (n <= 0) return 0;
		if (n == 1) return 1;
		vector<int> dp(n);
		dp[0] = 1;
		int t2 = 0, t3 = 0, t5 = 0;
		for (int i = 1; i < n; ++i) {
			dp[i] = min(dp[t2] * 2, min(dp[t3] * 3, dp[t5] * 5));
			if (dp[i] == dp[t2] * 2) t2++;
			if (dp[i] == dp[t3] * 3) t3++;
			if (dp[i] == dp[t5] * 5) t5++;
		}
		return dp[n - 1];
	}
};
//动态规划，利用队列
class Solution2 {
public:
	int nthUglyNumber(int n) {
		queue<int> q1, q2, q3;
		q1.push(1), q2.push(1), q3.push(1);

		int m = 0;
		for (int i = 0; i < n; ++i) {
			m = min(min(q1.front(), q2.front()), q3.front());
			if (m == q1.front()) q1.pop();
			if (m == q2.front()) q2.pop();
			if (m == q3.front()) q3.pop();
			q1.push(2 * m);
			q2.push(3 * m);
			q3.push(5 * m);
		}

		return m;
	}
};
class Solution3 {
public:
	int nthUglyNumber(int n) {
		static vector<int> ugly{ 1 };
		static int last(1);
		static int c2(2), c3(3), c5(5);
		static int i2(0), i3(0), i5(0);
		while (ugly.size() < n) {
			while (c2 <= last) c2 = 2 * ugly[++i2];
			while (c3 <= last) c3 = 3 * ugly[++i3];
			while (c5 <= last) c5 = 5 * ugly[++i5];
			ugly.push_back(last = min(c2, min(c3, c5)));
		}
		return ugly[n - 1];
	}
};
class Solution4 {
public:
	int nthUglyNumber(int n) {
		static vector<int> ugly;
		long long a, b, c, m = INT_MAX;
		if (ugly.empty()) {
			for (a = 1; a <= m; a *= 2)
				for (b = a; b <= m; b *= 3)
					for (c = b; c <= m; c *= 5)
						ugly.push_back(c);
			sort(begin(ugly), end(ugly));
		}
		return ugly[n - 1];
	}
};
//int main(void)
//{
//	Solution test;
//	cout << 10 << " " << test.nthUglyNumber(10) << endl;
//	for (int i = 0; i < 20; i++)
//		cout << i << " " << test.nthUglyNumber(i) << endl;
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