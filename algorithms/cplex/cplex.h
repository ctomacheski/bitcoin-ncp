#ifndef CPLEX_H
#define CPLEX_H

#include <vector>
#include "../utils/types.h"

Result nilcatenationCplex(
    Graph graph,
    int nodeCount,
    int timeLimit,
    bool useLB);

#endif