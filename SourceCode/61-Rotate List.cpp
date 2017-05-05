//	61. Rotate List
//------------------------------------------------------------------------------//
//	Given a list, rotate the list to the right by k places, where k is			//
//	non-negative.																//
//	For example :																//
//	Given 1->2->3->4->5->NULL and k = 2,										//
//	return 4->5->1->2->3->NULL.													//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<stack>
// constants
// function prototype
using namespace std;

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//方案一，先遍历一遍列表，并使得列表成环，然后找到倒数位置k，断开
class Solution 
{
public:
	ListNode* rotateRight(ListNode* head, int k) 
	{
		if (head == nullptr || k==0)
			return head;
		ListNode *p = head;
		int count = 1;
		while (p->next)
		{
			p = p->next;
			count++;
		}
		p->next = head;			//首尾相连
		k = count - k%count;	//右移k，则起始点为倒数第k个节点
		while (k--)
			p = p->next;
		head = p->next;
		p->next = nullptr;
		return head;
	}
};
//同方案一，但提交结果实际快了方案一？
class Solution2 
{
public:
	ListNode* rotateRight(ListNode* head, int k) 
	{
		if (!head) return head;

		int len = 1; // number of nodes
		ListNode *newH, *tail;
		newH = tail = head;

		while (tail->next)  // get the number of nodes in the list
		{
			tail = tail->next;
			len++;
		}
		tail->next = head; // circle the link

		if (k %= len)
		{
			for (auto i = 0; i<len - k; i++) tail = tail->next; // the tail node is the (len-k)-th node (1st node is head)
		}
		newH = tail->next;
		tail->next = NULL;
		return newH;
	}
};
//双指针，不需要统计节点数，但是需要特殊处理，而且在k大于节点数时效果不好，会超时
class Solution3
{
public:
	ListNode* rotateRight(ListNode* head, int k) {
		if (head == nullptr || head->next == nullptr || k == 0) 
		{
			return head;
		}
		ListNode *fast = head;
		ListNode *slow = head;
		ListNode *newHead;
		for (int i = 0; i < k; i++) 
		{
			if (fast->next == nullptr) 
				fast = head;
			else
				fast = fast->next;
		}
		while (fast->next != nullptr) {
			fast = fast->next;
			slow = slow->next;
		}
		fast->next = head;
		newHead = slow->next;
		slow->next = nullptr;
		return newHead;
	}
};
//int main(void)
//{
//	Solution3 test;
//	ListNode *q[5];
//	for (int i = 0; i < 5; i++)
//		q[i] = new ListNode(i + 1);
//	for (int i = 0; i < 4; i++)
//		q[i]->next = q[i + 1];
//	for (int i = 0; i < 5; i++)
//		cout << q[i]->val << " ";
//	cout << endl;
//	ListNode *p = test.rotateRight(q[0], 1324);
//	for (; p; p = p->next)
//		cout << p->val << " ";
//	for (int i = 0; i < 5; i++)
//		delete q[i];
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
