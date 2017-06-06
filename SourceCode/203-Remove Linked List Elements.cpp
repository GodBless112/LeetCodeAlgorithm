//	203. Remove Linked List Elements
//------------------------------------------------------------------------------//
//	Remove all elements from a linked list of integers that have value val.		//
//	Example																		//
//	Given : 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6						//
//	Return: 1 --> 2 --> 3 --> 4 --> 5											//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_set>
// constants
// function prototype
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
//利用牵引节点
class Solution {
public:
	ListNode* removeElements(ListNode* head, int val) {
		ListNode dummy(-1);
		dummy.next = head;
		ListNode* prev = &dummy;
		while (head) {
			if (val == head->val) {
				prev->next = head->next;
				delete head;
				head = prev->next;
			}
			else {
				prev = head;
				head = head->next;
			}
				
		}
		return dummy.next;
	}
};
//利用二级指针
class Solution2 {
public:
	ListNode* removeElements(ListNode* head, int val) {
		ListNode **list = &head;

		while (*list != nullptr) {
			if ((*list)->val == val) {
				ListNode* temp = *list;
				*list = (*list)->next;
				delete temp;
			}
			else
				list = &(*list)->next;
		}

		return head;
	}
};
//递归的方法
class Solution3 {
public:
	ListNode* removeElements(ListNode* head, int val) {
		if (nullptr == head) return nullptr;
		head->next = removeElements(head->next, val);
		if (val == head->val) {
			ListNode *tmp = head->next;
			delete head;
			return tmp;
		}
		return head;
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
//	ListNode* head = new ListNode(1);
//	head->next = new ListNode(2);
//	ListNode* res = test.removeElements(head, 2);
//	ml.showList(res);
//	ml.deleteList(res);
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//	
//	return 0;
//}