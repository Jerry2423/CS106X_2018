#include "RecursionToTheRescue.h"
#include "map.h"
#include <climits>
#include <iostream>
#include <string>
#include "Disasters.h"
#include "set.h"
#include "vector.h"
#include "map.h"
#include "recursion.h"
using namespace std;

/* * * * Doctors Without Orders * * * */

/**
 * Given a list of doctors and a list of patients, determines whether all the patients can
 * be seen. If so, this function fills in the schedule outparameter with a map from doctors
 * to the set of patients that doctor would see.
 *
 * @param doctors  The list of the doctors available to work.
 * @param patients The list of the patients that need to be seen.
 * @param schedule An outparameter that will be filled in with the schedule, should one exist.
 * @return Whether or not a schedule was found.
 */
bool canAllPatientsBeSeen(const Vector<Doctor>& doctors,
                          const Vector<Patient>& patients,
                          Map<string, Set<string>>& schedule) {
    // [TODO: Delee these lines and implement this function!]
    (void)(doctors, patients, schedule);
    return false;
}

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

bool isCityCovered(string city, const Map<string, Set<string>>& roadNetwork, Set<string>& locations) {
    if (!roadNetwork.containsKey(city))
        return false;
    if (locations.contains(city)) {
        return true;
    } else {
        for (string surrounding : roadNetwork[city]) {
            if (locations.contains(surrounding)) {
                return true;
            }
        }
    }
    return false;
}

bool allCitiesCovered(const Map<string, Set<string>>& roadNetwork, Set<string>& locations) {
    for (string city : roadNetwork.keys()) {
        if (!isCityCovered(city, roadNetwork, locations))
            return false;
    }
    return true;
}

string findUncoveredCity(const Map<string, Set<string>>& roadNetwork, Set<string>& locations) {
    if (allCitiesCovered(roadNetwork, locations))
        return "";
    else {
        for (string city : roadNetwork.keys()) {
            if (!isCityCovered(city, roadNetwork, locations)) {
                return city;
            }
        }
    }
    return "";
}

bool canBeMadeDisasterReady(const Map<string, Set<string>>& roadNetwork,
                            int numCities,
                            Set<string>& locations) {
    // [TODO: Delete these lines and implement this function!]
    (void)(roadNetwork, numCities, locations);


    if (allCitiesCovered(roadNetwork, locations)) {
        return true;
    } else if (numCities <= 0) {
        return false;
    } else {
        //find a uncover city
        string unCoveredCity = findUncoveredCity(roadNetwork, locations);
        //cover the uncovered city:
            //1. choose city itself
        //animation
        setStockpileInCity(unCoveredCity, true);

        locations.add(unCoveredCity);
        bool result = canBeMadeDisasterReady(roadNetwork, numCities-1, locations);
        if (result)
            return true;
            //2. choose cities around it
        setStockpileInCity(unCoveredCity, false);

        locations.remove(unCoveredCity);
        for (string surrounding : roadNetwork[unCoveredCity]) {

            setStockpileInCity(surrounding, true);

            locations.add(surrounding);
            result = canBeMadeDisasterReady(roadNetwork, numCities-1, locations);
            if (result)
                return true;
            locations.remove(surrounding);

            setStockpileInCity(surrounding, false);
        }
        //undo the choice.

    }

    return false;
}

/* * * * DNA Detective * * * */

/**
 * Given two DNA strands and a maximum edit distance, returns whether those two strands are
 * within that edit distance of one another.
 *
 * @param one The first DNA strand.
 * @param two The second DNA strand.
 * @param maxDistance The maximum distance between them.
 * @return Whether the two strands are within that edit distance of one another.
 */

