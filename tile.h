#ifndef  __TILE_H__
#define __TILE_H__

#include <iostream>
#include <string>
#include <vector>


// This class represents a single Carcassonne tile and includes code
// to produce a human-readable ASCII art representation of the tile.

class Tile {
public:

  // Constructor takes in 4 strings, representing what is on the edge
  // of each tile.  Each edge string is "pasture", "road", or "city".
  Tile(const std::string &north, const std::string &east, const std::string &south, const std::string &west);

  // ACCESSORS
  const char& getNorth() const { return north_; }
  const char& getSouth() const { return south_; }
  const char& getEast() const { return east_; }
  const char& getWest() const { return west_; }
  int numCities() const { return num_cities; }
  int numRoads() const { return num_roads; }
  int hasAbbey() const { return (num_cities == 0 && num_roads <= 1); }

  // MODIFIERS
  void rotate();

  // for ASCII art printing
  void printRow(std::ostream &ostr, int i) const;

private:

  // helper function called by the constructor for printing
  void prepare_ascii_art();

  // REPRESENTATION
  char north_;
  char east_;
  char south_;
  char west_;
  int num_roads;
  int num_cities;
  int rotation;
  std::vector<std::string> ascii_art;
};


#endif
