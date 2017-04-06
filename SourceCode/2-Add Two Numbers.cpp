// static.cpp -- using a static local variable
#include <iostream>
#include<vector>
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
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode dummy(-1);
		ListNode *p = l1, *q = l2, *current = &dummy;
		int carry = 0;
		while (p != nullptr || q != nullptr)
		{
			int x = (p == nullptr) ? 0 : p->val;
			int y = (q == nullptr) ? 0 : q->val;
			int sum = x + y + carry;
			carry = sum / 10;
			current->next = new ListNode(sum % 10);
			current = current->next;
			if (p != nullptr) p = p->next;
			if (q != nullptr) q = q->next;
		}
		if (carry>0)
			current->next = new ListNode(carry);
		return dummy.next;
	}
};
class Solution2 {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode dummy(-1);
		ListNode *current = &dummy;
		int carry = 0;
		for (ListNode *p = l1, *q = l2; p != nullptr || q != nullptr;
		p = p != nullptr ? p->next : nullptr, q = q != nullptr ? q->next : nullptr, current = current->next)
		{
			const int x = (p == nullptr) ? 0 : p->val;
			const int y = (q == nullptr) ? 0 : q->val;
			int sum = x + y + carry;
			carry = sum / 10;
			current->next = new ListNode(sum % 10);
		}
		if (carry>0)
			current->next = new ListNode(carry);
		return dummy.next;
	}
};
class Solution3 {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode stackAnchor(0);
		ListNode* tail = &stackAnchor;

		div_t sum = { 0, 0 };
		while (sum.quot > 0 || l1 || l2)
		{
			if (l1)
			{
				sum.quot += l1->val;
				l1 = l1->next;
			}
			if (l2)
			{
				sum.quot += l2->val;
				l2 = l2->next;
			}
			sum = div(sum.quot, 10);

			tail->next = new ListNode(sum.rem);
			tail = tail->next;
		}

		return stackAnchor.next;
	}
};
//int main(void)
//{
//	
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
