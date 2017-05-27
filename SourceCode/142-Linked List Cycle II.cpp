//	142. Linked List Cycle II
//------------------------------------------------------------------------------//
//	Given a linked list, return the node where the cycle begins. If there is no //
//	cycle, return null.															//
//	Note: Do not modify the linked list.										//
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
//哈希表的方法，使用了额外的空间，时间复杂度O(n),空间复杂度O(n)
class Solution {
public:
	ListNode *detectCycle(ListNode *head) {
		unordered_map<ListNode*, bool> mymap;
		while (head) {
			if (mymap[head] == true)
				return head;
			mymap[head] = true;
			head = head->next;
		}
		return nullptr;
	}
};
//双指针法，一快一慢
//设快慢指针相遇时走了s次，环的长度为r。由于相遇时快指针肯定多走了n圈环，那么有
//2*s=s+n*r，则s=n*r，再设头结点到环入口的距离为x，相遇点到环入口距离为a，链表总长L
//则有x+a=n*r => x+a=n*(r-1)+r => x+a=n*(r-1)+L-x => x=n*(r-1)+(L-x-a)
//那么，此时再从头结点出发一个慢指针，与相遇点的慢指针一起走，一定会再环入口处相遇
class Solution2 {
public:
	ListNode *detectCycle(ListNode *head) {
		ListNode *slow = head, *fast = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast) {
				ListNode *slow2 = head;
				while (slow != slow2) {
					slow = slow->next;
					slow2 = slow2->next;
				}
				return slow;
			}
		}
		return nullptr;
	}
};
//int main(void)
//{
//	Solution2 test;
//	ListNode *head = new ListNode(1);
//	head->next = new ListNode(2);
//	head->next->next = new ListNode(3);
//	head->next->next->next = head->next;
//	auto res = test.detectCycle(head);
//	cout << res->val << endl;
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