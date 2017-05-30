//	160. Intersection of Two Linked Lists
//------------------------------------------------------------------------------//
//	Write a program to find the node at which the intersection of two singly	//
//	linked lists begins.														//
//	For example, the following two linked lists :								//
//	A:            a1 → a2														//
//						  ↘													//
//							c1 → c2 → c3										//
//						  ↗													//
//	B :		b1 → b2 → b3														//
//	begin to intersect at node c1.												//
//	Notes :																		//
//		If the two linked lists have no intersection at all, return null.		//
//		The linked lists must retain their original structure after the function//
//		returns.																//
//		You may assume there are no cycles anywhere in the entire linked		//
//		structure.																//
//		Your code should preferably run in O(n) time and use only O(1) memory.	//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_set>
// constants
// function prototype
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
//利用哈希表记录节点是否出现过
class Solution {
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		unordered_set<ListNode*> dict;
		while (headA && headB) {
			if (dict.find(headA) != dict.end())
				return headA;
			dict.insert(headA);
			if (dict.find(headB) != dict.end())
				return headB;
			dict.insert(headB);
			headA = headA->next;
			headB = headB->next;
		}
		while (headA) {
			if (dict.find(headA) != dict.end())
				return headA;
			dict.insert(headA);
			headA = headA->next;
		}
		while (headB) {
			if (dict.find(headB) != dict.end())
				return headB;
			dict.insert(headB);
			headB = headB->next;
		}
		return nullptr;
	}
};
//将cur1从headA出发，cur2从headB出发，走到头时分别再从headB，headA出发
//那么最终两者相同时会停在交叉处或者null，这样最差会走两趟
class Solution2 {
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		ListNode *cur1 = headA, *cur2 = headB;
		while (cur1 != cur2) {
			cur1 = cur1 ? cur1->next : headB;
			cur2 = cur2 ? cur2->next : headA;
		}
		return cur1;
	}
};
//方法2的优化
class Solution3 {
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
	{
		ListNode *p1 = headA;
		ListNode *p2 = headB;

		if (p1 == NULL || p2 == NULL) return NULL;

		while (p1 != NULL && p2 != NULL && p1 != p2) {
			p1 = p1->next;
			p2 = p2->next;

			//
			// Any time they collide or reach end together without colliding 
			// then return any one of the pointers.
			//
			if (p1 == p2) return p1;

			//
			// If one of them reaches the end earlier then reuse it 
			// by moving it to the beginning of other list.
			// Once both of them go through reassigning, 
			// they will be equidistant from the collision point.
			//
			if (p1 == NULL) p1 = headB;
			if (p2 == NULL) p2 = headA;
		}

		return p1;
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
//	ListNode *pa, *pb;
//	pa = new ListNode(1);
//	pa->next = new ListNode(3);
//	pb = new ListNode(2);
//	pb->next = pa->next;
//	auto res = test.getIntersectionNode(pa, pb);
//	cout << res->val;
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