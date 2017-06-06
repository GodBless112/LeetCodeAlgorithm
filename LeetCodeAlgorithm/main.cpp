//	165. Compare Version Numbers
//------------------------------------------------------------------------------//
//	Compare two version numbers version1 and version2.							//
//	If version1 > version2 return 1, if version1 < version2 return -1, otherwise//
//	return 0.																	//
//	You may assume that the version strings are non - empty and contain only	//
//	digits and the.character.													//
//	The.character does not represent a decimal point and is used to separate	//
//	number sequences.															//
//	For instance, 2.5 is not "two and a half" or "half way to version three",	//
//	it is the fifth second - level revision of the second first - level			//
//	revision.																	//
//	Here is an example of version numbers ordering :							//
//	0.1 < 1.1 < 1.2 < 13.37														//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<sstream>
// constants
// function prototype
using namespace std;
class Solution {
public:
	int compareVersion(string version1, string version2) {
		istringstream ss1(version1), ss2(version2);
		int a = 0, b = 0;
		while (ss1 >> a && ss2 >> b) {
			if (a > b) return 1;
			else if (a < b) return -1;
			ss1.get();
			ss2.get();
			a = b = 0;
		}
		if (a > b) return 1;
		if (a < b) return -1;
		if (ss1.eof() && ss2.eof()) return 0;
	}
};
int main(void)
{
	Solution test;
	cout << test.compareVersion("1", "1.1");
	cout << endl;
	// code to keep window open for MSVC++
	cin.clear();
	while (cin.get() != '\n')
		continue;
	cin.get();
	
	return 0;
}