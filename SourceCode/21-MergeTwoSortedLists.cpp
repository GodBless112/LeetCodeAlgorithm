//	21. Merge Two Sorted Lists
//------------------------------------------------------------------------------//
//	Merge two sorted linked lists and return it as a new list. The new list		//
//	should be made by splicing together the nodes of the first two lists.		//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
#include<stack>
// constants
// function prototype
using namespace std;
/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution 
{
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
	{
		if (l1 == nullptr) return l2;
		if (l2 == nullptr) return l1;
		ListNode dummy(-1);
		ListNode *p = &dummy;
		while (l1&&l2)
		{
			if (l1->val < l2->val)
			{
				p->next = l1;
				l1 = l1->next;
			}
			else
			{
				p->next = l2;
				l2 = l2->next;
			}			
			p = p->next;		
		}
		if (l1)
			p->next = l1;
		if (l2)
			p->next = l2;
		return dummy.next;
	}
};
//µü´úÐÎÊ½
class Solution2 
{
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
	{
		if (!l1) return l2;
		if (!l2) return l1;
		if (l1->val < l2->val) { l1->next = mergeTwoLists(l1->next, l2); return l1; }
		else { l2->next = mergeTwoLists(l2->next, l1); return l2; }
	}
};
//int main(void)
//{
//	Solution2 test;
//	ListNode *p1=new ListNode(1);
//	ListNode *cur = p1;
//	for (int i = 0; i < 4; i++)
//	{
//		cur->next = new ListNode(i + 2);
//		cur = cur->next;
//	}
//	ListNode *p2 = new ListNode(1);
//	cur = p2;
//	for (int i = 0; i < 4; i++)
//	{
//		cur->next = new ListNode(i + 2);
//		cur = cur->next;
//	}
//	auto x=test.mergeTwoLists(p1, p2);
//	while (x)
//	{
//		cout << x->val;
//		x = x->next;
//	}
//		
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
