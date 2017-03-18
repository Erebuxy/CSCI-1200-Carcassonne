#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "board.h"


// this global variable is set in main.cpp and is adjustable from the command line
// (you are not allowed to make your own global variables)
extern int GLOBAL_TILE_SIZE;


// ==========================================================================
// CONSTRUCTOR
Board::Board(int i, int j) {
  board = std::vector<std::vector<Tile*> >
    ( (unsigned int)i,
      std::vector<Tile*>((unsigned int)j,NULL) );
}


// ==========================================================================
// ACCESSORS
Tile* Board::getTile(int i, int j) const {
  assert (i >= 0 && i < numRows());
  assert (j >= 0 && j < numColumns());
  return board[i][j];
}

void Board::begin_end(int &r_beg, int &r_end, int &c_beg, int &c_end) const{
	// Find the actual beginning and end of the board
	r_beg = 1, r_end = numRows()-1, c_beg = 1, c_end = numColumns()-1;
	// Find the first row
	for (int r = 1; r < numRows()-1; r++){
		bool empty = true;
		for (int c = 1; c < numColumns()-1; c++){
			if (board[r][c] != NULL){
				empty = false;
				break;
			}
		}
		if (empty)
			r_beg++;
		else
			break;
	}
	// Find the last row
	for (int r = numRows()-2; r > 0; r--){
		bool empty = true;
		for (int c = 1; c < numColumns()-1; c++){
			if (board[r][c] != NULL){
				empty = false;
				break;
			}
		}
		if (empty)
			r_end--;
		else
			break;
	}
	// Find the first column
	for (int c = 1; c < numColumns()-1; c++){
		bool empty = true;
		for (int r = 1; r < numRows()-1; r++){
			if (board[r][c] != NULL){
				empty = false;
				break;
			}
		}
		if (empty)
			c_beg++;
		else
			break;
	}
	// Find the last column
	for (int c = numColumns()-2; c > 0; c--){
		bool empty = true;
		for (int r = 1; r < numRows()-1; r++){
			if (board[r][c] != NULL){
				empty = false;
				break;
			}
		}
		if (empty)
			c_end--;
		else
			break;
	}
}

// ==========================================================================
// MODIFIERS
void Board::setTile(int i, int j, Tile* t) {
  assert (i >= 0 && i < numRows());
  assert (j >= 0 && j < numColumns());
  assert (t != NULL);
  assert (board[i][j] == NULL);
  board[i][j] = t;
}

void Board::setNULL(int i, int j) {
  assert (i >= 0 && i < numRows());
  assert (j >= 0 && j < numColumns());
  board[i][j] = NULL;
}

// ==========================================================================
// PRINTING
void Board::Print() const {
  for (int b = 0; b < numRows(); b++) {
    for (int i = 0; i < GLOBAL_TILE_SIZE; i++) {
      for (int j = 0; j < numColumns(); j++) {
        if (board[b][j] != NULL) {
          board[b][j]->printRow(std::cout,i);
        } else {
          std::cout << std::string(GLOBAL_TILE_SIZE,' ');
        }
      }
      std::cout << "\n";
    }
  }
  fflush(stdout);
}

void Board::PrintSmall() const{
	// Find the actual beginning and end of the board
	int r_beg, r_end, c_beg, c_end;
	begin_end(r_beg, r_end, c_beg, c_end);
	// Print the board
	for (int b = r_beg; b < r_end; b++){
		for (int i = 0; i < GLOBAL_TILE_SIZE; i++){
			for (int j = c_beg; j < c_end; j++){
				if (board[b][j] != NULL){
					board[b][j]->printRow(std::cout,i);
				}
				else {
					std::cout << std::string(GLOBAL_TILE_SIZE,' ');
				}
			}
			std::cout << "\n";
		}
	}
  fflush(stdout);
}
// ==========================================================================
