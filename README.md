# DS_Carcassonne
RPI CSCI-1200 Data Structures, Fall 2014/Spring 2015, Homework 6 - Carcassonne Recursion <br />
By Erebuxy

## Usage
```shell
<filename> -board_dimensions <h> <w>
<filename> -board_dimensions <h> <w>  -all_solutions
<filename> -board_dimensions <h> <w>  -allow_rotations
<filename> -all_solutions  -allow_rotations
<filename> -tile_size <odd number >= 11>
```

## Improvements/Optimizations
* Check whether a tile can be placed at the edge of a board.
* Change the representation of each edge of tile from a string to a char.
* Do not rotate a tile if all four edge is the same.
* Only place the first tile at the upper-left side of the board, if allow rotations.
* Stop recursion, if the number of roads and cities on the edge of the maps is larger than the number of roads and cities on the edge of the remaining tiles.

## Performance
Complied with `-O3` optimization, run on Intel Core-i7 6700k / Windows subsystem for Linux

Command | # of Solutions | Runtime
--- | :---: | ---: |
`puzzle1.txt -board_dimensions 2 2 -all_solutions` | 1 | 0.013s
`puzzle2.txt -board_dimensions 3 3 -all_solutions` | 1 | 0.014s
`puzzle3.txt -board_dimensions 2 2 -all_solutions -allow_rotations` | 1 | 0.015s
`puzzle4.txt -board_dimensions 4 4 -all_solutions -allow_rotations` | 4 | 0.021s
`puzzle5.txt -board_dimensions 4 3 -all_solutions` | 1 | 0.014s
`puzzle5.txt -board_dimensions 4 3 -all_solutions -allow_rotations` | 1 | 0.012s
`puzzle6.txt -board_dimensions 4 4 -all_solutions` | 4 | 0.016s
`puzzle6.txt -all_solutions -allow_rotations` | 7 | 0.161s
`puzzle7.txt -all_solutions` | 8 | 0.025s
`puzzle7.txt -all_solutions -allow_rotations` | 60 | 1.286s
`puzzle8.txt -all_solutions` | 1 | 0.014s
`puzzle8.txt -all_solutions -allow_rotations` | 23 | 1.048s
`puzzle9.txt -all_solutions` | 9 | 0.035s
`puzzle9.txt -all_solutions -allow_rotations` | 378 | 1m9.055s
