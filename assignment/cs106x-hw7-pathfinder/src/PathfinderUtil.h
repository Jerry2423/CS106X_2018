/*
 * CS 106X Pathfinder
 * This file declares general helper functions.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Marty Stepp, and Nick Troccoli based on past code by Keith Schwarz et al.
 * @version 2018/11/16
 * - update for 18au
 * @version 2014/11/19
 * - initial version for 14au
 */

#pragma once

#include "basicgraph.h"
#include "vector.h"

/*
 * Checks to make sure that a given path is valid on the provided graph.
 * That is, that all vertices are found in the graph, that they are connected
 * by edges, and that it starts/ends with the expected vertices.
 */
bool verifyPath(const BasicGraph& graph, const Vector<Vertex*>& path, Vertex* start, Vertex* end);
