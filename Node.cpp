#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled) {
    // TODO
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
}

Node::Node(Node& other) {
    this->row = other.row;
    this->col = other.col;
    this->dist_traveled = other.dist_traveled;
}

Node::~Node() {
    // TODO
}

int Node::getRow() {
    return this->row;
}

int Node::getCol() {
    return this->col;
}

int Node::getDistanceTraveled() {
    return this->dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled) {
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal) {
    // std::cout << "This node: " << this->row << " " << this->col << std::endl;
    // std::cout << "Goal node: " << goal->getRow() << " " << goal->getCol() << std::endl;
    return dist_traveled + getManhattanDis(goal->getRow(), goal->getCol());
}

int Node::getManhattanDis(int row, int col) {
    return abs(this->col - col) + abs(this->row - row);
}

//--------------------------------                             