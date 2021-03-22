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
    delete startNode;
    delete endNode;
}

void PathSolver::forwardSearch(Env env) {
    // TODO 
    findSandG(env);


    std::cout << startNode->getRow() << std::endl;
    std::cout << endNode->getRow() << std::endl;

}

NodeList* PathSolver::getNodesExplored() {
    return new NodeList(*nodesExplored);
}

NodeList* PathSolver::getPath(Env env) {
    // TODO
    return nullptr;
}

void PathSolver::findSandG(Env env) {
    for (int row = ROW_START; row < ENV_DIM && (!startNode || !endNode); row++) {
        for (int col = COL_START; col < ENV_DIM && (!startNode || !endNode); col++) {
            if (env[row][col] == SYMBOL_START) {
                startNode = new Node(row, col, 0);
            }
            else if (env[row][col] == SYMBOL_GOAL) {
                endNode = new Node(row, col, 0);
            }
        }
    }
}

//-----------------------------