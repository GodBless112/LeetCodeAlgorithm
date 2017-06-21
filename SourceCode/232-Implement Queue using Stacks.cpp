//	232. Implement Queue using Stacks
//------------------------------------------------------------------------------//
//	Implement the following operations of a queue using stacks.					//
//	push(x) --Push element x to the back of queue.								//
//	pop() --Removes the element from in front of queue.							//
//	peek() --Get the front element.												//
//	empty() --Return whether the queue is empty.								//
//	Notes:																		//
//	You must use only standard operations of a stack -- which means only push	//
//	to top, peek / pop from top, size, and is empty operations are valid.		//
//	Depending on your language, stack may not be supported natively.You may		//
//	simulate a stack by using a list or deque(double - ended queue), as long	//
//	as you use only standard operations of a stack.								//
//	You may assume that all operations are valid(for example, no pop or peek	//
//operations will be called on an empty queue).									//
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
//用两个stack来实现，每次push的时候将x放在栈底
class MyQueue {
public:
	/** Initialize your data structure here. */

	/** Push element x to the back of queue. */
	void push(int x) {
		while(!q.empty()) {
			s.push(q.top());
			q.pop();
		}
		q.push(x);
		while(!s.empty()){
			q.push(s.top());
			s.pop();
		}
	}

	/** Removes the element from in front of queue and returns that element. */
	int pop() {
		int val = q.top();
		q.pop();
		return val;
	}

	/** Get the front element. */
	int peek() {
		return q.top();
	}

	/** Returns whether the queue is empty. */
	bool empty() {
		return q.empty();
	}
private:
	stack<int> q, s;
};
//两个栈，一个用于out，一个用于input，在peek的时候将input的栈翻转存到out里，在push操作更多时更优
class MyQueue2 {
	stack<int> input, output;
public:

	void push(int x) {
		input.push(x);
	}

	int pop(void) {
		int val = peek();
		output.pop();
		return val;
	}

	int peek(void) {
		if (output.empty())
			while (input.size())
				output.push(input.top()), input.pop();
		return output.top();
	}

	bool empty(void) {
		return input.empty() && output.empty();
	}
};
//一个栈，递归的方法
class MyQueue3 {
public:
	stack<int> s;

	// Push element x to the back of queue.
	void push(int x) {
		pushHelper(x);
	}
	void pushHelper(int x) {
		if (s.size() == 0) {
			s.push(x);
			return;
		}
		int data;
		data = s.top();
		s.pop();
		pushHelper(x);
		s.push(data);
		return;

	}

	// Removes the element from in front of queue.
	int pop(void) {
		int val = s.top();
		s.pop();
		return val;
	}

	// Get the front element.
	int peek(void) {
		return s.top();
	}

	// Return whether the queue is empty.
	bool empty(void) {
		return (s.size() == 0);
	}
};
/**
* Your MyQueue object will be instantiated and called as such:
* MyQueue obj = new MyQueue();
* obj.push(x);
* int param_2 = obj.pop();
* int param_3 = obj.peek();
* bool param_4 = obj.empty();
*/
//int main(void)
//{
//	MyQueue3 q;
//	q.push(3);
//	q.push(4);
//	q.push(5);
//	cout << q.pop() << endl;
//	cout << q.peek() << endl;
//	cout << boolalpha << q.empty();
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}