int editDistance(string& w1, const string w2, int pos) {
    //base case
    if (pos == w1.size() && pos == w2.size()) {
        return 0;
    } else if (pos == w1.size() && pos < w2.size()) {
        w1.push_back(w2[pos]);
        int times = 1 + editDistance(w1, w2, pos+1);
        w1.pop_back();
        return times;
    } else if (pos == w2.size() && pos < w1.size()) {
        char ch = w1[pos];
        w1.erase(w1.begin()+pos);
        int times = 1+ editDistance(w1, w2, pos);
        w1.insert(w1.begin()+pos, ch);
        return times;
    } else {
        int ans;
        if (w1[pos] == w2[pos]) {
            ans = editDistance(w1, w2, pos+1);
        } else {     
            //insert: pos+1
            //choose explore unchoose
            w1.insert(w1.begin()+pos, w2[pos]);
            ans = 1+editDistance(w1, w2, pos+1);
            w1.erase(w1.begin()+pos);
            //del
            char ch = w1[pos];
            w1.erase(w1.begin()+pos);
            ans = min(ans, 1+editDistance(w1, w2, pos));
            w1.insert(w1.begin()+pos, ch);
            //replace
            w1[pos] = w2[pos];
            ans = min(ans, 1+editDistance(w1, w2, pos+1));
            w1[pos] = ch;
        }
        return ans;
    }
    //case one: pos = w1.s && i < w2.s: append only

    //case two: pos = w2.s && pos < w1.s del only

    //normal case pos < w1.s && i < s2.s
}

bool approximatelyMatch(const string& one, const string& two, int maxDistance) {
    // [TODO: Delete these lines and implement this function!]
    string w1 = one;
    int ans = editDistance(w1, two, 0);
    cout << ans << endl;
    return ans <= maxDistance;
}

/* * * * Winning the Election * * * */

/**
 * Given a list of the states in the election, including their popular and electoral vote
 * totals, and the number of electoral votes needed, as well as the index of the lowest-indexed
 * state to consider, returns information about how few popular votes you'd need in order to
 * win that at least that many electoral votes.
 *
 * @param electoralVotesNeeded the minimum number of electoral votes needed
 * @param states All the states in the election (plus DC, if appropriate)
 * @param minStateIndex the lowest index in the states Vector that should be considered
 */

int countElectoralVotes(const Vector<State>& states) {
    int count = 0;
    for (State s : states)
        count += s.electoralVotes;
    return count;
}

MinInfo minPopularVoteToGetAtLeast(int electoralVotesNeeded, const Vector<State>& states, int minStateIndex, int& count, Map<Vector<int>, MinInfo>& catche) {
    // [TODO: Delete these lines and implement this function!]
    (void)(electoralVotesNeeded);
    (void)(states);
    (void)(minStateIndex);
    count += 1;
    Vector<int> key = {electoralVotesNeeded, minStateIndex};

    if (catche.containsKey(key)) {
        return catche[key];
    } else if (electoralVotesNeeded <= 0) {
        return { 0, {} }; //if we have to stop at this step, we return 0.
    } else if (countElectoralVotes(states.subList(minStateIndex, states.size() - minStateIndex)) < electoralVotesNeeded || minStateIndex >= states.size()) {
        MinInfo failDetail;
        failDetail.popularVotesNeeded = INT_MAX;
        failDetail.statesUsed = states;
        return failDetail;
    } else {
        State candidateState = states[minStateIndex];
        //MinInfo choose;
        MinInfo choose = minPopularVoteToGetAtLeast(electoralVotesNeeded-candidateState.electoralVotes, states, minStateIndex+1, count, catche);
        int newPopVotes = candidateState.popularVotes / 2 + 1;
        if (choose.popularVotesNeeded <= INT_MAX - newPopVotes) {
            choose.popularVotesNeeded += newPopVotes; //add my answer/choice at this step to the rest of the step.
            choose.statesUsed.add(candidateState);
        }
        //exclude
        MinInfo exclude = minPopularVoteToGetAtLeast(electoralVotesNeeded, states, minStateIndex+1, count, catche);
        if (exclude.popularVotesNeeded < choose.popularVotesNeeded) {
            catche[key] = exclude;
            return exclude;
        } else {
            catche[key] = choose;
            return choose;
        }
    }
}

/**
 * Given a list of all the states in an election, including their popular and electoral vote
 * totals, returns information about how few popular votes you'd need to win in order to win
 * the presidency.
 *
 * @param states All the states in the election (plus DC, if appropriate)
 * @return Information about how few votes you'd need to win the election.
 */



MinInfo minPopularVoteToWin(const Vector<State>& states) {
    // [TODO: Delete these lines and implement this function!]
    (void)(states);
    int electoralVotesNeeded = countElectoralVotes(states) / 2 + 1;
    //cout << electoralVotesNeeded << endl;
    //cout << states << endl;
    int count = 0;
    Map<Vector<int>, MinInfo> catche;
    MinInfo ans = minPopularVoteToGetAtLeast(electoralVotesNeeded, states, 0, count, catche);
    cout << "total call times = " << count << endl;
    return ans;
}

