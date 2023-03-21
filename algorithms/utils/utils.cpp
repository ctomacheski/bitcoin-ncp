#include <iostream>
#include "utils.h"

Graph parseIncidenceMatrix(int vertexCount, int edgeCount)
{
  std::vector<Edge> incidenceMatrix(edgeCount);

  std::vector<std::vector<Edge>> ingoingEdges(vertexCount, std::vector<Edge>());
  std::vector<std::vector<Edge>> outgoingEdges(vertexCount, std::vector<Edge>());

  for (int i = 0; i < edgeCount; i++)
  {
    int from, to;
    unsigned long weight;
    std::cin >> from >> to >> weight;

    incidenceMatrix[i].id = i;
    incidenceMatrix[i].from = from;
    incidenceMatrix[i].to = to;
    incidenceMatrix[i].weight = weight;

    ingoingEdges[to].push_back(incidenceMatrix[i]);
    outgoingEdges[from].push_back(incidenceMatrix[i]);
  }

  return {incidenceMatrix, ingoingEdges, outgoingEdges};
}

bool verifySolution(std::vector<Edge> incidenceMatrix, Result result, int nodeCount)
{
  std::vector<unsigned long> graphBalance(nodeCount, 0);

  for (int i = 0; i < result.variablesResult.size(); i++)
  {
    graphBalance[incidenceMatrix[i].from] -= incidenceMatrix[i].weight * result.variablesResult[i];
    graphBalance[incidenceMatrix[i].to] += incidenceMatrix[i].weight * result.variablesResult[i];
  }

  bool isCorrect = true;
  for (int i = 0; i < graphBalance.size(); i++)
  {
    isCorrect &= graphBalance[i] == 0;
    if (graphBalance[i] != 0)
    {
      std::cout << i << "," << graphBalance[i] << std::endl;
    }
  }

  graphBalance = std::vector<unsigned long>();
  return isCorrect;
}
