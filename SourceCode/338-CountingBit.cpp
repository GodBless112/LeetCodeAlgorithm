// static.cpp -- using a static local variable
#include <iostream>
#include<vector>
// constants
// function prototype
using namespace std;
class Solution {
public:
	vector<int> countBits(int num) {
		vector<int> result;
		result.push_back(0);
		int len = 0;
		int j = 0;
		for (int i = 1; i <= num; i++) {
			result.push_back(result.at(j) + 1);
			if (result.at(j) == len) {
				j = 0;
				len++;
				continue;
			}
			j++;
		}
		return result;
	}
};
int main(void)
{
	vector<int> result;
	Solution a;
	result = a.countBits(2);
	// code to keep window open for MSVC++
	cin.clear();
	while (cin.get() != '\n')
		continue;
	cin.get();

	return 0;
}
