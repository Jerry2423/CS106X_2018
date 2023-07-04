/*
 * CS 106X Pathfinder
 * This file contains implementations of the members of the WorldMaze class.
 * See World.h for declarations and documentation of each member.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Marty Stepp, Keith Schwarz, et al
 * @version 2018/11/16
 * - 18au version
 * @version 2017/11/22
 * - address memory corruption issue with Kruskal's and MST edges
 * @version 2014/11/19
 * - initial version for 14au
 */

#include "WorldMaze.h"
#include "gmath.h"
#include "grid.h"
#include "random.h"
#include "set.h"
#include "PathfinderAlgorithms.h"

const int WorldMaze::MAZE_WALL = 0;
const int WorldMaze::MAZE_FLOOR = 1;

WorldMaze::WorldMaze(GWindow* gwnd, WorldSize size)
        : WorldGrid(gwnd, getRowsCols(size)) {
    // empty
}

double WorldMaze::costFunction(int r1, int c1, int r2, int c2) const {
    // The cost of moving from a location to itself is 0.
    if (r1 == r2 && c1 == c2) {
        return 0.0;
    }

    // Confirm that the locations are adjacent to one another.
    int drow = std::abs(r2 - r1);
    int dcol = std::abs(c2 - c1);
    if (drow > 1 || dcol > 1) {
        error("Non-adjacent locations passed into cost function.");
    }

    // Moving diagonally costs infinitely much.
    if (drow == 1 && dcol == 1) {
        return POSITIVE_INFINITY;
    } else if ((int) worldGrid.get(r1, c1) == MAZE_WALL
               || (int) worldGrid.get(r2, c2) == MAZE_WALL) {
        // See if we're moving to or from a wall.
        return POSITIVE_INFINITY;
    } else {
        // neighboring floor squares have a cost of 1 to travel between them
        return 1.0;
    }
}

int WorldMaze::getRowsCols(WorldSize size) const {
    static const int NUM_ROWS_MAZE[] = {6, 11, 31, 81, 161};
    return NUM_ROWS_MAZE[size];
}

std::string WorldMaze::getType() const {
    return "maze";
}

double WorldMaze::heuristic(int r1, int c1, int r2, int c2) {
    // straight-line "Manhattan" distance
    return std::abs(r2 - r1) + std::abs(c2 - c1);
}
