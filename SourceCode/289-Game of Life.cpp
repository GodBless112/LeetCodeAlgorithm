//	289. Game of Life
//------------------------------------------------------------------------------//
//	According to the Wikipedia's article: "The Game of Life, also known simply	//
//	as Life, is a cellular automaton devised by the British mathematician John	//
//	Horton Conway in 1970."														//
//	Given a board with m by n cells, each cell has an initial state live(1) or	//
//	dead(0).Each cell interacts with its eight neighbors(horizontal, vertical,	//
//	diagonal) using the following four rules(taken from the above Wikipedia		//
//	article) :																	//
//		1.Any live cell with fewer than two live neighbors dies, as if caused	//
//		by under - population.													//
//		2.Any live cell with two or three live neighbors lives on to the next	//
//		generation.																//
//		3.Any live cell with more than three live neighbors dies, as if by		//
//		over - population..														//
//		4.Any dead cell with exactly three live neighbors becomes a live cell,	//
//		as if by reproduction.													//
//	Write a function to compute the next state(after one update) of the board	//
//	given its current state.													//
//	Follow up :																	//
//		1.Could you solve it in - place ? Remember that the board needs to be	//
//	updated at the same time : You cannot update some cells first and then use	//
//	their updated values to update other cells.									//
//		2.In this question, we represent the board using a 2D array.In			//
//	principle, the board is infinite, which would cause problems when the		//
//	active area encroaches the border of the array.How would you address these	//
//	problems ?																	//
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
//位运算的方法，用高位来保存下一次的结果，就地运算
class Solution {
public:
	void gameOfLife(vector<vector<int>>& board) {
		int m = board.size();
		if (m == 0) return;
		int n = board[0].size();
		int dx[] = { 1,1,1,0,0,-1,-1,-1 };
		int	dy[] = { 1,0,-1,1,-1,1,0,-1 };
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				int lives = 0;
				for (int k = 0; k < 8; ++k) {
					int x = i + dx[k];
					int y = j + dy[k];
					lives += getCellStatus(board, x, y);
				}
				if (lives + board[i][j] == 3 || lives == 3)
					board[i][j] |= 2;
			}
		}
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				board[i][j] >>= 1;
	}
private:
	int getCellStatus(vector<vector<int>>& board, int x, int y) {
		if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size())
			return 0;
		return board[x][y] & 1;
	}
};
//用另一个数组来存储下一次的结果
class Solution2 {
public:
	void gameOfLife(vector<vector<int>>& board) {
		int m = board.size();
		if (m == 0) return;
		int n = board[0].size();
		vector<vector<int>> next(m, vector<int>(n));
		int dx[] = { 1,1,1,0,0,-1,-1,-1 };
		int	dy[] = { 1,0,-1,1,-1,1,0,-1 };
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				int lives = 0;
				for (int k = 0; k < 8; ++k) {
					int x = i + dx[k];
					int y = j + dy[k];
					lives += getCellStatus(board, x, y);
				}
				if (lives + board[i][j] == 3 || lives == 3)
					next[i][j] = 1;
			}
		}
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				board[i][j] = next[i][j];
	}
private:
	int getCellStatus(vector<vector<int>>& board, int x, int y) {
		if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size())
			return 0;
		return board[x][y];
	}
};
class Solution3 {
public:
	void gameOfLife(vector<vector<int>>& board) {
		int m = board.size(), n = m ? board[0].size() : 0;
		for (int i = 0; i<m; ++i) {
			for (int j = 0; j<n; ++j) {
				int count = 0;
				for (int I = max(i - 1, 0); I<min(i + 2, m); ++I)
					for (int J = max(j - 1, 0); J<min(j + 2, n); ++J)
						count += board[I][J] & 1;
				if (count == 3 || count - board[i][j] == 3)
					board[i][j] |= 2;
			}
		}
		for (int i = 0; i<m; ++i)
			for (int j = 0; j<n; ++j)
				board[i][j] >>= 1;
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<vector<int>> board{ {1,1,1},{1,0,1},{1,1,1} };
//	for (auto x : board) {
//		for (auto y : x)
//			cout << y << " ";
//		cout << endl;
//	}
//	test.gameOfLife(board);
//	for (auto x : board) {
//		for (auto y : x)
//			cout << y << " ";
//		cout << endl;
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