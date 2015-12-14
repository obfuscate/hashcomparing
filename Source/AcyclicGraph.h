#ifndef ACYCLICGRAPH_HEADER
#define ACYCLICGRAPH_HEADER

#include "Stdafx.h"

class AcyclicGraph
{
public:
  void Build(const std::vector<String>& pDictionary);

protected:
  void BuildTables(const std::vector<String>& pDictionary);

  int f1(const String& pWord);
  int f2(const String& pWord);

  bool IsAcyclic();

protected:
  const std::vector<String>* mTmpDictionary; //!< Temporary variable.
  std::vector<std::map<Char, int>> mTable1;
  std::vector<std::map<Char, int>> mTable2;

  int mMinLength; //!< Minimum length among all words.
  int mNbOfEdges;
  int mNbOfVertex;
  float mConstC;
};

#endif
