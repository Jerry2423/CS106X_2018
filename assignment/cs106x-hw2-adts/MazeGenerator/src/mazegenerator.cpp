// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)
#include "mazetypes.h"
#include "mazegui.h"
#include "random.h"
#include "set.h"
#include "vector.h"
#include <iostream>
using std::cout; using std::endl;
using chamber = Set<Cell>; // chamber can be seen as connected component

bool isConnected(const Set<chamber>& chambers, const Cell& u, const Cell& v) {
    for (const auto& i : chambers) {
        if (i.contains(u) && i.contains(v)) {
            return true;
        }
    }
    return false;
}

chamber findChamber(const Set<chamber>& chambers, const Cell& u) {
    for (const auto& i : chambers) {
        if (i.contains(u)) {
            return i;
        }
    }
    return {};
}

void generateMaze() {
    // TODO: Finish the code!
    Vector<Cell> cells = MazeGUI::getAllCells();
    Vector<Wall> walls = MazeGUI::getAllWalls();
    Set<chamber> chambers;
    HashSet<Wall> wall_set;
    for (const auto& i : cells) {
        chambers.add({i});
    }
    for (const auto& i : walls) {
        wall_set.add({i});
    }
    // cout << chambers << endl;
    while (!walls.isEmpty()) {
        int index = randomInteger(0, walls.size()-1);
        auto temp = walls[index];
        walls.remove(index);
        if (!isConnected(chambers, temp.one, temp.two)) {
            MazeGUI::removeWall(temp);
            auto chamber_1 = findChamber(chambers, temp.one);
            auto chamber_2 = findChamber(chambers, temp.two);
            // merge/connect chamber
            chambers.remove(chamber_1);
            chambers.remove(chamber_2);
            chambers.add(chamber_1+chamber_2);
        }

    }

}
