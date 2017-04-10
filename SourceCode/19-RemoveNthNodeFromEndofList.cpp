//	19. Remove Nth Node From End of List
//------------------------------------------------------------------------------//
//	Given a linked list, remove the nth node from the end of list and return	//
//	its head.																	//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
#include<set>
#include<unordered_map>
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
struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}

};
//方法1，构建一个节点数组存放n个节点指针，走到末尾的时候，当前索引向前数n个为要删除的指针
class Solution 
{
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) 
	{
		if (head == nullptr)
			return head;
		vector<ListNode*> MyNode(n + 1);
		int index = 0;
		int count = 0;
		ListNode* cur = head;
		while (cur != nullptr)
		{
			MyNode[index] = cur;
			cur = cur->next;
			index = (index + 1) % (n + 1);
			count++;
		}
		if (count == n)
		{
			delete head;
			return head->next;
		}
		ListNode* KNow = MyNode[(index+1) % (n + 1)];
		ListNode* KNext = KNow->next;
		ListNode* KPrev = MyNode[(index) % (n + 1)];
		KNow->next = nullptr;
		delete KNow;
		KPrev->next = KNext;
		return head;
	}
};
//方法2，两个指针，一个先走n步，然后同时走
class Solution2
{
public:
	ListNode* removeNthFromEnd(ListNode* head, int n)
	{
		if (!head)
			return nullptr;
		ListNode dummy(-1);
		dummy.next = head;
		ListNode *p = &dummy, *q = &dummy;
		for (int i = 0; i < n; i++)
			q = q->next;
		while (q->next)
		{
			p = p->next;
			q = q->next;
		}
		ListNode* tmp = p->next;
		p->next = p->next->next;
		delete tmp;
		return dummy.next;
	}
};
//int main(void)
//{
//	Solution2 test;
//	ListNode *p = new ListNode(1);
//	auto cur = p;
//	for (int i = 0; i < 0; i++)
//	{
//		cur->next = new ListNode(i + 2);
//		cur = cur->next;
//	}
//	auto q=test.removeNthFromEnd(p, 1);
//	while (q)
//	{
//		cout << q->val;
//		q = q->next;
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
