#include "NodeList.h"
#include <iostream>

NodeList::NodeList() {
    length = 0;
}

NodeList::~NodeList() {
    // std::cout << "NodeList des: " << this->length << std::endl;
    for (int index = 0; index < length; index++) {
        // std::cout << nodes[index]. << std::endl;
        delete nodes[index];
    }
    delete[] nodes;
}

NodeList::NodeList(NodeList& other) {
    nodes = new Node * [other.getEnvDim()];
    for (int index = 0; index < other.getLength(); index++) {
        Node* oldNode = other.getNode(index);
        nodes[index] = new Node(*oldNode);
    }
    length = other.getLength();
}

NodeList::NodeList(int length) {
    envDim = length;
    nodes = new Node * [length];

    // for (int i = 0; i < length; i++) {
    //     nodes[i] = nullptr;
    // }


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