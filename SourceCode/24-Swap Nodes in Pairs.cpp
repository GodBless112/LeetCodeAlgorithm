//	24. Swap Nodes in Pairs
//------------------------------------------------------------------------------//
//	Given a linked list, swap every two adjacent nodes and return its head.		//
//	For example, Given 1->2->3->4, you should return the list as 2->1->4->3.	//
//	Your algorithm should use only constant space.You may not modify the values //
//	in the list, only nodes itself can be changed.								//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
#include<stack>
#include<list>
// constants
// function prototype
using namespace std;

struct ListNode 
{
    int val;
    ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode* swapPairs(ListNode* head) 
	{
		if (head == nullptr || head->next == nullptr)
			return head;
		ListNode dummy(-1);
		dummy.next = head->next;
		ListNode*p, *q, *last;
		p = head; q = head->next; last = &dummy;
		while (p&&q)
		{
			last->next = q;
			p->next = q->next;
			q->next = p;
			last = p;
			if (p->next == nullptr)
				break;
			p = p->next;
			q = p->next;
		}
		return dummy.next;
	}
};
//递归形式
class Solution2
{
public:
	ListNode* swapPairs(ListNode* head)
	{
		if (head == nullptr || head->next == nullptr)
			return head;
		ListNode *newHead = head->next;
		head->next = swapPairs(head->next->next);
		newHead->next = head;
		return newHead;
	}
};
//int main(void)
//{
//	ListNode *p = new ListNode(1);
//	ListNode *q = p;
//	for (int i = 0; i < 1; i++)
//	{
//		q->next = new ListNode(i + 2);
//		q = q->next;
//	}
//	Solution2 test;
//	auto x=test.swapPairs(p);
//	while (x)
//	{
//		cout << x->val;
//		x = x->next;
//	}
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
