//	147. Insertion Sort List
//------------------------------------------------------------------------------//
//	Sort a linked list using insertion sort.									//
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

class Solution {
public:
	ListNode* insertionSortList(ListNode* head) {
		if (head == nullptr || head->next == nullptr)
			return head;
		ListNode dummy(-1);
		dummy.next = head;
		ListNode* cur = head->next;	//想插入的节点
		ListNode* tail = head;		//当前已排序好的链表的尾节点
		while (cur) {
			ListNode* next = cur->next;		//记录插入节点的下一节点
			ListNode* nowHead = dummy.next;	//头结点
			ListNode* prev = &dummy;
			while (nowHead != cur) {
				if (cur->val < nowHead->val) {
					prev->next = cur;
					tail->next = cur->next;
					cur->next = nowHead;
					break;
				}
				prev = nowHead;
				nowHead = nowHead->next;
			}
			if (nowHead == cur) tail = cur;
			cur = next;
		}
		return dummy.next;
	}
};
//插入排序，建立一个头结点，对当前节点找到从头结点开始可以插入的位置，插入
class Solution2 {
public:
	ListNode *insertionSortList(ListNode *head) {
		ListNode dummy(INT_MIN);
		//dummy.next = head;
		for (ListNode *cur = head; cur != nullptr;) {
			auto pos = findInsertPos(&dummy, cur->val);
			ListNode *tmp = cur->next;
			cur->next = pos->next;
			pos->next = cur;
			cur = tmp;
		}
		return dummy.next;
	}
	ListNode* findInsertPos(ListNode *head, int x) {
		ListNode *pre = nullptr;
		for (ListNode *cur = head; cur != nullptr && cur->val <= x;
			pre = cur, cur = cur->next)
			;
		return pre;
	}
};
//
class Solution3 {
public:
	ListNode* insertionSortList(ListNode* head) {
		ListNode* new_head = new ListNode(0);
		new_head->next = head;
		ListNode* pre = new_head;
		ListNode* cur = head;
		while (cur) {
			if (cur->next && cur->next->val < cur->val) {
				while (pre->next && pre->next->val < cur->next->val)
					pre = pre->next;
				/* Insert cur -> next after pre.*/
				ListNode* temp = pre->next;
				pre->next = cur->next;
				cur->next = cur->next->next;
				pre->next->next = temp;
				/* Move pre back to new_head. */
				pre = new_head;
			}
			else cur = cur->next;
		}
		ListNode* res = new_head->next;
		delete new_head;
		return res;
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
//	Solution3 test;
//	ManageListNode ml;
//	ListNode* head = new ListNode(3);
//	head->next = new ListNode(4);
//	head->next->next = new ListNode(1);
//	ml.showList(head);
//	auto res = test.insertionSortList(head);
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