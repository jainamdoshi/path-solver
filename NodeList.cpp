#include "NodeList.h"
#include <iostream>

NodeList::NodeList() {
    // TODO
    length = 0;
}

NodeList::~NodeList() {
    // TODO
    for (int index = 0; index < length; index++) {
        delete nodes[index];
    }
}

NodeList::NodeList(NodeList& other) {
    // TODO
}

int NodeList::getLength() {
    // TODO
    return length;
}

void NodeList::addElement(Node* newPos) {
    // TODO
    nodes[length] = new Node(newPos->getRow(), newPos->getCol(), newPos->getDistanceTraveled());
    length++;
}

Node* NodeList::getNode(int i) {
    // TODO
    return nodes[i];
}