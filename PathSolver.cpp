#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver() {
    // TODO
    nodesExplored = new NodeList();
    openList = new NodeList();
}

PathSolver::~PathSolver() {
    // TODO
    delete nodesExplored;
    delete openList;
}

void PathSolver::forwardSearch(Env env) {
    // TODO 

}

NodeList* PathSolver::getNodesExplored() {
    return new NodeList(*nodesExplored);
}

NodeList* PathSolver::getPath(Env env) {
    // TODO
    return nullptr;
}

//-----------------------------