//	204. Count Primes
//------------------------------------------------------------------------------//
//	Description:																//
//	Count the number of prime numbers less than a non - negative number, n.		//
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
//直接计算小于n的质数是哪些，输出个数，耗时较长
class Solution {
public:
	int countPrimes(int n) {
		if (n < 3) return 0;
		vector<int> primes;
		primes.push_back(2);
		for (int i = 3; i < n; i+=2) {
			bool flag = true;
			for (int j = 0; j < primes.size() && primes[j] <= sqrt(i); ++j)
				if (i%primes[j] == 0) {
					flag = false;
					break;
				}
			if (flag) primes.push_back(i);
		}
		return primes.size();
	}
};
//Sieve of Eratosthenes算法
//（1）先把1删除（现今数学界1既不是质数也不是合数）
//（2）读取队列中当前最小的数2，然后把2的倍数删去
//（3）读取队列中当前最小的数3，然后把3的倍数删去
//（4）读取队列中当前最小的数5，然后把5的倍数删去
//（5）如上所述直到需求的范围内所有的数均删除或读取
class Solution2 {
public:
	int countPrimes(int n) {
		if (n <= 2) return 0;
		vector<bool> passed(n, false);
		int sum = 1;
		int upper = sqrt(n);
		for (int i = 3; i < n; i += 2) {
			if (!passed[i]) {
				sum++;
				//avoid overflow
				if (i > upper) continue;
				for (int j = i*i; j < n; j += i) {
					passed[j] = true;
				}
			}
		}
		return sum;
	}
};
//Sieve of Eratosthenes算法的另一种实现，对于这一题来说效率不如2
class Solution3 {
public:
	int countPrimes(int n) {
		if (n <= 2) return 0;
		vector<bool> prime(n, true);
		prime[0] = false; prime[1] = false;
		int upper = sqrt(n);
		for (int i = 0; i < upper; ++i) {
			if (prime[i])
				for (int j = i*i; j < n; j += i)
					prime[j] = false;
		}
		return count(prime.begin(), prime.end(), true);
	}
};
class Solution4 {
public:
	int countPrimes(int n) {
		if (--n < 2) return 0;
		int m = (n + 1) / 2, count = m, k, u = (sqrt(n) - 1) / 2;
		vector<bool> notPrime(n, false);

		for (int i = 1; i <= u; i++)
			if (!notPrime[i])
				for (k = (i + 1) * 2 * i; k < m; k += i * 2 + 1)
					if (!notPrime[k])
					{
						notPrime[k] = true;
						count--;
					}
		return count;
	}
};
//利用一个char数组记录
class Solution5 {
public:
	int countPrimes(int n) {
		if (--n < 2) return 0;
		vector<char> notPrime((n + 1) / 16 + 1, false);
		int count = (n + 1) / 2, k, u = (sqrt(n) - 1) / 2;

		for (int i = 1; i <= u; i++)
			if (!(notPrime[i >> 3] & (1 << (i & 7))))
				for (k = 2 * i*(i + 1); k < (n + 1) / 2; k += 2 * i + 1)
					if (!(notPrime[k >> 3] & (1 << (k & 7))))
					{
						notPrime[k >> 3] |= (1 << (k & 7));
						count--;
					}
		return count;
	}
};
//int main(void)
//{
//	Solution5 test;
//	cout << test.countPrimes(100);
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//	
//	return 0;
//}