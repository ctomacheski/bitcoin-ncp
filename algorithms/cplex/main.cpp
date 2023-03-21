#include <iostream>

#include "cplex.h"
#include "../utils/utils.h"

int main(int argc, char **argv)
{
  int vertexCount;
  int edgeCount;
  std::cin >> vertexCount >> edgeCount;

  Graph graph = parseIncidenceMatrix(vertexCount, edgeCount);
  Result result = nilcatenationCplex(graph, vertexCount, 3600, false);

  std::cout
      << result.objectiveValue << " "
      << result.gap << " "
      << (result.isOptimal ? "1" : "0") << " "
      << (verifySolution(graph.incidenceMatrix, result, vertexCount) ? "1" : "0")
      << std::endl;

  std::cout << std::endl;
}
