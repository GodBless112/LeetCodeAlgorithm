//	125. Valid Palindrome
//------------------------------------------------------------------------------//
//	Given a string, determine if it is a palindrome, considering only			//
//	alphanumeric characters and ignoring cases.									//
//	For example,																//
//	"A man, a plan, a canal: Panama" is a palindrome.							//
//	"race a car" is not a palindrome.											//
//	Note:																		//
//	Have you consider that the string might be empty ? This is a good question	//
//	to ask during an interview.													//
//	For the purpose of this problem, we define empty string as valid palindrome.//
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

class Solution {
public:
	bool isPalindrome(string s) {
		int n = s.size();
		if (n == 0) return true;
		int start = 0, end = n - 1;
		while (start < end) {
			while (start < end && !isalnum(s[start]))
				start++;
			while (start < end && !isalnum(s[end]))
				end--;
			if (start > end) break;
			if (tolower(s[start++]) != tolower(s[end--]))
				return false;
		}
		return true;
	}
};
class Solution2 {
public:
	bool isPalindrome(string s) {
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		auto left = s.begin(), right = prev(s.end());
		while (left < right) {
			if (!::isalnum(*left)) ++left;
			else if (!::isalnum(*right)) --right;
			else if (*left != *right) return false;
			else { left++, right--; }
		}
		return true;
	}
};
//int main(void)
//{
//	Solution test;
//	string s = "A man, a plan, a canal: Panama";
//	cout << boolalpha << test.isPalindrome(s) << endl;
//	cout << boolalpha << test.isPalindrome("1P");
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