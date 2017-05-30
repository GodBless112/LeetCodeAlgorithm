//	148. Sort List
//------------------------------------------------------------------------------//
//	Sort a linked list in O(n log n) time using constant space complexity.		//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<stack>

// constants
// function prototype
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
//归并排序
class Solution {
public:
	ListNode* sortList(ListNode* head) {
		if (nullptr == head || nullptr == head->next) return head;
		ListNode *mid = head, *tail = head;
		//定位到中间节点的前一个节点
		while (tail->next && tail->next->next) {
			mid = mid->next;
			tail = tail->next->next;
		}
		tail = mid;
		mid = mid->next;
		tail->next = nullptr;
		ListNode *l1 = sortList(head);
		ListNode *l2 = sortList(mid);
		return mergeTwoLists(l1, l2);
	}
private:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (nullptr == l1) return l2;
		if (nullptr == l2) return l1;
		ListNode dummy(-1);
		ListNode *p = &dummy;
		while (l1 && l2) {
			if (l1->val < l2->val) {
				p->next = l1;
				l1 = l1->next;
			}
			else {
				p->next = l2;
				l2 = l2->next;
			}
			p = p->next;
		}
		if (l1) p->next = l1;
		if (l2) p->next = l2;
		return dummy.next;
	}
};
//
/**
* Merge sort use bottom-up policy,
* so Space Complexity is O(1)
* Time Complexity is O(NlgN)
* stable sort
*/
class Solution2 {
public:
	ListNode *sortList(ListNode *head) {
		if (!head || !(head->next)) return head;

		//get the linked list's length
		ListNode* cur = head;
		int length = 0;
		while (cur) {
			length++;
			cur = cur->next;
		}

		ListNode dummy(0);
		dummy.next = head;
		ListNode *left, *right, *tail;
		for (int step = 1; step < length; step <<= 1) {
			cur = dummy.next;
			tail = &dummy;
			while (cur) {
				left = cur;
				right = split(left, step);
				cur = split(right, step);
				tail = merge(left, right, tail);
			}
		}
		return dummy.next;
	}
private:
	/**
	* Divide the linked list into two lists,
	* while the first list contains first n ndoes
	* return the second list's head
	*/
	ListNode* split(ListNode *head, int n) {
		//if(!head) return NULL;
		for (int i = 1; head && i < n; i++) head = head->next;

		if (!head) return NULL;
		ListNode *second = head->next;
		head->next = NULL;
		return second;
	}
	/**
	* merge the two sorted linked list l1 and l2,
	* then append the merged sorted linked list to the node head
	* return the tail of the merged sorted linked list
	*/
	ListNode* merge(ListNode* l1, ListNode* l2, ListNode* head) {
		ListNode *cur = head;
		while (l1 && l2) {
			if (l1->val > l2->val) {
				cur->next = l2;
				cur = l2;
				l2 = l2->next;
			}
			else {
				cur->next = l1;
				cur = l1;
				l1 = l1->next;
			}
		}
		cur->next = (l1 ? l1 : l2);
		while (cur->next) cur = cur->next;
		return cur;
	}
};
class ManageListNode {
public:
	void showList(ListNode *head) {
		while (head) {
			cout << head->val << " ";
			head = head->next;
		}
		cout << endl;
	}
	void deleteList(ListNode* head) {
		while (head) {
			ListNode *temp = head;
			head = head->next;
			delete temp;
		}
	}
};
//int main(void)
//{
//	Solution2 test;
//	ManageListNode ml;
//	ListNode* head = new ListNode(3);
//	head->next = new ListNode(4);
//	head->next->next = new ListNode(1);
//	ml.showList(head);
//	auto res = test.sortList(head);
//	ml.showList(res);
//	ml.deleteList(res);
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