#include "NodeList.h"
#include <iostream>

NodeList::NodeList() {
    length = 0;
}

NodeList::~NodeList() {

    // Freeing up the memory of all the nodes from the list
    for (int index = 0; index < length; index++) {
        delete nodes[index];
    }

    // Freeing up the memory of the list itself
    delete[] nodes;
}

NodeList::NodeList(NodeList& other) {
    nodes = new Node * [other.getEnvDim()];

    // Deep coping all the nodes from the other list to the new list (this)
    for (int index = 0; index < other.getLength(); index++) {
        Node* oldNode = other.getNode(index);
        nodes[index] = new Node(*oldNode);
    }
    length = other.getLength();
}

NodeList::NodeList(int length) {
    nodes = new Node * [length];
    envDim = length;
    this->length = 0;
}

int NodeList::getEnvDim() {
    return envDim;
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