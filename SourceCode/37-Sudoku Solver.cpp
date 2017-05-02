//	37. Sudoku Solver
//------------------------------------------------------------------------------//
//	Write a program to solve a Sudoku puzzle by filling the empty cells.		//
//	Empty cells are indicated by the character '.'.								//
//	You may assume that there will be only one unique solution.					//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
#include<unordered_set>
#include<bitset>
#include<array>
#include<assert.h>
#include<functional>
// constants
// function prototype
using namespace std;
//回溯法，哈希表
class Solution 
{
public:
	bool solveSudoku(vector<vector<char> > &board) 
	{
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j) 
			{
				if (board[i][j] == '.') 
				{
					for (int k = 0; k < 9; ++k) 
					{
						board[i][j] = '1' + k;
						if (isValid(board, i, j) && solveSudoku(board))
							return true;
						board[i][j] = '.';
					}
					return false;
				}
			}
		return true;
	}
private:
	// 􁷯􁴔 (x, y) 􁭞􀥕􀤷􂈄
	bool isValid(const vector<vector<char> > &board, int x, int y) 
	{
		int i, j;
		for (i = 0; i < 9; i++) // 􁷯􁴔 y 􀝆
			if (i != x && board[i][y] == board[x][y])
				return false;
		for (j = 0; j < 9; j++) // 􁷯􁴔 x 􃵻
			if (j != y && board[x][j] == board[x][y])
				return false;
		for (i = 3 * (x / 3); i < 3 * (x / 3 + 1); i++)
			for (j = 3 * (y / 3); j < 3 * (y / 3 + 1); j++)
				if ((i != x || j != y) && board[i][j] == board[x][y])
					return false;
		return true;
	}
};
//超快算法
class Solution2 {
	struct cell // encapsulates a single cell on a Sudoku board
	{
		uint8_t value; // cell value 1..9 or 0 if unset
					   // number of possible (unconstrained) values for the cell
		uint8_t numPossibilities;
		// if bitset[v] is 1 then value can't be v
		bitset<10> constraints;
		cell() : value(0), numPossibilities(9), constraints() {};
	};
	array<array<cell, 9>, 9> cells;

	// sets the value of the cell to [v]
	// the function also propagates constraints to other cells and deduce new values where possible
	bool set(int i, int j, int v)
	{
		// updating state of the cell
		cell& c = cells[i][j];
		if (c.value == v)
			return true;
		if (c.constraints[v])
			return false;
		c.constraints = bitset<10>(0x3FE); // all 1s
		c.constraints.reset(v);
		c.numPossibilities = 1;
		c.value = v;

		// propagating constraints
		for (int k = 0; k<9; k++) {
			// to the row: 
			if (i != k && !updateConstraints(k, j, v))
				return false;
			// to the column:
			if (j != k && !updateConstraints(i, k, v))
				return false;
			// to the 3x3 square:
			int ix = (i / 3) * 3 + k / 3;
			int jx = (j / 3) * 3 + k % 3;
			if (ix != i && jx != j && !updateConstraints(ix, jx, v))
				return false;
		}
		return true;
	}
	// update constraints of the cell i,j by excluding possibility of 'excludedValue'
	// once there's one possibility left the function recurses back into set()
	bool updateConstraints(int i, int j, int excludedValue)
	{
		cell& c = cells[i][j];
		if (c.constraints[excludedValue]) {
			return true;
		}
		if (c.value == excludedValue) {
			return false;
		}
		c.constraints.set(excludedValue);
		if (--c.numPossibilities > 1)
			return true;
		for (int v = 1; v <= 9; v++) {
			if (!c.constraints[v]) {
				return set(i, j, v);
			}
		}
		assert(false);
	}

	// backtracking state - list of empty cells
	vector<pair<int, int>> bt;

	// find values for empty cells
	bool findValuesForEmptyCells()
	{
		// collecting all empty cells
		bt.clear();
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (!cells[i][j].value)
					bt.push_back(make_pair(i, j));
			}
		}
		// making backtracking efficient by pre-sorting empty cells by numPossibilities
		sort(bt.begin(), bt.end(), [this](const pair<int, int>&a, const pair<int, int>&b) {
			return cells[a.first][a.second].numPossibilities < cells[b.first][b.second].numPossibilities; });
		return backtrack(0);
	}

	// Finds value for all empty cells with index >=k
	bool backtrack(int k)
	{
		if (k >= bt.size())
			return true;
		int i = bt[k].first;
		int j = bt[k].second;
		// fast path - only 1 possibility
		if (cells[i][j].value)
			return backtrack(k + 1);
		auto constraints = cells[i][j].constraints;
		// slow path >1 possibility.
		// making snapshot of the state
		array<array<cell, 9>, 9> snapshot(cells);
		for (int v = 1; v <= 9; v++) {
			if (!constraints[v]) {
				if (set(i, j, v)) {
					if (backtrack(k + 1))
						return true;
				}
				// restoring from snapshot,
				// note: computationally this is cheaper
				// than alternative implementation with undoing the changes
				cells = snapshot;
			}
		}
		return false;
	}
