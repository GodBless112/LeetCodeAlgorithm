//	147. Insertion Sort List
//------------------------------------------------------------------------------//
//	Sort a linked list using insertion sort.									//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<stack>

// constants
// function prototype
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode* insertionSortList(ListNode* head) {
		if (head == nullptr || head->next == nullptr)
			return head;
		ListNode* cur = head;
	}
};
int main(void)
{
	Solution test;
	
	cout << endl;
		
	// code to keep window open for MSVC++
	cin.clear();
	while (cin.get() != '\n')
		continue;
	cin.get();
	
	return 0;
}