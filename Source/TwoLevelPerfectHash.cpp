#include "Stdafx.h"
#include "TwoLevelPerfectHash.h"

/**
 * Function : Build
 * Purpose  :
 */
void TwoLevelPerfectHash::Build(const std::vector<String>& pDictionary)
{
  mDictionarySize = pDictionary.size();

  mP = 67;
  mMaxLength = 0;
  for (int i = 0; i < mDictionarySize; ++i)
  {
    mMaxLength = std::max(mMaxLength, static_cast<int> (pDictionary[i].length()));
  }

  mSymbolOffset = std::numeric_limits<int>::max();
  std::set<Char> alphabet;
  for (int i = 0; i < mDictionarySize; ++i)
  {
    for (int j = 0; j < pDictionary[i].length(); ++j)
    {
      alphabet.emplace(pDictionary[i][j]);
    }
  }

  for (auto it = alphabet.cbegin(); it != alphabet.cend(); ++it)
  {
    mSymbolOffset = std::min(mSymbolOffset, static_cast<int> (*it));
  }

  BuildTablesForHashLevel1(pDictionary);

  BuildHashTable();

  BuildTableForHashLevel2(pDictionary);
}

/**
 * Function : Hash
 * Purpose  :
 */
int TwoLevelPerfectHash::Hash(const String& pKey)
{
  int hash;
  const int hashLevel1 = HashLevel1(pKey);

  if (mNbOfCollision[hashLevel1] > 1)
  {
    hash = mHashTable[hashLevel1][HashLevel2(pKey, hashLevel1)] - 1;
  }
  else
  {
    hash = mHashTable[hashLevel1][0] - 1;
  }

  return hash;
}

/**
 * Function : BuildTablesForHashLevel1
 * Purpose  :
 */
void TwoLevelPerfectHash::BuildTablesForHashLevel1(const std::vector<String>& pDictionary)
{
  IntRandom rnd(1, mP);

  mRandomTableForLevel1 = std::vector<int>(mMaxLength);
  for (int i = 0; i < mMaxLength; ++i)
  {
    mRandomTableForLevel1[i] = rnd.Next();
  }

  mNbOfCollision = std::vector<int>(mDictionarySize, 0);

  mHashLevel1 = std::vector<int>(mDictionarySize);
  for (int i = 0; i < mDictionarySize; ++i)
  {
    const int hash = HashLevel1(pDictionary[i]);

    mHashLevel1[i] = hash;

    ++mNbOfCollision[hash];
  }
}

/**
 * Function : BuildHashTable
 * Purpose  :
 */
void TwoLevelPerfectHash::BuildHashTable()
{
  mHashTable.resize(mDictionarySize);
  for (int i = 0; i < mDictionarySize; ++i)
  {
    const int size = (mNbOfCollision[i] <= 3)
      ? (mNbOfCollision[i] + 1) * (mNbOfCollision[i] + 1)
      : (mNbOfCollision[i] * mNbOfCollision[i]); // hack.

    mHashTable[i].resize(size);
  }
}

/**
 * Function : BuildTableForHashLevel2
 * Purpose  :
 */
void TwoLevelPerfectHash::BuildTableForHashLevel2(const std::vector<String>& pDictionary)
{
  mRandomTableForLevel2 = std::vector<std::vector<int>>(mDictionarySize);
  for (int i = 0; i < mDictionarySize; ++i)
  {
    mRandomTableForLevel2[i] = std::vector<int>(mMaxLength, 0);
  }

  std::vector<bool> visited(mDictionarySize, false);
  IntRandom rnd(1, mP);
  for (int i = 0; i < mDictionarySize; ++i)
  {
    if (!visited[i])
    {
      int currentHash = mHashLevel1[i];
      if (mNbOfCollision[currentHash] == 1)
      {
        mHashTable[currentHash][0] = i + 1;
        visited[i] = true;
      }
      else if (mNbOfCollision[currentHash] > 1)
      {
        bool isContinue;
        do
        {
          isContinue = false;

          for (int j = 0; j < mMaxLength; ++j)
          {
            mRandomTableForLevel2[currentHash][j] = rnd.Next();
          }

          for (int j = 0; j < mDictionarySize; ++j)
          {
            if (mHashLevel1[j] == currentHash)
            {
              int hash2 = HashLevel2(pDictionary[j], currentHash);
              if (mHashTable[currentHash][hash2] > 0)
              {
                isContinue = true;

                for (int k = 0; k < mHashTable[currentHash].size(); ++k)
                {
                  mHashTable[currentHash][k] = 0;
                }

                break;
              }
              mHashTable[currentHash][hash2] = j + 1;
              visited[j] = true;
            }
          }
        } while (isContinue);
      }
    }
  }
}

/**
 * Function : HashLevel1
 * Purpose  :
 */
int TwoLevelPerfectHash::HashLevel1(const String& pWord)
{
  int hash = 0;

  std::vector<int> wordToInts(mMaxLength, 0);
  for (int i = 0; i < pWord.size(); ++i)
  {
    wordToInts[i] = static_cast<int> (pWord[i]) - mSymbolOffset;
  }

  for (int i = 0; i < mMaxLength; ++i)
  {
    hash += mRandomTableForLevel1[i] * wordToInts[i];
  }

  return hash % mDictionarySize;
}

/**
 * Function : HashLevel2
 * Purpose  :
 */
int TwoLevelPerfectHash::HashLevel2(const String& pWord,
                                    const int     pIndex)
{
  int hash = 0;

  std::vector<int> wordToInts(mMaxLength, 0);
  for (int i = 0; i < pWord.size(); ++i)
  {
    wordToInts[i] = static_cast<int> (pWord[i]) - mSymbolOffset;
  }

  for (int i = 0; i < mMaxLength; ++i)
  {
    hash += mRandomTableForLevel2[pIndex][i] * wordToInts[i];
  }

  const int t = mHashTable[pIndex].size();

  return hash % t;
}
