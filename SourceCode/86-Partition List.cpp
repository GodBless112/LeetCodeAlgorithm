//	86. Partition List
//------------------------------------------------------------------------------//
//	Given a linked list and a value x, partition it such that all nodes less	//
//	than x come before nodes greater than or equal to x.						//
//	You should preserve the original relative order of the nodes in each of the //
//	two partitions.																//
//	For example,																//
//	Given 1->4->3->2->5->2 and x = 3,											//
//	return 1->2->2->4->3->5.													//
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
//分成两队，一队小于x，一队大于等于x，最后再连接起来
class Solution 
{
public:
	ListNode* partition(ListNode* head, int x) 
	{
		if (head == nullptr || head->next == nullptr)
			return head;
		ListNode Low_dummy(-1);
		ListNode High_dummy(-1);
		ListNode *Low = &Low_dummy, *High = &High_dummy;
		ListNode *p = head;
		while (p)
		{
			if (p->val < x)
			{
				Low->next = p;
				Low = p;
			}
			else
			{
				High->next = p;
				High = p;
			}
			p = p->next;
		}
		Low->next = High_dummy.next;	//连接两队节点
		High->next = nullptr;	//必要，最后一个节点的next需要指向NULL
		return Low_dummy.next;
	}
};

//int main(void)
//{
//	Solution test;
//	ListNode *p = new ListNode(1);
//	p->next = new ListNode(4);
//	p->next->next = new ListNode(3);
//	p->next->next->next = new ListNode(2);
//	p->next->next->next->next = new ListNode(5);
//	p->next->next->next->next->next = new ListNode(2);
//	ListNode *q = test.partition(p,3);
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