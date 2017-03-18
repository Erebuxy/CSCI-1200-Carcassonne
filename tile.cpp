#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include "tile.h"


// Fill in characters for the ASCII art
#define ROAD_CHAR '#'
#define CITY_CHAR '.'


// ==========================================================================
// This global variable is set in main.cpp and is adjustable from the command line
// (you are not allowed to make your own global variables)
extern int GLOBAL_TILE_SIZE;


// ==========================================================================
// CONSTRUCTOR
// Takes in 4 strings, checks the legality of the labeling
Tile::Tile(const std::string &north, const std::string &east,
           const std::string &south, const std::string &west) :
  north_(north[0]), east_(east[0]), south_(south[0]), west_(west[0]), rotation(0) {

  // Check the input strings
  assert (north_ == 'c' || north_ == 'r' || north_ == 'p');
  assert (east_  == 'c' || east_  == 'r' || east_  == 'p');
  assert (south_ == 'c' || south_ == 'r' || south_ == 'p');
  assert (west_  == 'c' || west_  == 'r' || west_  == 'p');

  // Count the number of cities and roads
  num_cities = 0;
  if (north_ == 'c') num_cities++;
  if (south_ == 'c') num_cities++;
  if (east_ == 'c') num_cities++;
  if (west_ == 'c') num_cities++;
  num_roads = 0;
  if (north_ == 'r') num_roads++;
  if (south_ == 'r') num_roads++;
  if (east_ == 'r') num_roads++;
  if (west_ == 'r') num_roads++;

  // For our version of Carcassonne, we put these restrictions on the
  // tile edge labeling:
  if (num_roads == 1) {
    assert (num_cities == 0 || num_cities == 3);
  }
  if (num_roads == 2 && num_cities == 2) {
    assert (north_ == east_ || north_ == west_);
  }

  // Pre-compute the ASCII art center of the tile
  prepare_ascii_art();
}

// ==========================================================================
// Rotate the tile
void Tile::rotate(){
	// Rotate the tile 90 degree clockwise
	rotation = rotation + 90 - (rotation + 90)/360 *360;
	char n = north_, e = east_, s = south_, w = west_;
	north_ = w;
	east_ = n;
	south_ = e;
	west_ = s;
	prepare_ascii_art();
}


// ==========================================================================
// Print one row of the tile at a time
// (allows a whole board of tiles to be printed)
void Tile::printRow(std::ostream &ostr, int row) const {
  // Must be a legal row for this tile size
  assert (row >= 0 && row < GLOBAL_TILE_SIZE);

  if (row == 0 || row == GLOBAL_TILE_SIZE-1) {
    ostr << '+' << std::string(GLOBAL_TILE_SIZE-2,'-') << '+';
  } else {
    ostr << '|' << ascii_art[row-1] << '|';
  }
}


