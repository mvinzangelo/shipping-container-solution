#ifndef __Node__
#define __Node__

#include "manifest/manifest.h"
//#include "atomicmove.h"
#include <vector>
#include <list>
#include <queue>




class AtomicMove
{
public:
    AtomicMove();
    AtomicMove(Ship* ship, std::string containerToMove, int curr_i, int curr_j, int target_i, int target_j);
    Ship *shipState;
    int timeToMove;
    std::string containerToMove; //name of container
    std::string locationToMove; // cords
    int curr_i; // current location
    int curr_j;
    int target_i; // target location truck = -1, -1
    int target_j;
    bool isOffloaded; // from ship to truck
    bool isOnloaded;  // from truck to ship
};

class orderedPair
{
    public:
        int first;
        int second;
        orderedPair();
        orderedPair(int y, int x);

        void print();
};



class Node
{
    //problem state: 2d array of containers ship?
    public:
        Ship ship;
        orderedPair crain;
        orderedPair pinkBox;
        orderedPair targetLoc;
        orderedPair containerLoc;
        bool inBuffer;
        bool inShip;
        bool inTruck;
        int Fx; //
        int Gx;
        Node* parent;
        std::vector<Container*> containersOFF;
        std::vector<Container*> containersON;
        std::string containerMoved;

        Node();
        Node(Ship initialState);
        Node(Ship state, std::vector<Container*> ON, std::vector<Container*> OFF);
        Node(Node &curNode);
        void print();
        bool GoalTest();
        

        std::vector<int> findTargetColumns();
        std::vector<Container*> findTop(std::vector<int> columns);
        std::vector<orderedPair> findTopFree();
        //void checkTops();
        void offLoad(orderedPair container);
        void moveContainer(orderedPair container);
        void onboard(Container* container);


        //orderedPair findOffboardTarget(std::string target);
        //std::vector<orderedPair> findMatchingContainers();
        //orderedPair findTargetLoc(std::vector<orderedPair> matchingContainers);
        //bool isMoveable(orderedPair container);
        
        int offloadCost(orderedPair container);
};

struct LessThanByFx
{
    bool operator()( Node* lhs, Node* rhs)
        {
            return lhs->Fx > rhs->Fx;
        }
};

class Que
{
    public:
        std::priority_queue<Node*, std::vector<Node*>, LessThanByFx> heap;
        std::vector<Node*> visited;
        std::list<Node*> solutionPath;

        //bool isVisited(Node* newState );
        //void expandNode(Node* currentNode);

        //Que();
        Que(Node*);

        void push(Node* newNode);

        void expand();
};

#endif