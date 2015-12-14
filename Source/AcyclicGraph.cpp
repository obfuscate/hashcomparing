#include "Stdafx.h"
#include "AcyclicGraph.h"

/**
 * Function : Build
 * Purpose  :
 */
void AcyclicGraph::Build(const std::vector<String>& pDictionary)
{
  BuildTables(pDictionary);
}

/**
 * Function : BuildTables
 * Purpose  :
 */
void AcyclicGraph::BuildTables(const std::vector<String>& pDictionary)
{
  // Get minimum length among all words.
  mMinLength = std::numeric_limits<int>::max();
  for (int i = 0; i < pDictionary.size(); ++i)
  {
    mMinLength = std::min(mMinLength, static_cast<int> (pDictionary[i].size()));
  }

  // Get actual alphabet.
  std::set<Char> alphabet;
  for (int i = 0; i < pDictionary.size(); ++i)
  {
    for (int j = 0; j < mMinLength; ++j)
    {
      alphabet.insert(pDictionary[i][j]);
    }
  }

  // Setup internal variables.
  mNbOfEdges = pDictionary.size();
  mConstC = 3.0f; // rewrite.
  mNbOfVertex = static_cast<int> (mConstC * mNbOfEdges);

  std::srand(time(NULL));
  // Create tables.
  const int nbOfRows = mMinLength;
  const int nbOfColumns = alphabet.size();
  mTable1.resize(nbOfRows);
  mTable2.resize(nbOfRows);

  // Fill tables.
  mTmpDictionary = &pDictionary;
  std::default_random_engine rnd(time(NULL));
  std::uniform_int_distribution<int> distr(0, mNbOfVertex);

  int count = 1;
  while (true)
  {
    for (int i = 0; i < nbOfRows; ++i)
    {
      std::set<Char>::iterator it = alphabet.begin();
      for (int j = 0; j < nbOfColumns; ++j, ++it)
      {
        mTable1[i][*it] = distr(rnd);
        mTable2[i][*it] = distr(rnd);
      }
    }

    if (IsAcyclic())
    {
      break;
    }
    ++count;
  }
  mTmpDictionary = NULL;
}

/**
 * Function : IsAcyclic
 * Purpose  :
 */
bool AcyclicGraph::IsAcyclic()
{
  int nbOfComponents = 1;
  std::vector<int> visited(mNbOfVertex, 0);
  std::vector<std::vector<int>> listOfConnectivity(mNbOfVertex);

  for (int i = 0; i < mTmpDictionary->size(); ++i)
  {
    int vertex1 = f1((*mTmpDictionary)[i]);
    int vertex2 = f2((*mTmpDictionary)[i]);
    
    if (vertex1 == vertex2)
    {
      return false;
    }

    // add edge.
    listOfConnectivity[vertex1].push_back(vertex2);
    listOfConnectivity[vertex2].push_back(vertex1);

    // mark as visited.
    if (visited[vertex1] == 0
     && visited[vertex2] == 0)
    {
      visited[vertex1] = nbOfComponents;
      visited[vertex2] = nbOfComponents;
      ++nbOfComponents;
    }
    else if (visited[vertex1] != 0
          && visited[vertex2] == 0)
    {
      visited[vertex2] = visited[vertex1];
    }
    else if (visited[vertex2] != 0
          && visited[vertex1] == 0)
    {
      visited[vertex1] = visited[vertex2];
    }
    else
    {
      if (visited[vertex1] == visited[vertex2])
      {
        return false;
      }
      else
      {
        const int min = std::min(visited[vertex1], visited[vertex2]);
        const int max = std::max(visited[vertex1], visited[vertex2]);
        for (int i = 0; i < visited.size(); ++i)
        {
          if (visited[i] == max)
          {
            visited[i] = min;
          }
        }
      }
    }
  }

  return true;
}

/**
 * Function : f1
 * Purpose  :
 */
int AcyclicGraph::f1(const String& pWord)
{
  int result = 0;

  for (int i = 0; i < mMinLength; ++i)
  {
    result += mTable1[i][pWord[i]];
  }

  return result % mNbOfVertex;
}

/**
 * Function : f2
 * Purpose  :
 */
int AcyclicGraph::f2(const String& pWord)
{
  int result = 0;

  for (int i = 0; i < mMinLength; ++i)
  {
    result += mTable2[i][pWord[i]];
  }

  return result % mNbOfVertex;
}
