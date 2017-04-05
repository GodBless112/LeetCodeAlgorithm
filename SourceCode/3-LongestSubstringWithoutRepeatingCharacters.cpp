#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
//算法思路：
//贪心算法，要使得最后的子串无重复字符，其子串也无重复字符。那么，可以从字符串起始位置开始往后遍历
//如果遇到重复的字符，那么就记录当前子字符串的长度并比较是否为较长的子串，然后将上一个重复字符出现
//的位置+1做为新的起点。
using namespace std;
class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		const int ASCII_MAX = 256;
		int last[ASCII_MAX];
		int start = 0;
		fill(last, last + ASCII_MAX, -1);
		int max_len = 0;
		for (int i = 0; i<s.size(); i++) {
			if (last[s[i]] >= start) {
				max_len = max(i - start, max_len);
				start = last[s[i]] + 1;
			}
			last[s[i]] = i;
		}
		return max((int)s.size() - start, max_len);
	}
};
class Solution2 {
public:
	int lengthOfLongestSubstring(string s) {
		vector<int> dict(256, -1);
		int maxLen = 0, start = -1;
		for (int i = 0; i != s.length(); i++) {
			if (dict[s[i]] > start)
				start = dict[s[i]];
			dict[s[i]] = i;
			maxLen = max(maxLen, i - start);
		}
		return maxLen;
	}
};
class Solution3 {
public:
	int lengthOfLongestSubstring(string s) {
		vector<int> charIndex(256, -1);
		int longest = 0, m = 0;

		for (int i = 0; i < s.length(); i++) {
			m = max(charIndex[s[i]] + 1, m);    // automatically takes care of -1 case
			charIndex[s[i]] = i;
			longest = max(longest, i - m + 1);
		}

		return longest;
	}
};
class Solution4 {
public:
	int lengthOfLongestSubstring(string s) {
		vector<int> last(256, -1);
		int longest = 0, start = 0, len = s.size();
		for (int i = 0; i != len; i++) {
			if (last[s[i]] >= start) {
				longest = max(longest, i - start);
				start = last[s[i]] + 1;
			}
			last[s[i]] = i;
		}

		return max(longest, len - start);
	}
};