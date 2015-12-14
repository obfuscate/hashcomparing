#include "Stdafx.h"
#include "Utils.h"

using namespace std;

int main(int pArgC, char** pArgV)
{
  std::unordered_map<String, String> dictionary;

  const String alphabet = __TEXT("ABCDEFGHIKLMNOPQRSTVXYZ");
  const int nbOfWords = 50;

  Utils::CreateDictionary(nbOfWords, alphabet, dictionary);

  for (const auto& elem : dictionary)
  {

    Cout << elem.first << __TEXT(" => ") << elem.second << endl;
  }
}
