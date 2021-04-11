#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

#define POSSIBLE_NODES_LENGTH 4

class PathSolver {
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Destructor
    PathSolver();
    ~PathSolver();

    // Execute forward search algorithm
    // To be implemented for Milestone 2
    void forwardSearch(Env env);

    // Get a DEEP COPY of the explored NodeList in forward search
    // To be implemented for Milestone 2
    NodeList* getNodesExplored();

    // Execute backtracking and Get a DEEP COPY of the path the 
    // robot should travel
    // To be implemented for Milestone 3
    NodeList* getPath(Env env);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    // Over load constructor with the params of the env rows and cols
    PathSolver(int envRows, int envCols);

private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // Nodes explored in forward search algorithm
    NodeList* nodesExplored;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

    // Start and Goal Nodes
    Node* startNode;
    Node* goalNode;

    // Environment dims and the max NodeList size 
    int envRows;
    int envCols;
    int maxListSize;

    NodeList* openList;

    // Finds and initializes the start and goal Nodes
    void findSandG(Env env);

    // Finds the best possible node which has the smallest
    // Estimated distance to the goal from the openList
    Node* getNodeWithSmallestDistance();

    // Checks if a node is in the list
    bool isNodeInList(NodeList* list, Node* node);

    // Finds all the possible nodes that the robot can go from the currNode
    // And adds the nodes to the openList
    // Except the nodes which are already in the nodesExplored
    void getNextNodes(Env env, Node* currNode);

    // Adds the node to the openList if it nodes not contain it
    void checkAndAdd(Node* newNode);

    // Checks if two nodes are same or not with their row and col numbers
    bool isSameNodes(Node* node, Node* otherNode);

    // Reverses the list from the last element to the first element
    NodeList* reverseList(NodeList* list);
};




#endif //COSC_ASSIGN_ONE_PATHSOLVER