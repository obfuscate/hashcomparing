#ifndef ACYCLICGRAPH_HEADER
#define ACYCLICGRAPH_HEADER

#include "Stdafx.h"

class AcyclicGraph
{
public:
  void Build(const std::vector<String>& pDictionary);
  int Hash(const String& pWord) const;

protected:
  //! Builds tables T1 and T2.
  void BuildFunctionTables(const std::vector<String>& pDictionary);
  void BuildTableG();

  int f1(const String& pWord) const;
  int f2(const String& pWord) const;

  bool IsAcyclic();

protected:
  struct Node
  {
    Node(const int pVertexId,
         const int pEdgeId)
    : mVertexId(pVertexId),
      mEdgeId(pEdgeId)
    {
      //
    }

    int mVertexId;
    int mEdgeId;
  };

protected:
  const std::vector<String>* mTmpDictionary; //!< Temporary variable.
  std::vector<std::map<Char, int>> mTable1;
  std::vector<std::map<Char, int>> mTable2;
  std::vector<int> mTableG; //!< nice prefect name (happy debug ^^).

  std::vector<std::vector<Node>> mListOfConnectivity; //!< Nice perfect code (is very optimized :D).
  std::unordered_map<int, int> mStartVertexOfComponents; //!< key - component id, value - vertex id.

  int mMinLength; //!< Minimum length among all words.
  int mNbOfEdges;
  int mNbOfVertex;
  float mConstC;
};

#endif
