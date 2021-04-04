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
    for (int index = 0; index < other.getLength(); index++) {
        Node* oldNode = other.getNode(index);
        nodes[index] = new Node(*oldNode);
    }
}

int NodeList::getLength() {
    return length;
}

void NodeList::addElement(Node* newPos) {
    nodes[length] = new Node(*newPos);
    length++;
}

Node* NodeList::getNode(int i) {
    return nodes[i];
}