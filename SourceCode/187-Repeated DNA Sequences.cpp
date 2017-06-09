//	187. Repeated DNA Sequences
//------------------------------------------------------------------------------//
//	All DNA is composed of a series of nucleotides abbreviated as A, C, G, and	//
//	T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to	//
//	identify repeated sequences within the DNA.									//
//	Write a function to find all the 10 - letter - long sequences(substrings)	//
//	that occur more than once in a DNA molecule.								//
//	For example,																//
//	Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",								//
//	Return:																		//
//	["AAAAACCCCC", "CCCCCAAAAA"].												//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<bitset>
// constants
// function prototype
using namespace std;
//哈希表的方法
class Solution {
public:
	vector<string> findRepeatedDnaSequences(string s) {
		int n = s.size();
		unordered_map<string, int> dict;
		vector<string> result;
		for (int i = 0; i <= n - 10; ++i) {
			string cur = s.substr(i, 10);
			if (dict[cur] == 1)
				result.push_back(cur);
			dict[cur]++;
		}
		return result;
	}
};
//A is 0x41, C is 0x43, G is 0x47, T is 0x54. Still don't see it? Let me write it in octal.
//A is 0101, C is 0103, G is 0107, T is 0124. The last digit in octal are different for all 
//four letters.That's all we need!
//We can simply use s[i] & 7 to get the last digit which are just the last 3 bits, it's much 
//easier than lookup table or switch or a bunch of if and else, right?
//We don't really need to generate the substring from the int. While counting the number of 
//occurrences, we can push the substring into result as soon as the count becomes 2, so there 
//won't be any duplicates in the result.
class Solution2 {
public:
	vector<string> findRepeatedDnaSequences(string s) {
		unordered_map<int, int> m;
		vector<string> r;
		int t = 0, i = 0, ss = s.size();
		while (i < 9)
			t = t << 3 | s[i++] & 7;
		while (i < ss)
			if (m[t = t << 3 & 0x3FFFFFFF | s[i++] & 7]++ == 1)
				r.push_back(s.substr(i - 10, 10));
		return r;
	}
};
//位运算，击败了100%，
//使flag只有三种状态，0没有，1有一个，3有多个
class Solution3 {
public:
	vector<string> findRepeatedDnaSequences(string s) {
		char flag[262144] = { 0 };
		vector<string> result;
		int len, DNA = 0, i;
		if ((len = s.length())< 11) return result;
		for (i = 0; i < 9; i++)
			DNA = DNA << 2 | (s[i] - 'A' + 1) % 5;
		for (i = 9; i<len; i++)
		{
			DNA = (DNA << 2 & 0xFFFFF) | (s[i] - 'A' + 1) % 5;
			if (!(flag[DNA >> 2] & (1 << ((DNA & 3) << 1))))
				flag[DNA >> 2] |= (1 << ((DNA & 3) << 1));
			else if (!(flag[DNA >> 2] & (2 << ((DNA & 3) << 1))))
			{
				result.push_back(s.substr(i - 9, 10));
				flag[DNA >> 2] |= (2 << ((DNA & 3) << 1));
			}
		}
		return result;
	}
};
//位运算
class Solution4 {
public:
	vector<string> findRepeatedDnaSequences(string s) {
		if (s.size() <= 10)
			return vector<string>();

		vector<string> R;
		bitset<1 << 20> S1;
		bitset<1 << 20> S2;

		int val = 0;
		for (int i = 0; i < 10; i++)   // Calc. the has value for the first string.
			val = (val << 2) | char2val(s[i]);
		S1.set(val);
		cout << val << " | ";

		int mask = (1 << 20) - 1;
		for (int i = 10; i < s.size(); i++) {
			// Calc the hash value for the string ending at position i.
			val = ((val << 2) & mask) | char2val(s[i]);
			if (S2[val])
				continue;
			if (S1[val]) {
				R.push_back(s.substr(i - 10 + 1, 10));
				S2.set(val);
			}
			else
				S1.set(val);
		}
		return R;
	}

	int char2val(char c) {
		switch (c) {
		case 'A': return 0;
		case 'C': return 1;
		case 'G': return 2;
		case 'T': return 3;
		}
	}
};
//int main(void)
//{
//	Solution3 test;
//	auto res = test.findRepeatedDnaSequences("AAAAAAAAAAAA");
//	for (auto s : res)
//		cout << s << " ";
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//	
//	return 0;
//}