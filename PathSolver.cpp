#include "PathSolver.h" 
#include <iostream>

PathSolver::PathSolver() {
}

PathSolver::PathSolver(int envRows, int envCols) {
    this->envRows = envRows;
    this->envCols = envCols;
    maxListSize = 4 * envRows * envCols;

    // Initializing openList and nodesExplored
    openList = new NodeList(maxListSize);
    nodesExplored = new NodeList(maxListSize);
}

PathSolver::~PathSolver() {

    // Freeing up all the memory used by this class
    delete openList;
    delete nodesExplored;
    delete startNode;
    delete goalNode;
}

bool PathSolver::isSameNodes(Node* node, Node* otherNode) {

    // Return true if both nodes are equal
    // False otherwise
    return node->getRow() == otherNode->getRow() &&
        node->getCol() == otherNode->getCol();
}

void PathSolver::forwardSearch(Env env) {
    startNode = nullptr;
    goalNode = nullptr;

    findSandG(env);
    openList->addElement(startNode);

    Node* currNode = nullptr;
    currNode = getNodeWithSmallestDistance();

    // Continue explore new nodes until the new node is equal to the goal node
    while (!isSameNodes(currNode, goalNode)) {

        getNextNodes(env, currNode);
        nodesExplored->addElement(currNode);
        currNode = getNodeWithSmallestDistance();
    }
    goalNode->setDistanceTraveled(currNode->getDistanceTraveled());

    // Adding the goal node to the nodesExplored
    nodesExplored->addElement(goalNode);
}

NodeList* PathSolver::getNodesExplored() {
    return new NodeList(*nodesExplored);
}

NodeList* PathSolver::getPath(Env env) {
    NodeList* shortPathNodes = new NodeList(maxListSize);

    Node* currNode = nodesExplored->getNode(nodesExplored->getLength() - 1);
    shortPathNodes->addElement(currNode);

    // Continues until the startNode is not found from the nodesExplored list
    while (!isSameNodes(currNode, startNode)) {
        bool found = false;

        // Iterates over nodesExplored list until the required node is found
        // The requirements for a node to be found are:
            // The distance between node and currNode needs to be 1
            // And the Manhattan distance between these two nodes needs to be 1
        for (int index = nodesExplored->getLength() -
            shortPathNodes->getLength(); index >= 0 && !found; index--) {

            Node* node = nodesExplored->getNode(index);

            // Checks for the above two conditions
            // If true, then add the node to the shortPathList
            if (currNode->getDistanceTraveled() - node->getDistanceTraveled()
                == 1 && currNode->getManhattanDis(node->getRow(),
                    node->getCol()) == 1) {


                shortPathNodes->addElement(node);
                currNode = node;
                found = true;
            }
        }
    }
    return reverseList(shortPathNodes);
}

NodeList* PathSolver::reverseList(NodeList* list) {
    NodeList* newList = new NodeList(maxListSize);

    // Iterates through all the elements from the list
    for (int index = list->getLength() - 1; index >= 0; index--) {
        newList->addElement(list->getNode(index));
    }

    // Freeing up the memory for the old list
    delete list;
    return newList;
}



void PathSolver::findSandG(Env env) {

    // Iterates over the 2D env to find the start and goal nodes
    for (int row = 0; row < envRows && (!startNode || !goalNode); row++) {
        for (int col = 0; col < envCols && (!startNode || !goalNode); col++) {
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

    // Iterates over the openList
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
    bool found = false;

    // Iterates over the NodeList until the the same node is found
    for (int index = 0; index < list->getLength() && !found; index++) {
        Node* node = list->getNode(index);
        if (node->getCol() == targetNode->getCol() &&
            node->getRow() == targetNode->getRow()) {
            found = true;
        }
    }

    return found;
}

void PathSolver::getNextNodes(Env env, Node* currNode) {

    int row = currNode->getRow();
    int col = currNode->getCol();

    int newDist = currNode->getDistanceTraveled() + 1;


    // Checks in all direction (left, top, right, bottom)
    // If there is no wall, then it adds to the openList
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

    // Adds the node to the openList if the nodes does not 
    // Contain in nodesExplored
    if (!isNodeInList(nodesExplored, newNode)) {
        openList->addElement(newNode);
    }
    delete newNode;
}

//-----------------------------