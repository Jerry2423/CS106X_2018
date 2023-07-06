// This is the .cpp file that you will turn in (TODO: replace this comment!)

#include "CS106XCellModel.h"
#include "Expression.h"
#include "ExpressionParser.h"
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
    cache[upper_cell_name] = exp->eval(cache);
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
    setDependency(exp, upper_cell_name);
    cout << cellGraph << endl;
    // TODO: remove the above line and implement this
    notifyObservers(upper_cell_name);
}


void CS106XCellModel::setDependency(const Expression* exp, const string& cell_name) {
    switch (exp->getType()) {
        case IDENTIFIER: {
            if (!cellGraph.containsEdge(toUpperCase(exp->toString()), cell_name)) {
                cellGraph.addEdge(toUpperCase(exp->toString()), cell_name);
            }
            break;
        }
        case RANGE: {
            if (!cellGraph.containsEdge(toUpperCase(static_cast<const RangeExp*>(exp)->getRange().getStartCellName()), cell_name)) {
                cellGraph.addEdge(toUpperCase(static_cast<const RangeExp*>(exp)->getRange().getStartCellName()), cell_name);
            }
            if (!cellGraph.containsEdge(toUpperCase(static_cast<const RangeExp*>(exp)->getRange().getEndCellName()), cell_name)) {
                cellGraph.addEdge(toUpperCase(static_cast<const RangeExp*>(exp)->getRange().getEndCellName()), cell_name);
            }
            break;
        }
        case COMPOUND: {
            setDependency(static_cast<const CompoundExp*>(exp)->getLeft(), cell_name);
            setDependency(static_cast<const CompoundExp*>(exp)->getRight(), cell_name);
            break;
        }
        default:
            break;
    }
}
