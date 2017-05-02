//	36. Valid Sudoku
//------------------------------------------------------------------------------//
//	Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.	//
//	The Sudoku board could be partially filled, where empty cells are filled	//
//	with the character '.'.														//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
#include<unordered_set>
#include<list>
#include<functional>
// constants
// function prototype
using namespace std;
//哈希表
class Solution 
{
public:
	bool isValidSudoku(vector<vector<char>>& board) 
	{
		unordered_set<char> sudoku;	
		for (int i = 0; i < 9; i++)
		{
			//check every row
			for (int j = 0; j < 9; j++)
			{
				if (board[i][j] == '.')
					continue;
				if (sudoku.find(board[i][j]) == sudoku.end())
					sudoku.insert(board[i][j]);
				else
					return false;
			}
			sudoku.clear();
			//check every column
			for (int j = 0; j < 9; j++)
			{
				if (board[j][i] == '.')
					continue;
				if (sudoku.find(board[j][i]) == sudoku.end())
					sudoku.insert(board[j][i]);
				else
					return false;
			}
			sudoku.clear();
			//check every subboxes
			int row = (i / 3) * 3;
			int col = (i % 3) * 3;
			for (int m = row; m < row + 3; m++)
			{
				for (int n = col; n < col + 3; n++)
				{
					if (board[m][n] == '.')
						continue;
					if (sudoku.find(board[m][n]) == sudoku.end())
						sudoku.insert(board[m][n]);
					else
						return false;
				}
			}
			sudoku.clear();
		}
		return true;
	}
};
//
class Solution2 
{
public:
	bool isValidSudoku(const vector<vector<char>>& board) 
	{
		bool used[9];
		for (int i = 0; i < 9; ++i) {
			fill(used, used + 9, false);
			for (int j = 0; j < 9; ++j)
				if (!check(board[i][j], used))
					return false;
			fill(used, used + 9, false);
			for (int j = 0; j < 9; ++j)
				if (!check(board[j][i], used))
					return false;
		}
		for (int r = 0; r < 3; ++r)
			for (int c = 0; c < 3; ++c) {
				fill(used, used + 9, false);
				for (int i = r * 3; i < r * 3 + 3; ++i)
					for (int j = c * 3; j < c * 3 + 3; ++j)
						if (!check(board[i][j], used))
							return false;
			}
		return true;
	}
	bool check(char ch, bool used[9]) {
		if (ch == '.') return true;
		if (used[ch - '1']) return false;
		return used[ch - '1'] = true;
	}
};
//int main(void)
//{
//	Solution2 test;
//	char a[10][10] = { "..5.....6","....14...",".........",".....92..","5....2...",".......3.","...54....","3.....42.","...27.6.." };
//	vector<vector<char>> x;
//	for (int i = 0; i < 9; i++)
//	{
//		vector<char> y;
//		for (int j = 0; j < 9; j++)
//		{
//			y.push_back(a[i][j]);
//		}
//		x.push_back(y);
//	}
//	
//	cout << test.isValidSudoku(x) << endl;
//
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
