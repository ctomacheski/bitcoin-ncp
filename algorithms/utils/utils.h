#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "types.h"

Graph parseIncidenceMatrix(int vertexCount, int edgeCount);

bool verifySolution(std::vector<Edge> incidenceMatrix, Result result, int nodeCount);

#endif