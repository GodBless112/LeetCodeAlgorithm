//	278. First Bad Version
//------------------------------------------------------------------------------//
//	You are a product manager and currently leading a team to develop a new		//
//	product. Unfortunately, the latest version of your product fails the		//
//	quality check. Since each version is developed based on the previous		//
//	version, all the versions after a bad version are also bad.					//
//	Suppose you have n versions[1, 2, ..., n] and you want to find out the		//
//	first bad one, which causes all the following ones to be bad.				//
//	You are given an API bool isBadVersion(version) which will return whether	//
//	version is bad.Implement a function to find the first bad version.You		//
//	should minimize the number of calls to the API.								//
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
// Forward declaration of isBadVersion API.
vector<bool> VersionStatus{ false ,true, true };
bool isBadVersion(int version) {
	return VersionStatus[version - 1];
}
//二分搜索
class Solution {
public:
	int firstBadVersion(int n) {
		int start = 1, end = n;
		int mid;
		while (start < end) {
			mid = start + (end - start) / 2;
			if (isBadVersion(mid))
				end = mid;
			else
				start = mid + 1;
		}
		return start;
	}
};
//int main(void)
//{
//	Solution test;
//	cout << test.firstBadVersion(3);
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