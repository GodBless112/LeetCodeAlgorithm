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
				if (sudoku.find(board[i][j]) == sudoku.end())
					sudoku.insert(board[i][j]);
				else
					return false;
			}
			sudoku.clear();
			//check every column
			for (int j = 0; j < 9; j++)
			{
				if (sudoku.find(board[j][i]) == sudoku.end())
					sudoku.insert(board[j][i]);
				else
					return false;
			}
			sudoku.clear();
			//check every subboxes
			int row = (i / 3) * 3;
			int col = (i % 3) * 3;
			for (int m = row; m < row + 3; row++)
			{
				for (int n = col; n < col + 3; n++)
				{
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
int main(void)
{
	Solution test;
	vector<int> a({ 1,2});
	
	cout << x;

	// code to keep window open for MSVC++
	cin.clear();
	while (cin.get() != '\n')
		continue;
	cin.get();

	return 0;
}
