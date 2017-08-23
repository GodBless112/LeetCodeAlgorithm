﻿//	299. Bulls and Cows
//------------------------------------------------------------------------------//
//	You are playing the following Bulls and Cows game with your friend: You		//
//	write down a number and ask your friend to guess what the number is. Each	//
//	time your friend makes a guess, you provide a hint that indicates how many	//
//	digits in said guess match your secret number exactly in both digit and		//
//	position (called "bulls") and how many digits match the secret number but	//
//	locate in the wrong position (called "cows"). Your friend will use			//
//	successive guesses and hints to eventually derive the secret number.		//
//	For example :																//
//		Secret number : "1807"													//
//		Friend's guess: "7810"													//
//	Hint : 1 bull and 3 cows. (The bull is 8, the cows are 0, 1 and 7.)			//
//	Write a function to return a hint according to the secret number and		//
//	friend's guess, use A to indicate the bulls and B to indicate the cows. In	//
//	the above example, your function should return "1A3B".						//
//	Please note that both secret number and friend's guess may contain			//
//	duplicate digits, for example:												//
//		Secret number : "1123"													//
//		Friend's guess: "0111"													//
//	In this case, the 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a	//
//	cow, and your function should return "1A1B".								//
//	You may assume that the secret number and your friend's guess only contain	//
//	digits, and their lengths are always equal.									//
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
//两趟，先找bull再找cow
class Solution {
public:
	string getHint(string secret, string guess) {
		int n = secret.size();
		string hint;
		if (n != guess.size()) return hint;
		int bulls = 0, cows = 0;
		unordered_map<char, int> dict;
		for (int i = 0; i < n; ++i) {
			dict[secret[i]]++;
			if (secret[i] == guess[i]) {
				bulls++;
				dict[secret[i]]--;
			}
		}		
		for (int i = 0; i < n; ++i) {
			if (secret[i] == guess[i])
				continue;
			if (dict[guess[i]] > 0) {
					dict[guess[i]]--;
					cows++;
			}
		}
		return to_string(bulls) + 'A' + to_string(cows) + 'B';
	}
};
//改进，用数组存放'0'-'9'
class Solution2 {
public:
	// only contains digits 
	string getHint(string secret, string guess) {
		int aCnt = 0;
		int bCnt = 0;
		vector<int> sVec(10, 0); // 0 ~ 9 for secret
		vector<int> gVec(10, 0); // 0 ~ 9 for guess 
		if (secret.size() != guess.size() || secret.empty()) { return "0A0B"; }
		for (int i = 0; i < secret.size(); ++i) {
			char c1 = secret[i]; char c2 = guess[i];
			if (c1 == c2) {
				++aCnt;
			}
			else {
				++sVec[c1 - '0'];
				++gVec[c2 - '0'];
			}
		}
		// count b 
		for (int i = 0; i < sVec.size(); ++i) {
			bCnt += min(sVec[i], gVec[i]);
		}
		return to_string(aCnt) + 'A' + to_string(bCnt) + 'B';
	}
};
//one pass，双哈希表
class Solution3 {
public:
	string getHint(string secret, string guess) {
		unordered_map<char, int> s_map;
		unordered_map<char, int> g_map;
		int n = secret.size();
		int A = 0, B = 0;
		for (int i = 0; i < n; i++)
		{
			char s = secret[i], g = guess[i];
			if (s == g)
				A++;
			else
			{
				(s_map[g] > 0) ? s_map[g]--, B++ : g_map[g]++;
				(g_map[s] > 0) ? g_map[s]--, B++ : s_map[s]++;
			}
		}
		return to_string(A) + "A" + to_string(B) + "B";;
	}
};
//int main(void)
//{
//	Solution test;
//	cout << test.getHint("1123", "0111") << endl;
//	cout << test.getHint("1807", "7810") << endl;
//	cout << test.getHint("1122", "1222");
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