// This is the .cpp file that you will turn in (TODO: replace this comment!)

#include "CS106XCellModel.h"
#include "Expression.h"
#include "ExpressionParser.h"
#include "basicgraph.h"
#include "queue.h"
#include "set.h"
#include "strlib.h"

using namespace std;

CS106XCellModel::CS106XCellModel() {
    // TODO: implement this
}

CS106XCellModel::~CS106XCellModel() {
    // TODO: implement this
    clear();
}

const Expression *CS106XCellModel::getExpressionForCell(const string& cellname) const {
    (void)cellname;
    auto temp = toUpperCase(cellname);
    if (!cellGraph.containsVertex(temp) || !cellGraph.getVertex(temp)) {
        return nullptr;
    }
    return cellGraph.getVertex(cellname)->data;
    // TODO: remove the above lines and implement this
}

void CS106XCellModel::clear() {
    // TODO: implement this
    for (auto& i : cellGraph.getVertexSet()) {
        delete i->data;
        i->data = nullptr;
    }
    cellGraph.clear();
}

void CS106XCellModel::load(istream& infile) {
    (void)infile;
    // TODO: remove the above line and implement this
}

void CS106XCellModel::save(ostream& outfile) const {
    (void)outfile;
    // TODO: remove the above line and implement this
}

void CS106XCellModel::setCell(const string& cellname, const string& rawText) {
    (void)cellname;
    (void)rawText;
    string upper_cell_name = toUpperCase(cellname);
    string upper_value = toUpperCase(rawText);
    Expression* exp = ExpressionParser::parseExpression(rawText);
    cout << "exp type is " << exp->getType() << endl;
    if (cellGraph.containsVertex(upper_cell_name)) {
        delete cellGraph.getVertex(upper_cell_name)->data;
        cellGraph.getVertex(upper_cell_name)->data = exp;
    } else {
        cellGraph.addVertex(upper_cell_name);
        cellGraph.getVertex(upper_cell_name)->data = exp;
    }
    // dependency
    // cout << "neighbors" << cellGraph.getNeighbors(upper_cell_name) << endl;
    for (auto& i : cellGraph.getInverseNeighbors(upper_cell_name)) {
        cellGraph.removeEdge(i->name, upper_cell_name);
    }
    cout << "after removal" << cellGraph << endl;
    Set<EdgeV<Expression*>*> newEdges;
    setDependency(exp, upper_cell_name, newEdges);
    if (containLoop(upper_cell_name)) {
        for (const auto& i : newEdges) {
            cellGraph.removeEdge(i);
        }
        throw ErrorException("there is circular in the exp");
    }
    cout << cellGraph << endl;
    // TODO: remove the above line and implement this
    // update values!
    cache[upper_cell_name] = exp->eval(cache);
    auto topVec = topSort();
    cout << "the top sort" << topVec << endl;
    int cell_index = 0;
    for (cell_index = 0; cell_index < topVec.size(); cell_index++) {
        if (topVec[cell_index] == upper_cell_name) {
            break;
        }
    }
    for (int i = cell_index+1; i < topVec.size(); i++) {
        cache[topVec[i]] = cellGraph.getVertex(topVec[i])->data->eval(cache);
        cout << "cell " << upper_cell_name << "value is " << cellGraph.getVertex(topVec[i])->data->getValue() << endl;
        notifyObservers(topVec[i]); // call the viewer to update view
        // update value
    }
    cout << "cache " << cache << endl;
    notifyObservers(upper_cell_name);
}


void CS106XCellModel::setDependency(const Expression* exp, const string& cell_name, Set<EdgeV<Expression*>*>& newEdges) {
    switch (exp->getType()) {
        case IDENTIFIER: {
            if (!cellGraph.containsEdge(toUpperCase(exp->toString()), cell_name)) {
                cellGraph.addEdge(toUpperCase(exp->toString()), cell_name);
                newEdges.add(cellGraph.getEdge(toUpperCase(exp->toString()), cell_name));
            }
            break;
        }
        case RANGE: {
            for (const auto& i : static_cast<const RangeExp*>(exp)->getRange().getAllCellNames()) {
                if (!cellGraph.containsEdge(i, cell_name)) {
                    cellGraph.addEdge(i, cell_name);
                    newEdges.add(cellGraph.getEdge(toUpperCase(i), cell_name));
                }
            }
            break;
        }
        case COMPOUND: {
            setDependency(static_cast<const CompoundExp*>(exp)->getLeft(), cell_name, newEdges);
            setDependency(static_cast<const CompoundExp*>(exp)->getRight(), cell_name, newEdges);
            break;
        }
        default:
            break;
    }
}

Vector<string> CS106XCellModel::topSort() const {
    Vector<string> vec;
    Map<string, int> nodeInbound;
    Queue<string> zeroInbound;
    for (const auto& i : cellGraph.getVertexNames()) {
        nodeInbound[i] = cellGraph.getInverseNeighbors(i).size();
        if (nodeInbound[i] == 0) {
            zeroInbound.add(i);
        }
    }
    while (!zeroInbound.isEmpty()) {
        vec.push_back(zeroInbound.dequeue());
        for (const auto& i : cellGraph.getNeighborNames(vec.back())) {
            nodeInbound[i] -= 1;
            if (nodeInbound[i] == 0) {
                zeroInbound.add(i);
            }
        }
    }
    return vec;
}

bool CS106XCellModel::containLoop(const string& vertex) const {
    Set<string> visited;
    return dfs(cellGraph.getVertex(vertex), cellGraph.getVertex(vertex), visited, true);
}

bool CS106XCellModel::dfs(const VertexV<Expression*>* start, const VertexV<Expression*>* end, Set<string>& visited, bool first) const {
    if (start->name == end->name && !first) {
        return true;
    }
    if (!start) {
        return false;
    }
    if (!first) {
        visited.add(start->name);
    }
    for (const auto& i : start->edges) {
        if (!visited.contains(i->finish->name)) {
            if (dfs(i->finish, end, visited)) {
                return true;
            }
        }
    }
    visited.remove(start->name);
    return false;
}
