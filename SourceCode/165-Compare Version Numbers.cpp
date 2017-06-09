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
//利用stringstream，但需要提前将点替换成‘ ’
class Solution {
public:
	int compareVersion(string version1, string version2) {
		for (int i = 0; i < version1.size(); ++i)
			if (version1[i] == '.') version1[i] = ' ';
		for (int i = 0; i < version2.size(); ++i)
			if (version2[i] == '.') version2[i] = ' ';
		istringstream ss1(version1), ss2(version2);
		int a = 0, b = 0;
		ss1 >> a; ss2 >> b;
		while (ss1 || ss2) {
			if (a > b) return 1;
			else if (a < b) return -1;
			a = b = 0;
			ss1 >> a; ss2 >> b;
		}
		return 0;
	}
};
//寻找'.'，累加计算版本号
class Solution2 {
public:
	int compareVersion(string version1, string version2) {
		int n1 = version1.size();
		int n2 = version2.size();
		int i = 0, j = 0;
		int num1 = 0, num2 = 0;
		while (i < n1 || j < n2) {
			while (i < n1 && version1[i] != '.') {
				num1 = num1 * 10 + (version1[i] - '0');
				i++;
			}
			while (j < n2 && version2[j] != '.') {
				num2 = num2 * 10 + (version2[j] - '0');
				j++;
			}
			if (num1 > num2) return 1;
			else if (num1 < num2) return -1;
			num1 = num2 = 0;
			i++; j++;
		}
		return 0;
	}
};
//字符串内部方法寻找'.'，并利用atoi，效率更高
class Solution3 {
public:
	int compareVersion(string version1, string version2) {
		int n1 = version1.size();
		int n2 = version2.size();
		int iStart1 = 0, iStart2 = 0;
		int index1, index2;
		int num1 = 0, num2 = 0;
		while (iStart1 < n1 || iStart2 < n2) {
			if (iStart1 >= n1) num1 = 0;
			else {
				index1 = version1.find_first_of('.', iStart1);
				if (index1 == version1.npos)
					index1 = n1;
				num1 = stoi(version1.substr(iStart1, index1 - iStart1));
			}
			if (iStart2 >= n2) num2 = 0;
			else {
				index2 = version2.find_first_of('.', iStart2);
				if (index2 == version2.npos)
					index2 = n2;
				num2 = stoi(version2.substr(iStart2, index2 - iStart2));
			}			
			if (num1 > num2) return 1;
			else if (num1 < num2) return -1;
			iStart1 = index1 + 1;
			iStart2 = index2 + 1;
		}
		return 0;
	}
};
//利用字符串流的改进版
class Solution4 {
public:
	int compareVersion(string version1, string version2) {
		istringstream ver1(version1 + "."), ver2(version2 + ".");
		int val1 = 0, val2 = 0;
		char dot = '.';
		while (ver1.good() || ver2.good()) {
			if (ver1.good()) ver1 >> val1 >> dot;
			if (ver2.good()) ver2 >> val2 >> dot;
			if (val1 > val2) return 1;
			else if (val1 < val2) return -1;
			val1 = val2 = 0;
		}
		return 0;
	}
};
//int main(void)
//{
//	Solution3 test;
//	cout << test.compareVersion("1", "1.1");
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//	
//	return 0;
//}