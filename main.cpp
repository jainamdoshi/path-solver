#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"
// #include "milestone4.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
Env readEnvStdin(Env env, int* currentRow, int* currentCol);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution, int rows, int cols);

Env make_env(const int rows, const int cols);
void delete_env(Env env, int rows, int cols);
Env copyChars(Env oldEnv, Env newEnv, int rows, int cols);
Env readCols(Env env, int* currentRow, int* currentCol);
Env readRows(Env env, int* currentRow, int totalCols);

int main(int argc, char** argv) {
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment 

    int* currentRow = new int(0);
    int* currentCol = new int(0);
    // Env env = make_env(*currentRow, *currentCol);
    Env env = make_env(*currentRow, *currentCol);

    env = readEnvStdin(env, currentRow, currentCol);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2


    PathSolver* pathSolver = new PathSolver();
    pathSolver->setEnvDim(*currentRow, *currentCol);
    pathSolver->forwardSearch(env);


    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env);


    printEnvStdout(env, solution, *currentRow, *currentCol);
    delete pathSolver;
    delete exploredPositions;
    delete solution;
    delete_env(env, *currentRow, *currentCol);
    delete currentRow;
    delete currentCol;

}

Env readEnvStdin(Env env, int* currentRow, int* currentCol) {

    env = readCols(env, currentRow, currentCol);
    env = readRows(env, currentRow, *currentCol);
    return env;
}

Env readRows(Env env, int* currentRow, int totalCols) {
    int currentCol = totalCols;
    char newChar;

    while (!std::cin.eof()) {

        std::cin.get(newChar);

        if (!std::cin.eof() && newChar != '\n') {

            if (currentCol == totalCols) {
                (*currentRow)++;
                currentCol = 0;

                Env newEnv = make_env(*currentRow + 1, totalCols);
                newEnv = copyChars(env, newEnv, *currentRow, totalCols);
                delete_env(env, *currentRow, totalCols);
                env = newEnv;
            }
            env[*currentRow][currentCol] = newChar;
            currentCol++;
        }
    }
    (*currentRow)++;
    return env;
}


Env readCols(Env env, int* currentRow, int* currentCol) {
    bool newLineCharFound = false;
    char newChar;

    while (!newLineCharFound) {

        std::cin.get(newChar);

        if (newChar == '\n') {
            newLineCharFound = true;
        }
        else {

            Env newEnv = make_env(*currentRow + 1, *currentCol + 1);
            newEnv = copyChars(env, newEnv, *currentRow + 1, *currentCol);
            delete_env(env, *currentRow + 1, *currentCol);
            env = newEnv;
            env[*currentRow][*currentCol] = newChar;
            (*currentCol)++;
        }
    }
    return env;
}

Env copyChars(Env oldEnv, Env newEnv, int rows, int cols) {
    // std::cout << "Copy " << rows << " " << cols << std::endl;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            // std::cout << "Envv " << oldEnv[row][col] << std::endl;
            // std::cout << "Innn " << row << " " << col << std::endl;

            newEnv[row][col] = oldEnv[row][col];
        }
    }
    return newEnv;
}

Env make_env(const int rows, const int cols) {
    Env env = nullptr;

    // std::cout << "Make " << rows << " " << cols << std::endl;

    if (rows >= 0 && cols >= 0) {
        env = new char* [rows];
        for (int i = 0; i < rows; i++) {
            env[i] = new char[cols];
        }
    }

    return env;
}

void delete_env(Env env, int rows, int cols) {
    // std::cout << "Delete " << rows << " " << cols << std::endl;

    if (rows >= 0 && cols >= 0) {
        for (int i = 0; i < rows; i++) {
            delete env[i];
        }
        delete[] env;
    }

    return;
}

void printEnvStdout(Env env, NodeList* solution, int rows, int cols) {

    Node* prevNode = solution->getNode(1);
    int prevRow = prevNode->getRow();
    int prevCol = prevNode->getCol();

    for (int index = 2; index < solution->getLength(); index++) {
        Node* currNode = solution->getNode(index);
        int currRow = currNode->getRow();
        int currCol = currNode->getCol();

        if (prevRow == currRow && prevCol - currCol == 1) {
            env[prevRow][prevCol] = '<';
        }
        else if (prevRow == currRow && prevCol - currCol == -1) {
            env[prevRow][prevCol] = '>';
        }
        else if (prevCol == currCol && prevRow - currRow == 1) {
            env[prevRow][prevCol] = '^';
        }
        else {
            env[prevRow][prevCol] = 'V';
        }

        prevRow = currRow;
        prevCol = currCol;
    }


    for (int row = ROW_START; row < rows; row++) {
        for (int col = COL_START; col < cols; col++) {
            std::cout << env[row][col];
        }
        std::cout << std::endl;
    }


}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}