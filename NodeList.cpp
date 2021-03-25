#include "NodeList.h"
#include <iostream>

NodeList::NodeList() {
    // TODO
    length = 0;
}

NodeList::~NodeList() {
    // TODO
    std::cout << length << std::endl;
    for (int index = 0; index < length; index++) {
        std::cout << index << std::endl;
        delete nodes[index];
    }
}

NodeList::NodeList(NodeList& other) {
    // TODO
    for (int index = 0; index < other.getLength(); index++) {
        nodes[index] = other.getNode(index);
    }
}

int NodeList::getLength() {
    return length;
}

void NodeList::addElement(Node* newPos) {
    nodes[length] = new Node(newPos->getRow(),
        newPos->getCol(), newPos->getDistanceTraveled());
    length++;
    delete newPos;
}

Node* NodeList::getNode(int i) {
    return nodes[i];
}