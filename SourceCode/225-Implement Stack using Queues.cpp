//	225. Implement Stack using Queues
//------------------------------------------------------------------------------//
//	Implement the following operations of a stack using queues.					//
//	push(x) --Push element x onto stack.										//
//	pop() --Removes the element on top of the stack.							//
//	top() --Get the top element.												//
//	empty() --Return whether the stack is empty.								//
//	Notes:																		//
//	You must use only standard operations of a queue -- which means only push	//
//	to back, peek / pop from front, size, and is empty operations are valid.	//
//	Depending on your language, queue may not be supported natively.You may		//
//	simulate a queue by using a list or deque(double - ended queue), as long as //
//	you use only standard operations of a queue.								//
//	You may assume that all operations are valid(for example, no pop or top		//
//	operations will be called on an empty stack).								//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<queue>
// constants
// function prototype
using namespace std;
class MyStack {
public:
	/** Initialize your data structure here. */
	MyStack() {

	}

	/** Push element x onto stack. */
	void push(int x) {
		s.push(x);
		for (int i = 0; i < s.size() - 1; ++i) {
			s.push(s.front());
			s.pop();
		}
	}

	/** Removes the element on top of the stack and returns that element. */
	int pop() {
		int tmp = s.front();
		s.pop();
		return tmp;
	}

	/** Get the top element. */
	int top() {
		return s.front();
	}

	/** Returns whether the stack is empty. */
	bool empty() {
		return s.empty();
	}
private:
	queue<int> s;
};

/**
* Your MyStack object will be instantiated and called as such:
* MyStack obj = new MyStack();
* obj.push(x);
* int param_2 = obj.pop();
* int param_3 = obj.top();
* bool param_4 = obj.empty();
*/
//int main(void)
//{
//	MyStack obj;
//	obj.push(1);
//	obj.push(2);
//	cout << obj.pop() << endl;
//	cout << obj.top() << endl;
//	cout << boolalpha << obj.empty();
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}