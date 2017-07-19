//	307. Range Sum Query - Mutable
//------------------------------------------------------------------------------//
//	Given an integer array nums, find the sum of the elements between indices i //
//	and j (i ≤ j), inclusive.													//
//	The update(i, val) function modifies nums by updating the element at index	//
//	i to val.																	//
//	Example:																	//
//		Given nums = [1, 3, 5]													//
//		sumRange(0, 2) -> 9														//
//		update(1, 2)															//
//		sumRange(0, 2) -> 8														//
//	Note :																		//
//		1.The array is only modifiable by the update function.					//
//		2.You may assume the number of calls to update and sumRange function is //
//	distributed evenly.															//
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
//延续固定数组时的处理，令range为前i个数的和，并用一个数组记录改变的值，时间复杂度较高
class NumArray {
public:
	NumArray(vector<int> nums) :StorageNums(nums), range(nums.size() + 1), modify(nums.size()){
		for (int i = 1; i <= nums.size(); ++i)
			range[i] = range[i - 1] + nums[i - 1];
	}

	void update(int i, int val) {
		int prev = StorageNums[i];
		int change = val - prev;
		modify[i] = change;
	}

	int sumRange(int i, int j) {
		int sum = range[j + 1] - range[i];
		for (int k = i; k <= j; ++k)
			sum += modify[k];
		return sum;
	}
private:
	vector<int> StorageNums;
	vector<int> range;
	vector<int> modify;
};

//线段树：Segment Tree
class NumArray2 {
	struct SegmentTreeNode {
		int start, end, sum;
		SegmentTreeNode* left;
		SegmentTreeNode* right;
		SegmentTreeNode(int a, int b) :start(a), end(b), sum(0), left(nullptr), right(nullptr) {}
	};
	SegmentTreeNode* root;
public:
	NumArray2(vector<int> nums) {
		int n = nums.size();
		root = buildTree(nums, 0, n - 1);
	}

	void update(int i, int val) {
		modifyTree(i, val, root);
	}

	int sumRange(int i, int j) {
		return queryTree(i, j, root);
	}
	SegmentTreeNode* buildTree(vector<int> &nums, int start, int end) {
		if (start > end) return nullptr;
		SegmentTreeNode* root = new SegmentTreeNode(start, end);
		if (start == end) {
			root->sum = nums[start];
			return root;
		}
		int mid = start + (end - start) / 2;
		root->left = buildTree(nums, start, mid);
		root->right = buildTree(nums, mid + 1, end);
		root->sum = root->left->sum + root->right->sum;
		return root;
	}
	int modifyTree(int i, int val, SegmentTreeNode* root) {
		if (root == nullptr) return 0;
		int diff;
		if (root->start == i && root->end == i) {
			diff = val - root->sum;
			root->sum = val;
			return diff;
		}
		int mid = (root->start + root->end) / 2;
		if (i > mid) {
			diff = modifyTree(i, val, root->right);
		}
		else {
			diff = modifyTree(i, val, root->left);
		}
		root->sum = root->sum + diff;
		return diff;
	}
	int queryTree(int i, int j, SegmentTreeNode* root) {
		if (root == nullptr) return 0;
		if (root->start == i && root->end == j) return root->sum;
		int mid = (root->start + root->end) / 2;
		if (i > mid) return queryTree(i, j, root->right);
		if (j <= mid) return queryTree(i, j, root->left);
		return queryTree(i, mid, root->left) + queryTree(mid + 1, j, root->right);
	}
};
//开方分解：Sqrt decomposition，令n为数组长度，n^0.5为分割的块大小，将数组分割成这么多块得到数组b
class NumArray3 {
public:
	NumArray3(vector<int> nums): StorageNums(nums) {
		double l = sqrt(nums.size());
		len = ceil(nums.size() / l);
		b.resize(len);
		for (int i = 0; i < nums.size(); i++)
			b[i / len] += StorageNums[i];
	}

	void update(int i, int val) {
		int b_l = i / len;
		b[b_l] = b[b_l] - StorageNums[i] + val;
		StorageNums[i] = val;
	}

	int sumRange(int i, int j) {
		int sum = 0;
		int startBlock = i / len;
		int endBlock = j / len;
		if (startBlock == endBlock) {
			for (int k = i; k <= j; k++)
				sum += StorageNums[k];
		}
		else {
			for (int k = i; k <= (startBlock + 1) * len - 1; k++)
				sum += StorageNums[k];
			for (int k = startBlock + 1; k <= endBlock - 1; k++)
				sum += b[k];
			for (int k = endBlock * len; k <= j; k++)
				sum += StorageNums[k];
		}
		return sum;
	}
private:
	vector<int> b;
	vector<int> StorageNums;
	int len;
};

/**
* Your NumArray object will be instantiated and called as such:
* NumArray obj = new NumArray(nums);
* obj.update(i,val);
* int param_2 = obj.sumRange(i,j);
*/

int main(void)
{
	vector<int> nums{ -2, 0, 3, -5, 2, -1 };
	NumArray3 test(nums);
	cout << test.sumRange(1, 3) << endl;
	test.update(3, -10);
	cout << test.sumRange(1, 3) << endl;
	test.update(3, -5);
	cout << test.sumRange(1, 3) << endl;

	cout << endl;

	// code to keep window open for MSVC++
	cin.clear();
	while (cin.get() != '\n')
		continue;
	cin.get();

	return 0;
}