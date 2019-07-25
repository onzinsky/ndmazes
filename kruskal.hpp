#ifndef KRUSK_H
#define KRUSK_H

#include "graph.hpp"

class Kruskal {

    public:
        void kruskalMST(Graph *g, int n, int d, bool watch, bool stepByStep, int stopTime);
};
#endif
