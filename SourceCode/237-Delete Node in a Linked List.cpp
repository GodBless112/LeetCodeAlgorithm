//	237. Delete Node in a Linked List
//------------------------------------------------------------------------------//
//	Write a function to delete a node (except the tail) in a singly linked list,//
//	given only access to that node.												//
//	Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third	//
//	node with value 3, the linked list should become 1 -> 2 -> 4 after calling	//
//	your function.																//
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
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
//此题无法真正的删除所输入的节点，只能假删除，将后面节点的值换到要删除的节点，其next也接到后面，删除后一节点
class Solution {
public:
	void deleteNode(ListNode* node) {
		ListNode *tmp = node->next;
		node->val = node->next->val;
		node->next = node->next->next;
		delete tmp;
	}
};
//不考虑内存泄漏的情况下假删除
class Solution2 {
public:
	void deleteNode(ListNode* node) {
		*node = *node->next;
	}
};
class ManageListNode {
public:
	void showList(ListNode *head) {
		while (head) {
			cout << head->val << " ";
			head = head->next;
		}
		cout << endl;
	}
	void deleteList(ListNode* head) {
		while (head) {
			ListNode *temp = head;
			head = head->next;
			delete temp;
		}
	}
};
//int main(void)
//{
//	Solution2 test;
//	ManageListNode ml;
//	ListNode *root = new ListNode(1);
//	root->next = new ListNode(2);
//	root->next->next = new ListNode(3);
//	root->next->next->next = new ListNode(4);
//	test.deleteNode(root->next->next);
//	ml.showList(root);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}