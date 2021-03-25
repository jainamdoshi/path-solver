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
    delete goalNode;
}

void PathSolver::forwardSearch(Env env) {
    // TODO 
    findSandG(env);

    openList->addElement(startNode);
    Node* currNode = nullptr;

    currNode = getNodeWithSmallestDistance();
    while (currNode->getRow() != goalNode->getRow() || currNode->getCol() != goalNode->getCol()) {

        // std::cout << currNode->getRow() << currNode->getCol() << std::endl;

        // NodeList* nextNodeList = new NodeList();
        getNextNodes(env, currNode);
        nodesExplored->addElement(currNode);

        currNode = getNodeWithSmallestDistance();
    }

    goalNode->setDistanceTraveled(currNode->getDistanceTraveled());
    nodesExplored->addElement(goalNode);

    for (int i = 0; i < nodesExplored->getLength(); i++) {
        std::cout << nodesExplored->getNode(i)->getRow() << " " << nodesExplored->getNode(i)->getCol() << " " << nodesExplored->getNode(i)->getDistanceTraveled() << std::endl;
    }


    // std::cout << startNode->getRow() << std::endl;
    // std::cout << goalNode->getRow() << std::endl;

}

NodeList* PathSolver::getNodesExplored() {
    return new NodeList(*nodesExplored);
}

NodeList* PathSolver::getPath(Env env) {
    // TODO
    return nullptr;
}

void PathSolver::findSandG(Env env) {
    for (int row = ROW_START; row < ENV_DIM && (!startNode || !goalNode); row++) {
        for (int col = COL_START; col < ENV_DIM && (!startNode || !goalNode); col++) {
            if (env[row][col] == SYMBOL_START) {
                startNode = new Node(row, col, 0);
            }
            else if (env[row][col] == SYMBOL_GOAL) {
                goalNode = new Node(row, col, 0);
            }
        }
    }
}

Node* PathSolver::getNodeWithSmallestDistance() {

    Node* node = nullptr;

    for (int index = 0; index < openList->getLength(); index++) {
        Node* currNode = openList->getNode(index);
        if (!isNodeInList(nodesExplored, currNode) && (!node ||
            currNode->getEstimatedDist2Goal(goalNode) <
            node->getEstimatedDist2Goal(goalNode))) {


            node = currNode;
        }
    }

    return node;
}

bool PathSolver::isNodeInList(NodeList* list, Node* targetNode) {
    bool result = false;

    for (int index = 0; index < list->getLength() && !result; index++) {
        Node* node = list->getNode(index);
        if (node->getCol() == targetNode->getCol() &&
            node->getRow() == targetNode->getRow()) {
            result = true;
        }
    }

    return result;
}

void PathSolver::getNextNodes(Env env, Node* currNode) {

    int row = currNode->getRow();
    int col = currNode->getCol();

    int newDist = currNode->getDistanceTraveled() + 1;

    if (env[row][col - 1] != SYMBOL_WALL) {
        Node* newNode = new Node(row, col - 1, newDist);
        checkAndAdd(newNode);
    }
    if (env[row - 1][col] != SYMBOL_WALL) {
        Node* newNode = new Node(row - 1, col, newDist);
        checkAndAdd(newNode);
    }
    if (env[row][col + 1] != SYMBOL_WALL) {
        Node* newNode = new Node(row, col + 1, newDist);
        checkAndAdd(newNode);
    }
    if (env[row + 1][col] != SYMBOL_WALL) {
        Node* newNode = new Node(row + 1, col, newDist);
        checkAndAdd(newNode);
    }

}

void PathSolver::checkAndAdd(Node* newNode) {
    if (!isNodeInList(nodesExplored, newNode)) {
        openList->addElement(newNode);
    }
    delete newNode;
}

//-----------------------------