//	141. Linked List Cycle
//------------------------------------------------------------------------------//
//	Given a linked list, determine if it has a cycle in it.						//
//	Follow up :																	//
//	Can you solve it without using extra space ?								//
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

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
//双指针法，一快一慢，如果快的追上了慢的则说明存在环路
class Solution {
public:
	bool hasCycle(ListNode *head) {
		ListNode *slow = head, *fast = head;
		while (fast && fast->next)
		{
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast)
				return true;
		}
		return false;
	}
};
//利用哈希表记录节点是否出现过
class Solution2 {
public:
	bool hasCycle(ListNode *head) {
		unordered_map<ListNode *, bool> myMap;
		while (head) {
			if (myMap[head] == true)
				return true;
			myMap[head] = true;
			head = head->next;
		}
		return false;
	}
};
//int main(void)
//{
//	Solution2 test;
//	ListNode *head = new ListNode(1);
//	head->next = new ListNode(2);
//	head->next->next = new ListNode(3);
//	head->next->next->next = head->next;
//	cout << boolalpha << test.hasCycle(head);
//	delete head->next->next;
//	delete head->next;
//	delete head;
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