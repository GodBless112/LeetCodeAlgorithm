//	206. Reverse Linked List
//------------------------------------------------------------------------------//
//	Reverse a singly linked list.												//
//	Hint:																		//
//	A linked list can be reversed either iteratively or recursively.Could you	//
//	implement both ?															//
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
//迭代版本
class Solution 
{
public:
	ListNode* reverseList(ListNode* head) 
	{
		ListNode *prev = nullptr;
		ListNode *next;
		while (head)
		{
			next = head->next;
			head->next = prev;
			prev = head;
			head = next;
		}
		return prev;
	}
};
//递归版本
class Solution2
{
public:
	ListNode* reverseList(ListNode* head)
	{
		ListNode *New_head;
		if (head == nullptr || head->next == nullptr)
			return head;
		New_head = reverseList(head->next);
		head->next->next = head;
		head->next = nullptr;
		return New_head;
	}
};
//另一种迭代
class Solution3 {
public:
	ListNode* reverseList(ListNode* head) {
		ListNode new_head(0);
		new_head.next = head;
		ListNode* pre = &new_head;
		ListNode* cur = head;
		while (cur && cur->next) {
			ListNode* temp = pre->next;
			pre->next = cur->next;
			cur->next = cur->next->next;
			pre->next->next = temp;
		}
		return new_head.next;
	}
};
//int main(void)
//{
//	Solution2 test;
//	ListNode *p, *q;
//	q = new ListNode(1);
//	p = q;
//	for (int i = 2; i <= 5; i++)
//	{
//		q->next = new ListNode(i);
//		q = q->next;
//	}
//	auto ptr = test.reverseList(p);
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