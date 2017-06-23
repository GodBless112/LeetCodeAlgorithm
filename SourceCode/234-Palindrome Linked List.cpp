//	234. Palindrome Linked List
//------------------------------------------------------------------------------//
//	Given a singly linked list, determine if it is a palindrome.				//
//	Follow up :																	//
//	Could you do it in O(n) time and O(1) space ?								//
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
//先找到链表中点，将后半部分翻转，然后比较
class Solution {
public:
	bool isPalindrome(ListNode* head) {
		if (head == nullptr || head->next == nullptr)
			return true;
		ListNode *slow = head, *fast = head;
		while (fast->next && fast->next->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		slow->next = reverseList(slow->next);
		slow = slow->next;
		while (slow) {
			if (head->val != slow->val)
				return false;
			head = head->next;
			slow = slow->next;
		}
		return true;
	}
private:
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
//递归的方法，有点巧妙
class Solution2 {
public:
	ListNode* temp;
	bool isPalindrome(ListNode* head) {
		temp = head;
		return check(head);
	}

	bool check(ListNode* p) {
		if (NULL == p) return true;
		bool isPal = check(p->next) && (temp->val == p->val);
		temp = temp->next;
		return isPal;
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
//	root->next->next = new ListNode(2);
//	root->next->next->next = new ListNode(1);
//	ml.showList(root);
//	cout << boolalpha << test.isPalindrome(root);
//	ml.deleteList(root);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}