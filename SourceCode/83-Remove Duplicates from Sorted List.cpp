//	83. Remove Duplicates from Sorted List
//------------------------------------------------------------------------------//
//	Given a sorted linked list, delete all duplicates such that each element	//
//	appear only once.															//
//	For example,																//
//	Given 1->1->2, return 1->2.													//
//	Given 1->1->2->3->3, return 1->2->3.											//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
// constants
// function prototype
using namespace std;

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
//迭代的方法，记录上一个出现的不重复值，依次向后比较
class Solution 
{
public:
	ListNode* deleteDuplicates(ListNode* head) 
	{
		if (head == nullptr || head->next == nullptr)
			return head;
		ListNode *p = head->next;
		ListNode *prev = head;
		int prevval = head->val;
		while (p)
		{
			if (p->val == prevval)
			{
				prev->next = p->next;
				delete p;
				p = prev->next;
			}
			else
			{
				prevval = p->val;
				prev = p;
				p = p->next;
			}
		}
		return head;
	}
};
//递归版本
class Solution2 
{
public:
	ListNode* deleteDuplicates(ListNode* head)
	{
		if (head == nullptr)
			return head;
		ListNode dummy(head->val - 1);
		dummy.next = head;
		recur(&dummy, head);
		return dummy.next;
	}
private:
	static void recur(ListNode *prev, ListNode *cur)
	{
		if (cur == nullptr)
			return;
		if (prev->val == cur->val) 
		{
			prev->next = cur->next;
			delete cur;
			recur(prev, prev->next);
		}
		else 
		{
			recur(prev->next, cur->next);
		}
	}
};
//另一种迭代
class Solution3 
{
public:
	ListNode *deleteDuplicates(ListNode *head) 
	{
		if (head == nullptr) return nullptr;
		for (ListNode *prev = head, *cur = head->next; cur; cur = prev->next) 
		{
			if (prev->val == cur->val) {
				prev->next = cur->next;
				delete cur;
			}
			else {
				prev = cur;
			}
		}
		return head;
	}
};
//int main(void)
//{
//	Solution2 test;
//	ListNode *p = new ListNode(1);
//	p->next = new ListNode(1);
//	p->next->next = new ListNode(3);
//	ListNode *q = test.deleteDuplicates(p);
//	while(q)
//	{
//		cout << q->val << " ";
//		q = q->next;
//	}
//	delete p->next->next; delete p->next; delete p;
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
