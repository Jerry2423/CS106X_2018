#include "RecursionToTheRescue.h"
#include "map.h"
#include <climits>
#include <iostream>
#include "Disasters.h"
using namespace std;


/* * * * Disaster Planning * * * */

/**
 * Given a transportation grid for a country or region, along with the number of cities where disaster
 * supplies can be stockpiled, returns whether it's possible to stockpile disaster supplies in at most
 * the specified number of cities such that each city either has supplies or is connected to a city that
 * does.
 * <p>
 * This function can assume that every city is a key in the transportation map and that roads are
 * bidirectional: if there's a road from City A to City B, then there's a road from City B back to
 * City A as well.
 *
 * @param roadNetwork The underlying transportation network.
 * @param numCities   How many cities you can afford to put supplies in.
 * @param locations   An outparameter filled in with which cities to choose if a solution exists.
 * @return Whether a solution exists.
 */
bool canBeMadeDisasterReady(const Map<string, Set<string>>& roadNetwork, int numCities, Set<string>& locations) {
    // function to check if all cities are either covered or adjacent to a covered city
    function<bool(Set<string>&)> isDisasterReady = [&](Set<string>& cities) {
        for (const auto& city : roadNetwork) {
            bool isCovered = cities.contains(city);
            if (!isCovered) {
                for (const string& neighbor : roadNetwork[city]) {
                    if (cities.contains(neighbor)) {
                        isCovered = true;
                        break;
                    }
                }
            }
            if (!isCovered) return false;
        }
        return true;
    };

    // base case, if all cities are covered, return true
    if (isDisasterReady(locations)) return true;

    // if we have reached the maximum number of cities
    // that can be made disaster ready, return false
    if (locations.size() >= numCities) return false;

    // try all unvisited cities
    for (const auto& city : roadNetwork) {
        if (!locations.contains(city)) {
            locations.add(city);
            if (canBeMadeDisasterReady(roadNetwork, numCities, locations)) return true;
            locations.remove(city);
        }
    }
    return false;
}


