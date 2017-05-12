//	92. Reverse Linked List II
//------------------------------------------------------------------------------//
//	Reverse a linked list from position m to n. Do it in-place and in one-pass.	//
//	For example :																//
//	Given 1->2->3->4->5->NULL, m = 2 and n = 4,									//
//	return 1->4->3->2->5->NULL.													//
//	Note :																		//
//	Given m, n satisfy the following condition :								//
//	1 ≤ m ≤ n ≤ length of list.												//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<set>
#include<iterator>
// constants
// function prototype
using namespace std;

struct ListNode {
	int val;
	ListNode *next;     
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution 
{
public:
	ListNode* reverseBetween(ListNode* head, int m, int n)
	{
		ListNode dummy(-1);
		dummy.next = head;
		ListNode *prev = &dummy;
		for (int i = 0; i < m - 1; i++)
			prev = prev->next;
		ListNode * const head2 = prev;
		prev = head2->next;
		ListNode *cur = prev->next;
		for (int i = m; i < n; i++)
		{
			prev->next = cur->next;
			cur->next = head2->next;
			head2->next = cur;
			cur = prev->next;
		}
		return dummy.next;
	}
};
//int main(void)
//{
//	Solution test;
//	ListNode *p, *q;
//	q = new ListNode(1);
//	p = q;
//	for (int i = 2; i <= 2; i++)
//	{
//		q->next = new ListNode(i);
//		q = q->next;
//	}
//	auto ptr = test.reverseBetween(p, 1, 2);
//	while (ptr)
//	{
//		cout << ptr->val << " ";
//		ListNode *tmp = ptr;
//		ptr = ptr->next;
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