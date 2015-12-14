#include "Stdafx.h"
#include "Utils.h"

using namespace std;

namespace
{
  void NextWord(const String pAlphabet,
                String&      rString)
  {
    const Char lastSymbol = pAlphabet[pAlphabet.length() - 1];
    for (int i = rString.length() - 1; i >= 0; --i)
    {
      if (rString[i] == lastSymbol)
      {
        continue;
      }

      const int nextSymbolIndex = pAlphabet.find(rString[i]) + 1;
      rString[i] = pAlphabet[nextSymbolIndex];

      for (int j = i + 1; j < rString.length(); ++j)
      {
        rString[j] = pAlphabet[0];
      }

      break;
    }
  }
}
/**
 * Function : CreateDictionary
 * Purpose  :
 */
void Utils::CreateDictionary(const int       pNbOfWords,
                             const String&   pAlphabet,
                             vector<String>& rDictionary)
{
  const Char firstSymbol = pAlphabet[0];
  const Char lastSymbol = pAlphabet[pAlphabet.length() - 1];
  const int minLength = 5;

  String word(minLength, firstSymbol);
  for (int i = 0; i < pNbOfWords;)
  {
    String lastWord(word.length(), lastSymbol);
    while (word != lastWord)
    {
      rDictionary.push_back(word);

      ++i;

      if (i >= pNbOfWords)
      {
        break;
      }

      NextWord(pAlphabet, word);
    }

    word = String(word.length() + 1, firstSymbol);
  }
}