public:
	void solveSudoku(vector<vector<char>> &board) {
		cells = array<array<cell, 9>, 9>(); // clear array
											// Decoding input board into the internal cell matrix.
											// As we do it - constraints are propagated and even additional values are set as we go
											// (in the case if it is possible to unambiguously deduce them).
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++) {
				if (board[i][j] != '.' && !set(i, j, board[i][j] - '0'))
					return; // sudoku is either incorrect or unsolvable
			}
		}
		// if we're lucky we've already got a solution,
		// however, if we have empty cells we need to use backtracking to fill them
		if (!findValuesForEmptyCells())
			return; // sudoku is unsolvable

					// copying the solution back to the board
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++) {
				if (cells[i][j].value)
					board[i][j] = cells[i][j].value + '0';
			}
		}
	}
};
//
class Solution3 {
	// Table which allows compute the value of the cell
	// from the unambiguous bit mask as maskToValue[(mask%11)-1] 
	// uses the fact that (1<<i)%11 is unique for i = [0..8] and never produces 0
	const char maskToValue[10] = { '1','2','9','3','5','6','8','4','7','6' };
	struct SudokuSolver {
		// Using mask for each cell which constraints values which can be in the cell
		// Yeap, it is more storage, comparing to rows/cols/sqrs approach
		// but it allows to do super-fast reactive constraint propagation
		array<array<uint16_t, 9>, 9> board;
		SudokuSolver()
		{
			// Initializing the board with mask, which permits all numbers
			for (int i = 0; i<9; i++)
				for (int j = 0; j<9; j++)
					board[i][j] = 0x1ff;
		}

		// adds value v [1..9] to the board, return false if it violates constraints
		bool add(int i, int j, int v)
		{
			return set(i, j, 1 << (v - 1));
		}

		// set a value mask to the cell (i,j) and reactively updates constraints
		bool set(int i, int j, uint16_t mask)
		{
			int16_t prev = board[i][j];
			if (prev == mask) return true;
			if (!(prev&mask)) return false;
			board[i][j] = mask;
			return propagate(i, j, mask);
		}

		// propagates constraints as a result of setting i,j to mask
		bool propagate(int i, int j, uint16_t mask)
		{
			for (int k = 0; k<9; k++) {
				if (k != j && !addConstraint(i, k, mask)) return false;
				if (k != i && !addConstraint(k, j, mask)) return false;
				int ii = (i / 3) * 3 + (k / 3);
				int jj = (j / 3) * 3 + (k % 3);
				if ((i != ii || j != jj) && !addConstraint(ii, jj, mask)) return false;
			}
			return true;
		}

		// prohibits putting value in mask to the cell (i,j)
		bool addConstraint(int i, int j, uint16_t mask)
		{
			int16_t newMask = board[i][j] & ~mask;
			if (newMask != board[i][j]) {
				if (newMask == 0) return false;
				board[i][j] = newMask;
				if (((newMask - 1)&newMask) == 0) {
					// good news - we have only one possibility for the cell (i,j)
					return propagate(i, j, newMask);
				}
			}
			return true;
		}

		// list of cell coordinates with >1 possibilities for values
		vector<pair<int, int>> v;
		void solve()
		{
			// finding all ambiguous cells
			for (int i = 0; i<9; i++) {
				for (int j = 0; j<9; j++) {
					uint16_t mask = board[i][j];
					if (mask&(mask - 1)) v.push_back(make_pair(i, j));
				}
			}
			// note: it is also a good idea to sort v by the hamming weight, but
			// without sorting it is still super-fast
			// running backtracking as is
			backtrack(0);
		}

		// backtracking        
		bool backtrack(int k) {
			if (k == v.size()) return true;
			int i = v[k].first;
			int j = v[k].second;
			uint16_t mask = board[i][j];
			if (mask&(mask - 1)) {
				// the board state is so compact and backtracking depth is so shallow, so
				// it is cheaper to make a snapshot of the state vs. doing classical
				// undo at each move
				auto snapshot = board;
				for (uint16_t cand = 1; cand <= 0x1ff; cand = cand << 1) {
					if (set(i, j, cand) && backtrack(k + 1)) return true;
					board = snapshot;
				}
				return false;
			}
			else {
				return backtrack(k + 1);
			}
		}

	};

public:
	void solveSudoku(vector<vector<char>>& board) {
		SudokuSolver solver;
		for (int i = 0; i<9; i++) {
			for (int j = 0; j<9; j++) {
				char c = board[i][j];
				if (c != '.' && !solver.add(i, j, c - '0')) return;
			}
		}
		// At this point 9 of 10 sudokus published in magazines will be solved by constraint propagation
		// only 'hard' sudokus will require some (limited) backtracking 
		solver.solve();
		for (int i = 0; i<9; i++)
			for (int j = 0; j<9; j++)
				board[i][j] = maskToValue[(solver.board[i][j] % 11) - 1];
	}
};
//DFS
class Solution4 
{
public:
	bool col[10][10], row[10][10], f[10][10];
	bool flag = false;
	void solveSudoku(vector<vector<char>>& board) 
	{
		memset(col, false, sizeof(col));
		memset(row, false, sizeof(row));
		memset(f, false, sizeof(f));
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (board[i][j] == '.')   continue;
				int temp = 3 * (i / 3) + j / 3;
				int num = board[i][j] - '0';
				col[j][num] = row[i][num] = f[temp][num] = true;
			}
		}
		dfs(board, 0, 0);
	}
	void dfs(vector<vector<char>>& board, int i, int j) {
		if (flag == true)  return;
		if (i >= 9) {
			flag = true;
			return;
		}
		if (board[i][j] != '.') {
			if (j < 8)  dfs(board, i, j + 1);
			else dfs(board, i + 1, 0);
			if (flag)  return;
		}

		else 
		{
			int temp = 3 * (i / 3) + j / 3;
			for (int n = 1; n <= 9; n++) 
			{
				if (!col[j][n] && !row[i][n] && !f[temp][n]) 
				{
					board[i][j] = n + '0';
					col[j][n] = row[i][n] = f[temp][n] = true;
					if (j < 8)  dfs(board, i, j + 1);
					else dfs(board, i + 1, 0);
					col[j][n] = row[i][n] = f[temp][n] = false;
					if (flag)  return;
				}
			}
			board[i][j] = '.';
		}
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
//	test.solveSudoku(x);
//
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
