//	82. Remove Duplicates from Sorted List II
//------------------------------------------------------------------------------//
//	Given a sorted linked list, delete all nodes that have duplicate numbers,	//
//	leaving only distinct numbers from the original list.						//
//	For example,																//
//	Given 1->2->3->3->4->4->5, return 1->2->5.									//
//	Given 1->1->1->2->3, return 2->3.											//
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

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
//迭代的方法，先删除重复元素
class Solution 
{
public:
	ListNode* deleteDuplicates(ListNode* head) 
	{
		if (head == nullptr || head->next == nullptr)
			return head;
		ListNode dummy(INT_MIN);
		ListNode *prev = &dummy;
		ListNode *cur = head;
		while (cur)
		{
			bool dupliacte = false;
			while (cur->next&&cur->next->val == cur->val)
			{
				ListNode *temp = cur->next;
				cur->next = cur->next->next;
				delete temp;
				dupliacte = true;
			}
			if (dupliacte)
			{
				ListNode *temp = cur;
				cur = cur->next;
				delete temp;
				continue;
			}
			prev->next = cur;
			prev = cur;
			cur = cur->next;
		}
		prev->next = cur;	//最后都是重复元素的情况
		return dummy.next;
	}
};

//递归版本
class Solution2
{
public:
	ListNode* deleteDuplicates(ListNode* head)
	{
		if (head == nullptr || head->next == nullptr)
			return head;
		ListNode *p = head->next;
		if (head->val == p->val) {
			while (p && head->val == p->val) {
				ListNode *tmp = p;
				p = p->next;
				delete tmp;
			}
			delete head;
			return deleteDuplicates(p);
		}
		else {
			head->next = deleteDuplicates(head->next);
			return head;
		}
	}
};

//int main(void)
//{
//	Solution2 test;
//	ListNode *p = new ListNode(1);
//	p->next = new ListNode(3);
//	p->next->next = new ListNode(3);
//	ListNode *q = test.deleteDuplicates(p);
//	while(q)
//	{
//		cout << q->val << " ";
//		ListNode *temp = q;
//		q = q->next;
//		delete temp;
//	}
//	
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