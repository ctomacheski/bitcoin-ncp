#include <ilcplex/ilocplex.h>
#include <vector>
#include <set>

#include "cplex.h"

bool essentiallyEqual(float a, float b, float epsilon)
{
  return fabs(a - b) <= ((fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

ILOMIPINFOCALLBACK3(MIPInfoCallback, bool, isMinimization, IloCplex, cplex, IloNum, startTime)
{
  if (!hasIncumbent())
    return;

  static double prevBest = -1e+100;
  const IloNum currentBest = getIncumbentObjValue();

  static IloNum internalStartTime = 1e+100;
  if (internalStartTime > startTime)
  {
    internalStartTime = startTime;
  }

  if (currentBest > prevBest)
  {
    prevBest = currentBest;
    std::cout << (cplex.getCplexTime() - internalStartTime) << " " << currentBest << std::endl;
  }
};

Result nilcatenationCplex(
    Graph graph,
    int nodeCount,
    int timeLimit,
    bool useLB)
{
  std::vector<Edge> incidenceMatrix = graph.incidenceMatrix;

  IloEnv env;

  try
  {
    IloModel model(env);

    IloIntVarArray vars(env);
    IloExpr objective(env);
    for (int i = 0; i < incidenceMatrix.size(); i++)
    {
      vars.add(IloIntVar(env, 0, 1));
      objective += vars[i];
    }

    model.add(objective > 0);
    model.add(IloMaximize(env, objective));

    IloExprArray conditionNilc(env);
    for (int i = 0; i < nodeCount; i++)
    {
      conditionNilc.add(IloExpr(env));
    }

    for (int i = 0; i < incidenceMatrix.size(); i++)
    {
      Edge e = incidenceMatrix[i];
      conditionNilc[e.from] -= e.weight * vars[i];
      conditionNilc[e.to] += e.weight * vars[i];
    }

    for (int i = 0; i < nodeCount; i++)
    {
      model.add(conditionNilc[i] == 0);
    }

    IloCplex cplex(model);
    const IloNum startTime = cplex.getCplexTime();

    cplex.setOut(env.getNullStream());
    cplex.setParam(IloCplex::TiLim, timeLimit);
    cplex.setParam(IloCplex::Param::RandomSeed, 1);
    cplex.setParam(IloCplex::Param::Parallel, CPX_PARALLEL_DETERMINISTIC);

    if (useLB)
    {
      cplex.setParam(IloCplex::Param::MIP::Strategy::LBHeur, 1);
    }

    cplex.use(MIPInfoCallback(env, false, cplex, startTime));

    if (!cplex.solve())
    {
      return {false};
    }

    bool isInfeasible = cplex.getStatus() == IloAlgorithm::Infeasible;
    if (isInfeasible)
    {
      return {true, isInfeasible};
    }

    IloNumArray values(env);
    cplex.getValues(values, vars);

    int count = 0;
    std::vector<int> resultVariables(incidenceMatrix.size());
    for (long i = 0; i < incidenceMatrix.size(); i++)
    {
      resultVariables[i] = (essentiallyEqual(values[i], 1, 0.001) ? 1 : 0);
      count += resultVariables[i];
    }

    bool isOptimal = cplex.getStatus() == IloAlgorithm::Optimal;

    return {true, isInfeasible, isOptimal, (int)cplex.getObjValue(), resultVariables, (double)cplex.getMIPRelativeGap()};
  }
  catch (IloException &e)
  {
    std::cerr << "Concert exception caught: " << e << std::endl;
  }
  catch (...)
  {
    std::cerr << "Unknown exception caught" << std::endl;
  }

  return {false};

  env.end();
}
