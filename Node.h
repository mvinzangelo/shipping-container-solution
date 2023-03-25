#ifndef __Node__
#define __Node__

#include "manifest/manifest.h"
#include <vector>


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
        bool inBuffer;
        bool inShip;
        int Fx; //
        int Gx;
        Node* parent;
        std::vector<Container*> containersOFF;
        std::vector<Container*> containersON;
        ;

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

#endif