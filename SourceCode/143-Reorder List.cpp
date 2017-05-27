//	143. Reorder List
//------------------------------------------------------------------------------//
//	Given a singly linked list L: L0→L1→…→Ln-1→Ln,							//
//	reorder it to : L0→Ln→L1→Ln-1→L2→Ln-2→…								//
//	You must do this in - place without altering the nodes' values.				//
//	For example,																//
//	Given{ 1,2,3,4 }, reorder it to{ 1,4,2,3 }.									//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>

// constants
// function prototype
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

//因为要求原地。先找到中间节点，分成两部分，后半部分翻转，然后合并
class Solution {
public:
	void reorderList(ListNode* head) {
		if (head == nullptr || head->next == nullptr) return;
		ListNode *mid = head, *tail = head, *prev = nullptr;
		while (tail && tail->next) {
			prev = mid;
			mid = mid->next;
			tail = tail->next->next;
		}
		prev->next = nullptr;
		mid = reverseList(mid);
		//合并两个链表
		ListNode* cur = head;
		while (cur->next) {
			ListNode *tmp = cur->next;
			cur->next = mid;
			mid = mid->next;
			cur->next->next = tmp;
			cur = tmp;
		}
		cur->next = mid;
	}
private:
	ListNode* reverseList(ListNode* head) {
		ListNode *prev = nullptr;
		ListNode *next;
		while (head) {
			next = head->next;
			head->next = prev;
			prev = head;
			head = next;
		}
		return prev;
	}
};
//int main(void)
//{
//	Solution test;
//	ListNode *head = new ListNode(1);
//	head->next = new ListNode(2);
//	head->next->next = new ListNode(3);
//	head->next->next->next = new ListNode(4);
//	test.reorderList(head);
//	while (head) {
//		ListNode *tmp = head;
//		cout << head->val << " ";
//		head = head->next;
//		delete tmp;
//	}
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