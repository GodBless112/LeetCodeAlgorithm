//	57. Insert Interval
//------------------------------------------------------------------------------//
//	Given a set of non-overlapping intervals, insert a new interval into the	//
//	intervals (merge if necessary).												//
//	You may assume that the intervals were initially sorted according to their	//
//	start times.																//
//	Example 1:																	//
//		Given intervals[1, 3], [6, 9], insert and merge[2, 5] in as[1, 5],		//
//		[6, 9].																	//
//	Example 2 :																	//
//		Given[1, 2], [3, 5], [6, 7], [8, 10], [12, 16], insert and merge[4, 9]	//
//		in as[1, 2], [3, 10], [12, 16].											//
//	This is because the new interval[4, 9] overlaps with[3, 5], [6, 7], [8, 10].//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
// constants
// function prototype
using namespace std;

struct Interval 
{
	int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution 
{
public:
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) 
	{
		auto itr = intervals.begin();
		while (itr != intervals.end())
		{
			if (newInterval.end < itr->start)
			{
				intervals.insert(itr, newInterval);
				return intervals;
			}
			else if (newInterval.start > itr->end)
				itr++;
			else
			{
				newInterval.start = min(newInterval.start, itr->start);
				newInterval.end = max(newInterval.end, itr->end);
				itr = intervals.erase(itr);
			}
		}
		intervals.insert(intervals.end(), newInterval);
		return intervals;
	}
};
//int main(void)
//{
//	Solution test;
//	vector<Interval> a = { {1,3},{6,9} };
//	Interval b({ 2,5 });
//	auto x = test.insert(a, b);
//	for (auto y : x)
//	{
//		cout << "[" << y.start << "," << y.end << "]" << ", ";
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
