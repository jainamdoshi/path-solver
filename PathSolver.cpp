#include "PathSolver.h" 
#include <iostream>

PathSolver::PathSolver() {
    // TODO
    // nodesExplored = nullptr;
    // startNode = nullptr;
    // goalNode = nullptr;
    // openList = new NodeList();
}

PathSolver::~PathSolver() {
    // TODOz
    delete nodesExplored;
    // delete openList;
    delete startNode;
    delete goalNode;
}

bool PathSolver::isSameNodes(Node* node, Node* otherNode) {
    return node->getRow() == otherNode->getRow() &&
        node->getCol() == otherNode->getCol();
}

void PathSolver::forwardSearch(Env env) {
    // TODO

    openList = new NodeList(4 * envRows * envCols);
    nodesExplored = new NodeList(4 * envRows * envCols);

    startNode = nullptr;
    goalNode = nullptr;

    findSandG(env);


    openList->addElement(startNode);
    Node* currNode = nullptr;

    currNode = getNodeWithSmallestDistance();
    while (!isSameNodes(currNode, goalNode)) {

        getNextNodes(env, currNode);
        nodesExplored->addElement(currNode);

        currNode = getNodeWithSmallestDistance();
    }

    goalNode->setDistanceTraveled(currNode->getDistanceTraveled());
    nodesExplored->addElement(goalNode);

    delete openList;

}

NodeList* PathSolver::getNodesExplored() {
    return new NodeList(*nodesExplored);
}

NodeList* PathSolver::getPath(Env env) {
    NodeList* shortPathNodes = new NodeList(4 * envRows * envCols);

    Node* currNode = nodesExplored->getNode(nodesExplored->getLength() - 1);
    shortPathNodes->addElement(currNode);

    while (!isSameNodes(currNode, startNode)) {
        bool found = false;
        for (int index = nodesExplored->getLength() - shortPathNodes->getLength(); index >= 0 && !found; index--) {
            Node* node = nodesExplored->getNode(index);
            if (currNode->getDistanceTraveled() - node->getDistanceTraveled() == 1 && currNode->getManhattanDis(node->getRow(), node->getCol()) == 1) {
                shortPathNodes->addElement(node);
                currNode = node;
                found = true;
            }
        }
    }

    NodeList* result = new NodeList(4 * envRows * envCols);

    for (int index = shortPathNodes->getLength() - 1; index >= 0; index--) {
        result->addElement(shortPathNodes->getNode(index));
    }
    delete shortPathNodes;

    return result;
}

void PathSolver::setEnvDim(int rows, int cols) {
    envRows = rows;
    envCols = cols;
}

void PathSolver::findSandG(Env env) {
    for (int row = ROW_START; row < envRows && (!startNode || !goalNode); row++) {
        for (int col = COL_START; col < envCols && (!startNode || !goalNode); col++) {
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