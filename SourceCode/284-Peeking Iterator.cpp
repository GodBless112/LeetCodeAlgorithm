//	284. Peeking Iterator
//------------------------------------------------------------------------------//
//	Given an Iterator class interface with methods: next() and hasNext(),		//
//	design and implement a PeekingIterator that support the peek() operation -- //
//	it essentially peek() at the element that will be returned by the next call //
//	to next().																	//
//	Here is an example.Assume that the iterator is initialized to the beginning //
//	of the list : [1, 2, 3].													//
//	Call next() gets you 1, the first element in the list.						//
//	Now you call peek() and it returns 2, the next element.Calling next() after //
//	that still return 2.														//
//	You call next() the final time and it returns 3, the last element.Calling	//
//	hasNext() after that should return false.									//
//	Follow up : How would you extend your design to be generic and work with	//
//	all types, not just integer ?												//
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
// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
	struct Data;
	Data* data;
public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
	virtual ~Iterator();
	// Returns the next element in the iteration.
	int next();
	// Returns true if the iteration has more elements.
	bool hasNext() const;
};

//利用Iterator的复制构造函数，在peek的时候重新生成一个
class PeekingIterator : public Iterator {
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
		// Initialize any member here.
		// **DO NOT** save a copy of nums and manipulate it directly.
		// You should only use the Iterator interface methods.

	}

	// Returns the next element in the iteration without advancing the iterator.
	int peek() {
		return Iterator(*this).next();
	}

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
		return Iterator::next();
	}

	bool hasNext() const {
		return Iterator::hasNext();
	}
};
//cache当前的next状态和值，在next的时候更新当前的状态
class PeekingIterator2 : public Iterator {
public:
	PeekingIterator2(const vector<int>& nums) : Iterator(nums) {
		// Initialize any member here.
		// **DO NOT** save a copy of nums and manipulate it directly.
		// You should only use the Iterator interface methods.
		m_hasNext = Iterator::hasNext();
		if (m_hasNext) m_Next = Iterator::next();
	}

	// Returns the next element in the iteration without advancing the iterator.
	int peek() {
		return m_Next;
	}

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
		int temp = m_Next;
		m_hasNext = Iterator::hasNext();
		if (m_hasNext) m_Next = Iterator::next();
		return temp;
	}

	bool hasNext() const {
		return m_hasNext;
	}
private:
	bool m_hasNext;
	int m_Next;
};
//另一种缓存的方法
class PeekingIterator3 : public Iterator {
	bool hasPeeked;
	int peekedElem;
public:
	PeekingIterator3(const vector<int>& num) : Iterator(num) {
		hasPeeked = false;
	}

	int peek() {
		peekedElem = hasPeeked ? peekedElem : Iterator::next();
		hasPeeked = true;
		return peekedElem;
	}

	int next() {
		int nextElem = hasPeeked ? peekedElem : Iterator::next();
		hasPeeked = false;
		return nextElem;
	}

	bool hasNext() const {
		return hasPeeked || Iterator::hasNext();
	}
};
//int main(void)
//{
//	
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