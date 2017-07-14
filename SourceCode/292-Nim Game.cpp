//	292. Nim Game
//------------------------------------------------------------------------------//
//	You are playing the following Nim Game with your friend: There is a heap of //
//	stones on the table, each time one of you take turns to remove 1 to 3		//
//	stones. The one who removes the last stone will be the winner. You will		//
//	take the first turn to remove the stones.									//
//	Both of you are very clever and have optimal strategies for the game.Write	//
//	a function to determine whether you can win the game given the number of	//
//	stones in the heap.															//
//	For example, if there are 4 stones in the heap, then you will never win		//
//	the game : no matter 1, 2, or 3 stones you remove, the last stone will		//
//	always be removed by your friend.											//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>

// constants
// function prototype
using namespace std;
//只要是4的倍数，必输，如果不是4的倍数，先拿掉一部分变成4的倍数，必赢
class Solution {
public:
	bool canWinNim(int n) {
		return n % 4 > 0;
	}
};
class Solution2 {
public:
	bool canWinNim(int n) {
		return (n & 0x03) != 0;
	}
};
//int main(void)
//{
//	Solution2 test;
//	for (int i = 1; i < 10; ++i)
//		cout << i << " " << boolalpha << test.canWinNim(i) << endl;
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