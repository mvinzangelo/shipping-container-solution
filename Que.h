#ifndef __Que__
#define __Que__

#include <vector>
#include <list>
#include <queue>
#include "Node.h"

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