//	166. Fraction to Recurring Decimal
//------------------------------------------------------------------------------//
//	Given two integers representing the numerator and denominator of a fraction,//
//	return the fraction in string format.										//
//	If the fractional part is repeating, enclose the repeating part in			//
//	parentheses.																//
//	For example																	//
//		Given numerator = 1, denominator = 2, return "0.5".						//
//		Given numerator = 2, denominator = 1, return "2".						//
//		Given numerator = 2, denominator = 3, return "0.(6)".					//
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
//利用除法的性质，记录余数出现的位置，如果出现了重复的余数，则说明有循环
class Solution {
public:
	string fractionToDecimal(int numerator, int denominator) {
		if (numerator == 0) return"0";
		string result;
		if (numerator < 0 ^ denominator < 0) result += '-';
		numerator = abs(numerator);
		denominator = abs(denominator);
		result += to_string(numerator / denominator);
		if (numerator % denominator == 0) return result;
		result += '.';
		unordered_map<int, int> dict;
		for (int r = numerator%denominator; r; r %= denominator) {
			if (dict.count(r) > 0) {
				result.insert(dict[r], 1, '(');
				result += ')';
				break;
			}
			// remember the current position for it
			dict[r] = result.size();

			r *= 10;

			// append the quotient digit
			result += to_string(r / denominator);
		}
		return result;
	}
};
//
class Solution2 {
public:
	string fractionToDecimal(int numerator, int denominator) {
		if (!numerator) return "0";
		string res;
		if (numerator < 0 ^ denominator < 0) res += '-';
		long numer = numerator < 0 ? (long)numerator * (-1) : (long)numerator;
		long denom = denominator < 0 ? (long)denominator * (-1) : (long)denominator;
		long integral = numer / denom;
		res += to_string(integral);
		long rmd = numer % denom;
		if (!rmd) return res;
		res += '.';
		rmd *= 10;
		unordered_map<long, long> mp;
		while (rmd) {
			long quotient = rmd / denom;
			if (mp.find(rmd) != mp.end()) {
				res.insert(mp[rmd], 1, '(');
				res += ')';
				break;
			}
			mp[rmd] = res.size();
			res += to_string(quotient);
			rmd = (rmd % denom) * 10;
		}
		return res;
	}
};
//int main(void)
//{
//	Solution test;
//	cout << test.fractionToDecimal(11, 100);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}