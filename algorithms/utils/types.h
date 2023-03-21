#ifndef TYPES_H
#define TYPES_H

#include <vector>

struct Result
{
  bool isSolutionFound;
  bool isInfeasible;
  bool isOptimal;
  int objectiveValue;
  std::vector<int> variablesResult;
  double gap;
};

struct BranchingConstraint
{
  std::vector<int> referenceSolution;
  bool isLeft;
  int rhs;
};

struct Edge
{
  int id;
  int from;
  int to;
  long weight;
  const bool operator<(const Edge &a) const
  {
    return weight < a.weight;
  }
};

struct Graph
{
  std::vector<Edge> incidenceMatrix;

  std::vector<std::vector<Edge>> ingoingEdges;
  std::vector<std::vector<Edge>> outgoingEdges;
};

#endif