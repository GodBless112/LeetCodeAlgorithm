//	190. Reverse Bits
//------------------------------------------------------------------------------//
//	Reverse bits of a given 32 bits unsigned integer.							//
//	For example, given input 43261596 (represented in binary as					//
//	00000010100101000001111010011100), return 964176192 (represented in binary	//
//	as 00111001011110000010100101000000).										//
//	Follow up :																	//
//	If this function is called many times, how would you optimize it ?			//
//	Related problem : Reverse Integer 											//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<ctime>
// constants
// function prototype
using namespace std;
//直接移位
class Solution {
public:
	uint32_t reverseBits(uint32_t n) {
		uint32_t result = 0;
		for (int i = 0; i < 32; ++i, n >>= 1) {
			result <<= 1;
			result |= n & 1;
		}
		return result;
	}
};
//另一种直接移位
class Solution2 {
public:
	uint32_t reverseBits(uint32_t n) {
		uint32_t result = 0;
		for (int i = 0; i < 32; ++i, n >>= 1)
			result |= (n & 0x01) << (32 - i - 1);
		return result;
	}
};
//先交换16位，然后交换8位，4位，。。。直至1位
class Solution3 {
public:
	uint32_t reverseBits(uint32_t n) {
		n = (n >> 16) | (n << 16);
		n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
		n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
		n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
		n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
		return n;
	}
};
//利用结构体的特性，位图法
class Solution4 {
public:
	uint32_t reverseBits(uint32_t n) {
		struct bs
		{
			unsigned int _00 : 1; unsigned int _01 : 1; unsigned int _02 : 1; unsigned int _03 : 1;
			unsigned int _04 : 1; unsigned int _05 : 1; unsigned int _06 : 1; unsigned int _07 : 1;
			unsigned int _08 : 1; unsigned int _09 : 1; unsigned int _10 : 1; unsigned int _11 : 1;
			unsigned int _12 : 1; unsigned int _13 : 1; unsigned int _14 : 1; unsigned int _15 : 1;
			unsigned int _16 : 1; unsigned int _17 : 1; unsigned int _18 : 1; unsigned int _19 : 1;
			unsigned int _20 : 1; unsigned int _21 : 1; unsigned int _22 : 1; unsigned int _23 : 1;
			unsigned int _24 : 1; unsigned int _25 : 1; unsigned int _26 : 1; unsigned int _27 : 1;
			unsigned int _28 : 1; unsigned int _29 : 1; unsigned int _30 : 1; unsigned int _31 : 1;
		} *b = (bs*)&n,
			c =
		{
			b->_31, b->_30, b->_29, b->_28
			, b->_27, b->_26, b->_25, b->_24
			, b->_23, b->_22, b->_21, b->_20
			, b->_19, b->_18, b->_17, b->_16
			, b->_15, b->_14, b->_13, b->_12
			, b->_11, b->_10, b->_09, b->_08
			, b->_07, b->_06, b->_05, b->_04
			, b->_03, b->_02, b->_01, b->_00
		};

		return *(unsigned int *)&c;
	}
};
//int main(void)
//{
//	Solution4 test;
//	cout << test.reverseBits(43261596);
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//	
//	return 0;
//}