#include "Stdafx.h"
#include "AcyclicGraph.h"

/**
 * Function : Build
 * Purpose  :
 */
void AcyclicGraph::Build(const std::vector<String>& pDictionary)
{
  BuildFunctionTables(pDictionary);

  BuildTableG();
}

/**
 * Function : Hash
 * Purpose  :
 */
int AcyclicGraph::Hash(const String& pWord)
{
  return (mTableG[f1(pWord)] + mTableG[f2(pWord)]) % mNbOfEdges;
}

namespace
{
  int MyCoolModFunction(int value, int base)
  {
    if (value >= 0)
    {
      return value % base;
    }
    else
    {
      while (value < 0)
      {
        value += base;
      }

      return value;
    }
  }
}
/**
 * Function : BuildTableG
 * Purpose  :
 */
void AcyclicGraph::BuildTableG()
{
  std::queue<int> queue;
  std::unordered_map<int, int> startVertices(mStartVertexOfComponents);
  std::vector<char> visitedEdges(mNbOfEdges, 0); //vector<bool> is bullshit.

  mTableG = std::vector<int>(mNbOfVertex, -1);

  while (!startVertices.empty())
  {
    const int startVertex = startVertices.cbegin()->second; // second - is start vertex.

    queue.push(startVertex);
    mTableG[startVertex] = 0;

    while (!queue.empty())
    {
      const int top = queue.front();
      for (int i = 0; i < mListOfConnectivity[top].size(); ++i)
      {
        Node& currentVertex = mListOfConnectivity[top][i];
        char& isVisited = visitedEdges[currentVertex.mEdgeId];
        if (!isVisited)
        {
          isVisited = 1;
          //mTableG[currentVertex.mVertexId] = (currentVertex.mEdgeId - mTableG[top]) % mNbOfEdges; It is doesn't work with negative numbers.
          mTableG[currentVertex.mVertexId] = MyCoolModFunction(currentVertex.mEdgeId - mTableG[top], mNbOfEdges);
          queue.push(currentVertex.mVertexId);
        }
      }
      queue.pop();
    }

    startVertices.erase(startVertices.cbegin());
  }
}

/**
 * Function : BuildFunctionTables
 * Purpose  :
 */
void AcyclicGraph::BuildFunctionTables(const std::vector<String>& pDictionary)
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

  // Create tables.
  const int nbOfRows = mMinLength;
  const int nbOfColumns = alphabet.size();
  mTable1.resize(nbOfRows);
  mTable2.resize(nbOfRows);

  // Fill tables.
  mTmpDictionary = &pDictionary;

  // init RNG
  std::array<int, std::mt19937::state_size> seeds;
  std::random_device rnd;
  std::generate_n(seeds.data(), seeds.size(), std::ref(rnd));
  std::seed_seq seq(std::begin(seeds), std::end(seeds));
  std::mt19937 gen(seq);

  // get random number
  std::uniform_int_distribution<int> distr(0, mNbOfVertex);

  while (true)
  {
    for (int i = 0; i < nbOfRows; ++i)
    {
      std::set<Char>::iterator it = alphabet.begin();
      for (int j = 0; j < nbOfColumns; ++j, ++it)
      {
        mTable1[i][*it] = distr(gen);
        mTable2[i][*it] = distr(gen);
      }
    }

    //std::cout << std::endl;
    if (IsAcyclic())
    {
      break;
    }
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

  mStartVertexOfComponents.clear();
  mListOfConnectivity.clear();
  mListOfConnectivity.resize(mNbOfVertex);

  for (int i = 0; i < mTmpDictionary->size(); ++i)
  {
    int vertex1 = f1((*mTmpDictionary)[i]);
    int vertex2 = f2((*mTmpDictionary)[i]);

    if (vertex1 == vertex2)
    {
      return false;
    }

    // add edge.
    mListOfConnectivity[vertex1].push_back(Node(vertex2, i));
    mListOfConnectivity[vertex2].push_back(Node(vertex1, i));

    // mark as visited.
    if (visited[vertex1] == 0
     && visited[vertex2] == 0)
    {
      mStartVertexOfComponents[nbOfComponents] = vertex1;
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

        mStartVertexOfComponents.erase(max);
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