// ==========================================================================
// Long, messy, uninteresting function that prepares the inner block of ASCII
// art for the tile
void Tile::prepare_ascii_art() {

  // Tiles have to be odd sized
  assert (GLOBAL_TILE_SIZE % 2 == 1);
  // Tiles must be big enough to the ascii art is visible
  assert (GLOBAL_TILE_SIZE >= 11);

  // Helper variables
  int inner_size = GLOBAL_TILE_SIZE-2;
  int half = inner_size/2;
  int city_depth = (half+2) / 2;
  assert (city_depth >= 3);
  int road_curve = city_depth-1;
  ascii_art = std::vector<std::string>(inner_size,std::string(inner_size,' '));

  // -------------------------------------------------------------------
  // ROADS

  // Does a road go straight vertically or horizontally through the tile?
  bool center_road = false;
  if ((north_ == 'r' && south_ == 'r') ||
       (east_ == 'r' && west_ == 'r')) {
    center_road = true;
    ascii_art[half][half] = ROAD_CHAR;
  }

  // Construct the road fragments from edge towards the center of the tile
  if (north_ == 'r') {
    for (int i = 0; i < half-1; i++) {
      ascii_art[i][half] = ROAD_CHAR;
    }
    if (center_road) {
      ascii_art[half-1][half] = ROAD_CHAR;
    }
  }
  if (south_ == 'r') {
    for (int i = half+2; i < inner_size; i++) {
      ascii_art[i][half] = ROAD_CHAR;
    }
    if (center_road) {
        ascii_art[half+1][half] = ROAD_CHAR;
    }
  }
  if (west_ == 'r') {
    for (int i = 0; i < half-1; i++) {
      ascii_art[half][i] = ROAD_CHAR;
    }
    if (center_road) {
      ascii_art[half][half-1] = ROAD_CHAR;
    }
  }
  if (east_ == 'r') {
    for (int i = half+2; i < inner_size; i++) {
      ascii_art[half][i] = ROAD_CHAR;
    }
    if (center_road) {
      ascii_art[half][half+1] = ROAD_CHAR;
    }
  }

  // Construct the curved pieces of "corner" roads
  if (!center_road) {
    if (north_ == 'r' && east_ == 'r') {
      for (int c = 1; c < road_curve; c++) {
        ascii_art[half-c][half+road_curve-c] = ROAD_CHAR;
        ascii_art[half-c][half+road_curve-c] = ROAD_CHAR;
        ascii_art[half-c][half] = ' ';
        ascii_art[half][half+road_curve-c] = ' ';
      }
    }
    if (east_ == 'r' && south_ == 'r') {
      for (int c = 1; c < road_curve; c++) {
        ascii_art[half+c][half+road_curve-c] = ROAD_CHAR;
        ascii_art[half+c][half+road_curve-c] = ROAD_CHAR;
        ascii_art[half+c][half] = ' ';
        ascii_art[half][half+road_curve-c] = ' ';
      }
    }
    if (south_ == 'r' && west_ == 'r') {
      for (int c = 1; c < road_curve; c++) {
        ascii_art[half+c][half-road_curve+c] = ROAD_CHAR;
        ascii_art[half+c][half-road_curve+c] = ROAD_CHAR;
        ascii_art[half+c][half] = ' ';
        ascii_art[half][half-road_curve+c] = ' ';
      }
    }
    if (west_ == 'r' && north_ == 'r') {
      for (int c = 1; c < road_curve; c++) {
        ascii_art[half-c][half-road_curve+c] = ROAD_CHAR;
        ascii_art[half-c][half-road_curve+c] = ROAD_CHAR;
        ascii_art[half-c][half] = ' ';
        ascii_art[half][half-road_curve+c] = ' ';
      }
    }
  }


  // -------------------------------------------------------------------
  // CITIES
  // Construct the curved wedges of cities for each edge
  if (north_ == 'c') {
    int depth = city_depth;
    if (east_ == 'c' || west_ == 'c') {
      depth = half;
    }
    for (int i = 0; i < depth; i++) {
      for (int j = i+1; j < inner_size-i-1; j++) {
        ascii_art[i][j] = CITY_CHAR;
      }
    }
  }
  if (south_ == 'c') {
    int depth = city_depth;
    if (east_ == 'c' || west_ == 'c') {
      depth = half;
    }
    for (int i = 0; i < depth; i++) {
      for (int j = i+1; j < inner_size-i-1; j++) {
        ascii_art[GLOBAL_TILE_SIZE-3-i][j] = CITY_CHAR;
      }
    }
  }
  if (west_ == 'c') {
    int depth = city_depth;
    if (north_ == 'c' || south_ == 'c') {
      depth = half;
    }
    for (int i = 0; i < depth; i++) {
      for (int j = i+1; j < inner_size-i-1; j++) {
        ascii_art[j][i] = CITY_CHAR;
      }
    }
  }
  if (east_ == 'c') {
    int depth = city_depth;
    if (north_ == 'c' || south_ == 'c') {
      depth = half;
    }
    for (int i = 0; i < depth; i++) {
      for (int j = i+1; j < inner_size-i-1; j++) {
        ascii_art[j][GLOBAL_TILE_SIZE-3-i] = CITY_CHAR;
      }
    }
  }

  // If there are at least 3 wedges of city, fill in the middle as city
  if (num_cities >= 3) {
    for (int i = city_depth; i < inner_size-city_depth; i++) {
      for (int j = city_depth; j < inner_size-city_depth; j++) {
        ascii_art[i][j] = CITY_CHAR;
      }
    }
  }

  // If there are 2 neighboring wedges of city, fill in the gap
  if (north_ == 'c' && west_ == 'c') {
    for (int i = 0; i < half; i++) {
      ascii_art[i][i] = CITY_CHAR;
    }
  }
  if (north_ == 'c' && east_ == 'c') {
    for (int i = 0; i < half; i++) {
      ascii_art[i][GLOBAL_TILE_SIZE-3-i] = CITY_CHAR;
    }
  }
  if (south_ == 'c' && west_ == 'c') {
    for (int i = 0; i < half; i++) {
      ascii_art[GLOBAL_TILE_SIZE-3-i][i] = CITY_CHAR;
    }
  }
  if (south_ == 'c' && east_ == 'c') {
    for (int i = 0; i < half; i++) {
      ascii_art[GLOBAL_TILE_SIZE-3-i][GLOBAL_TILE_SIZE-3-i] = CITY_CHAR;
    }
  }

  // -------------------------------------------------------------------
  // DRAW THE ABBEY BUILDING
  if (hasAbbey()) {
    ascii_art[half-2][half] = '^';
    ascii_art[half-1][half-1] = '/';
    ascii_art[half-1][half  ] = ' ';
    ascii_art[half-1][half+1] = '\\';
    ascii_art[half  ][half-2] = '/';
    ascii_art[half  ][half-1] = '|';
    ascii_art[half  ][half  ] = ' ';
    ascii_art[half  ][half+1] = '|';
    ascii_art[half  ][half+2] = '\\';
    ascii_art[half+1][half-1] = '|';
    ascii_art[half+1][half  ] = ' ';
    ascii_art[half+1][half+1] = '|';
    ascii_art[half+2][half-1] = '+';
    ascii_art[half+2][half  ] = '-';
    ascii_art[half+2][half+1] = '+';
  }
}

// ==========================================================================
