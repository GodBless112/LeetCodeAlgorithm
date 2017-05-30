//	155. Min Stack
//------------------------------------------------------------------------------//
//	Design a stack that supports push, pop, top, and retrieving the minimum		//
//	element in constant time.													//
//	push(x) --Push element x onto stack.										//
//	pop() --Removes the element on top of the stack.							//
//	top() --Get the top element.												//
//	getMin() --Retrieve the minimum element in the stack.						//
//	Example:																	//
//	MinStack minStack = new MinStack();											//
//	minStack.push(-2);															//
//	minStack.push(0);															//
//	minStack.push(-3);															//
//	minStack.getMin();   --> Returns - 3.										//
//	minStack.pop();																//
//	minStack.top();      --> Returns 0.											//
//	minStack.getMin();   --> Returns - 2.										//
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
//双栈，一个正常出入栈，一个用来记录最小值
class MinStack {
public:
	/** initialize your data structure here. */
	MinStack() {
		
	}

	void push(int x) {
		s1.push(x);
		if (s2.empty() || x <= s2.top()) s2.push(x);
	}

	void pop() {
		if (s2.top() == s1.top()) s2.pop();
		s1.pop();
	}

	int top() {
		return s1.top();
	}

	int getMin() {
		return s2.top();
	}
private:
	stack<int> s1;
	stack<int> s2;	//record minimun element
};
//用一个栈实现，用一个min记录最小值，每次入栈时判断最小值是否更新，若要更新则将上一个最小值压入栈
//出栈时如果最小值等于栈顶值，则出栈两次并更新最小值为栈顶下面的值
class MinStack2 {
public:
	void push(int x) {
		// only push the old minimum value when the current 
		// minimum value changes after pushing the new value x
		if (x <= min) {
			s.push(min);
			min = x;
		}
		s.push(x);
	}

	void pop() {
		// if pop operation could result in the changing of the current minimum value, 
		// pop twice and change the current minimum value to the last minimum value.
		if (s.top() == min) {
			s.pop();
			min = s.top();
			s.pop();
		}
		else
			s.pop();
	}

	int top() {
		return s.top();
	}

	int getMin() {
		return min;
	}
private:
	stack<int> s;
	int min = INT_MAX;
};
//int main(void)
//{
//	MinStack2 obj;
//	obj.push(2);
//	obj.push(0);
//	obj.push(3);
//	obj.push(0);
//	cout << obj.getMin() << endl;
//	obj.pop();
//	cout << obj.getMin() << endl;
//	obj.pop();
//	cout << obj.getMin() << endl;
//	obj.pop();
//	cout << obj.getMin() << endl;
//	obj.pop();
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