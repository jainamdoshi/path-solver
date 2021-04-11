/*
My approach to implement this assignment

    Milestone 2 was quite straight forward (no pun intended) as the pseudocode
    was given to us. My approach was to complete each step of the pseudocode
    and test it using some print statements. I only moved to the next step
    if the previous step worked correct with all the test cases I have.
    However, I found a flaw in the pseudocode given in the specification
    In line 10 of the pseudocode, it states to add q to openList only if it
    is not already in it (in openList). With this logic, there some test cases
    which does not give a shortest path. Instead I add q to openList only if
    it is not in closeList. Changing this does give me a shortest path.

    With regards to Milestone 3, I had issue to create a pseudocode for
    backtracking algorithm. My first pseudocode had many flaws and
    I had to re-think my logic to find a correct login. Once I had
    right pseudocode, I approach to implement this was the same as
    Milestone.

    Milestone 4 was big step from Milestone 3 and 2. For me, the hardest
    thing was to read the maze into the environment. The way I implemented
    Milestone 4 produces a lot of memory leaks and errors. Majority of my time
    for this Milestone was to fix all the memory errors. Moreover, I had to
    change some parts of Mileston 3, so it can adapt with the changes of
    Nodelist from Milestone 4.
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
Env readEnvStdin(Env env, int* currentRow, int* currentCol);

// Read in the Environment
// First it will read and record the columns
// Then it reads in rows with the given columns
void printEnvStdout(Env env, NodeList* solution, int rows, int cols);

// Make a 2D array of the environment with given rows and cols
Env make_env(const int rows, const int cols);

// Delete a 2D array of environment with given rows and cols
void delete_env(Env env, int rows, int cols);

// Copy characters from the oldEnv to the newEnv with given rows and cols
Env copyChars(Env oldEnv, Env newEnv, int rows, int cols);

// Reads all the cols from the first rows
Env readCols(Env env, int* currentRow, int* currentCol);

// Reads in all the rows of the environment
Env readRows(Env env, int* currentRow, int totalCols);

// Returns an apporiate arrow
char getArrow(int prevRow, int prevCol, int currRow, int currCol);

// Replaces the open space with the arrows
Env setArrows(Env env, NodeList* solution);



int main(int argc, char** argv) {

    // Load Environment 
    int* currentRow = new int(0);
    int* currentCol = new int(0);
    // Env env = make_env(*currentRow, *currentCol);
    Env env = nullptr;
    env = readEnvStdin(env, currentRow, currentCol);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver* pathSolver = new PathSolver(*currentRow, *currentCol);
    pathSolver->forwardSearch(env);


    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env);

    std::cout << solution->getLength() << std::endl;

    // Printing out the path into the 
    printEnvStdout(env, solution, *currentRow, *currentCol);

    // Freeing up all the memory from the heap
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

    // Read until the EOF is found
    while (!std::cin.eof()) {

        std::cin.get(newChar);
        if (!std::cin.eof() && newChar != '\n') {

            // Checks if all the cols in one row is been read
            // If true, then the newChar is from the next row
            // If false, then the newChar is still in the same row
            if (currentCol == totalCols) {

                (*currentRow)++;
                currentCol = 0;

                // Make a 2D of the env with the current rows and cols
                // Copy the oldEnv with the newEnv
                // Then delete the oldEnv
                Env newEnv = make_env(*currentRow + 1, totalCols);
                newEnv = copyChars(env, newEnv, *currentRow, totalCols);
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

    // Read characters until a new line character is found
    while (!newLineCharFound) {

        std::cin.get(newChar);


        // Check if the newChar is a new line character
        // If true, then set the flag as true
        // If false, then the newChar in the 2D array
        if (newChar == '\n') {
            newLineCharFound = true;
        }
        else {

            // Make a 2D of the env with the current rows and cols
            // Copy the oldEnv with the newEnv
            // Then delete the oldEnv 
            Env newEnv = make_env(*currentRow + 1, *currentCol + 1);
            if (env) {
                newEnv = copyChars(env, newEnv,
                    *currentRow + 1, *currentCol);
            }
            env = newEnv;
            env[*currentRow][*currentCol] = newChar;
            (*currentCol)++;
        }
    }
    return env;
}

Env copyChars(Env oldEnv, Env newEnv, int rows, int cols) {

    // Iteration through all the elements in a 2D array
    // And copy each element from old to new Env
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            newEnv[row][col] = oldEnv[row][col];
        }
    }

    // Freeing up the memory of the old env
    delete_env(oldEnv, rows, cols);
    return newEnv;
}

Env make_env(const int rows, const int cols) {
    Env env = nullptr;

    // Initializing rows
    if (rows >= 0 && cols >= 0) {
        env = new char* [rows];

        // Initializing cols for every row
        for (int row = 0; row < rows; row++) {
            env[row] = new char[cols];
        }
    }
    return env;
}

void delete_env(Env env, int rows, int cols) {
    if (rows >= 0 && cols >= 0) {

        // Freeing up the all the column for every row
        for (int row = 0; row < rows; row++) {
            delete[] env[row];
        }

        // Freeing up all the rows
        delete[] env;
    }

}

void printEnvStdout(Env env, NodeList* solution, int rows, int cols) {

    env = setArrows(env, solution);

    // Prints out the Environment
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            std::cout << env[row][col];
        }
        if (row + 1 != rows) {
            std::cout << std::endl;
        }
    }
}

Env setArrows(Env env, NodeList* solution) {
    Node* prevNode = solution->getNode(1);
    int prevRow = prevNode->getRow();
    int prevCol = prevNode->getCol();

    // Iterates through all the nodes from the solution
    // And compares with the previous node to get an apporiate arrow
    for (int index = 2; index < solution->getLength(); index++) {
        Node* currNode = solution->getNode(index);
        int currRow = currNode->getRow();
        int currCol = currNode->getCol();

        env[prevRow][prevCol] =
            getArrow(prevRow, prevCol, currRow, currCol);

        prevRow = currRow;
        prevCol = currCol;
    }
    return env;
}

char getArrow(int prevRow, int prevCol, int currRow, int currCol) {

    // Default arrow to be down
    char arrow = DOWN_ARROW;

    // Checks the differces of the positions (row and col)
    // And returns the apporiate arrow
    if (prevRow == currRow && prevCol - currCol == 1) {
        arrow = LEFT_ARROW;
    }
    else if (prevRow == currRow && prevCol - currCol == -1) {
        arrow = RIGHT_ARROW;
    }
    else if (prevCol == currCol && prevRow - currRow == 1) {
        arrow = UP_ARROW;
    }
    return arrow;
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
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO"
        << std::endl;
}