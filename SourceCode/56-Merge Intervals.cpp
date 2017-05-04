//	56. Merge Intervals
//------------------------------------------------------------------------------//
//	Given a collection of intervals, merge all overlapping intervals.			//
//	For example,																//
//	Given[1, 3], [2, 6], [8, 10], [15, 18],										//
//	return[1, 6], [8, 10], [15, 18].											//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<unordered_map>
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
bool operator<(const Interval &I1, const Interval &I2)
{
	return I1.start < I2.start;
}
//思路：先将interval按起点升序排序，然后从左往右依次合并
class Solution 
{
public:
	vector<Interval> merge(vector<Interval>& intervals) 
	{
		if (intervals.size() < 2)
			return intervals;
		vector<Interval> result;
		sort(intervals.begin(), intervals.end());
		Interval mergeInterval = intervals[0];
		for (int i = 1; i < intervals.size(); i++)
		{
			if (intervals[i].start <= mergeInterval.end)
				mergeInterval.end = max(intervals[i].end, mergeInterval.end);
			else
			{
				result.push_back(mergeInterval);
				mergeInterval = intervals[i];
			}
		}
		result.push_back(mergeInterval);
		return result;
	}
};
//插入的方法
class Solution2 {
public:
	vector<Interval> merge(vector<Interval> &intervals) {
		vector<Interval> result;
		for (int i = 0; i < intervals.size(); i++) {
			insert(result, intervals[i]);
		}
		return result;
	}
private:
	vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
		vector<Interval>::iterator it = intervals.begin();
		while (it != intervals.end()) {
			if (newInterval.end < it->start) {
				intervals.insert(it, newInterval);
				return intervals;
			}
			else if (newInterval.start > it->end) {
				it++;
				continue;
			}
			else {
				newInterval.start = min(newInterval.start, it->start);
				newInterval.end = max(newInterval.end, it->end);
				it = intervals.erase(it);
			}
		}
		intervals.insert(intervals.end(), newInterval);
		return intervals;
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<Interval> a = { {1,4},{2,3} };
//	auto x = test.merge(a);
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
