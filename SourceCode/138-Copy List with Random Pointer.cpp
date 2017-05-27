//	138. Copy List with Random Pointer
//------------------------------------------------------------------------------//
//	A linked list is given such that each node contains an additional random	//
//	pointer which could point to any node in the list or null.					//
//	Return a deep copy of the list.												//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<queue>
// constants
// function prototype
using namespace std;

struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};
//深度优先搜索，利用哈希表来记录是否访问节点
class Solution {
public:
	RandomListNode *copyRandomList(RandomListNode *head) {
		if (head == nullptr) return nullptr;
		if (hashtable.find(head) == hashtable.end()) {
			hashtable[head] = new RandomListNode(head->label);
			hashtable[head]->next = copyRandomList(head->next);
			hashtable[head]->random = copyRandomList(head->random);
		}
		return hashtable[head];
	}
private:
	unordered_map<RandomListNode*, RandomListNode*> hashtable;
};
//迭代法，利用队列,广度优先搜索
class Solution2 {
public:
	RandomListNode *copyRandomList(RandomListNode *head) {
		if (nullptr == head) return nullptr;
		queue<RandomListNode*> q;
		q.push(head);
		hashtable[head] = new RandomListNode(head->label);
		while (!q.empty()) {
			RandomListNode *cur = q.front();
			q.pop();
			if (cur->next && hashtable.find(cur->next) == hashtable.end()) {
				hashtable[cur->next] = new RandomListNode(cur->next->label);
				q.push(cur->next);
			}			
			if (cur->random && hashtable.find(cur->random) == hashtable.end()) {
				hashtable[cur->random] = new RandomListNode(cur->random->label);
				q.push(cur->random);
			}
			hashtable[cur]->next = hashtable[cur->next];
			hashtable[cur]->random = hashtable[cur->random];
		}
		return hashtable[head];
	}
private:
	unordered_map<RandomListNode*, RandomListNode*> hashtable;
};
//更巧妙的做法，不用额外的空间，复杂度O(n)
//思想是走两遍，第一遍将复制的节点插入到原结点之后，第二遍把随机访问节点加上，然后分割两个链表
class Solution3 {
public:
	RandomListNode *copyRandomList(RandomListNode *head) {
		for (RandomListNode* cur = head; cur;) {
			//建立结点，并插入到原节点之后
			RandomListNode* node = new RandomListNode(cur->label);
			node->next = cur->next;
			cur->next = node;
			cur = node->next;
		}
		//加入random节点
		for (RandomListNode* cur = head; cur;) {
			if (cur->random)
				cur->next->random = cur->random->next;
			cur = cur->next->next;
		}
		//分拆成两个链表
		RandomListNode dummy(-1);
		for (RandomListNode* cur = head, *new_cur = &dummy;
			cur != nullptr; ) {
			new_cur->next = cur->next;
			new_cur = new_cur->next;
			cur->next = cur->next->next;
			cur = cur->next;
		}
		return dummy.next;
	}
};
//int main(void)
//{
//	Solution3 test;
//	RandomListNode* head = new RandomListNode(1);
//	head->next = new RandomListNode(2);
//	head->random = head;
//	head->next->random = head;
//	auto res = test.copyRandomList(head);
//	delete head, head->next;
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