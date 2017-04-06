//二分法的查找，给出一个通用的寻找第K大元素的函数，调用两次得到结果

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cmath>
#include<ctime>
#include<iomanip>
#include<exception>
#include<cstdlib>
#include<fstream>
#include<cstdio>
#include<set>
#include<map>
#include<vector>
#include<stack>
#include<list>
#include<queue>
#include<deque>
#include<algorithm>
#include<functional>
#include<numeric>
#include<iterator>
#include<unordered_set>
#include<unordered_map>
#include<Windows.h>
// constants
using namespace std;
// function prototype
//余数表
long long n1[100001], n2[100001];
long long CountRemainder(string dividend, int n)
{
	n1[0] = 1;
	for (int i = 0; i < dividend.size(); i++)
	{
		memset(n2, 0, sizeof(n2));
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				if (isdigit(dividend[i]) && ((dividend[i] - '0') != k))
					continue;
				n2[(j * 10 + k) % n] += n1[j];
			}
		}
		memcpy(n1, n2, sizeof(n2));
	}
	return n1[0];
}

class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
	{
		const int m = nums1.size();
		const int n = nums2.size();
		int all = m + n;
		if (all & 0x01)
			return findKthOfTwoSortedArray(nums1.begin(), m, nums2.begin(), n, (all + 1) / 2);
		else
			return (findKthOfTwoSortedArray(nums1.begin(), m, nums2.begin(), n, all / 2)
				+ findKthOfTwoSortedArray(nums1.begin(), m, nums2.begin(), n, all / 2 + 1)) / 2.0;
	}
	typedef vector<int>::const_iterator VIiterator;
	int findKthOfTwoSortedArray(vector<int>::const_iterator A, int m, vector<int>::const_iterator B, int n, int k)
	{
		if (m > n)
			return findKthOfTwoSortedArray(B, n, A, m, k);
		if (m == 0)
			return *(B + k - 1);
		if (k == 1)
			return min(*A, *B);
		int ia = min(k / 2, m);
		int ib = k - ia;
		if (*(A + ia - 1) < *(B + ib - 1))
			return findKthOfTwoSortedArray(A + ia, m - ia, B, n, k - ia);
		else if (*(A + ia - 1) > *(B + ib - 1))
			return findKthOfTwoSortedArray(A, m, B + ib, n - ib, k - ib);
		else
			return A[ia - 1];
	}
};
vector<int> getPathandDepth(int K, int data)
{
	vector<int> Path;
	int start = 1;
	int end = pow(2, K) - 1;
	int key = (end + start) / 2;
	while (key != data)
	{
		if (data < key)
			end = key - 1;
		else
			start = key + 1;
		Path.push_back(key);
		key = (start + end) / 2;
	}
	Path.push_back(data);
	return Path;
}
int GetMinSubTree(int K, int data1, int data2, int data3)
{
	vector<int> Path[3];
	Path[0] = getPathandDepth(K, data1);
	Path[1] = getPathandDepth(K, data2);
	Path[2] = getPathandDepth(K, data3);
	int minSize = min(min(Path[0].size(), Path[1].size()), Path[2].size());
	int result = Path[0][0];
	for (int i = 0; i < minSize; i++)
	{
		if (Path[0][i] == Path[1][i] && Path[1][i] == Path[2][i])
			result = Path[0][i];
	}
	return result;
}
//int main(int argc, char* argv[])
//{
//	cout << CountRemainder("XXXXXXXXXXXXXXXXXX", 5) << endl;
//	cout << "Done.\n";
//	vector<int> a = { 2};
//	vector<int> b = {};
//	Solution test;
//	cout << GetMinSubTree(4, 15, 11, 10);
//	cout << test.findMedianSortedArrays(a, b);
//	//auto b= test.twoSum(a, 6);
//	// code to keep window open for MSVC++
//	std::cin.clear();
//	while (std::cin.get() != '\n')
//		continue;
//	std::cin.get();
//	return 0;
//}


