#ifndef TWOLEVELPERFECTHASH_HEADER
#define TWOLEVELPERFECTHASH_HEADER

#include "Stdafx.h"
#include "IntRandom.h"

class TwoLevelPerfectHash
{
public:
  void Build(const std::vector<String>& pDictionary);
  int Hash(const String& pWord);

protected:
  void BuildTablesForHashLevel1(const std::vector<String>& pDictionary);
  void BuildHashTable();
  void BuildTableForHashLevel2(const std::vector<String>& pDictionary);

protected:
  int HashLevel1(const String& pWord);
  int HashLevel2(const String& pWord,
                 const int     pIndex);

protected:
  int mMaxLength;
  int mP;
  int mDictionarySize;
  int mSymbolOffset;

  std::vector<std::vector<int>> mHashTable;
  std::vector<int> mHashLevel1;

  std::vector<int> mRandomTableForLevel1;
  std::vector<int> mNbOfCollision; //!< number of collision on the first level.

  std::vector<std::vector<int>> mRandomTableForLevel2;

  std::vector<std::map<Char, int>> mSymbolsToInt;
};

#endif
